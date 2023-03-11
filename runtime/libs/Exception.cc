

#include <assert.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cxxabi.h>
#include <iostream>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unwind.h>
#include <utility>

#define UNREACHABLE                                                            \
    do {                                                                       \
        std::abort();                                                          \
    } while (0);

namespace snowball {

struct Exception {

    _Unwind_Exception unwindHeader;
    std::uintptr_t _landingPad;
    std::uint32_t _typeIndex;

    struct ActualException {
        void *vtable;
        char *_msg;
    } *actualException = nullptr;

    [[nodiscard]] std::uintptr_t getLandingPad() const { return _landingPad; }

    void setLandingPad(std::uintptr_t p_landing_pad) {
        _landingPad = p_landing_pad;
    }

    [[nodiscard]] std::uint32_t getTypeIndex() const { return _typeIndex; }

    void setTypeIndex(std::uint32_t p_type_index) { _typeIndex = p_type_index; }

    static const std::uint64_t EXCEPTION_CLASS = 0x50594C5250590000;

    static Exception *fromUnwindHeader(_Unwind_Exception *header) {
        return reinterpret_cast<Exception *>(reinterpret_cast<char *>(header) -
                                             offsetof(Exception, unwindHeader));
    }
};

enum {
    // NOLINTBEGIN(readability-identifier-naming): These names are part of a
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
    // NOLINTEND(readability-identifier-naming)
};

std::uintptr_t readULEB128(const std::uint8_t **data) {
    std::uintptr_t result = 0;
    std::uintptr_t shift  = 0;
    unsigned char byte;
    const uint8_t *p = *data;
    do {
        byte = *p++;
        result |= static_cast<std::uintptr_t>(byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);
    *data = p;
    return result;
}

std::intptr_t readSLEB128(const std::uint8_t **data) {
    std::uintptr_t result = 0;
    std::uintptr_t shift  = 0;
    unsigned char byte;
    const uint8_t *p = *data;
    do {
        byte = *p++;
        result |= static_cast<std::uintptr_t>(byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);
    *data = p;
    if ((byte & 0x40) && (shift < (sizeof(result) << 3))) {
        result |= static_cast<std::uintptr_t>(~0) << shift;
    }
    return static_cast<std::intptr_t>(result);
}

template <class AsType>
std::uintptr_t readPointerHelper(const std::uint8_t *& p) {
    AsType value;
    std::memcpy(&value, p, sizeof(AsType));
    p += sizeof(AsType);
    return static_cast<std::uintptr_t>(value);
}

std::uintptr_t readEncodedPointer(const std::uint8_t **data,
                                  std::uint8_t encoding) {
    std::uintptr_t result = 0;
    if (encoding == DW_EH_PE_omit) {
        return result;
    }
    const std::uint8_t *p = *data;
    // first get value
    switch (encoding & 0x0F) {
        case DW_EH_PE_absptr:
            result = readPointerHelper<std::uintptr_t>(p);
            break;
        case DW_EH_PE_uleb128:
            result = readULEB128(&p);
            break;
        case DW_EH_PE_sleb128:
            result = static_cast<std::uintptr_t>(readSLEB128(&p));
            break;
        case DW_EH_PE_udata2:
            result = readPointerHelper<std::uint16_t>(p);
            break;
        case DW_EH_PE_udata4:
            result = readPointerHelper<std::uint32_t>(p);
            break;
        case DW_EH_PE_udata8:
            result = readPointerHelper<std::uint64_t>(p);
            break;
        case DW_EH_PE_sdata2:
            result = readPointerHelper<std::int16_t>(p);
            break;
        case DW_EH_PE_sdata4:
            result = readPointerHelper<std::int32_t>(p);
            break;
        case DW_EH_PE_sdata8:
            result = readPointerHelper<std::int64_t>(p);
            break;
        default:
            // not supported
            UNREACHABLE;
    }
    // then add relative offset
    switch (encoding & 0x70) {
        case DW_EH_PE_absptr:
            // do nothing
            break;
        case DW_EH_PE_pcrel:
            if (result) {
                result += reinterpret_cast<intptr_t>(*data);
            }
            break;
        case DW_EH_PE_datarel:
        case DW_EH_PE_textrel:
        case DW_EH_PE_funcrel:
        case DW_EH_PE_aligned:
        default:
            // not supported
            UNREACHABLE;
    }
    // then apply indirection
    if (result && (encoding & DW_EH_PE_indirect)) {
        result = *(reinterpret_cast<std::uintptr_t *>(result));
    }
    *data = p;
    return result;
}

struct Result {
    _Unwind_Reason_Code code;
    std::uintptr_t landingPad;
    std::uint32_t typeIndex;

    Exception::ActualException *baseException;
};

Result findLandingPad(_Unwind_Action actions, bool nativeException,
                      _Unwind_Exception *exception, _Unwind_Context *context) {
    // Inconsistent states
    if (actions & _UA_SEARCH_PHASE) {
        if (actions &
            (_UA_CLEANUP_PHASE | _UA_HANDLER_FRAME | _UA_FORCE_UNWIND)) {
            return {_URC_FATAL_PHASE1_ERROR, 0, 0};
        }
    } else if (actions & _UA_CLEANUP_PHASE) {
        if ((actions & (_UA_HANDLER_FRAME)) && (actions & _UA_FORCE_UNWIND)) {
            return {_URC_FATAL_PHASE2_ERROR, 0, 0};
        }
    } else {
        return {_URC_FATAL_PHASE1_ERROR, 0, 0};
    }

    const auto *exceptionTable = reinterpret_cast<const uint8_t *>(
        _Unwind_GetLanguageSpecificData(context));
    if (!exceptionTable) {
        return {_URC_CONTINUE_UNWIND, 0, 0};
    }

    std::uintptr_t ip            = _Unwind_GetIP(context) - 1;
    std::uintptr_t functionStart = _Unwind_GetRegionStart(context);
    auto offset                  = ip - functionStart;
    auto encodingStart           = *exceptionTable++;
    const auto *lpStart          = reinterpret_cast<const uint8_t *>(
        readEncodedPointer(&exceptionTable, encodingStart));
    if (!lpStart) {
        lpStart = reinterpret_cast<const uint8_t *>(functionStart);
    }

    const std::uint8_t *classInfo = nullptr;
    std::uint8_t typeEncoding     = *exceptionTable++;

    if (typeEncoding != DW_EH_PE_omit) {
        auto classInfoOffset = readULEB128(&exceptionTable);
        classInfo            = exceptionTable + classInfoOffset;
    }

    std::uint8_t callSiteEncoding = *exceptionTable++;
    auto callSiteTableLength =
        static_cast<std::uint32_t>(readULEB128(&exceptionTable));
    const auto *callSiteTableStart = exceptionTable;
    const auto *callSiteTableEnd   = callSiteTableStart + callSiteTableLength;
    const auto *actionTableStart   = callSiteTableEnd;
    for (const auto *callSitePtr = callSiteTableStart;
         callSitePtr < callSiteTableEnd;) {

        auto start       = readEncodedPointer(&callSitePtr, callSiteEncoding);
        auto length      = readEncodedPointer(&callSitePtr, callSiteEncoding);
        auto landingPad  = readEncodedPointer(&callSitePtr, callSiteEncoding);
        auto actionEntry = readULEB128(&callSitePtr);
        if (offset >= (start + length)) {
            continue;
        }

        assert(offset >= start);

        if (landingPad == 0) {
            return {_URC_CONTINUE_UNWIND, 0, 0};
        }

        landingPad = reinterpret_cast<std::uintptr_t>(lpStart) + landingPad;
        if (actionEntry == 0) {
            return {actions & _UA_SEARCH_PHASE ? _URC_CONTINUE_UNWIND
                                               : _URC_HANDLER_FOUND,
                    landingPad, 0, 0};
        }

        const auto *action = actionTableStart + (actionEntry - 1);
        bool hasCleanUp    = false;
        while (true) {
            // auto* actionRecord = action;
            std::int32_t typeIndex     = readSLEB128(&action);
            std::int32_t baseException = readSLEB128(&action);
            if (typeIndex > 0) {
                // catch clauses
                return {_URC_HANDLER_FOUND, landingPad,
                        static_cast<std::uint32_t>(typeIndex),
                        reinterpret_cast<Exception::ActualException *>(
                            baseException)};
            } else if (typeIndex < 0) {
                // Don't support filters or anything of the sort at the moment
                // as I don't have a need yet
            } else {
                // cleanup clause
                hasCleanUp = true;
            }
            const auto *temp  = action;
            auto actionOffset = readSLEB128(&temp);
            if (actionOffset == 0) {
                return {hasCleanUp && (actions & _UA_CLEANUP_PHASE)
                            ? _URC_HANDLER_FOUND
                            : _URC_CONTINUE_UNWIND,
                        landingPad, static_cast<std::uint32_t>(typeIndex)};
            }
            action += actionOffset;
        }
    }
    UNREACHABLE;
}

Exception::ActualException *toExceptionType(void *p_exct) {
    return reinterpret_cast<Exception::ActualException *>(p_exct);
}

} // namespace snowball

#define EXCEPTION_ARGUMENTS() void *thrown_exception

extern const void *
    throwException(EXCEPTION_ARGUMENTS()) __asm__("sn.core.eh.throw");
const void *throwException(EXCEPTION_ARGUMENTS()) {

    auto exception = reinterpret_cast<snowball::Exception *>(thrown_exception);
    auto header    = exception->unwindHeader;

    std::memset(&header, 0, sizeof(header));
    header.exception_cleanup =
        +[](_Unwind_Reason_Code, _Unwind_Exception *) { /*NOOP for now*/ };
    header.exception_class = snowball::Exception::EXCEPTION_CLASS;
    auto code              = _Unwind_RaiseException(&header);
    switch (code) {
        case _URC_END_OF_STACK: {
            // TODO: show exception class name
            std::cerr << "Runtime Error: " << exception->actualException->_msg
                      << std::endl;
            std::exit(1);
        };

        case _URC_FATAL_PHASE1_ERROR:
        case _URC_FATAL_PHASE2_ERROR:
            std::abort();

        default:
            UNREACHABLE;
    }

    // throw_exception never returns
    printf("no one handled throwException, terminate!\n");
    exit(0);
}

extern const void *createException(snowball::Exception::ActualException
                                       *exception) __asm__("sn.core.eh.create");
extern const void *
createException(snowball::Exception::ActualException *exception) {
    snowball::Exception *exception_result =
        static_cast<snowball::Exception *>(malloc(sizeof(snowball::Exception)));

    exception_result->actualException = snowball::toExceptionType(
        malloc(sizeof(snowball::Exception::ActualException *)));
    memcpy(exception_result->actualException, exception,
           sizeof(snowball::Exception::ActualException));
    return static_cast<void *>(exception_result);
}

#undef EXCEPTION_ARGUMENTS
#define PERSONALITY_ARGUMENTS()                                                \
    int version, _Unwind_Action actions, std::uint64_t clazz,                  \
        _Unwind_Exception *exceptionInfo, _Unwind_Context *context

extern const _Unwind_Reason_Code
    personalityImpl(PERSONALITY_ARGUMENTS()) __asm__("sn.core.eh.personality");
extern const _Unwind_Reason_Code personalityImpl(PERSONALITY_ARGUMENTS()) {
    if (version != 1 || !exceptionInfo || !context) {
        return _URC_FATAL_PHASE1_ERROR;
    }

    bool nativeException = clazz == snowball::Exception::EXCEPTION_CLASS;
    if (actions == (_UA_CLEANUP_PHASE | _UA_HANDLER_FRAME) && nativeException) {
        auto *snException =
            snowball::Exception::fromUnwindHeader(exceptionInfo);
        _Unwind_SetGR(context, __builtin_eh_return_data_regno(0),
                      reinterpret_cast<uintptr_t>(exceptionInfo));
        _Unwind_SetGR(context, __builtin_eh_return_data_regno(1),
                      static_cast<uintptr_t>(snException->getTypeIndex()));
        _Unwind_SetGR(
            context, __builtin_eh_return_data_regno(2),
            reinterpret_cast<uintptr_t>(snException->actualException));
        _Unwind_SetIP(context, snException->getLandingPad());
        return _URC_INSTALL_CONTEXT;
    }

    auto result = snowball::findLandingPad(actions, nativeException,
                                           exceptionInfo, context);
    if (result.code == _URC_CONTINUE_UNWIND ||
        result.code == _URC_FATAL_PHASE1_ERROR) {
        return result.code;
    }

    if (actions & _UA_SEARCH_PHASE) {
        assert(result.code == _URC_HANDLER_FOUND);
        if (nativeException) {
            auto *snException =
                snowball::Exception::fromUnwindHeader(exceptionInfo);
            snException->setLandingPad(result.landingPad);
            snException->setTypeIndex(result.typeIndex);
            snException->actualException = result.baseException;
        }
        return _URC_HANDLER_FOUND;
    }

    // TODO: Trying to jump to a catch handler with a foreign exception. Figure
    // out how that is supposed
    //       to work
    _Unwind_SetGR(context, __builtin_eh_return_data_regno(0),
                  reinterpret_cast<uintptr_t>(exceptionInfo));
    _Unwind_SetGR(context, __builtin_eh_return_data_regno(1),
                  static_cast<uintptr_t>(result.typeIndex));
    _Unwind_SetGR(context, __builtin_eh_return_data_regno(2),
                  reinterpret_cast<uintptr_t>(result.baseException));
    _Unwind_SetIP(context, result.landingPad);
    return _URC_INSTALL_CONTEXT;
}

#undef PERSONALITY_ARGUMENTS