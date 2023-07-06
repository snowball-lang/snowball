// Content modified from the original: 
// https://github.com/codeplaysoftware/llvm-leg/blob/master/examples/ExceptionDemo/ExceptionDemo.cpp

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <sstream>
#include <unwind.h>

#include "runtime.h"

enum {
    // standard.
    DW_EH_PE_absptr   = 0x00,
    DW_EH_PE_uleb128  = 0x01,
    DW_EH_PE_udata2   = 0x02,
    DW_EH_PE_udata4   = 0x03,
    DW_EH_PE_udata8   = 0x04,
    DW_EH_PE_sleb128  = 0x09,
    DW_EH_PE_sdata2   = 0x0A,
    DW_EH_PE_sdata4   = 0x0B,
    DW_EH_PE_sdata8   = 0x0C,
    DW_EH_PE_pcrel    = 0x10,
    DW_EH_PE_textrel  = 0x20,
    DW_EH_PE_datarel  = 0x30,
    DW_EH_PE_funcrel  = 0x40,
    DW_EH_PE_aligned  = 0x50,
    DW_EH_PE_indirect = 0x80,
    DW_EH_PE_omit     = 0xFF
};

// System C++ ABI unwind types from:
//     http://mentorembedded.github.com/cxx-abi/abi-eh.html (v1.22)

extern "C" {
  struct _Unwind_Context;
  typedef struct _Unwind_Context *_Unwind_Context_t;

  extern uintptr_t _Unwind_GetGR (_Unwind_Context_t c, int i);
  extern void _Unwind_SetGR (_Unwind_Context_t c, int i, uintptr_t n);
  extern void _Unwind_SetIP (_Unwind_Context_t, uintptr_t new_value);
  extern uintptr_t _Unwind_GetIP (_Unwind_Context_t context);
  extern uintptr_t _Unwind_GetRegionStart (_Unwind_Context_t context);

} // extern "C"

// This is the type of the exception object
struct OurExceptionType_t {
  /// type info type
  int type;
};

/**
 * This is the type of the exception object instance
 * @note This is the type of the object instance, not the object itself.
 *       The object instance is a member of the object.
 * @see OurBaseException_t below.
*/
struct SnowballExceptionInstance_t {
  void* _vtable;
  char* message;
};

/// This is our Exception class which relies on a negative offset to calculate
/// pointers to its instances from pointers to its unwindException member.
///
/// Note: The above unwind.h defines struct _Unwind_Exception to be aligned
///       on a double word boundary. This is necessary to match the standard:
///       http://mentorembedded.github.com/cxx-abi/abi-eh.html
struct OurBaseException_t {
  struct OurExceptionType_t type;

  /// @brief Object instance
  void* snowball_object;

  // Note: This is properly aligned in unwind.h
  struct _Unwind_Exception unwindException;
};

// Note: Not needed since we are C++
typedef struct OurBaseException_t OurException;
typedef struct _Unwind_Exception OurUnwindException;

namespace snowball {

int64_t ourBaseFromUnwindOffset;

const unsigned char ourBaseExcpClassChars[] =
    {'o', 'b', 'j', '\0', 's', 'n', '\0'};

static uint64_t ourBaseExceptionClass = 0;

/// Deletes the true previosly allocated exception whose address
/// is calculated from the supplied OurBaseException_t::unwindException
/// member address. Handles (ignores), NULL pointers.
/// @param expToDelete exception to delete
void deleteOurException(OurUnwindException *expToDelete) {
#ifdef DEBUG
  fprintf(stderr,
          "deleteOurException(...).\n");
#endif

  if (expToDelete &&
      (expToDelete->exception_class == ourBaseExceptionClass)) {

    free(((char*) expToDelete) + ourBaseFromUnwindOffset);
  }
}


/// This function is the struct _Unwind_Exception API mandated delete function
/// used by foreign exception handlers when deleting our exception
/// (OurException), instances.
/// @param reason See @link http://mentorembedded.github.com/cxx-abi/abi-eh.html
/// @unlink
/// @param expToDelete exception instance to delete
void deleteFromUnwindOurException(_Unwind_Reason_Code reason,
                                  OurUnwindException *expToDelete) {
#ifdef DEBUG
  fprintf(stderr,
          "deleteFromUnwindOurException(...).\n");
#endif

  deleteOurException(expToDelete);
}

/// Read a uleb128 encoded value and advance pointer
/// See Variable Length Data in:
/// @link http://dwarfstd.org/Dwarf3.pdf @unlink
/// @param data reference variable holding memory pointer to decode from
/// @returns decoded value
static uintptr_t readULEB128(const uint8_t **data) {
  uintptr_t result = 0;
  uintptr_t shift = 0;
  unsigned char byte;
  const uint8_t *p = *data;

  do {
    byte = *p++;
    result |= (byte & 0x7f) << shift;
    shift += 7;
  }
  while (byte & 0x80);

  *data = p;

  return result;
}

/// Read a sleb128 encoded value and advance pointer
/// See Variable Length Data in:
/// @link http://dwarfstd.org/Dwarf3.pdf @unlink
/// @param data reference variable holding memory pointer to decode from
/// @returns decoded value
static uintptr_t readSLEB128(const uint8_t **data) {
  uintptr_t result = 0;
  uintptr_t shift = 0;
  unsigned char byte;
  const uint8_t *p = *data;

  do {
    byte = *p++;
    result |= (byte & 0x7f) << shift;
    shift += 7;
  }
  while (byte & 0x80);

  *data = p;

  if ((byte & 0x40) && (shift < (sizeof(result) << 3))) {
    result |= (~0 << shift);
  }

  return result;
}

unsigned getEncodingSize(uint8_t Encoding) {
  if (Encoding == DW_EH_PE_omit)
    return 0;

  switch (Encoding & 0x0F) {
  case DW_EH_PE_absptr:
    return sizeof(uintptr_t);
  case DW_EH_PE_udata2:
    return sizeof(uint16_t);
  case DW_EH_PE_udata4:
    return sizeof(uint32_t);
  case DW_EH_PE_udata8:
    return sizeof(uint64_t);
  case DW_EH_PE_sdata2:
    return sizeof(int16_t);
  case DW_EH_PE_sdata4:
    return sizeof(int32_t);
  case DW_EH_PE_sdata8:
    return sizeof(int64_t);
  default:
    // not supported
    abort();
  }
}

/// Read a pointer encoded value and advance pointer
/// See Variable Length Data in:
/// @link http://dwarfstd.org/Dwarf3.pdf @unlink
/// @param data reference variable holding memory pointer to decode from
/// @param encoding dwarf encoding type
/// @returns decoded value
static uintptr_t readEncodedPointer(const uint8_t **data, uint8_t encoding) {
  uintptr_t result = 0;
  const uint8_t *p = *data;

  if (encoding == DW_EH_PE_omit)
    return(result);

  // first get value
  switch (encoding & 0x0F) {
    case DW_EH_PE_absptr:
      result = *((uintptr_t*)p);
      p += sizeof(uintptr_t);
      break;
    case DW_EH_PE_uleb128:
      result = readULEB128(&p);
      break;
      // Note: This case has not been tested
    case DW_EH_PE_sleb128:
      result = readSLEB128(&p);
      break;
    case DW_EH_PE_udata2:
      result = *((uint16_t*)p);
      p += sizeof(uint16_t);
      break;
    case DW_EH_PE_udata4:
      result = *((uint32_t*)p);
      p += sizeof(uint32_t);
      break;
    case DW_EH_PE_udata8:
      result = *((uint64_t*)p);
      p += sizeof(uint64_t);
      break;
    case DW_EH_PE_sdata2:
      result = *((int16_t*)p);
      p += sizeof(int16_t);
      break;
    case DW_EH_PE_sdata4:
      result = *((int32_t*)p);
      p += sizeof(int32_t);
      break;
    case DW_EH_PE_sdata8:
      result = *((int64_t*)p);
      p += sizeof(int64_t);
      break;
    default:
      // not supported
      abort();
      break;
  }

  // then add relative offset
  switch (encoding & 0x70) {
    case DW_EH_PE_absptr:
      // do nothing
      break;
    case DW_EH_PE_pcrel:
      result += (uintptr_t)(*data);
      break;
    case DW_EH_PE_textrel:
    case DW_EH_PE_datarel:
    case DW_EH_PE_funcrel:
    case DW_EH_PE_aligned:
    default:
      // not supported
      abort();
      break;
  }

  // then apply indirection
  if (encoding & DW_EH_PE_indirect) {
    result = *((uintptr_t*)result);
  }

  *data = p;

  return result;
}


/// Deals with Dwarf actions matching our type infos
/// (OurExceptionType_t instances). Returns whether or not a dwarf emitted
/// action matches the supplied exception type. If such a match succeeds,
/// the resultAction argument will be set with > 0 index value. Only
/// corresponding llvm.eh.selector type info arguments, cleanup arguments
/// are supported. Filters are not supported.
/// See Variable Length Data in:
/// @link http://dwarfstd.org/Dwarf3.pdf @unlink
/// Also see @link http://mentorembedded.github.com/cxx-abi/abi-eh.html @unlink
/// @param resultAction reference variable which will be set with result
/// @param classInfo our array of type info pointers (to globals)
/// @param actionEntry index into above type info array or 0 (clean up).
///        We do not support filters.
/// @param exceptionClass exception class (_Unwind_Exception::exception_class)
///        of thrown exception.
/// @param exceptionObject thrown _Unwind_Exception instance.
/// @returns whether or not a type info was found. False is returned if only
///          a cleanup was found
static bool handleActionValue(int64_t *resultAction,
                              uint8_t TTypeEncoding,
                              const uint8_t *ClassInfo,
                              uintptr_t actionEntry,
                              uint64_t exceptionClass,
                              struct _Unwind_Exception *exceptionObject) {
  bool ret = false;

  if (!resultAction ||
      !exceptionObject ||
      (exceptionClass != ourBaseExceptionClass))
    return(ret);

  struct OurBaseException_t *excp = (struct OurBaseException_t*)
  (((char*) exceptionObject) + ourBaseFromUnwindOffset);
  struct OurExceptionType_t *excpType = &(excp->type);
  int type = excpType->type;

#ifdef DEBUG
  fprintf(stderr,
          "handleActionValue(...): exceptionObject = <%p>, "
          "excp = <%p>.\n",
          exceptionObject,
          excp);
#endif

  const uint8_t *actionPos = (uint8_t*) actionEntry,
  *tempActionPos;
  int64_t typeOffset = 0,
  actionOffset;

  for (int i = 0; true; ++i) {
    // Each emitted dwarf action corresponds to a 2 tuple of
    // type info address offset, and action offset to the next
    // emitted action.
    typeOffset = readSLEB128(&actionPos);
    tempActionPos = actionPos;
    actionOffset = readSLEB128(&tempActionPos);

#ifdef DEBUG
    fprintf(stderr,
            "handleActionValue(...):typeOffset: <%lld>, "
            "actionOffset: <%lld>.\n",
            typeOffset,
            actionOffset);
#endif
    assert((typeOffset >= 0) &&
           "handleActionValue(...):filters are not supported.");

    // Note: A typeOffset == 0 implies that a cleanup llvm.eh.selector
    //       argument has been matched.
    if (typeOffset > 0) {
#ifdef DEBUG
      fprintf(stderr,
              "handleActionValue(...):actionValue <%d> found.\n",
              i);
#endif
      unsigned EncSize = getEncodingSize(TTypeEncoding);
      const uint8_t *EntryP = ClassInfo - typeOffset * EncSize;
      uintptr_t P = readEncodedPointer(&EntryP, TTypeEncoding);
      struct OurExceptionType_t *ThisClassInfo =
        reinterpret_cast<struct OurExceptionType_t *>(P);
      if (ThisClassInfo->type == type) {
        *resultAction = i + 1;
        ret = true;
        break;
      }
    }

#ifdef DEBUG
    fprintf(stderr,
            "handleActionValue(...):actionValue not found.\n");
#endif
    if (!actionOffset)
      break;

    actionPos += actionOffset;
  }

  return(ret);
}


/// Deals with the Language specific data portion of the emitted dwarf code.
/// See @link http://mentorembedded.github.com/cxx-abi/abi-eh.html @unlink
/// @param version unsupported (ignored), unwind version
/// @param lsda language specific data area
/// @param _Unwind_Action actions minimally supported unwind stage
///        (forced specifically not supported)
/// @param exceptionClass exception class (_Unwind_Exception::exception_class)
///        of thrown exception.
/// @param exceptionObject thrown _Unwind_Exception instance.
/// @param context unwind system context
/// @returns minimally supported unwinding control indicator
static _Unwind_Reason_Code handleLsda(int version,
                                      const uint8_t *lsda,
                                      _Unwind_Action actions,
                                      uint64_t exceptionClass,
                                    struct _Unwind_Exception *exceptionObject,
                                      _Unwind_Context_t context) {
  _Unwind_Reason_Code ret = _URC_CONTINUE_UNWIND;

  if (!lsda)
    return(ret);

#ifdef DEBUG
  fprintf(stderr,
          "handleLsda(...):lsda is non-zero.\n");
#endif

  // Get the current instruction pointer and offset it before next
  // instruction in the current frame which threw the exception.
  uintptr_t pc = _Unwind_GetIP(context)-1;

  // Get beginning current frame's code (as defined by the
  // emitted dwarf code)
  uintptr_t funcStart = _Unwind_GetRegionStart(context);
  uintptr_t pcOffset = pc - funcStart;
  const uint8_t *ClassInfo = NULL;

  // Note: See JITDwarfEmitter::EmitExceptionTable(...) for corresponding
  //       dwarf emission

  // Parse LSDA header.
  uint8_t lpStartEncoding = *lsda++;

  if (lpStartEncoding != DW_EH_PE_omit) {
    readEncodedPointer(&lsda, lpStartEncoding);
  }

  uint8_t ttypeEncoding = *lsda++;
  uintptr_t classInfoOffset;

  if (ttypeEncoding != DW_EH_PE_omit) {
    // Calculate type info locations in emitted dwarf code which
    // were flagged by type info arguments to llvm.eh.selector
    // intrinsic
    classInfoOffset = readULEB128(&lsda);
    ClassInfo = lsda + classInfoOffset;
  }

  // Walk call-site table looking for range that
  // includes current PC.

  uint8_t         callSiteEncoding = *lsda++;
  uint32_t        callSiteTableLength = readULEB128(&lsda);
  const uint8_t   *callSiteTableStart = lsda;
  const uint8_t   *callSiteTableEnd = callSiteTableStart +
  callSiteTableLength;
  const uint8_t   *actionTableStart = callSiteTableEnd;
  const uint8_t   *callSitePtr = callSiteTableStart;

  while (callSitePtr < callSiteTableEnd) {
    uintptr_t start = readEncodedPointer(&callSitePtr,
                                         callSiteEncoding);
    uintptr_t length = readEncodedPointer(&callSitePtr,
                                          callSiteEncoding);
    uintptr_t landingPad = readEncodedPointer(&callSitePtr,
                                              callSiteEncoding);

    // Note: Action value
    uintptr_t actionEntry = readULEB128(&callSitePtr);

    if (exceptionClass != ourBaseExceptionClass) {
      // We have been notified of a foreign exception being thrown,
      // and we therefore need to execute cleanup landing pads
      actionEntry = 0;
    }

    if (landingPad == 0) {
#ifdef DEBUG
      fprintf(stderr,
              "handleLsda(...): No landing pad found.\n");
#endif

      continue; // no landing pad for this entry
    }

    if (actionEntry) {
      actionEntry += ((uintptr_t) actionTableStart) - 1;
    }
    else {
#ifdef DEBUG
      fprintf(stderr,
              "handleLsda(...):No action table found.\n");
#endif
    }

    bool exceptionMatched = false;

    if ((start <= pcOffset) && (pcOffset < (start + length))) {
#ifdef DEBUG
      fprintf(stderr,
              "handleLsda(...): Landing pad found.\n");
#endif
      int64_t actionValue = 0;

      if (actionEntry) {
        exceptionMatched = handleActionValue(&actionValue,
                                             ttypeEncoding,
                                             ClassInfo,
                                             actionEntry,
                                             exceptionClass,
                                             exceptionObject);
      }

      if (!(actions & _UA_SEARCH_PHASE)) {
#ifdef DEBUG
        fprintf(stderr,
                "handleLsda(...): installed landing pad "
                "context.\n");
#endif

        // Found landing pad for the PC.
        // Set Instruction Pointer to so we re-enter function
        // at landing pad. The landing pad is created by the
        // compiler to take two parameters in registers.
        _Unwind_SetGR(context,
                      __builtin_eh_return_data_regno(0),
                      (uintptr_t)exceptionObject);

        // Note: this virtual register directly corresponds
        //       to the return of the llvm.eh.selector intrinsic
        if (!actionEntry || !exceptionMatched) {
          // We indicate cleanup only
          _Unwind_SetGR(context,
                        __builtin_eh_return_data_regno(1),
                        0);
        }
        else {
          // Matched type info index of llvm.eh.selector intrinsic
          // passed here.
          _Unwind_SetGR(context,
                        __builtin_eh_return_data_regno(1),
                        actionValue);
        }

        // To execute landing pad set here
        _Unwind_SetIP(context, funcStart + landingPad);
        ret = _URC_INSTALL_CONTEXT;
      }
      else if (exceptionMatched) {
#ifdef DEBUG
        fprintf(stderr,
                "handleLsda(...): setting handler found.\n");
#endif
        ret = _URC_HANDLER_FOUND;
      }
      else {
        // Note: Only non-clean up handlers are marked as
        //       found. Otherwise the clean up handlers will be
        //       re-found and executed during the clean up
        //       phase.
#ifdef DEBUG
        fprintf(stderr,
                "handleLsda(...): cleanup handler found.\n");
#endif
      }

      break;
    }
  }

  return(ret);
}

/// Generates our _Unwind_Exception class from a given character array.
/// thereby handling arbitrary lengths (not in standard), and handling
/// embedded \0s.
/// See @link http://mentorembedded.github.com/cxx-abi/abi-eh.html @unlink
/// @param classChars char array to encode. NULL values not checkedf
/// @param classCharsSize number of chars in classChars. Value is not checked.
/// @returns class value
uint64_t genClass(const unsigned char classChars[], size_t classCharsSize)
{
  uint64_t ret = classChars[0];

  for (unsigned i = 1; i < classCharsSize; ++i) {
    ret <<= 8;
    ret += classChars[i];
  }

  return(ret);
}

/// @brief Returns the offset of the exception member of OurException_t
/// @return offset of exception member of OurException_t
int64_t exception_offset() {
  static OurBaseException_t dummy = {};
  return (int64_t)((uintptr_t)&dummy - (uintptr_t) & (dummy.unwindException));
}

uint64_t exception_class() {
  return genClass(ourBaseExcpClassChars, sizeof(ourBaseExcpClassChars));
}

void end_stack(void* exep) {
  auto *base = (OurBaseException_t *)((char *)exep + exception_offset());
  void *obj = base->snowball_object;
  auto *hdr = (SnowballExceptionInstance_t *)obj;
  bool showBacktrace = false;

  // TODO: Class name and location
  std::ostringstream buf;
  buf << "\n\e[1;31merror\e[1;37m: Unhandled exception";
  if (strcmp(hdr->message, "") != 0) {
    buf << ": \033[0m";
    buf << hdr->message;
  } else {
    buf << "\033[0m";
  }

  if (!showBacktrace) {
    buf << "\n \e[1;32minfo\e[0m: You can export the enviroment variable `SN_BACKTRACE=1` to enable backtrace logging.";
  }

  buf << "\n\n";
  auto output = buf.str();
  fwrite(output.data(), 1, output.size(), stderr);
  abort();
}

} // namespace snowball

// MARK: - Eported functions

void throwOurException(void* obj) __asm__("sn.eh.throw");
OurUnwindException *createOurException(void* obj, int type) __asm__("sn.eh.create");
_Unwind_Reason_Code ourPersonality(int version,
                                   _Unwind_Action actions,
                                   uint64_t exceptionClass,
                                   struct _Unwind_Exception *exceptionObject,
                                   _Unwind_Context_t context) __asm__("sn.eh.personality");

/// Creates (allocates on the heap), an exception (OurException instance),
/// of the supplied type info type.
/// @param type type info type
OurUnwindException *createOurException(void* obj, int type) {
  size_t size = sizeof(OurException);
  OurException *ret = (OurException*) memset(malloc(size), 0, size);
  (ret->type).type = type;
  (ret->unwindException).exception_class = snowball::ourBaseExceptionClass;
  (ret->unwindException).exception_cleanup = snowball::deleteFromUnwindOurException;
  ret->snowball_object = obj;

  return(&(ret->unwindException));
}

/// This is the personality function which is embedded (dwarf emitted), in the
/// dwarf unwind info block. Again see: JITDwarfEmitter.cpp.
/// See @link http://mentorembedded.github.com/cxx-abi/abi-eh.html @unlink
/// @param version unsupported (ignored), unwind version
/// @param _Unwind_Action actions minimally supported unwind stage
///        (forced specifically not supported)
/// @param exceptionClass exception class (_Unwind_Exception::exception_class)
///        of thrown exception.
/// @param exceptionObject thrown _Unwind_Exception instance.
/// @param context unwind system context
/// @returns minimally supported unwinding control indicator
_Unwind_Reason_Code ourPersonality(int version,
                                   _Unwind_Action actions,
                                   uint64_t exceptionClass,
                                   struct _Unwind_Exception *exceptionObject,
                                   _Unwind_Context_t context) {
#ifdef DEBUG
  fprintf(stderr,
          "We are in ourPersonality(...):actions is <%d>.\n",
          actions);

  if (actions & _UA_SEARCH_PHASE) {
    fprintf(stderr, "ourPersonality(...):In search phase.\n");
  }
  else {
    fprintf(stderr, "ourPersonality(...):In non-search phase.\n");
  }
#endif

  const uint8_t *lsda = (uint8_t *)_Unwind_GetLanguageSpecificData(context);

#ifdef DEBUG
  fprintf(stderr,
          "ourPersonality(...):lsda = <%p>.\n",
          lsda);
#endif

  // The real work of the personality function is captured here
  return(snowball::handleLsda(version,
                    lsda,
                    actions,
                    exceptionClass,
                    exceptionObject,
                    context));
}

void throwOurException(void *exc) {
  _Unwind_Reason_Code code = _Unwind_RaiseException((_Unwind_Exception *)exc);
  (void)code;
  snowball::end_stack(exc);
}

namespace snowball {
void initialize_exceptions() {
  ourBaseFromUnwindOffset = exception_offset();
  ourBaseExceptionClass = exception_class();
}
}
