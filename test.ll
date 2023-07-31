Lexer: 0.000107s
Parser: 0.000540s
Lexer: 0.001208s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Parser: 0.003323s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Lexer: 0.000101s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Internal/Preloads.sn)
Parser: 0.000130s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Internal/Preloads.sn)
Lexer: 0.000369s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Parser: 0.000375s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Lexer: 0.000152s (/home/mauro/work/snowball/tests/option.sn)
Parser: 0.000467s (/home/mauro/work/snowball/tests/option.sn)
Lexer: 0.000135s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Optional.sn)
Parser: 0.000327s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Optional.sn)
Lexer: 0.000077s (/home/mauro/work/snowball/tests/vector.sn)
Parser: 0.000330s (/home/mauro/work/snowball/tests/vector.sn)
Lexer: 0.000040s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Parser: 0.000120s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Lexer: 0.001017s (/home/mauro/work/snowball/tests/chars.sn)
Parser: 0.002553s (/home/mauro/work/snowball/tests/chars.sn)
Lexer: 0.000310s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Parser: 0.000909s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Lexer: 0.000243s (/home/mauro/work/snowball/tests/cls.sn)
Parser: 0.000671s (/home/mauro/work/snowball/tests/cls.sn)
Lexer: 0.000044s (/home/mauro/work/snowball/tests/string.sn)
Parser: 0.000121s (/home/mauro/work/snowball/tests/string.sn)
Lexer: 0.000063s (/home/mauro/work/snowball/tests/macros.sn)
Parser: 0.000214s (/home/mauro/work/snowball/tests/macros.sn)
Lexer: 0.000378s (/home/mauro/work/snowball/tests/syntax.sn)
Parser: 0.000933s (/home/mauro/work/snowball/tests/syntax.sn)
Lexer: 0.000075s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Parser: 0.000163s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Lexer: 0.000127s (/home/mauro/work/snowball/tests/clib.sn)
Parser: 0.000332s (/home/mauro/work/snowball/tests/clib.sn)
Lexer: 0.000092s (/home/mauro/work/snowball/tests/tuples.sn)
Parser: 0.000347s (/home/mauro/work/snowball/tests/tuples.sn)
Lexer: 0.000150s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Tuples.sn)
Parser: 0.000249s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Tuples.sn)
Simplifier: 0.089716s
Passes: 0.000036s
TypeChecker: 0.000038s (Core::Internal::Preloads)
TypeChecker: 0.000009s (Core::CLib::c_string)
TypeChecker: 0.000066s (Core::CLib::__internal)
TypeChecker: 0.000045s (Core::CLib)
TypeChecker: 0.000007s (Core::_$core::Core::UA)
TypeChecker: 0.000002s (Core::_$core::Core::__internal)
TypeChecker: 0.000853s (Core::_$core::Core)
TypeChecker: 0.000044s (Core::_$core)
TypeChecker: 0.000003s (Core::Optional)
TypeChecker: 0.000001s (pkg::option::tests)
TypeChecker: 0.000001s (pkg::option)
TypeChecker: 0.000002s (Core::Assert)
TypeChecker: 0.000002s (pkg::vector::tests)
TypeChecker: 0.000001s (pkg::vector)
TypeChecker: 0.000040s (Core::Char)
TypeChecker: 0.000002s (pkg::chars::tests)
TypeChecker: 0.000001s (pkg::chars)
TypeChecker: 0.000020s (pkg::cls::test)
TypeChecker: 0.000002s (pkg::cls)
TypeChecker: 0.000002s (pkg::string::tests)
TypeChecker: 0.000001s (pkg::string)
TypeChecker: 0.000001s (pkg::macros::tests)
TypeChecker: 0.000001s (pkg::macros)
TypeChecker: 0.000025s (Core::System)
TypeChecker: 0.000002s (pkg::syntax::tests)
TypeChecker: 0.000001s (pkg::syntax)
TypeChecker: 0.000001s (pkg::clib::tests)
TypeChecker: 0.000002s (pkg::clib)
TypeChecker: 0.000001s (Core::Tuples)
TypeChecker: 0.000001s (pkg::tuples::tests)
TypeChecker: 0.000001s (pkg::tuples)
TypeChecker: 0.000032s ($main)
Emitting object file... (/home/mauro/work/snowball/.sn/bin/out.o.so)
Finished codegen, proceeding to verify module
Finished verifying module, proceeding to optimize module (if requested)
; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE" = type { ptr }
%"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE" = type { ptr, ptr }
%"vtable._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { ptr }
%"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE" = type { ptr, i32, i32, i32 }
%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" = type { i1, i32 }
%"class._$SN&4IterCv17757ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { i1, ptr }
%"class._$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { ptr, i32 }
%"class._$SN&8IterableCv17204ClsGStA1T3i32ClsE" = type { ptr, i32 }
%"class._$SN&4IterCv17033ClsGStA1T4charClsE" = type { i1, i8 }
%"class._$SN&8IterableCv17032ClsGStA1T4charClsE" = type { ptr, i32 }
%"class._$SN&9ExceptionCv17060ClsE" = type { ptr }

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE" = global %"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE" { ptr @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4nextCv17120SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE" }
@.str.5 = private unnamed_addr constant [3 x i8] c", \00", align 1
@"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE" = global %"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE" { ptr @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4nextCv17260SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE", ptr @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4nextCv17312SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE" }
@.str.6 = private unnamed_addr constant [7 x i8] c"i: %i\0A\00", align 1
@.str.7 = private unnamed_addr constant [7 x i8] c"i: %i\0A\00", align 1
@.str.8 = private unnamed_addr constant [21 x i8] c"Index out of bounds.\00", align 1
@.str.10 = private unnamed_addr constant [2 x i8] c"\22\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c"\22\00", align 1
@.str.12 = private unnamed_addr constant [25 x i8] c"Invalid iterator access!\00", align 1
@.str.15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.22 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.23 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@"vtable._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = global %"vtable._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" { ptr @"_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4nextCv17812SaA1_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE" }
@.str.24 = private unnamed_addr constant [4 x i8] c"awd\00", align 1
@.str.25 = private unnamed_addr constant [4 x i8] c"awd\00", align 1
@.str.26 = private unnamed_addr constant [4 x i8] c"awd\00", align 1

; Function Attrs: noinline
define private ptr @"_$SNT4char&3#PlCv16965SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %other) #0 !dbg !5 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %other
  ret ptr %0
}

; Function Attrs: noinline
declare i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64)) #0

; Function Attrs: nocallback nofree noinline nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline
declare ptr @malloc(i32) #0

; Function Attrs: noinline
declare i32 @sn.eh.personality(i32, i32, i64, ptr, ptr) #0

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17225SaFnE"() #2 personality ptr @sn.eh.personality !dbg !13 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !17
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17217SaFnE"() #2 personality ptr @sn.eh.personality !dbg !18 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !19
}

; Function Attrs: noinline
declare i32 @printf(ptr noundef nonnull align 8 dereferenceable(64), ...) #0

; Function Attrs: noinline
declare void @memcpy(ptr, ptr, i32) #0

; Function Attrs: noinline
declare ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64), i32) #0

; Function Attrs: noinline
declare void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64), i32, ptr) #0

; Function Attrs: noinline
declare ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64), i32) #0

; Function Attrs: noinline
declare ptr @sn.ua.alloc(i32) #0

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17937SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(ptr sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") %0, %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %1) #2 personality ptr @sn.eh.personality !dbg !20 {
entry:
  %arg.buffer = alloca %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  store %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !28, metadata !DIExpression()), !dbg !29
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  call void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&9to_stringCv17940SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr %arg.buffer), !dbg !30
  %3 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !30
  ret void, !dbg !30
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&9to_stringCv17940SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !31 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !36, metadata !DIExpression()), !dbg !37
  %var.result = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %0, metadata !38, metadata !DIExpression()), !dbg !40
  %var.separator = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.separator, metadata !41, metadata !DIExpression()), !dbg !42
  %var.x = alloca %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.x, metadata !43, metadata !DIExpression()), !dbg !46
  %var.a = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.a, metadata !47, metadata !DIExpression()), !dbg !49
  %var.b = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.b, metadata !50, metadata !DIExpression()), !dbg !51
  %"var.$iter" = alloca %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !52, metadata !DIExpression()), !dbg !53
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !54, metadata !DIExpression()), !dbg !53
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !55, metadata !DIExpression()), !dbg !53
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %4 = alloca %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", align 8
  %5 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  %6 = alloca %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", align 8
  %7 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  %8 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %9 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %10 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %11 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %12 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %12, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) @.str), !dbg !56
  %13 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !56
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %13, ptr %0, align 8, !dbg !56
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %14, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, ptr noundef nonnull align 8 dereferenceable(64) @.str.5), !dbg !57
  %15 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, align 8, !dbg !57
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %15, ptr %var.separator, align 8, !dbg !57
  %16 = load ptr, ptr %arg.self, align 8, !dbg !37
  %17 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %16, i32 0, i32 3, !dbg !37
  %18 = load i32, ptr %17, align 4, !dbg !37
  %19 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 0
  store ptr @"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %19, align 8
  call void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, i32 0, i32 %18), !dbg !58
  %20 = load %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, align 8, !dbg !58
  store %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE" %20, ptr %var.x, align 8, !dbg !58
  %21 = load ptr, ptr %5, align 8, !dbg !59
  %22 = getelementptr inbounds ptr, ptr %21, i32 1, !dbg !59
  %23 = load ptr, ptr %22, align 8, !dbg !59
  call void %23(ptr %5, ptr %var.x), !dbg !59
  %24 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %5, align 4, !dbg !59
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %24, ptr %var.a, align 4, !dbg !59
  %25 = call i32 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a) #5, !dbg !60
  store i32 %25, ptr %var.b, align 4, !dbg !60
  %26 = load ptr, ptr %arg.self, align 8, !dbg !37
  %27 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %26, i32 0, i32 3, !dbg !37
  %28 = load i32, ptr %27, align 4, !dbg !37
  %29 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 0
  store ptr @"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %29, align 8
  call void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, i32 0, i32 %28), !dbg !53
  %30 = load %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %6, align 8, !dbg !53
  store %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE" %30, ptr %"var.$iter", align 8, !dbg !53
  %31 = load ptr, ptr %7, align 8, !dbg !53
  %32 = getelementptr inbounds ptr, ptr %31, i32 1, !dbg !53
  %33 = load ptr, ptr %32, align 8, !dbg !53
  call void %33(ptr %7, ptr %"var.$iter"), !dbg !53
  %34 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %7, align 4, !dbg !53
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %34, ptr %"var.$iter_value", align 4, !dbg !53
  br label %35, !dbg !53

35:                                               ; preds = %63, %body
  %36 = call i1 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&8is_validCv17234SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #5, !dbg !53
  br i1 %36, label %37, label %57, !dbg !53

37:                                               ; preds = %35
  %38 = call i32 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #5, !dbg !53
  store i32 %38, ptr %var.i, align 4, !dbg !53
  %39 = load i32, ptr %var.i, align 4, !dbg !61
  %40 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.6, i32 %39), !dbg !62
  %41 = load ptr, ptr %arg.self, align 8, !dbg !37
  %42 = load i32, ptr %var.i, align 4, !dbg !63
  %43 = call ptr @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17867SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %41, i32 %42), !dbg !64
  %44 = call i32 @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4sizeCv17189SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %43) #5, !dbg !64
  %45 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.7, i32 %44), !dbg !65
  %46 = load ptr, ptr %arg.self, align 8, !dbg !37
  %47 = load i32, ptr %var.i, align 4, !dbg !66
  %48 = call ptr @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17867SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %46, i32 %47), !dbg !67
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17972SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %8, ptr %48) #5, !dbg !68
  %49 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %8, align 8, !dbg !68
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %9, ptr %0, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %49) #5, !dbg !69
  %50 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %9, align 8, !dbg !69
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %50, ptr %0, align 8, !dbg !69
  %51 = load i32, ptr %var.i, align 4, !dbg !53
  %52 = load ptr, ptr %arg.self, align 8, !dbg !37
  %53 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %52, i32 0, i32 3, !dbg !37
  %54 = load i32, ptr %53, align 4, !dbg !37
  %55 = sub i32 %54, 1, !dbg !70
  %56 = icmp ne i32 %51, %55, !dbg !70
  br i1 %56, label %59, label %62, !dbg !70

57:                                               ; preds = %35
  %58 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !71
  ret void, !dbg !71

59:                                               ; preds = %37
  %60 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %var.separator, align 8, !dbg !72
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %10, ptr %0, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %60) #5, !dbg !73
  %61 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %10, align 8, !dbg !73
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %61, ptr %0, align 8, !dbg !73
  br label %63, !dbg !73

62:                                               ; preds = %37
  br label %63, !dbg !73

63:                                               ; preds = %62, %59
  %64 = load ptr, ptr %11, align 8, !dbg !53
  %65 = getelementptr inbounds ptr, ptr %64, i32 1, !dbg !53
  %66 = load ptr, ptr %65, align 8, !dbg !53
  call void %66(ptr %11, ptr %"var.$iter"), !dbg !53
  %67 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %11, align 4, !dbg !53
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %67, ptr %"var.$iter_value", align 4, !dbg !53
  br label %35, !dbg !53
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17972SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #2 personality ptr @sn.eh.personality !dbg !74 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !78, metadata !DIExpression()), !dbg !79
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.buffer, align 8, !dbg !79
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&9to_stringCv17377SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr %3) #5, !dbg !80
  %4 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !80
  ret void, !dbg !80
}

; Function Attrs: noinline
define internal ptr @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17867SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !81 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !84, metadata !DIExpression()), !dbg !85
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !86, metadata !DIExpression()), !dbg !85
  br label %body

body:                                             ; preds = %entry
  %2 = load i32, ptr %arg.index, align 4, !dbg !85
  %3 = icmp slt i32 %2, 0, !dbg !87
  %4 = load i32, ptr %arg.index, align 4, !dbg !85
  %5 = load ptr, ptr %arg.self, align 8, !dbg !85
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %5, i32 0, i32 3, !dbg !85
  %7 = load i32, ptr %6, align 4, !dbg !85
  %8 = icmp sge i32 %4, %7, !dbg !85
  %9 = or i1 %3, %8, !dbg !85
  br i1 %9, label %10, label %13, !dbg !85

10:                                               ; preds = %body
  %11 = call ptr @sn.alloca(i32 8), !dbg !88
  call void @"_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, ptr noundef nonnull align 8 dereferenceable(64) @.str.8), !dbg !88
  %12 = call ptr @sn.eh.create(ptr %11, i32 1000), !dbg !88
  call void @sn.eh.throw(ptr %12), !dbg !88
  br label %14, !dbg !88

13:                                               ; preds = %body
  br label %14, !dbg !88

14:                                               ; preds = %13, %10
  %15 = load ptr, ptr %arg.self, align 8, !dbg !85
  %16 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %15, i32 0, i32 4, !dbg !85
  %17 = load ptr, ptr %16, align 8, !dbg !85
  %18 = load i32, ptr %arg.index, align 4, !dbg !89
  %19 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18), !dbg !90
  ret ptr %19, !dbg !90
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17843SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !91 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !94, metadata !DIExpression()), !dbg !95
  %arg.value = alloca ptr, align 8
  store ptr %1, ptr %arg.value, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !96, metadata !DIExpression()), !dbg !95
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !95
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %2, i32 0, i32 3, !dbg !95
  %4 = load i32, ptr %3, align 4, !dbg !95
  %5 = add i32 %4, 1, !dbg !97
  %6 = load ptr, ptr %arg.self, align 8, !dbg !95
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %6, i32 0, i32 2, !dbg !95
  %8 = load i32, ptr %7, align 4, !dbg !95
  %9 = icmp sge i32 %5, %8, !dbg !95
  br i1 %9, label %10, label %16, !dbg !95

10:                                               ; preds = %body
  %11 = load ptr, ptr %arg.self, align 8, !dbg !95
  %12 = load ptr, ptr %arg.self, align 8, !dbg !95
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %12, i32 0, i32 2, !dbg !95
  %14 = load i32, ptr %13, align 4, !dbg !95
  %15 = add i32 %14, 10, !dbg !98
  call void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&6resizeCv17848SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %15), !dbg !99
  br label %17, !dbg !99

16:                                               ; preds = %body
  br label %17, !dbg !99

17:                                               ; preds = %16, %10
  %18 = load ptr, ptr %arg.self, align 8, !dbg !95
  %19 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %18, i32 0, i32 4, !dbg !95
  %20 = load ptr, ptr %19, align 8, !dbg !95
  %21 = load ptr, ptr %arg.self, align 8, !dbg !95
  %22 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %21, i32 0, i32 3, !dbg !95
  %23 = load i32, ptr %22, align 4, !dbg !95
  %24 = load ptr, ptr %arg.value, align 8, !dbg !100
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %23, ptr %24), !dbg !101
  %25 = load ptr, ptr %arg.self, align 8, !dbg !95
  %26 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %25, i32 0, i32 3, !dbg !95
  %27 = load i32, ptr %26, align 4, !dbg !95
  %28 = load ptr, ptr %arg.self, align 8, !dbg !95
  %29 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %28, i32 0, i32 3, !dbg !95
  %30 = load i32, ptr %29, align 4, !dbg !95
  %31 = add i32 %30, 1, !dbg !102
  store i32 %31, ptr %26, align 4, !dbg !102
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&6resizeCv17848SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !103 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !106, metadata !DIExpression()), !dbg !107
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !108, metadata !DIExpression()), !dbg !107
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !107
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %2, i32 0, i32 2, !dbg !107
  %4 = load i32, ptr %3, align 4, !dbg !107
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !109
  store i32 %5, ptr %3, align 4, !dbg !109
  %6 = load ptr, ptr %arg.self, align 8, !dbg !107
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %6, i32 0, i32 4, !dbg !107
  %8 = load ptr, ptr %7, align 8, !dbg !107
  %9 = load ptr, ptr %arg.self, align 8, !dbg !107
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %9, i32 0, i32 4, !dbg !107
  %11 = load ptr, ptr %10, align 8, !dbg !107
  %12 = load ptr, ptr %arg.self, align 8, !dbg !107
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %12, i32 0, i32 2, !dbg !107
  %14 = load i32, ptr %13, align 4, !dbg !107
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !110
  store ptr %15, ptr %7, align 8, !dbg !110
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17837SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !111 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !114, metadata !DIExpression()), !dbg !115
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !115
  call void @"_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17807SaA1_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !115
  %2 = load ptr, ptr %arg.self, align 8, !dbg !115
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %2, i32 0, i32 1, !dbg !115
  %4 = load i32, ptr %3, align 4, !dbg !115
  store i32 0, ptr %3, align 4, !dbg !116
  %5 = load ptr, ptr %arg.self, align 8, !dbg !115
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %5, i32 0, i32 2, !dbg !115
  %7 = load i32, ptr %6, align 4, !dbg !115
  store i32 10, ptr %6, align 4, !dbg !117
  %8 = load ptr, ptr %arg.self, align 8, !dbg !115
  %9 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %8, i32 0, i32 3, !dbg !115
  %10 = load i32, ptr %9, align 4, !dbg !115
  store i32 0, ptr %9, align 4, !dbg !118
  %11 = load ptr, ptr %arg.self, align 8, !dbg !115
  %12 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %11, i32 0, i32 4, !dbg !115
  %13 = load ptr, ptr %12, align 8, !dbg !115
  %14 = load ptr, ptr %arg.self, align 8, !dbg !115
  %15 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %14, i32 0, i32 2, !dbg !115
  %16 = load i32, ptr %15, align 4, !dbg !115
  %17 = call ptr @sn.ua.alloc(i32 %16) #6, !dbg !119
  store ptr %17, ptr %12, align 8, !dbg !119
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4nextCv17812SaA1_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17757ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !120 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !125, metadata !DIExpression()), !dbg !126
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17807SaA1_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !127 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !130, metadata !DIExpression()), !dbg !131
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !131
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %1, i32 0, i32 1, !dbg !131
  %3 = load i32, ptr %2, align 4, !dbg !131
  store i32 0, ptr %2, align 4, !dbg !132
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&9to_stringCv17377SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #2 personality ptr @sn.eh.personality !dbg !133 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !134, metadata !DIExpression()), !dbg !135
  %var.base = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.base, metadata !136, metadata !DIExpression()), !dbg !137
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %4 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %5, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.10), !dbg !138
  %6 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !138
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %6, ptr %var.base, align 8, !dbg !138
  %7 = load ptr, ptr %arg.self, align 8, !dbg !139
  %8 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.self, align 8, !dbg !139
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, ptr %var.base, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %8) #5, !dbg !140
  %9 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, align 8, !dbg !140
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17339SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %3, ptr @.str.11) #5, !dbg !141
  %10 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !141
  ret void, !dbg !141
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %2) #2 personality ptr @sn.eh.personality !dbg !142 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !145, metadata !DIExpression()), !dbg !146
  %arg.other = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %2, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !147, metadata !DIExpression()), !dbg !146
  %var.result = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.result, metadata !148, metadata !DIExpression()), !dbg !149
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = load ptr, ptr %arg.self, align 8, !dbg !146
  %5 = load ptr, ptr %arg.self, align 8, !dbg !146
  %6 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %5, i32 0, i32 4, !dbg !146
  %7 = load ptr, ptr %6, align 8, !dbg !146
  %8 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !146
  %9 = load ptr, ptr %8, align 8, !dbg !146
  %10 = load ptr, ptr %arg.self, align 8, !dbg !146
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %10, i32 0, i32 3, !dbg !146
  %12 = load i32, ptr %11, align 4, !dbg !146
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !146
  %14 = load i32, ptr %13, align 4, !dbg !146
  %15 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, ptr noundef nonnull align 8 dereferenceable(64) %7, ptr noundef nonnull align 8 dereferenceable(64) %9, i32 %12, i32 %14), !dbg !150
  store ptr %15, ptr %var.result, align 8, !dbg !150
  %16 = load ptr, ptr %var.result, align 8, !dbg !151
  %17 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %17, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %16), !dbg !152
  %18 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !152
  ret void, !dbg !152
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17339SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, ptr %2) #2 personality ptr @sn.eh.personality !dbg !153 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !156, metadata !DIExpression()), !dbg !157
  %arg.other = alloca ptr, align 8
  store ptr %2, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !158, metadata !DIExpression()), !dbg !157
  %var.len1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len1, metadata !159, metadata !DIExpression()), !dbg !160
  %var.len2 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len2, metadata !161, metadata !DIExpression()), !dbg !162
  %var.res = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.res, metadata !163, metadata !DIExpression()), !dbg !164
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = load ptr, ptr %arg.self, align 8, !dbg !157
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %4, i32 0, i32 3, !dbg !157
  %6 = load i32, ptr %5, align 4, !dbg !157
  store i32 %6, ptr %var.len1, align 4, !dbg !157
  %7 = load ptr, ptr %arg.other, align 8, !dbg !165
  %8 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %7), !dbg !166
  store i32 %8, ptr %var.len2, align 4, !dbg !166
  %9 = load ptr, ptr %arg.self, align 8, !dbg !157
  %10 = load ptr, ptr %arg.self, align 8, !dbg !157
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %10, i32 0, i32 4, !dbg !157
  %12 = load ptr, ptr %11, align 8, !dbg !157
  %13 = load ptr, ptr %arg.other, align 8, !dbg !167
  %14 = load i32, ptr %var.len1, align 4, !dbg !168
  %15 = load i32, ptr %var.len2, align 4, !dbg !169
  %16 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %9, ptr noundef nonnull align 8 dereferenceable(64) %12, ptr noundef nonnull align 8 dereferenceable(64) %13, i32 %14, i32 %15), !dbg !170
  store ptr %16, ptr %var.res, align 8, !dbg !170
  %17 = load ptr, ptr %var.res, align 8, !dbg !171
  %18 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %18, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %17), !dbg !172
  %19 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !172
  ret void, !dbg !172
}

; Function Attrs: noinline
define internal ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3, i32 %4) #0 personality ptr @sn.eh.personality !dbg !173 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !176, metadata !DIExpression()), !dbg !177
  %arg.str1 = alloca ptr, align 8
  store ptr %1, ptr %arg.str1, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.str1, metadata !178, metadata !DIExpression()), !dbg !177
  %arg.str2 = alloca ptr, align 8
  store ptr %2, ptr %arg.str2, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.str2, metadata !179, metadata !DIExpression()), !dbg !177
  %arg.len1 = alloca i32, align 4
  store i32 %3, ptr %arg.len1, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.len1, metadata !180, metadata !DIExpression()), !dbg !177
  %arg.len2 = alloca i32, align 4
  store i32 %4, ptr %arg.len2, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.len2, metadata !181, metadata !DIExpression()), !dbg !177
  %var.sum = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.sum, metadata !182, metadata !DIExpression()), !dbg !183
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !184, metadata !DIExpression()), !dbg !185
  br label %body

body:                                             ; preds = %entry
  %5 = load i32, ptr %arg.len1, align 4, !dbg !177
  %6 = load i32, ptr %arg.len2, align 4, !dbg !186
  %7 = add i32 %5, %6, !dbg !186
  store i32 %7, ptr %var.sum, align 4, !dbg !186
  %8 = load i32, ptr %var.sum, align 4, !dbg !187
  %9 = call ptr @malloc(i32 %8), !dbg !188
  store ptr %9, ptr %var.buffer, align 8, !dbg !188
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !189
  %11 = load ptr, ptr %arg.str1, align 8, !dbg !190
  %12 = load i32, ptr %arg.len1, align 4, !dbg !191
  call void @memcpy(ptr %10, ptr %11, i32 %12), !dbg !192
  %13 = load ptr, ptr %var.buffer, align 8, !dbg !185
  %14 = load i32, ptr %arg.len1, align 4, !dbg !193
  %15 = call ptr @"_$SNT4char&3#PlCv16965SaA1T4char.rA2T3i32FnE"(ptr %13, i32 %14) #6, !dbg !194
  %16 = load ptr, ptr %arg.str2, align 8, !dbg !195
  %17 = load i32, ptr %arg.len2, align 4, !dbg !196
  call void @memcpy(ptr %15, ptr %16, i32 %17), !dbg !197
  %18 = load ptr, ptr %var.buffer, align 8, !dbg !198
  ret ptr %18, !dbg !198
}

; Function Attrs: noinline
define internal void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4nextCv17312SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !199 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !204, metadata !DIExpression()), !dbg !205
  %var.iter = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %0, metadata !206, metadata !DIExpression()), !dbg !208
  %2 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  %3 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = load ptr, ptr %arg.self, align 8, !dbg !205
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !205
  %6 = load i32, ptr %5, align 4, !dbg !205
  %7 = load ptr, ptr %arg.self, align 8, !dbg !205
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 1, !dbg !205
  %9 = load i32, ptr %8, align 4, !dbg !205
  %10 = add i32 %9, 1, !dbg !209
  store i32 %10, ptr %5, align 4, !dbg !209
  %11 = load ptr, ptr %arg.self, align 8, !dbg !205
  %12 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %11, i32 0, i32 1, !dbg !205
  %13 = load i32, ptr %12, align 4, !dbg !205
  %14 = load ptr, ptr %arg.self, align 8, !dbg !205
  %15 = call i32 @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&3endCv17308SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %14) #5, !dbg !210
  %16 = icmp sge i32 %13, %15, !dbg !210
  br i1 %16, label %17, label %19, !dbg !210

17:                                               ; preds = %body
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&7invalidCv17238SaFnE"(ptr %0) #5, !dbg !211
  %18 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !211
  ret void, !dbg !211

19:                                               ; preds = %body
  br label %20, !dbg !211

20:                                               ; preds = %19
  %21 = load ptr, ptr %arg.self, align 8, !dbg !205
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 1, !dbg !205
  %23 = load i32, ptr %22, align 4, !dbg !205
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5validCv17240SaA1T3i32FnE"(ptr %3, i32 %23) #5, !dbg !212
  %24 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %3, align 4, !dbg !212
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %24, ptr %0, align 4, !dbg !212
  %25 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !213
  ret void, !dbg !213
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&3endCv17308SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !214 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !217, metadata !DIExpression()), !dbg !218
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !218
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !218
  %3 = load i32, ptr %2, align 4, !dbg !218
  ret i32 %3, !dbg !218
}

; Function Attrs: noinline
define internal void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) #0 personality ptr @sn.eh.personality !dbg !219 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !222, metadata !DIExpression()), !dbg !223
  %arg.start = alloca i32, align 4
  store i32 %1, ptr %arg.start, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.start, metadata !224, metadata !DIExpression()), !dbg !223
  %arg.end = alloca i32, align 4
  store i32 %2, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !225, metadata !DIExpression()), !dbg !223
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !223
  call void @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4#NwCCv17255SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !223
  %4 = load ptr, ptr %arg.self, align 8, !dbg !223
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !223
  %6 = load i32, ptr %5, align 4, !dbg !223
  store i32 0, ptr %5, align 4, !dbg !226
  %7 = load ptr, ptr %arg.self, align 8, !dbg !223
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 2, !dbg !223
  %9 = load i32, ptr %8, align 4, !dbg !223
  store i32 0, ptr %8, align 4, !dbg !227
  %10 = load ptr, ptr %arg.self, align 8, !dbg !223
  %11 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 2, !dbg !223
  %12 = load i32, ptr %11, align 4, !dbg !223
  %13 = load i32, ptr %arg.start, align 4, !dbg !228
  store i32 %13, ptr %11, align 4, !dbg !228
  %14 = load ptr, ptr %arg.self, align 8, !dbg !223
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 3, !dbg !223
  %16 = load i32, ptr %15, align 4, !dbg !223
  %17 = load i32, ptr %arg.end, align 4, !dbg !229
  store i32 %17, ptr %15, align 4, !dbg !229
  %18 = load ptr, ptr %arg.self, align 8, !dbg !223
  %19 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 1, !dbg !223
  %20 = load i32, ptr %19, align 4, !dbg !223
  %21 = load ptr, ptr %arg.self, align 8, !dbg !223
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 2, !dbg !223
  %23 = load i32, ptr %22, align 4, !dbg !223
  %24 = sub i32 %23, 1, !dbg !230
  store i32 %24, ptr %19, align 4, !dbg !230
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4nextCv17260SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !231 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !235, metadata !DIExpression()), !dbg !236
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4#NwCCv17255SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !237 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !240, metadata !DIExpression()), !dbg !241
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !241
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17204ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !241
  %3 = load i32, ptr %2, align 4, !dbg !241
  store i32 0, ptr %2, align 4, !dbg !242
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5validCv17240SaA1T3i32FnE"(ptr sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") %0, i32 %1) #2 personality ptr @sn.eh.personality !dbg !243 {
entry:
  %arg.val = alloca i32, align 4
  store i32 %1, ptr %arg.val, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !246, metadata !DIExpression()), !dbg !247
  %2 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.val, align 4, !dbg !248
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17219SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %3), !dbg !249
  %4 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !249
  ret void, !dbg !249
}

; Function Attrs: alwaysinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&7invalidCv17238SaFnE"(ptr sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") %0) #2 personality ptr @sn.eh.personality !dbg !250 {
entry:
  %1 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17213SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !253
  %2 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !253
  ret void, !dbg !253
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&8is_validCv17234SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !254 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !259, metadata !DIExpression()), !dbg !260
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !260
  %2 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !260
  %3 = load i1, ptr %2, align 1, !dbg !260
  ret i1 %3, !dbg !260
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !261 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !264, metadata !DIExpression()), !dbg !265
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !265
  %2 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !265
  %3 = load i1, ptr %2, align 1, !dbg !265
  %4 = icmp eq i1 %3, false, !dbg !265
  br i1 %4, label %5, label %8, !dbg !265

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !266
  call void @"_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.12), !dbg !266
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !266
  call void @sn.eh.throw(ptr %7), !dbg !266
  br label %9, !dbg !266

8:                                                ; preds = %body
  br label %9, !dbg !266

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !265
  %11 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 1, !dbg !265
  %12 = load i32, ptr %11, align 4, !dbg !265
  ret i32 %12, !dbg !265
}

; Function Attrs: noinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17219SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !267 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !270, metadata !DIExpression()), !dbg !271
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !272, metadata !DIExpression()), !dbg !271
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !271
  %3 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 0, !dbg !271
  %4 = load i1, ptr %3, align 1, !dbg !271
  store i1 false, ptr %3, align 1, !dbg !273
  %5 = load ptr, ptr %arg.self, align 8, !dbg !271
  %6 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 1, !dbg !271
  %7 = load i32, ptr %6, align 4, !dbg !271
  %8 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17225SaFnE"() #5, !dbg !274
  store i32 %8, ptr %6, align 4, !dbg !274
  %9 = load ptr, ptr %arg.self, align 8, !dbg !271
  %10 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 1, !dbg !271
  %11 = load i32, ptr %10, align 4, !dbg !271
  %12 = load i32, ptr %arg.value, align 4, !dbg !275
  store i32 %12, ptr %10, align 4, !dbg !275
  %13 = load ptr, ptr %arg.self, align 8, !dbg !271
  %14 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 0, !dbg !271
  %15 = load i1, ptr %14, align 1, !dbg !271
  store i1 true, ptr %14, align 1, !dbg !276
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17213SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !277 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !280, metadata !DIExpression()), !dbg !281
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !281
  %2 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !281
  %3 = load i1, ptr %2, align 1, !dbg !281
  store i1 false, ptr %2, align 1, !dbg !282
  %4 = load ptr, ptr %arg.self, align 8, !dbg !281
  %5 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !281
  %6 = load i32, ptr %5, align 4, !dbg !281
  %7 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17217SaFnE"() #5, !dbg !283
  store i32 %7, ptr %5, align 4, !dbg !283
  ret void
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !284 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !287, metadata !DIExpression()), !dbg !288
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !288
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %1, i32 0, i32 4, !dbg !288
  %3 = load ptr, ptr %2, align 8, !dbg !288
  ret ptr %3, !dbg !288
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4sizeCv17189SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !289 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !292, metadata !DIExpression()), !dbg !293
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !293
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %1, i32 0, i32 3, !dbg !293
  %3 = load i32, ptr %2, align 4, !dbg !293
  ret i32 %3, !dbg !293
}

; Function Attrs: noinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !294 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !297, metadata !DIExpression()), !dbg !298
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !299, metadata !DIExpression()), !dbg !298
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !298
  call void @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4#NwCCv17115SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !298
  %3 = load ptr, ptr %arg.self, align 8, !dbg !298
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !298
  %5 = load i32, ptr %4, align 4, !dbg !298
  store i32 0, ptr %4, align 4, !dbg !300
  %6 = load ptr, ptr %arg.self, align 8, !dbg !298
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !298
  %8 = load i32, ptr %7, align 4, !dbg !298
  store i32 10, ptr %7, align 4, !dbg !301
  %9 = load ptr, ptr %arg.self, align 8, !dbg !298
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !298
  %11 = load i32, ptr %10, align 4, !dbg !298
  store i32 0, ptr %10, align 4, !dbg !302
  %12 = load ptr, ptr %arg.self, align 8, !dbg !298
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !298
  %14 = load ptr, ptr %13, align 8, !dbg !298
  store ptr @.str.15, ptr %13, align 8, !dbg !303
  %15 = load ptr, ptr %arg.self, align 8, !dbg !298
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !298
  %17 = load ptr, ptr %16, align 8, !dbg !298
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !304
  store ptr %18, ptr %16, align 8, !dbg !304
  %19 = load ptr, ptr %arg.self, align 8, !dbg !298
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %19, i32 0, i32 3, !dbg !298
  %21 = load i32, ptr %20, align 4, !dbg !298
  %22 = load ptr, ptr %arg.buffer, align 8, !dbg !305
  %23 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %22), !dbg !306
  store i32 %23, ptr %20, align 4, !dbg !306
  %24 = load ptr, ptr %arg.self, align 8, !dbg !298
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !298
  %26 = load i32, ptr %25, align 4, !dbg !298
  %27 = load ptr, ptr %arg.self, align 8, !dbg !298
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %27, i32 0, i32 3, !dbg !298
  %29 = load i32, ptr %28, align 4, !dbg !298
  %30 = add i32 %29, 10, !dbg !307
  store i32 %30, ptr %25, align 4, !dbg !307
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4nextCv17120SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17033ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !308 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !313, metadata !DIExpression()), !dbg !314
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4#NwCCv17115SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !315 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !318, metadata !DIExpression()), !dbg !319
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !319
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17032ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !319
  %3 = load i32, ptr %2, align 4, !dbg !319
  store i32 0, ptr %2, align 4, !dbg !320
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !321 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !326, metadata !DIExpression()), !dbg !327
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !328, metadata !DIExpression()), !dbg !327
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !327
  %3 = getelementptr inbounds %"class._$SN&9ExceptionCv17060ClsE", ptr %2, i32 0, i32 0, !dbg !327
  %4 = load ptr, ptr %3, align 8, !dbg !327
  %5 = load ptr, ptr %arg.m, align 8, !dbg !329
  store ptr %5, ptr %3, align 8, !dbg !329
  ret void
}

; Function Attrs: noinline
declare noalias noundef nonnull ptr @sn.alloca(i32) #0

; Function Attrs: noinline nounwind
declare noalias noundef nonnull ptr @sn.eh.create(ptr, i32) #3

; Function Attrs: noinline
declare void @sn.eh.throw(ptr) #0

; Function Attrs: alwaysinline
define internal void @"_$SNT4char&9to_stringCv17422SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #2 personality ptr @sn.eh.personality !dbg !330 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !333, metadata !DIExpression()), !dbg !334
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !335
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %4, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !336
  %5 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !336
  ret void, !dbg !336
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv17926SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(%"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0) #2 personality ptr @sn.eh.personality !dbg !337 {
entry:
  %arg.msg = alloca %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  store %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !341, metadata !DIExpression()), !dbg !342
  br label %body

body:                                             ; preds = %entry
  %1 = load %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %arg.msg, align 8, !dbg !343
  %2 = call i32 @"_$SN@sn.Core.System&5printCv17930SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEA2T4char.rFnE"(%"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.22) #5, !dbg !344
  ret i32 %2, !dbg !344
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv17930SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEA2T4char.rFnE"(%"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !345 {
entry:
  %arg.msg = alloca %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  store %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !348, metadata !DIExpression()), !dbg !349
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !350, metadata !DIExpression()), !dbg !349
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !351, metadata !DIExpression()), !dbg !352
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %arg.msg, align 8, !dbg !353
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17937SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(ptr sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") %2, %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %3) #5, !dbg !354
  %4 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !354
  %5 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !354
  store ptr %5, ptr %var.m, align 8, !dbg !354
  %6 = load ptr, ptr %var.m, align 8, !dbg !355
  %7 = load ptr, ptr %arg.end, align 8, !dbg !356
  %8 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.23, ptr %6, ptr %7), !dbg !357
  ret i32 %8, !dbg !357
}

; Function Attrs: noinline
define i32 @main() #0 personality ptr @sn.eh.personality !dbg !358 {
entry:
  call void @sn.runtime.initialize()
  %var.a = alloca %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.a, metadata !359, metadata !DIExpression()), !dbg !360
  %0 = alloca %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  %1 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = getelementptr inbounds %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %4, align 8
  call void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17837SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !361
  %5 = load %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %0, align 8, !dbg !361
  store %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %5, ptr %var.a, align 8, !dbg !361
  call void @"_$SNT4char&9to_stringCv17422SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %1, ptr @.str.24) #5, !dbg !362
  %6 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %1, align 8, !dbg !362
  call void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17843SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !363
  call void @"_$SNT4char&9to_stringCv17422SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %2, ptr @.str.25) #5, !dbg !364
  %7 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !364
  call void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17843SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a, ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !365
  call void @"_$SNT4char&9to_stringCv17422SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %3, ptr @.str.26) #5, !dbg !366
  %8 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, align 8, !dbg !366
  call void @"_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17843SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a, ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !367
  %9 = load %"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %var.a, align 8, !dbg !368
  %10 = call i32 @"_$SN@sn.Core.System&7printlnCv17926SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(%"class._$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %9) #5, !dbg !369
  ret i32 0
}

; Function Attrs: alwaysinline nounwind
declare void @sn.runtime.initialize() #4

attributes #0 = { noinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #1 = { nocallback nofree noinline nosync nounwind speculatable willreturn memory(none) "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #2 = { alwaysinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #3 = { noinline nounwind "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #4 = { alwaysinline nounwind "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #5 = { alwaysinline }
attributes #6 = { noinline }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Snowball version 0.0.7", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "main.sn", directory: "tests")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 2, !"Snowball Compiler ID", i32 7}
!4 = !{i32 2, !"Snowball Compiler Version", [6 x i8] c"0.0.7\00"}
!5 = distinct !DISubprogram(name: "char::operator +", linkageName: "_$SNT4char&3#PlCv16965SaA1T4char.rA2T3i32FnE", scope: !6, file: !6, line: 8, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!6 = !DIFile(filename: "Preloads.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib/Internal")
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !9, !11}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed)
!11 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!12 = !{}
!13 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17225SaFnE", scope: !14, file: !14, line: 123, type: !15, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!14 = !DIFile(filename: "CLib.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!15 = !DISubroutineType(types: !16)
!16 = !{!11}
!17 = !DILocation(line: 124, column: 12, scope: !13)
!18 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17217SaFnE", scope: !14, file: !14, line: 123, type: !15, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!19 = !DILocation(line: 124, column: 12, scope: !18)
!20 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17937SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE", scope: !21, file: !21, line: 644, type: !22, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!21 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!22 = !DISubroutineType(types: !23)
!23 = !{!24, !26}
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::StringView<char>", scope: !21, file: !21, line: 514, baseType: !25, elements: !12)
!25 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<char>", scope: !21, file: !21, line: 230, elements: !12)
!26 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 392, baseType: !27, elements: !12)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 230, elements: !12)
!28 = !DILocalVariable(name: "buffer", arg: 2, scope: !20, file: !1, line: 644, type: !26)
!29 = !DILocation(line: 644, column: 15, scope: !20)
!30 = !DILocation(line: 645, column: 38, scope: !20)
!31 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::to_string", linkageName: "_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&9to_stringCv17940SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 473, type: !32, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!32 = !DISubroutineType(types: !33)
!33 = !{!24, !34}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 392, baseType: !27, elements: !12)
!36 = !DILocalVariable(name: "self", arg: 2, scope: !31, file: !1, line: 473, type: !34)
!37 = !DILocation(line: 473, column: 8, scope: !31)
!38 = !DILocalVariable(name: "result", scope: !31, file: !1, line: 474, type: !39)
!39 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::StringView<char>", scope: !21, file: !21, line: 514, baseType: !25, elements: !12)
!40 = !DILocation(line: 474, column: 15, scope: !31)
!41 = !DILocalVariable(name: "separator", scope: !31, file: !1, line: 475, type: !24)
!42 = !DILocation(line: 475, column: 11, scope: !31)
!43 = !DILocalVariable(name: "x", scope: !31, file: !1, line: 477, type: !44)
!44 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Range<i32>", scope: !21, file: !21, line: 319, baseType: !45, elements: !12)
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<i32>", scope: !21, file: !21, line: 230, elements: !12)
!46 = !DILocation(line: 477, column: 15, scope: !31)
!47 = !DILocalVariable(name: "a", scope: !31, file: !1, line: 478, type: !48)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Iter<i32>", scope: !21, file: !21, line: 262, elements: !12)
!49 = !DILocation(line: 478, column: 11, scope: !31)
!50 = !DILocalVariable(name: "b", scope: !31, file: !1, line: 479, type: !11)
!51 = !DILocation(line: 479, column: 11, scope: !31)
!52 = !DILocalVariable(name: "$iter", scope: !31, file: !1, line: 481, type: !44)
!53 = !DILocation(line: 481, column: 17, scope: !31)
!54 = !DILocalVariable(name: "$iter_value", scope: !31, file: !1, line: 481, type: !48)
!55 = !DILocalVariable(name: "i", scope: !31, file: !1, line: 481, type: !11)
!56 = !DILocation(line: 474, column: 28, scope: !31)
!57 = !DILocation(line: 475, column: 27, scope: !31)
!58 = !DILocation(line: 477, column: 20, scope: !31)
!59 = !DILocation(line: 478, column: 15, scope: !31)
!60 = !DILocation(line: 479, column: 15, scope: !31)
!61 = !DILocation(line: 482, column: 33, scope: !31)
!62 = !DILocation(line: 482, column: 9, scope: !31)
!63 = !DILocation(line: 483, column: 41, scope: !31)
!64 = !DILocation(line: 483, column: 33, scope: !31)
!65 = !DILocation(line: 483, column: 9, scope: !31)
!66 = !DILocation(line: 484, column: 48, scope: !31)
!67 = !DILocation(line: 484, column: 40, scope: !31)
!68 = !DILocation(line: 484, column: 27, scope: !31)
!69 = !DILocation(line: 484, column: 25, scope: !31)
!70 = !DILocation(line: 485, column: 31, scope: !31)
!71 = !DILocation(line: 489, column: 14, scope: !31)
!72 = !DILocation(line: 486, column: 29, scope: !31)
!73 = !DILocation(line: 486, column: 27, scope: !31)
!74 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17972SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 644, type: !75, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!75 = !DISubroutineType(types: !76)
!76 = !{!24, !77}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64)
!78 = !DILocalVariable(name: "buffer", arg: 2, scope: !74, file: !1, line: 644, type: !77)
!79 = !DILocation(line: 644, column: 15, scope: !74)
!80 = !DILocation(line: 645, column: 38, scope: !74)
!81 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::at", linkageName: "_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17867SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE", scope: !21, file: !21, line: 431, type: !82, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!82 = !DISubroutineType(types: !83)
!83 = !{!77, !34, !11}
!84 = !DILocalVariable(name: "self", arg: 1, scope: !81, file: !1, line: 431, type: !34)
!85 = !DILocation(line: 431, column: 8, scope: !81)
!86 = !DILocalVariable(name: "index", arg: 2, scope: !81, file: !1, line: 431, type: !11)
!87 = !DILocation(line: 433, column: 18, scope: !81)
!88 = !DILocation(line: 435, column: 19, scope: !81)
!89 = !DILocation(line: 437, column: 40, scope: !81)
!90 = !DILocation(line: 437, column: 14, scope: !81)
!91 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::push", linkageName: "_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17843SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 404, type: !92, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!92 = !DISubroutineType(types: !93)
!93 = !{null, !34, !77}
!94 = !DILocalVariable(name: "self", arg: 1, scope: !91, file: !1, line: 404, type: !34)
!95 = !DILocation(line: 404, column: 8, scope: !91)
!96 = !DILocalVariable(name: "value", arg: 2, scope: !91, file: !1, line: 404, type: !77)
!97 = !DILocation(line: 406, column: 24, scope: !91)
!98 = !DILocation(line: 408, column: 37, scope: !91)
!99 = !DILocation(line: 408, column: 9, scope: !91)
!100 = !DILocation(line: 410, column: 46, scope: !91)
!101 = !DILocation(line: 410, column: 7, scope: !91)
!102 = !DILocation(line: 411, column: 35, scope: !91)
!103 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::resize", linkageName: "_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&6resizeCv17848SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE", scope: !21, file: !21, line: 421, type: !104, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!104 = !DISubroutineType(types: !105)
!105 = !{null, !34, !11}
!106 = !DILocalVariable(name: "self", arg: 1, scope: !103, file: !1, line: 421, type: !34)
!107 = !DILocation(line: 421, column: 8, scope: !103)
!108 = !DILocalVariable(name: "capacity", arg: 2, scope: !103, file: !1, line: 421, type: !11)
!109 = !DILocation(line: 423, column: 23, scope: !103)
!110 = !DILocation(line: 424, column: 21, scope: !103)
!111 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::constructor", linkageName: "_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17837SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 398, type: !112, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!112 = !DISubroutineType(types: !113)
!113 = !{null, !34}
!114 = !DILocalVariable(name: "self", arg: 1, scope: !111, file: !1, line: 398, type: !34)
!115 = !DILocation(line: 398, column: 5, scope: !111)
!116 = !DILocation(line: 232, column: 31, scope: !111)
!117 = !DILocation(line: 494, column: 29, scope: !111)
!118 = !DILocation(line: 496, column: 27, scope: !111)
!119 = !DILocation(line: 399, column: 14, scope: !111)
!120 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>&>::next", linkageName: "_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4nextCv17812SaA1_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 245, type: !121, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!121 = !DISubroutineType(types: !122)
!122 = !{!123, !124}
!123 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 262, elements: !12)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64)
!125 = !DILocalVariable(name: "self", arg: 2, scope: !120, file: !1, line: 245, type: !124)
!126 = !DILocation(line: 245, column: 13, scope: !120)
!127 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>&>::constructor", linkageName: "_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17807SaA1_$SN&8IterableCv17756ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 240, type: !128, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!128 = !DISubroutineType(types: !129)
!129 = !{null, !124}
!130 = !DILocalVariable(name: "self", arg: 1, scope: !127, file: !1, line: 240, type: !124)
!131 = !DILocation(line: 240, column: 5, scope: !127)
!132 = !DILocation(line: 232, column: 31, scope: !127)
!133 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::to_string", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&9to_stringCv17377SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 608, type: !75, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!134 = !DILocalVariable(name: "self", arg: 2, scope: !133, file: !1, line: 608, type: !77)
!135 = !DILocation(line: 608, column: 8, scope: !133)
!136 = !DILocalVariable(name: "base", scope: !133, file: !1, line: 610, type: !24)
!137 = !DILocation(line: 610, column: 11, scope: !133)
!138 = !DILocation(line: 610, column: 22, scope: !133)
!139 = !DILocation(line: 611, column: 22, scope: !133)
!140 = !DILocation(line: 611, column: 19, scope: !133)
!141 = !DILocation(line: 611, column: 27, scope: !133)
!142 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator +", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE", scope: !21, file: !21, line: 599, type: !143, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!143 = !DISubroutineType(types: !144)
!144 = !{!24, !77, !24}
!145 = !DILocalVariable(name: "self", arg: 2, scope: !142, file: !1, line: 599, type: !77)
!146 = !DILocation(line: 599, column: 14, scope: !142)
!147 = !DILocalVariable(name: "other", arg: 3, scope: !142, file: !1, line: 599, type: !24)
!148 = !DILocalVariable(name: "result", scope: !142, file: !1, line: 601, type: !9)
!149 = !DILocation(line: 601, column: 11, scope: !142)
!150 = !DILocation(line: 601, column: 20, scope: !142)
!151 = !DILocation(line: 602, column: 23, scope: !142)
!152 = !DILocation(line: 602, column: 18, scope: !142)
!153 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator +", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17339SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !21, file: !21, line: 584, type: !154, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!154 = !DISubroutineType(types: !155)
!155 = !{!24, !77, !9}
!156 = !DILocalVariable(name: "self", arg: 2, scope: !153, file: !1, line: 584, type: !77)
!157 = !DILocation(line: 584, column: 14, scope: !153)
!158 = !DILocalVariable(name: "other", arg: 3, scope: !153, file: !1, line: 584, type: !9)
!159 = !DILocalVariable(name: "len1", scope: !153, file: !1, line: 586, type: !11)
!160 = !DILocation(line: 586, column: 11, scope: !153)
!161 = !DILocalVariable(name: "len2", scope: !153, file: !1, line: 587, type: !11)
!162 = !DILocation(line: 587, column: 11, scope: !153)
!163 = !DILocalVariable(name: "res", scope: !153, file: !1, line: 588, type: !9)
!164 = !DILocation(line: 588, column: 11, scope: !153)
!165 = !DILocation(line: 587, column: 41, scope: !153)
!166 = !DILocation(line: 587, column: 18, scope: !153)
!167 = !DILocation(line: 588, column: 42, scope: !153)
!168 = !DILocation(line: 588, column: 49, scope: !153)
!169 = !DILocation(line: 588, column: 55, scope: !153)
!170 = !DILocation(line: 588, column: 17, scope: !153)
!171 = !DILocation(line: 589, column: 23, scope: !153)
!172 = !DILocation(line: 589, column: 18, scope: !153)
!173 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::concat", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE", scope: !21, file: !21, line: 657, type: !174, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!174 = !DISubroutineType(types: !175)
!175 = !{!9, !77, !9, !9, !11, !11}
!176 = !DILocalVariable(name: "self", arg: 1, scope: !173, file: !1, line: 657, type: !77)
!177 = !DILocation(line: 657, column: 8, scope: !173)
!178 = !DILocalVariable(name: "str1", arg: 2, scope: !173, file: !1, line: 657, type: !9)
!179 = !DILocalVariable(name: "str2", arg: 3, scope: !173, file: !1, line: 657, type: !9)
!180 = !DILocalVariable(name: "len1", arg: 4, scope: !173, file: !1, line: 657, type: !11)
!181 = !DILocalVariable(name: "len2", arg: 5, scope: !173, file: !1, line: 657, type: !11)
!182 = !DILocalVariable(name: "sum", scope: !173, file: !1, line: 660, type: !11)
!183 = !DILocation(line: 660, column: 11, scope: !173)
!184 = !DILocalVariable(name: "buffer", scope: !173, file: !1, line: 661, type: !9)
!185 = !DILocation(line: 661, column: 11, scope: !173)
!186 = !DILocation(line: 660, column: 24, scope: !173)
!187 = !DILocation(line: 661, column: 33, scope: !173)
!188 = !DILocation(line: 661, column: 20, scope: !173)
!189 = !DILocation(line: 662, column: 20, scope: !173)
!190 = !DILocation(line: 662, column: 36, scope: !173)
!191 = !DILocation(line: 662, column: 50, scope: !173)
!192 = !DILocation(line: 662, column: 7, scope: !173)
!193 = !DILocation(line: 663, column: 30, scope: !173)
!194 = !DILocation(line: 663, column: 28, scope: !173)
!195 = !DILocation(line: 663, column: 45, scope: !173)
!196 = !DILocation(line: 663, column: 59, scope: !173)
!197 = !DILocation(line: 663, column: 7, scope: !173)
!198 = !DILocation(line: 664, column: 14, scope: !173)
!199 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::next", linkageName: "_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4nextCv17312SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 358, type: !200, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!200 = !DISubroutineType(types: !201)
!201 = !{!48, !202}
!202 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64)
!203 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Range<i32>", scope: !21, file: !21, line: 319, baseType: !45, elements: !12)
!204 = !DILocalVariable(name: "self", arg: 2, scope: !199, file: !1, line: 358, type: !202)
!205 = !DILocation(line: 358, column: 13, scope: !199)
!206 = !DILocalVariable(name: "iter", scope: !199, file: !1, line: 365, type: !207)
!207 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<i32>", scope: !21, file: !21, line: 262, elements: !12)
!208 = !DILocation(line: 365, column: 11, scope: !199)
!209 = !DILocation(line: 360, column: 43, scope: !199)
!210 = !DILocation(line: 361, column: 29, scope: !199)
!211 = !DILocation(line: 363, column: 16, scope: !199)
!212 = !DILocation(line: 365, column: 18, scope: !199)
!213 = !DILocation(line: 366, column: 14, scope: !199)
!214 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::end", linkageName: "_$SN&5RangeCv17203ClsGStA1T3i32ClsE&3endCv17308SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 352, type: !215, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!215 = !DISubroutineType(types: !216)
!216 = !{!11, !202}
!217 = !DILocalVariable(name: "self", arg: 1, scope: !214, file: !1, line: 352, type: !202)
!218 = !DILocation(line: 352, column: 8, scope: !214)
!219 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::constructor", linkageName: "_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE", scope: !21, file: !21, line: 326, type: !220, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!220 = !DISubroutineType(types: !221)
!221 = !{null, !202, !11, !11}
!222 = !DILocalVariable(name: "self", arg: 1, scope: !219, file: !1, line: 326, type: !202)
!223 = !DILocation(line: 326, column: 5, scope: !219)
!224 = !DILocalVariable(name: "start", arg: 2, scope: !219, file: !1, line: 326, type: !11)
!225 = !DILocalVariable(name: "end", arg: 3, scope: !219, file: !1, line: 326, type: !11)
!226 = !DILocation(line: 232, column: 31, scope: !219)
!227 = !DILocation(line: 375, column: 32, scope: !219)
!228 = !DILocation(line: 327, column: 23, scope: !219)
!229 = !DILocation(line: 327, column: 36, scope: !219)
!230 = !DILocation(line: 329, column: 37, scope: !219)
!231 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::next", linkageName: "_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4nextCv17260SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 245, type: !232, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!232 = !DISubroutineType(types: !233)
!233 = !{!207, !234}
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64)
!235 = !DILocalVariable(name: "self", arg: 2, scope: !231, file: !1, line: 245, type: !234)
!236 = !DILocation(line: 245, column: 13, scope: !231)
!237 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::constructor", linkageName: "_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4#NwCCv17255SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 240, type: !238, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!238 = !DISubroutineType(types: !239)
!239 = !{null, !234}
!240 = !DILocalVariable(name: "self", arg: 1, scope: !237, file: !1, line: 240, type: !234)
!241 = !DILocation(line: 240, column: 5, scope: !237)
!242 = !DILocation(line: 232, column: 31, scope: !237)
!243 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::valid", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&5validCv17240SaA1T3i32FnE", scope: !21, file: !21, line: 308, type: !244, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!244 = !DISubroutineType(types: !245)
!245 = !{!207, !11}
!246 = !DILocalVariable(name: "val", arg: 2, scope: !243, file: !1, line: 308, type: !11)
!247 = !DILocation(line: 308, column: 15, scope: !243)
!248 = !DILocation(line: 309, column: 40, scope: !243)
!249 = !DILocation(line: 309, column: 20, scope: !243)
!250 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::invalid", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&7invalidCv17238SaFnE", scope: !21, file: !21, line: 302, type: !251, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!251 = !DISubroutineType(types: !252)
!252 = !{!207}
!253 = !DILocation(line: 303, column: 20, scope: !250)
!254 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::is_valid", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&8is_validCv17234SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 295, type: !255, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!255 = !DISubroutineType(types: !256)
!256 = !{!257, !258}
!257 = !DIBasicType(name: "bool", size: 8, encoding: DW_ATE_signed)
!258 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !207, size: 64)
!259 = !DILocalVariable(name: "self", arg: 1, scope: !254, file: !1, line: 295, type: !258)
!260 = !DILocation(line: 295, column: 8, scope: !254)
!261 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::value", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 283, type: !262, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!262 = !DISubroutineType(types: !263)
!263 = !{!11, !258}
!264 = !DILocalVariable(name: "self", arg: 1, scope: !261, file: !1, line: 283, type: !258)
!265 = !DILocation(line: 283, column: 8, scope: !261)
!266 = !DILocation(line: 287, column: 19, scope: !261)
!267 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17219SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !21, file: !21, line: 277, type: !268, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!268 = !DISubroutineType(types: !269)
!269 = !{null, !258, !11}
!270 = !DILocalVariable(name: "self", arg: 1, scope: !267, file: !1, line: 277, type: !258)
!271 = !DILocation(line: 277, column: 5, scope: !267)
!272 = !DILocalVariable(name: "value", arg: 2, scope: !267, file: !1, line: 277, type: !11)
!273 = !DILocation(line: 264, column: 24, scope: !267)
!274 = !DILocation(line: 266, column: 33, scope: !267)
!275 = !DILocation(line: 277, column: 41, scope: !267)
!276 = !DILocation(line: 278, column: 14, scope: !267)
!277 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17213SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 272, type: !278, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!278 = !DISubroutineType(types: !279)
!279 = !{null, !258}
!280 = !DILocalVariable(name: "self", arg: 1, scope: !277, file: !1, line: 272, type: !258)
!281 = !DILocation(line: 272, column: 5, scope: !277)
!282 = !DILocation(line: 264, column: 24, scope: !277)
!283 = !DILocation(line: 266, column: 33, scope: !277)
!284 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 554, type: !285, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!285 = !DISubroutineType(types: !286)
!286 = !{!9, !77}
!287 = !DILocalVariable(name: "self", arg: 1, scope: !284, file: !1, line: 554, type: !77)
!288 = !DILocation(line: 554, column: 8, scope: !284)
!289 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::size", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4sizeCv17189SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 549, type: !290, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!290 = !DISubroutineType(types: !291)
!291 = !{!11, !77}
!292 = !DILocalVariable(name: "self", arg: 1, scope: !289, file: !1, line: 549, type: !77)
!293 = !DILocation(line: 549, column: 8, scope: !289)
!294 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !21, file: !21, line: 528, type: !295, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!295 = !DISubroutineType(types: !296)
!296 = !{null, !77, !9}
!297 = !DILocalVariable(name: "self", arg: 1, scope: !294, file: !1, line: 528, type: !77)
!298 = !DILocation(line: 528, column: 5, scope: !294)
!299 = !DILocalVariable(name: "buffer", arg: 2, scope: !294, file: !1, line: 528, type: !9)
!300 = !DILocation(line: 232, column: 31, scope: !294)
!301 = !DILocation(line: 615, column: 29, scope: !294)
!302 = !DILocation(line: 617, column: 27, scope: !294)
!303 = !DILocation(line: 619, column: 30, scope: !294)
!304 = !DILocation(line: 529, column: 23, scope: !294)
!305 = !DILocation(line: 529, column: 62, scope: !294)
!306 = !DILocation(line: 529, column: 39, scope: !294)
!307 = !DILocation(line: 530, column: 39, scope: !294)
!308 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::next", linkageName: "_$SN&8IterableCv17032ClsGStA1T4charClsE&4nextCv17120SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 245, type: !309, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!309 = !DISubroutineType(types: !310)
!310 = !{!311, !312}
!311 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<char>", scope: !21, file: !21, line: 262, elements: !12)
!312 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64)
!313 = !DILocalVariable(name: "self", arg: 2, scope: !308, file: !1, line: 245, type: !312)
!314 = !DILocation(line: 245, column: 13, scope: !308)
!315 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::constructor", linkageName: "_$SN&8IterableCv17032ClsGStA1T4charClsE&4#NwCCv17115SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 240, type: !316, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!316 = !DISubroutineType(types: !317)
!317 = !{null, !312}
!318 = !DILocalVariable(name: "self", arg: 1, scope: !315, file: !1, line: 240, type: !312)
!319 = !DILocation(line: 240, column: 5, scope: !315)
!320 = !DILocation(line: 232, column: 31, scope: !315)
!321 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::constructor", linkageName: "_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE", scope: !21, file: !21, line: 193, type: !322, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!322 = !DISubroutineType(types: !323)
!323 = !{null, !324, !9}
!324 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !325, size: 64)
!325 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Exception", scope: !21, file: !21, line: 187, elements: !12)
!326 = !DILocalVariable(name: "self", arg: 1, scope: !321, file: !1, line: 193, type: !324)
!327 = !DILocation(line: 193, column: 5, scope: !321)
!328 = !DILocalVariable(name: "m", arg: 2, scope: !321, file: !1, line: 193, type: !9)
!329 = !DILocation(line: 193, column: 31, scope: !321)
!330 = distinct !DISubprogram(name: "char::to_string", linkageName: "_$SNT4char&9to_stringCv17422SaA1T4char.rFnE", scope: !21, file: !21, line: 10, type: !331, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!331 = !DISubroutineType(types: !332)
!332 = !{!24, !9}
!333 = !DILocalVariable(name: "self", arg: 2, scope: !330, file: !1, line: 10, type: !9)
!334 = !DILocation(line: 10, column: 8, scope: !330)
!335 = !DILocation(line: 11, column: 27, scope: !330)
!336 = !DILocation(line: 11, column: 20, scope: !330)
!337 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv17926SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE", scope: !338, file: !338, line: 27, type: !339, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!338 = !DIFile(filename: "System.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!339 = !DISubroutineType(types: !340)
!340 = !{!11, !26}
!341 = !DILocalVariable(name: "msg", arg: 1, scope: !337, file: !1, line: 27, type: !26)
!342 = !DILocation(line: 27, column: 15, scope: !337)
!343 = !DILocation(line: 28, column: 20, scope: !337)
!344 = !DILocation(line: 28, column: 14, scope: !337)
!345 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv17930SaA1_$SN&6VectorCv17755ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEA2T4char.rFnE", scope: !338, file: !338, line: 16, type: !346, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!346 = !DISubroutineType(types: !347)
!347 = !{!11, !26, !9}
!348 = !DILocalVariable(name: "msg", arg: 1, scope: !345, file: !1, line: 16, type: !26)
!349 = !DILocation(line: 16, column: 15, scope: !345)
!350 = !DILocalVariable(name: "end", arg: 2, scope: !345, file: !1, line: 16, type: !9)
!351 = !DILocalVariable(name: "m", scope: !345, file: !1, line: 17, type: !9)
!352 = !DILocation(line: 17, column: 9, scope: !345)
!353 = !DILocation(line: 17, column: 26, scope: !345)
!354 = !DILocation(line: 17, column: 13, scope: !345)
!355 = !DILocation(line: 18, column: 33, scope: !345)
!356 = !DILocation(line: 18, column: 36, scope: !345)
!357 = !DILocation(line: 18, column: 12, scope: !345)
!358 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 19, type: !15, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!359 = !DILocalVariable(name: "a", scope: !358, file: !1, line: 21, type: !26)
!360 = !DILocation(line: 21, column: 13, scope: !358)
!361 = !DILocation(line: 21, column: 21, scope: !358)
!362 = !DILocation(line: 22, column: 13, scope: !358)
!363 = !DILocation(line: 22, column: 5, scope: !358)
!364 = !DILocation(line: 23, column: 13, scope: !358)
!365 = !DILocation(line: 23, column: 5, scope: !358)
!366 = !DILocation(line: 24, column: 13, scope: !358)
!367 = !DILocation(line: 24, column: 5, scope: !358)
!368 = !DILocation(line: 25, column: 21, scope: !358)
!369 = !DILocation(line: 25, column: 5, scope: !358)
Emitting object file... (/home/mauro/work/snowball/.sn/bin/out.o.so)
Running object pass manager...
Invoking linker (/usr/bin/ld with stdlib at .snowball)
Linker command: /usr/bin/ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/x86_64-linux-gnu/crtn.o -lm -lunwind -lc -L.snowball/lib -lSnowballRuntime /home/mauro/work/snowball/.sn/bin/out.o.so --eh-frame-hdr -o /home/mauro/work/snowball/.sn/bin/out.o --verbose 
GNU ld (GNU Binutils for Ubuntu) 2.38
  Supported emulations:
   elf_x86_64
   elf32_x86_64
   elf_i386
   elf_iamcu
   elf_l1om
   elf_k1om
   i386pep
   i386pe
using internal linker script:
==================================================
/* Script for -z combreloc -z separate-code */
/* Copyright (C) 2014-2022 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */
OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64",
	      "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SEARCH_DIR("=/usr/local/lib/x86_64-linux-gnu"); SEARCH_DIR("=/lib/x86_64-linux-gnu"); SEARCH_DIR("=/usr/lib/x86_64-linux-gnu"); SEARCH_DIR("=/usr/lib/x86_64-linux-gnu64"); SEARCH_DIR("=/usr/local/lib64"); SEARCH_DIR("=/lib64"); SEARCH_DIR("=/usr/lib64"); SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib"); SEARCH_DIR("=/usr/x86_64-linux-gnu/lib64"); SEARCH_DIR("=/usr/x86_64-linux-gnu/lib");
SECTIONS
{
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x400000)); . = SEGMENT_START("text-segment", 0x400000) + SIZEOF_HEADERS;
  .interp         : { *(.interp) }
  .note.gnu.build-id  : { *(.note.gnu.build-id) }
  .hash           : { *(.hash) }
  .gnu.hash       : { *(.gnu.hash) }
  .dynsym         : { *(.dynsym) }
  .dynstr         : { *(.dynstr) }
  .gnu.version    : { *(.gnu.version) }
  .gnu.version_d  : { *(.gnu.version_d) }
  .gnu.version_r  : { *(.gnu.version_r) }
  .rela.dyn       :
    {
      *(.rela.init)
      *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
      *(.rela.fini)
      *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
      *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
      *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
      *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
      *(.rela.ctors)
      *(.rela.dtors)
      *(.rela.got)
      *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
      *(.rela.ldata .rela.ldata.* .rela.gnu.linkonce.l.*)
      *(.rela.lbss .rela.lbss.* .rela.gnu.linkonce.lb.*)
      *(.rela.lrodata .rela.lrodata.* .rela.gnu.linkonce.lr.*)
      *(.rela.ifunc)
    }
  .rela.plt       :
    {
      *(.rela.plt)
      PROVIDE_HIDDEN (__rela_iplt_start = .);
      *(.rela.iplt)
      PROVIDE_HIDDEN (__rela_iplt_end = .);
    }
  .relr.dyn : { *(.relr.dyn) }
  . = ALIGN(CONSTANT (MAXPAGESIZE));
  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  }
  .plt            : { *(.plt) *(.iplt) }
.plt.got        : { *(.plt.got) }
.plt.sec        : { *(.plt.sec) }
  .text           :
  {
    *(.text.unlikely .text.*_unlikely .text.unlikely.*)
    *(.text.exit .text.exit.*)
    *(.text.startup .text.startup.*)
    *(.text.hot .text.hot.*)
    *(SORT(.text.sorted.*))
    *(.text .stub .text.* .gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf.em.  */
    *(.gnu.warning)
  }
  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  }
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  . = ALIGN(CONSTANT (MAXPAGESIZE));
  /* Adjust the address for the rodata segment.  We want to adjust up to
     the same address within the page on the next page up.  */
  . = SEGMENT_START("rodata-segment", ALIGN(CONSTANT (MAXPAGESIZE)) + (. & (CONSTANT (MAXPAGESIZE) - 1)));
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
  .rodata1        : { *(.rodata1) }
  .eh_frame_hdr   : { *(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*) }
  .eh_frame       : ONLY_IF_RO { KEEP (*(.eh_frame)) *(.eh_frame.*) }
  .gcc_except_table   : ONLY_IF_RO { *(.gcc_except_table .gcc_except_table.*) }
  .gnu_extab   : ONLY_IF_RO { *(.gnu_extab*) }
  /* These sections are generated by the Sun/Oracle C++ compiler.  */
  .exception_ranges   : ONLY_IF_RO { *(.exception_ranges*) }
  /* Adjust the address for the data segment.  We want to adjust up to
     the same address within the page on the next page up.  */
  . = DATA_SEGMENT_ALIGN (CONSTANT (MAXPAGESIZE), CONSTANT (COMMONPAGESIZE));
  /* Exception handling  */
  .eh_frame       : ONLY_IF_RW { KEEP (*(.eh_frame)) *(.eh_frame.*) }
  .gnu_extab      : ONLY_IF_RW { *(.gnu_extab) }
  .gcc_except_table   : ONLY_IF_RW { *(.gcc_except_table .gcc_except_table.*) }
  .exception_ranges   : ONLY_IF_RW { *(.exception_ranges*) }
  /* Thread Local Storage sections  */
  .tdata	  :
   {
     PROVIDE_HIDDEN (__tdata_start = .);
     *(.tdata .tdata.* .gnu.linkonce.td.*)
   }
  .tbss		  : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }
  .preinit_array    :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  }
  .init_array    :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  }
  .fini_array    :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  }
  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }
  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }
  .jcr            : { KEEP (*(.jcr)) }
  .data.rel.ro : { *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data.rel.ro .data.rel.ro.* .gnu.linkonce.d.rel.ro.*) }
  .dynamic        : { *(.dynamic) }
  .got            : { *(.got) *(.igot) }
  . = DATA_SEGMENT_RELRO_END (SIZEOF (.got.plt) >= 24 ? 24 : 0, .);
  .got.plt        : { *(.got.plt) *(.igot.plt) }
  .data           :
  {
    *(.data .data.* .gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
  }
  .data1          : { *(.data1) }
  _edata = .; PROVIDE (edata = .);
  . = .;
  __bss_start = .;
  .bss            :
  {
   *(.dynbss)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections.
      FIXME: Why do we need it? When there is no .bss section, we do not
      pad the .data section.  */
   . = ALIGN(. != 0 ? 64 / 8 : 1);
  }
  .lbss   :
  {
    *(.dynlbss)
    *(.lbss .lbss.* .gnu.linkonce.lb.*)
    *(LARGE_COMMON)
  }
  . = ALIGN(64 / 8);
  . = SEGMENT_START("ldata-segment", .);
  .lrodata   ALIGN(CONSTANT (MAXPAGESIZE)) + (. & (CONSTANT (MAXPAGESIZE) - 1)) :
  {
    *(.lrodata .lrodata.* .gnu.linkonce.lr.*)
  }
  .ldata   ALIGN(CONSTANT (MAXPAGESIZE)) + (. & (CONSTANT (MAXPAGESIZE) - 1)) :
  {
    *(.ldata .ldata.* .gnu.linkonce.l.*)
    . = ALIGN(. != 0 ? 64 / 8 : 1);
  }
  . = ALIGN(64 / 8);
  _end = .; PROVIDE (end = .);
  . = DATA_SEGMENT_END (.);
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  .gnu.build.attributes : { *(.gnu.build.attributes .gnu.build.attributes.*) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1.  */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions.  */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2.  */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2.  */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions.  */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3.  */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* DWARF 5.  */
  .debug_addr     0 : { *(.debug_addr) }
  .debug_line_str 0 : { *(.debug_line_str) }
  .debug_loclists 0 : { *(.debug_loclists) }
  .debug_macro    0 : { *(.debug_macro) }
  .debug_names    0 : { *(.debug_names) }
  .debug_rnglists 0 : { *(.debug_rnglists) }
  .debug_str_offsets 0 : { *(.debug_str_offsets) }
  .debug_sup      0 : { *(.debug_sup) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}


==================================================
/usr/bin/ld: mode elf_x86_64
attempt to open /usr/lib/x86_64-linux-gnu/crt1.o succeeded
/usr/lib/x86_64-linux-gnu/crt1.o
attempt to open /usr/lib/x86_64-linux-gnu/crti.o succeeded
/usr/lib/x86_64-linux-gnu/crti.o
attempt to open /usr/lib/x86_64-linux-gnu/crtn.o succeeded
/usr/lib/x86_64-linux-gnu/crtn.o
attempt to open .snowball/lib/libm.so failed
attempt to open .snowball/lib/libm.a failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libm.so failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libm.a failed
attempt to open /lib/x86_64-linux-gnu/libm.so succeeded
opened script file /lib/x86_64-linux-gnu/libm.so
/lib/x86_64-linux-gnu/libm.so
opened script file /lib/x86_64-linux-gnu/libm.so
attempt to open /lib/x86_64-linux-gnu/libm.so.6 succeeded
/lib/x86_64-linux-gnu/libm.so.6
attempt to open /lib/x86_64-linux-gnu/libmvec.so.1 succeeded
/lib/x86_64-linux-gnu/libmvec.so.1
/lib/x86_64-linux-gnu/libmvec.so.1
attempt to open .snowball/lib/libunwind.so failed
attempt to open .snowball/lib/libunwind.a failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libunwind.so failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libunwind.a failed
attempt to open /lib/x86_64-linux-gnu/libunwind.so succeeded
/lib/x86_64-linux-gnu/libunwind.so
attempt to open .snowball/lib/libc.so failed
attempt to open .snowball/lib/libc.a failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libc.so failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libc.a failed
attempt to open /lib/x86_64-linux-gnu/libc.so succeeded
opened script file /lib/x86_64-linux-gnu/libc.so
/lib/x86_64-linux-gnu/libc.so
opened script file /lib/x86_64-linux-gnu/libc.so
attempt to open /lib/x86_64-linux-gnu/libc.so.6 succeeded
/lib/x86_64-linux-gnu/libc.so.6
attempt to open /usr/lib/x86_64-linux-gnu/libc_nonshared.a succeeded
/usr/lib/x86_64-linux-gnu/libc_nonshared.a
attempt to open /lib64/ld-linux-x86-64.so.2 succeeded
/lib64/ld-linux-x86-64.so.2
/usr/lib/x86_64-linux-gnu/libc_nonshared.a
/lib64/ld-linux-x86-64.so.2
attempt to open .snowball/lib/libSnowballRuntime.so failed
attempt to open .snowball/lib/libSnowballRuntime.a failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libSnowballRuntime.so failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libSnowballRuntime.a failed
attempt to open /lib/x86_64-linux-gnu/libSnowballRuntime.so failed
attempt to open /lib/x86_64-linux-gnu/libSnowballRuntime.a failed
attempt to open /usr/lib/x86_64-linux-gnu/libSnowballRuntime.so failed
attempt to open /usr/lib/x86_64-linux-gnu/libSnowballRuntime.a failed
attempt to open /usr/lib/x86_64-linux-gnu64/libSnowballRuntime.so failed
attempt to open /usr/lib/x86_64-linux-gnu64/libSnowballRuntime.a failed
attempt to open /usr/local/lib64/libSnowballRuntime.so failed
attempt to open /usr/local/lib64/libSnowballRuntime.a failed
attempt to open /lib64/libSnowballRuntime.so failed
attempt to open /lib64/libSnowballRuntime.a failed
attempt to open /usr/lib64/libSnowballRuntime.so failed
attempt to open /usr/lib64/libSnowballRuntime.a failed
attempt to open /usr/local/lib/libSnowballRuntime.so succeeded
/usr/local/lib/libSnowballRuntime.so
attempt to open /home/mauro/work/snowball/.sn/bin/out.o.so succeeded
/home/mauro/work/snowball/.sn/bin/out.o.so
ld-linux-x86-64.so.2 needed by /lib/x86_64-linux-gnu/libm.so.6
found ld-linux-x86-64.so.2 at /lib64/ld-linux-x86-64.so.2
libstdc++.so.6 needed by /usr/local/lib/libSnowballRuntime.so
attempt to open /usr/lib/x86_64-linux-gnu/libfakeroot/libstdc++.so.6 failed
attempt to open /usr/local/lib/i386-linux-gnu/libstdc++.so.6 failed
attempt to open /usr/local/lib/i686-linux-gnu/libstdc++.so.6 failed
attempt to open /lib/i686-linux-gnu/libstdc++.so.6 failed
attempt to open /usr/lib/i686-linux-gnu/libstdc++.so.6 failed
attempt to open /usr/local/lib/libstdc++.so.6 failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libstdc++.so.6 failed
found libstdc++.so.6 at /lib/x86_64-linux-gnu/libstdc++.so.6
libgcc_s.so.1 needed by /usr/local/lib/libSnowballRuntime.so
attempt to open /usr/lib/x86_64-linux-gnu/libfakeroot/libgcc_s.so.1 failed
attempt to open /usr/local/lib/i386-linux-gnu/libgcc_s.so.1 failed
attempt to open /usr/local/lib/i686-linux-gnu/libgcc_s.so.1 failed
attempt to open /lib/i686-linux-gnu/libgcc_s.so.1 failed
attempt to open /usr/lib/i686-linux-gnu/libgcc_s.so.1 failed
attempt to open /usr/local/lib/libgcc_s.so.1 failed
attempt to open /usr/local/lib/x86_64-linux-gnu/libgcc_s.so.1 failed
found libgcc_s.so.1 at /lib/x86_64-linux-gnu/libgcc_s.so.1
Cleaning up object file... (/home/mauro/work/snowball/.sn/bin/out.o.so)
