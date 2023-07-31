Lexer: 0.000129s
Parser: 0.000685s
Lexer: 0.001288s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Parser: 0.003418s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Lexer: 0.000057s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Internal/Preloads.sn)
Parser: 0.000080s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Internal/Preloads.sn)
Lexer: 0.000356s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Parser: 0.000345s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Lexer: 0.000246s (/home/mauro/work/snowball/tests/option.sn)
Parser: 0.001142s (/home/mauro/work/snowball/tests/option.sn)
Lexer: 0.000205s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Optional.sn)
Parser: 0.000606s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Optional.sn)
Lexer: 0.000132s (/home/mauro/work/snowball/tests/vector.sn)
Parser: 0.000774s (/home/mauro/work/snowball/tests/vector.sn)
Lexer: 0.000096s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Parser: 0.000340s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Lexer: 0.001201s (/home/mauro/work/snowball/tests/chars.sn)
Parser: 0.004184s (/home/mauro/work/snowball/tests/chars.sn)
Lexer: 0.000579s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Parser: 0.002375s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Lexer: 0.000194s (/home/mauro/work/snowball/tests/cls.sn)
Parser: 0.001342s (/home/mauro/work/snowball/tests/cls.sn)
Lexer: 0.000085s (/home/mauro/work/snowball/tests/string.sn)
Parser: 0.000269s (/home/mauro/work/snowball/tests/string.sn)
Lexer: 0.000141s (/home/mauro/work/snowball/tests/macros.sn)
Parser: 0.000347s (/home/mauro/work/snowball/tests/macros.sn)
Lexer: 0.000260s (/home/mauro/work/snowball/tests/syntax.sn)
Parser: 0.000859s (/home/mauro/work/snowball/tests/syntax.sn)
Lexer: 0.000083s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Parser: 0.000364s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Lexer: 0.000227s (/home/mauro/work/snowball/tests/clib.sn)
Parser: 0.000934s (/home/mauro/work/snowball/tests/clib.sn)
Lexer: 0.000160s (/home/mauro/work/snowball/tests/tuples.sn)
Parser: 0.000502s (/home/mauro/work/snowball/tests/tuples.sn)
Lexer: 0.000254s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Tuples.sn)
Parser: 0.000497s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Tuples.sn)
Simplifier: 0.124057s
Passes: 0.000083s
TypeChecker: 0.000110s (Core::Internal::Preloads)
TypeChecker: 0.000024s (Core::CLib::c_string)
TypeChecker: 0.000145s (Core::CLib::__internal)
TypeChecker: 0.000098s (Core::CLib)
TypeChecker: 0.000019s (Core::_$core::Core::UA)
TypeChecker: 0.000003s (Core::_$core::Core::__internal)
TypeChecker: 0.001917s (Core::_$core::Core)
TypeChecker: 0.000089s (Core::_$core)
TypeChecker: 0.000004s (Core::Optional)
TypeChecker: 0.000002s (pkg::option::tests)
TypeChecker: 0.000002s (pkg::option)
TypeChecker: 0.000002s (Core::Assert)
TypeChecker: 0.000002s (pkg::vector::tests)
TypeChecker: 0.000002s (pkg::vector)
TypeChecker: 0.000066s (Core::Char)
TypeChecker: 0.000003s (pkg::chars::tests)
TypeChecker: 0.000003s (pkg::chars)
TypeChecker: 0.000039s (pkg::cls::test)
TypeChecker: 0.000004s (pkg::cls)
TypeChecker: 0.000002s (pkg::string::tests)
TypeChecker: 0.000002s (pkg::string)
TypeChecker: 0.000002s (pkg::macros::tests)
TypeChecker: 0.000002s (pkg::macros)
TypeChecker: 0.000055s (Core::System)
TypeChecker: 0.000004s (pkg::syntax::tests)
TypeChecker: 0.000002s (pkg::syntax)
TypeChecker: 0.000002s (pkg::clib::tests)
TypeChecker: 0.000002s (pkg::clib)
TypeChecker: 0.000002s (Core::Tuples)
TypeChecker: 0.000002s (pkg::tuples::tests)
TypeChecker: 0.000002s (pkg::tuples)
TypeChecker: 0.000067s ($main)
Emitting object file... (/home/mauro/work/snowball/.sn/bin/out.o.so)
Finished codegen, proceeding to verify module
Finished verifying module, proceeding to optimize module (if requested)
; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE" = type { ptr }
%"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE" = type { ptr, ptr }
%"vtable._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { ptr }
%"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE" = type { ptr, i32, i32, i32 }
%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" = type { i1, i32 }
%"class._$SN&4IterCv17760ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { i1, ptr }
%"class._$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = type { ptr, i32 }
%"class._$SN&8IterableCv17204ClsGStA1T3i32ClsE" = type { ptr, i32 }
%"class._$SN&4IterCv17033ClsGStA1T4charClsE" = type { i1, i8 }
%"class._$SN&8IterableCv17032ClsGStA1T4charClsE" = type { ptr, i32 }
%"class._$SN&9ExceptionCv17060ClsE" = type { ptr }

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE" = global %"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE" { ptr @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4nextCv17120SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE" }
@.str.5 = private unnamed_addr constant [3 x i8] c", \00", align 1
@"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE" = global %"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE" { ptr @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4nextCv17260SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE", ptr @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4nextCv17312SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE" }
@.str.6 = private unnamed_addr constant [11 x i8] c"result: %s\00", align 1
@.str.7 = private unnamed_addr constant [21 x i8] c"Index out of bounds.\00", align 1
@.str.9 = private unnamed_addr constant [2 x i8] c"\22\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"base: %s\0A\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c"\22\00", align 1
@.str.12 = private unnamed_addr constant [25 x i8] c"Invalid iterator access!\00", align 1
@.str.15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.22 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.23 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@"vtable._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" = global %"vtable._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" { ptr @"_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4nextCv17815SaA1_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE" }
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
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17940SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(ptr sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") %0, %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %1) #2 personality ptr @sn.eh.personality !dbg !20 {
entry:
  %arg.buffer = alloca %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  store %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !28, metadata !DIExpression()), !dbg !29
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  call void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&9to_stringCv17943SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr %arg.buffer), !dbg !30
  %3 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !30
  ret void, !dbg !30
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&9to_stringCv17943SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !31 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !36, metadata !DIExpression()), !dbg !37
  %var.result = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %0, metadata !38, metadata !DIExpression()), !dbg !40
  %var.separator = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.separator, metadata !41, metadata !DIExpression()), !dbg !42
  %"var.$iter" = alloca %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !43, metadata !DIExpression()), !dbg !46
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !47, metadata !DIExpression()), !dbg !46
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !49, metadata !DIExpression()), !dbg !46
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %4 = alloca %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", align 8
  %5 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  %6 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %7 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %8 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %9 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %10, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) @.str), !dbg !50
  %11 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !50
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %11, ptr %0, align 8, !dbg !50
  %12 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %12, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, ptr noundef nonnull align 8 dereferenceable(64) @.str.5), !dbg !51
  %13 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, align 8, !dbg !51
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %13, ptr %var.separator, align 8, !dbg !51
  %14 = load ptr, ptr %arg.self, align 8, !dbg !37
  %15 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %14, i32 0, i32 3, !dbg !37
  %16 = load i32, ptr %15, align 4, !dbg !37
  %17 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 0
  store ptr @"vtable._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %17, align 8
  call void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, i32 0, i32 %16), !dbg !46
  %18 = load %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, align 8, !dbg !46
  store %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE" %18, ptr %"var.$iter", align 8, !dbg !46
  %19 = load ptr, ptr %"var.$iter", align 8, !dbg !46
  %20 = getelementptr inbounds ptr, ptr %19, i32 1, !dbg !46
  %21 = load ptr, ptr %20, align 8, !dbg !46
  call void %21(ptr %5, ptr %"var.$iter"), !dbg !46
  %22 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %5, align 4, !dbg !46
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %22, ptr %"var.$iter_value", align 4, !dbg !46
  br label %23, !dbg !46

23:                                               ; preds = %46, %body
  %24 = call i1 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&8is_validCv17234SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #5, !dbg !46
  br i1 %24, label %25, label %38, !dbg !46

25:                                               ; preds = %23
  %26 = call i32 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #5, !dbg !46
  store i32 %26, ptr %var.i, align 4, !dbg !46
  %27 = load ptr, ptr %arg.self, align 8, !dbg !37
  %28 = load i32, ptr %var.i, align 4, !dbg !52
  %29 = call ptr @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17870SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %27, i32 %28), !dbg !53
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17963SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr %29) #5, !dbg !54
  %30 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %6, align 8, !dbg !54
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %7, ptr %0, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %30) #5, !dbg !55
  %31 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %7, align 8, !dbg !55
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %31, ptr %0, align 8, !dbg !55
  %32 = load i32, ptr %var.i, align 4, !dbg !46
  %33 = load ptr, ptr %arg.self, align 8, !dbg !37
  %34 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %33, i32 0, i32 3, !dbg !37
  %35 = load i32, ptr %34, align 4, !dbg !37
  %36 = sub i32 %35, 1, !dbg !56
  %37 = icmp ne i32 %32, %36, !dbg !56
  br i1 %37, label %42, label %45, !dbg !56

38:                                               ; preds = %23
  %39 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #5, !dbg !57
  %40 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.6, ptr %39), !dbg !58
  %41 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !59
  ret void, !dbg !59

42:                                               ; preds = %25
  %43 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %var.separator, align 8, !dbg !60
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %8, ptr %0, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %43) #5, !dbg !61
  %44 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %8, align 8, !dbg !61
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %44, ptr %0, align 8, !dbg !61
  br label %46, !dbg !61

45:                                               ; preds = %25
  br label %46, !dbg !61

46:                                               ; preds = %45, %42
  %47 = load ptr, ptr %"var.$iter", align 8, !dbg !46
  %48 = getelementptr inbounds ptr, ptr %47, i32 1, !dbg !46
  %49 = load ptr, ptr %48, align 8, !dbg !46
  call void %49(ptr %9, ptr %"var.$iter"), !dbg !46
  %50 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %9, align 4, !dbg !46
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %50, ptr %"var.$iter_value", align 4, !dbg !46
  br label %23, !dbg !46
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17963SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #2 personality ptr @sn.eh.personality !dbg !62 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !66, metadata !DIExpression()), !dbg !67
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.buffer, align 8, !dbg !67
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&9to_stringCv17377SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr %3) #5, !dbg !68
  %4 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !68
  ret void, !dbg !68
}

; Function Attrs: noinline
define internal ptr @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17870SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !69 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !72, metadata !DIExpression()), !dbg !73
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !74, metadata !DIExpression()), !dbg !73
  br label %body

body:                                             ; preds = %entry
  %2 = load i32, ptr %arg.index, align 4, !dbg !73
  %3 = icmp slt i32 %2, 0, !dbg !75
  %4 = load i32, ptr %arg.index, align 4, !dbg !73
  %5 = load ptr, ptr %arg.self, align 8, !dbg !73
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %5, i32 0, i32 3, !dbg !73
  %7 = load i32, ptr %6, align 4, !dbg !73
  %8 = icmp sge i32 %4, %7, !dbg !73
  %9 = or i1 %3, %8, !dbg !73
  br i1 %9, label %10, label %13, !dbg !73

10:                                               ; preds = %body
  %11 = call ptr @sn.alloca(i32 8), !dbg !76
  call void @"_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, ptr noundef nonnull align 8 dereferenceable(64) @.str.7), !dbg !76
  %12 = call ptr @sn.eh.create(ptr %11, i32 1000), !dbg !76
  call void @sn.eh.throw(ptr %12), !dbg !76
  br label %14, !dbg !76

13:                                               ; preds = %body
  br label %14, !dbg !76

14:                                               ; preds = %13, %10
  %15 = load ptr, ptr %arg.self, align 8, !dbg !73
  %16 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %15, i32 0, i32 4, !dbg !73
  %17 = load ptr, ptr %16, align 8, !dbg !73
  %18 = load i32, ptr %arg.index, align 4, !dbg !77
  %19 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18), !dbg !78
  ret ptr %19, !dbg !78
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17846SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !79 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !82, metadata !DIExpression()), !dbg !83
  %arg.value = alloca ptr, align 8
  store ptr %1, ptr %arg.value, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !84, metadata !DIExpression()), !dbg !83
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !83
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %2, i32 0, i32 3, !dbg !83
  %4 = load i32, ptr %3, align 4, !dbg !83
  %5 = add i32 %4, 1, !dbg !85
  %6 = load ptr, ptr %arg.self, align 8, !dbg !83
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %6, i32 0, i32 2, !dbg !83
  %8 = load i32, ptr %7, align 4, !dbg !83
  %9 = icmp sge i32 %5, %8, !dbg !83
  br i1 %9, label %10, label %16, !dbg !83

10:                                               ; preds = %body
  %11 = load ptr, ptr %arg.self, align 8, !dbg !83
  %12 = load ptr, ptr %arg.self, align 8, !dbg !83
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %12, i32 0, i32 2, !dbg !83
  %14 = load i32, ptr %13, align 4, !dbg !83
  %15 = add i32 %14, 10, !dbg !86
  call void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&6resizeCv17851SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %15), !dbg !87
  br label %17, !dbg !87

16:                                               ; preds = %body
  br label %17, !dbg !87

17:                                               ; preds = %16, %10
  %18 = load ptr, ptr %arg.self, align 8, !dbg !83
  %19 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %18, i32 0, i32 4, !dbg !83
  %20 = load ptr, ptr %19, align 8, !dbg !83
  %21 = load ptr, ptr %arg.self, align 8, !dbg !83
  %22 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %21, i32 0, i32 3, !dbg !83
  %23 = load i32, ptr %22, align 4, !dbg !83
  %24 = load ptr, ptr %arg.value, align 8, !dbg !88
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %23, ptr %24), !dbg !89
  %25 = load ptr, ptr %arg.self, align 8, !dbg !83
  %26 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %25, i32 0, i32 3, !dbg !83
  %27 = load i32, ptr %26, align 4, !dbg !83
  %28 = load ptr, ptr %arg.self, align 8, !dbg !83
  %29 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %28, i32 0, i32 3, !dbg !83
  %30 = load i32, ptr %29, align 4, !dbg !83
  %31 = add i32 %30, 1, !dbg !90
  store i32 %31, ptr %26, align 4, !dbg !90
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&6resizeCv17851SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !91 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !94, metadata !DIExpression()), !dbg !95
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !96, metadata !DIExpression()), !dbg !95
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !95
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %2, i32 0, i32 2, !dbg !95
  %4 = load i32, ptr %3, align 4, !dbg !95
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !97
  store i32 %5, ptr %3, align 4, !dbg !97
  %6 = load ptr, ptr %arg.self, align 8, !dbg !95
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %6, i32 0, i32 4, !dbg !95
  %8 = load ptr, ptr %7, align 8, !dbg !95
  %9 = load ptr, ptr %arg.self, align 8, !dbg !95
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %9, i32 0, i32 4, !dbg !95
  %11 = load ptr, ptr %10, align 8, !dbg !95
  %12 = load ptr, ptr %arg.self, align 8, !dbg !95
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %12, i32 0, i32 2, !dbg !95
  %14 = load i32, ptr %13, align 4, !dbg !95
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !98
  store ptr %15, ptr %7, align 8, !dbg !98
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17840SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !99 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !102, metadata !DIExpression()), !dbg !103
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !103
  call void @"_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17810SaA1_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !103
  %2 = load ptr, ptr %arg.self, align 8, !dbg !103
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %2, i32 0, i32 1, !dbg !103
  %4 = load i32, ptr %3, align 4, !dbg !103
  store i32 0, ptr %3, align 4, !dbg !104
  %5 = load ptr, ptr %arg.self, align 8, !dbg !103
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %5, i32 0, i32 2, !dbg !103
  %7 = load i32, ptr %6, align 4, !dbg !103
  store i32 10, ptr %6, align 4, !dbg !105
  %8 = load ptr, ptr %arg.self, align 8, !dbg !103
  %9 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %8, i32 0, i32 3, !dbg !103
  %10 = load i32, ptr %9, align 4, !dbg !103
  store i32 0, ptr %9, align 4, !dbg !106
  %11 = load ptr, ptr %arg.self, align 8, !dbg !103
  %12 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %11, i32 0, i32 4, !dbg !103
  %13 = load ptr, ptr %12, align 8, !dbg !103
  %14 = load ptr, ptr %arg.self, align 8, !dbg !103
  %15 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %14, i32 0, i32 2, !dbg !103
  %16 = load i32, ptr %15, align 4, !dbg !103
  %17 = call ptr @sn.ua.alloc(i32 %16) #6, !dbg !107
  store ptr %17, ptr %12, align 8, !dbg !107
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4nextCv17815SaA1_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17760ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !108 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !113, metadata !DIExpression()), !dbg !114
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17810SaA1_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !115 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !118, metadata !DIExpression()), !dbg !119
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !119
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %1, i32 0, i32 1, !dbg !119
  %3 = load i32, ptr %2, align 4, !dbg !119
  store i32 0, ptr %2, align 4, !dbg !120
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&9to_stringCv17377SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #2 personality ptr @sn.eh.personality !dbg !121 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !122, metadata !DIExpression()), !dbg !123
  %var.base = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.base, metadata !124, metadata !DIExpression()), !dbg !125
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %4 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %5, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.9), !dbg !126
  %6 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !126
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %6, ptr %var.base, align 8, !dbg !126
  %7 = load ptr, ptr %arg.self, align 8, !dbg !127
  %8 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.self, align 8, !dbg !127
  %9 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %arg.self) #5, !dbg !128
  %10 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.10, ptr %9), !dbg !129
  %11 = load ptr, ptr %arg.self, align 8, !dbg !130
  %12 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.self, align 8, !dbg !130
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, ptr %var.base, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %12) #5, !dbg !131
  %13 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, align 8, !dbg !131
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17339SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %3, ptr @.str.11) #5, !dbg !132
  %14 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !132
  ret void, !dbg !132
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1, %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %2) #2 personality ptr @sn.eh.personality !dbg !133 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !136, metadata !DIExpression()), !dbg !137
  %arg.other = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE" %2, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !138, metadata !DIExpression()), !dbg !137
  %var.result = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.result, metadata !139, metadata !DIExpression()), !dbg !140
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = load ptr, ptr %arg.self, align 8, !dbg !137
  %5 = load ptr, ptr %arg.self, align 8, !dbg !137
  %6 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %5, i32 0, i32 4, !dbg !137
  %7 = load ptr, ptr %6, align 8, !dbg !137
  %8 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !137
  %9 = load ptr, ptr %8, align 8, !dbg !137
  %10 = load ptr, ptr %arg.self, align 8, !dbg !137
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %10, i32 0, i32 3, !dbg !137
  %12 = load i32, ptr %11, align 4, !dbg !137
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !137
  %14 = load i32, ptr %13, align 4, !dbg !137
  %15 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, ptr noundef nonnull align 8 dereferenceable(64) %7, ptr noundef nonnull align 8 dereferenceable(64) %9, i32 %12, i32 %14), !dbg !141
  store ptr %15, ptr %var.result, align 8, !dbg !141
  %16 = load ptr, ptr %var.result, align 8, !dbg !142
  %17 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %17, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %16), !dbg !143
  %18 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !143
  ret void, !dbg !143
}

; Function Attrs: alwaysinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17339SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, ptr %2) #2 personality ptr @sn.eh.personality !dbg !144 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !147, metadata !DIExpression()), !dbg !148
  %arg.other = alloca ptr, align 8
  store ptr %2, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !149, metadata !DIExpression()), !dbg !148
  %var.len1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len1, metadata !150, metadata !DIExpression()), !dbg !151
  %var.len2 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len2, metadata !152, metadata !DIExpression()), !dbg !153
  %var.res = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.res, metadata !154, metadata !DIExpression()), !dbg !155
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = load ptr, ptr %arg.self, align 8, !dbg !148
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %4, i32 0, i32 3, !dbg !148
  %6 = load i32, ptr %5, align 4, !dbg !148
  store i32 %6, ptr %var.len1, align 4, !dbg !148
  %7 = load ptr, ptr %arg.other, align 8, !dbg !156
  %8 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %7), !dbg !157
  store i32 %8, ptr %var.len2, align 4, !dbg !157
  %9 = load ptr, ptr %arg.self, align 8, !dbg !148
  %10 = load ptr, ptr %arg.self, align 8, !dbg !148
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %10, i32 0, i32 4, !dbg !148
  %12 = load ptr, ptr %11, align 8, !dbg !148
  %13 = load ptr, ptr %arg.other, align 8, !dbg !158
  %14 = load i32, ptr %var.len1, align 4, !dbg !159
  %15 = load i32, ptr %var.len2, align 4, !dbg !160
  %16 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %9, ptr noundef nonnull align 8 dereferenceable(64) %12, ptr noundef nonnull align 8 dereferenceable(64) %13, i32 %14, i32 %15), !dbg !161
  store ptr %16, ptr %var.res, align 8, !dbg !161
  %17 = load ptr, ptr %var.res, align 8, !dbg !162
  %18 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %18, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %17), !dbg !163
  %19 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !163
  ret void, !dbg !163
}

; Function Attrs: noinline
define internal ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3, i32 %4) #0 personality ptr @sn.eh.personality !dbg !164 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !167, metadata !DIExpression()), !dbg !168
  %arg.str1 = alloca ptr, align 8
  store ptr %1, ptr %arg.str1, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.str1, metadata !169, metadata !DIExpression()), !dbg !168
  %arg.str2 = alloca ptr, align 8
  store ptr %2, ptr %arg.str2, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.str2, metadata !170, metadata !DIExpression()), !dbg !168
  %arg.len1 = alloca i32, align 4
  store i32 %3, ptr %arg.len1, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.len1, metadata !171, metadata !DIExpression()), !dbg !168
  %arg.len2 = alloca i32, align 4
  store i32 %4, ptr %arg.len2, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.len2, metadata !172, metadata !DIExpression()), !dbg !168
  %var.sum = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.sum, metadata !173, metadata !DIExpression()), !dbg !174
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !175, metadata !DIExpression()), !dbg !176
  br label %body

body:                                             ; preds = %entry
  %5 = load i32, ptr %arg.len1, align 4, !dbg !168
  %6 = load i32, ptr %arg.len2, align 4, !dbg !177
  %7 = add i32 %5, %6, !dbg !177
  store i32 %7, ptr %var.sum, align 4, !dbg !177
  %8 = load i32, ptr %var.sum, align 4, !dbg !178
  %9 = call ptr @malloc(i32 %8), !dbg !179
  store ptr %9, ptr %var.buffer, align 8, !dbg !179
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !180
  %11 = load ptr, ptr %arg.str1, align 8, !dbg !181
  %12 = load i32, ptr %arg.len1, align 4, !dbg !182
  call void @memcpy(ptr %10, ptr %11, i32 %12), !dbg !183
  %13 = load ptr, ptr %var.buffer, align 8, !dbg !176
  %14 = load i32, ptr %arg.len1, align 4, !dbg !184
  %15 = call ptr @"_$SNT4char&3#PlCv16965SaA1T4char.rA2T3i32FnE"(ptr %13, i32 %14) #6, !dbg !185
  %16 = load ptr, ptr %arg.str2, align 8, !dbg !186
  %17 = load i32, ptr %arg.len2, align 4, !dbg !187
  call void @memcpy(ptr %15, ptr %16, i32 %17), !dbg !188
  %18 = load ptr, ptr %var.buffer, align 8, !dbg !189
  ret ptr %18, !dbg !189
}

; Function Attrs: noinline
define internal void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4nextCv17312SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !190 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !195, metadata !DIExpression()), !dbg !196
  %var.iter = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %0, metadata !197, metadata !DIExpression()), !dbg !199
  %2 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  %3 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = load ptr, ptr %arg.self, align 8, !dbg !196
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !196
  %6 = load i32, ptr %5, align 4, !dbg !196
  %7 = load ptr, ptr %arg.self, align 8, !dbg !196
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 1, !dbg !196
  %9 = load i32, ptr %8, align 4, !dbg !196
  %10 = add i32 %9, 1, !dbg !200
  store i32 %10, ptr %5, align 4, !dbg !200
  %11 = load ptr, ptr %arg.self, align 8, !dbg !196
  %12 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %11, i32 0, i32 1, !dbg !196
  %13 = load i32, ptr %12, align 4, !dbg !196
  %14 = load ptr, ptr %arg.self, align 8, !dbg !196
  %15 = call i32 @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&3endCv17308SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %14) #5, !dbg !201
  %16 = icmp sge i32 %13, %15, !dbg !201
  br i1 %16, label %17, label %19, !dbg !201

17:                                               ; preds = %body
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&7invalidCv17238SaFnE"(ptr %0) #5, !dbg !202
  %18 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !202
  ret void, !dbg !202

19:                                               ; preds = %body
  br label %20, !dbg !202

20:                                               ; preds = %19
  %21 = load ptr, ptr %arg.self, align 8, !dbg !196
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 1, !dbg !196
  %23 = load i32, ptr %22, align 4, !dbg !196
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5validCv17240SaA1T3i32FnE"(ptr %3, i32 %23) #5, !dbg !203
  %24 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %3, align 4, !dbg !203
  store %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE" %24, ptr %0, align 4, !dbg !203
  %25 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !204
  ret void, !dbg !204
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&3endCv17308SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !205 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !208, metadata !DIExpression()), !dbg !209
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !209
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !209
  %3 = load i32, ptr %2, align 4, !dbg !209
  ret i32 %3, !dbg !209
}

; Function Attrs: noinline
define internal void @"_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) #0 personality ptr @sn.eh.personality !dbg !210 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !213, metadata !DIExpression()), !dbg !214
  %arg.start = alloca i32, align 4
  store i32 %1, ptr %arg.start, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.start, metadata !215, metadata !DIExpression()), !dbg !214
  %arg.end = alloca i32, align 4
  store i32 %2, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !216, metadata !DIExpression()), !dbg !214
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !214
  call void @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4#NwCCv17255SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !214
  %4 = load ptr, ptr %arg.self, align 8, !dbg !214
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !214
  %6 = load i32, ptr %5, align 4, !dbg !214
  store i32 0, ptr %5, align 4, !dbg !217
  %7 = load ptr, ptr %arg.self, align 8, !dbg !214
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 2, !dbg !214
  %9 = load i32, ptr %8, align 4, !dbg !214
  store i32 0, ptr %8, align 4, !dbg !218
  %10 = load ptr, ptr %arg.self, align 8, !dbg !214
  %11 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 2, !dbg !214
  %12 = load i32, ptr %11, align 4, !dbg !214
  %13 = load i32, ptr %arg.start, align 4, !dbg !219
  store i32 %13, ptr %11, align 4, !dbg !219
  %14 = load ptr, ptr %arg.self, align 8, !dbg !214
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 3, !dbg !214
  %16 = load i32, ptr %15, align 4, !dbg !214
  %17 = load i32, ptr %arg.end, align 4, !dbg !220
  store i32 %17, ptr %15, align 4, !dbg !220
  %18 = load ptr, ptr %arg.self, align 8, !dbg !214
  %19 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 1, !dbg !214
  %20 = load i32, ptr %19, align 4, !dbg !214
  %21 = load ptr, ptr %arg.self, align 8, !dbg !214
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17203ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 2, !dbg !214
  %23 = load i32, ptr %22, align 4, !dbg !214
  %24 = sub i32 %23, 1, !dbg !221
  store i32 %24, ptr %19, align 4, !dbg !221
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4nextCv17260SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !222 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !226, metadata !DIExpression()), !dbg !227
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4#NwCCv17255SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !228 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !231, metadata !DIExpression()), !dbg !232
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !232
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17204ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !232
  %3 = load i32, ptr %2, align 4, !dbg !232
  store i32 0, ptr %2, align 4, !dbg !233
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5validCv17240SaA1T3i32FnE"(ptr sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") %0, i32 %1) #2 personality ptr @sn.eh.personality !dbg !234 {
entry:
  %arg.val = alloca i32, align 4
  store i32 %1, ptr %arg.val, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !237, metadata !DIExpression()), !dbg !238
  %2 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.val, align 4, !dbg !239
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17219SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %3), !dbg !240
  %4 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !240
  ret void, !dbg !240
}

; Function Attrs: alwaysinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&7invalidCv17238SaFnE"(ptr sret(%"class._$SN&4IterCv17205ClsGStA1T3i32ClsE") %0) #2 personality ptr @sn.eh.personality !dbg !241 {
entry:
  %1 = alloca %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", align 8
  br label %body

body:                                             ; preds = %entry
  call void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17213SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !244
  %2 = load %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !244
  ret void, !dbg !244
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&8is_validCv17234SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !245 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !250, metadata !DIExpression()), !dbg !251
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !251
  %2 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !251
  %3 = load i1, ptr %2, align 1, !dbg !251
  ret i1 %3, !dbg !251
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !252 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !255, metadata !DIExpression()), !dbg !256
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !256
  %2 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !256
  %3 = load i1, ptr %2, align 1, !dbg !256
  %4 = icmp eq i1 %3, false, !dbg !256
  br i1 %4, label %5, label %8, !dbg !256

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !257
  call void @"_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.12), !dbg !257
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !257
  call void @sn.eh.throw(ptr %7), !dbg !257
  br label %9, !dbg !257

8:                                                ; preds = %body
  br label %9, !dbg !257

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !256
  %11 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 1, !dbg !256
  %12 = load i32, ptr %11, align 4, !dbg !256
  ret i32 %12, !dbg !256
}

; Function Attrs: noinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17219SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !258 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !261, metadata !DIExpression()), !dbg !262
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !263, metadata !DIExpression()), !dbg !262
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !262
  %3 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 0, !dbg !262
  %4 = load i1, ptr %3, align 1, !dbg !262
  store i1 false, ptr %3, align 1, !dbg !264
  %5 = load ptr, ptr %arg.self, align 8, !dbg !262
  %6 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 1, !dbg !262
  %7 = load i32, ptr %6, align 4, !dbg !262
  %8 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17225SaFnE"() #5, !dbg !265
  store i32 %8, ptr %6, align 4, !dbg !265
  %9 = load ptr, ptr %arg.self, align 8, !dbg !262
  %10 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 1, !dbg !262
  %11 = load i32, ptr %10, align 4, !dbg !262
  %12 = load i32, ptr %arg.value, align 4, !dbg !266
  store i32 %12, ptr %10, align 4, !dbg !266
  %13 = load ptr, ptr %arg.self, align 8, !dbg !262
  %14 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 0, !dbg !262
  %15 = load i1, ptr %14, align 1, !dbg !262
  store i1 true, ptr %14, align 1, !dbg !267
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17213SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !268 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !271, metadata !DIExpression()), !dbg !272
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !272
  %2 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !272
  %3 = load i1, ptr %2, align 1, !dbg !272
  store i1 false, ptr %2, align 1, !dbg !273
  %4 = load ptr, ptr %arg.self, align 8, !dbg !272
  %5 = getelementptr inbounds %"class._$SN&4IterCv17205ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !272
  %6 = load i32, ptr %5, align 4, !dbg !272
  %7 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17217SaFnE"() #5, !dbg !274
  store i32 %7, ptr %5, align 4, !dbg !274
  ret void
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !275 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !278, metadata !DIExpression()), !dbg !279
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !279
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %1, i32 0, i32 4, !dbg !279
  %3 = load ptr, ptr %2, align 8, !dbg !279
  ret ptr %3, !dbg !279
}

; Function Attrs: noinline
define internal void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !280 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !283, metadata !DIExpression()), !dbg !284
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !285, metadata !DIExpression()), !dbg !284
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !284
  call void @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4#NwCCv17115SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !284
  %3 = load ptr, ptr %arg.self, align 8, !dbg !284
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !284
  %5 = load i32, ptr %4, align 4, !dbg !284
  store i32 0, ptr %4, align 4, !dbg !286
  %6 = load ptr, ptr %arg.self, align 8, !dbg !284
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !284
  %8 = load i32, ptr %7, align 4, !dbg !284
  store i32 10, ptr %7, align 4, !dbg !287
  %9 = load ptr, ptr %arg.self, align 8, !dbg !284
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !284
  %11 = load i32, ptr %10, align 4, !dbg !284
  store i32 0, ptr %10, align 4, !dbg !288
  %12 = load ptr, ptr %arg.self, align 8, !dbg !284
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !284
  %14 = load ptr, ptr %13, align 8, !dbg !284
  store ptr @.str.15, ptr %13, align 8, !dbg !289
  %15 = load ptr, ptr %arg.self, align 8, !dbg !284
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !284
  %17 = load ptr, ptr %16, align 8, !dbg !284
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !290
  store ptr %18, ptr %16, align 8, !dbg !290
  %19 = load ptr, ptr %arg.self, align 8, !dbg !284
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %19, i32 0, i32 3, !dbg !284
  %21 = load i32, ptr %20, align 4, !dbg !284
  %22 = load ptr, ptr %arg.buffer, align 8, !dbg !291
  %23 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %22), !dbg !292
  store i32 %23, ptr %20, align 4, !dbg !292
  %24 = load ptr, ptr %arg.self, align 8, !dbg !284
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !284
  %26 = load i32, ptr %25, align 4, !dbg !284
  %27 = load ptr, ptr %arg.self, align 8, !dbg !284
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %27, i32 0, i32 3, !dbg !284
  %29 = load i32, ptr %28, align 4, !dbg !284
  %30 = add i32 %29, 10, !dbg !293
  store i32 %30, ptr %25, align 4, !dbg !293
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4nextCv17120SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull sret(%"class._$SN&4IterCv17033ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #0 personality ptr @sn.eh.personality !dbg !294 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !299, metadata !DIExpression()), !dbg !300
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17032ClsGStA1T4charClsE&4#NwCCv17115SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !301 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !304, metadata !DIExpression()), !dbg !305
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !305
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17032ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !305
  %3 = load i32, ptr %2, align 4, !dbg !305
  store i32 0, ptr %2, align 4, !dbg !306
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !307 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !312, metadata !DIExpression()), !dbg !313
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !314, metadata !DIExpression()), !dbg !313
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !313
  %3 = getelementptr inbounds %"class._$SN&9ExceptionCv17060ClsE", ptr %2, i32 0, i32 0, !dbg !313
  %4 = load ptr, ptr %3, align 8, !dbg !313
  %5 = load ptr, ptr %arg.m, align 8, !dbg !315
  store ptr %5, ptr %3, align 8, !dbg !315
  ret void
}

; Function Attrs: noinline
declare noalias noundef nonnull ptr @sn.alloca(i32) #0

; Function Attrs: noinline nounwind
declare noalias noundef nonnull ptr @sn.eh.create(ptr, i32) #3

; Function Attrs: noinline
declare void @sn.eh.throw(ptr) #0

; Function Attrs: alwaysinline
define internal void @"_$SNT4char&9to_stringCv17425SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %0, ptr %1) #2 personality ptr @sn.eh.personality !dbg !316 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %1, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !319, metadata !DIExpression()), !dbg !320
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !321
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %4, align 8
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !322
  %5 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %0, align 8, !dbg !322
  ret void, !dbg !322
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv17929SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(%"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0) #2 personality ptr @sn.eh.personality !dbg !323 {
entry:
  %arg.msg = alloca %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  store %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !327, metadata !DIExpression()), !dbg !328
  br label %body

body:                                             ; preds = %entry
  %1 = load %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %arg.msg, align 8, !dbg !329
  %2 = call i32 @"_$SN@sn.Core.System&5printCv17933SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEA2T4char.rFnE"(%"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.22) #5, !dbg !330
  ret i32 %2, !dbg !330
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv17933SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEA2T4char.rFnE"(%"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !331 {
entry:
  %arg.msg = alloca %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  store %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !334, metadata !DIExpression()), !dbg !335
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !336, metadata !DIExpression()), !dbg !335
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !337, metadata !DIExpression()), !dbg !338
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %3 = load %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %arg.msg, align 8, !dbg !339
  call void @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17940SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(ptr sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") %2, %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %3) #5, !dbg !340
  %4 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !340
  %5 = call ptr @"_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !340
  store ptr %5, ptr %var.m, align 8, !dbg !340
  %6 = load ptr, ptr %var.m, align 8, !dbg !341
  %7 = load ptr, ptr %arg.end, align 8, !dbg !342
  %8 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.23, ptr %6, ptr %7), !dbg !343
  ret i32 %8, !dbg !343
}

; Function Attrs: noinline
define i32 @main() #0 personality ptr @sn.eh.personality !dbg !344 {
entry:
  call void @sn.runtime.initialize()
  %var.a = alloca %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.a, metadata !345, metadata !DIExpression()), !dbg !346
  %0 = alloca %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", align 8
  %1 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %2 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  %3 = alloca %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", align 8
  br label %body

body:                                             ; preds = %entry
  %4 = getelementptr inbounds %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %0, i32 0, i32 0
  store ptr @"vtable._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %4, align 8
  call void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17840SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !347
  %5 = load %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %0, align 8, !dbg !347
  store %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %5, ptr %var.a, align 8, !dbg !347
  call void @"_$SNT4char&9to_stringCv17425SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %1, ptr @.str.24) #5, !dbg !348
  %6 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %1, align 8, !dbg !348
  call void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17846SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !349
  call void @"_$SNT4char&9to_stringCv17425SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %2, ptr @.str.25) #5, !dbg !350
  %7 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %2, align 8, !dbg !350
  call void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17846SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a, ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !351
  call void @"_$SNT4char&9to_stringCv17425SaA1T4char.rFnE"(ptr noundef nonnull sret(%"class._$SN&10StringViewCv17031ClsGStA1T4charClsE") align 8 dereferenceable(64) %3, ptr @.str.26) #5, !dbg !352
  %8 = load %"class._$SN&10StringViewCv17031ClsGStA1T4charClsE", ptr %3, align 8, !dbg !352
  call void @"_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17846SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.a, ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !353
  %9 = load %"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE", ptr %var.a, align 8, !dbg !354
  %10 = call i32 @"_$SN@sn.Core.System&7printlnCv17929SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE"(%"class._$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE" %9) #5, !dbg !355
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
!20 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17940SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE", scope: !21, file: !21, line: 640, type: !22, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!21 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!22 = !DISubroutineType(types: !23)
!23 = !{!24, !26}
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::StringView<char>", scope: !21, file: !21, line: 509, baseType: !25, elements: !12)
!25 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<char>", scope: !21, file: !21, line: 230, elements: !12)
!26 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 392, baseType: !27, elements: !12)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 230, elements: !12)
!28 = !DILocalVariable(name: "buffer", arg: 2, scope: !20, file: !1, line: 640, type: !26)
!29 = !DILocation(line: 640, column: 15, scope: !20)
!30 = !DILocation(line: 641, column: 38, scope: !20)
!31 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::to_string", linkageName: "_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&9to_stringCv17943SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 473, type: !32, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!32 = !DISubroutineType(types: !33)
!33 = !{!24, !34}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 392, baseType: !27, elements: !12)
!36 = !DILocalVariable(name: "self", arg: 2, scope: !31, file: !1, line: 473, type: !34)
!37 = !DILocation(line: 473, column: 8, scope: !31)
!38 = !DILocalVariable(name: "result", scope: !31, file: !1, line: 474, type: !39)
!39 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::StringView<char>", scope: !21, file: !21, line: 509, baseType: !25, elements: !12)
!40 = !DILocation(line: 474, column: 15, scope: !31)
!41 = !DILocalVariable(name: "separator", scope: !31, file: !1, line: 475, type: !24)
!42 = !DILocation(line: 475, column: 11, scope: !31)
!43 = !DILocalVariable(name: "$iter", scope: !31, file: !1, line: 477, type: !44)
!44 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Range<i32>", scope: !21, file: !21, line: 319, baseType: !45, elements: !12)
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<i32>", scope: !21, file: !21, line: 230, elements: !12)
!46 = !DILocation(line: 477, column: 17, scope: !31)
!47 = !DILocalVariable(name: "$iter_value", scope: !31, file: !1, line: 477, type: !48)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Iter<i32>", scope: !21, file: !21, line: 262, elements: !12)
!49 = !DILocalVariable(name: "i", scope: !31, file: !1, line: 477, type: !11)
!50 = !DILocation(line: 474, column: 28, scope: !31)
!51 = !DILocation(line: 475, column: 27, scope: !31)
!52 = !DILocation(line: 478, column: 48, scope: !31)
!53 = !DILocation(line: 478, column: 40, scope: !31)
!54 = !DILocation(line: 478, column: 27, scope: !31)
!55 = !DILocation(line: 478, column: 25, scope: !31)
!56 = !DILocation(line: 479, column: 31, scope: !31)
!57 = !DILocation(line: 483, column: 34, scope: !31)
!58 = !DILocation(line: 483, column: 7, scope: !31)
!59 = !DILocation(line: 484, column: 14, scope: !31)
!60 = !DILocation(line: 480, column: 29, scope: !31)
!61 = !DILocation(line: 480, column: 27, scope: !31)
!62 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4fromCv17963SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 640, type: !63, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!63 = !DISubroutineType(types: !64)
!64 = !{!24, !65}
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64)
!66 = !DILocalVariable(name: "buffer", arg: 2, scope: !62, file: !1, line: 640, type: !65)
!67 = !DILocation(line: 640, column: 15, scope: !62)
!68 = !DILocation(line: 641, column: 38, scope: !62)
!69 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::at", linkageName: "_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&2atCv17870SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE", scope: !21, file: !21, line: 431, type: !70, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!70 = !DISubroutineType(types: !71)
!71 = !{!65, !34, !11}
!72 = !DILocalVariable(name: "self", arg: 1, scope: !69, file: !1, line: 431, type: !34)
!73 = !DILocation(line: 431, column: 8, scope: !69)
!74 = !DILocalVariable(name: "index", arg: 2, scope: !69, file: !1, line: 431, type: !11)
!75 = !DILocation(line: 433, column: 18, scope: !69)
!76 = !DILocation(line: 435, column: 19, scope: !69)
!77 = !DILocation(line: 437, column: 40, scope: !69)
!78 = !DILocation(line: 437, column: 14, scope: !69)
!79 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::push", linkageName: "_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4pushCv17846SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 404, type: !80, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!80 = !DISubroutineType(types: !81)
!81 = !{null, !34, !65}
!82 = !DILocalVariable(name: "self", arg: 1, scope: !79, file: !1, line: 404, type: !34)
!83 = !DILocation(line: 404, column: 8, scope: !79)
!84 = !DILocalVariable(name: "value", arg: 2, scope: !79, file: !1, line: 404, type: !65)
!85 = !DILocation(line: 406, column: 24, scope: !79)
!86 = !DILocation(line: 408, column: 37, scope: !79)
!87 = !DILocation(line: 408, column: 9, scope: !79)
!88 = !DILocation(line: 410, column: 46, scope: !79)
!89 = !DILocation(line: 410, column: 7, scope: !79)
!90 = !DILocation(line: 411, column: 35, scope: !79)
!91 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::resize", linkageName: "_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&6resizeCv17851SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rA2T3i32FnE", scope: !21, file: !21, line: 421, type: !92, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!92 = !DISubroutineType(types: !93)
!93 = !{null, !34, !11}
!94 = !DILocalVariable(name: "self", arg: 1, scope: !91, file: !1, line: 421, type: !34)
!95 = !DILocation(line: 421, column: 8, scope: !91)
!96 = !DILocalVariable(name: "capacity", arg: 2, scope: !91, file: !1, line: 421, type: !11)
!97 = !DILocation(line: 423, column: 23, scope: !91)
!98 = !DILocation(line: 424, column: 21, scope: !91)
!99 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>&>::constructor", linkageName: "_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17840SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 398, type: !100, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!100 = !DISubroutineType(types: !101)
!101 = !{null, !34}
!102 = !DILocalVariable(name: "self", arg: 1, scope: !99, file: !1, line: 398, type: !34)
!103 = !DILocation(line: 398, column: 5, scope: !99)
!104 = !DILocation(line: 232, column: 31, scope: !99)
!105 = !DILocation(line: 489, column: 29, scope: !99)
!106 = !DILocation(line: 491, column: 27, scope: !99)
!107 = !DILocation(line: 399, column: 14, scope: !99)
!108 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>&>::next", linkageName: "_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4nextCv17815SaA1_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 245, type: !109, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!109 = !DISubroutineType(types: !110)
!110 = !{!111, !112}
!111 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<Core::_$core::Core::StringView<char>&>", scope: !21, file: !21, line: 262, elements: !12)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64)
!113 = !DILocalVariable(name: "self", arg: 2, scope: !108, file: !1, line: 245, type: !112)
!114 = !DILocation(line: 245, column: 13, scope: !108)
!115 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>&>::constructor", linkageName: "_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE&4#NwCCv17810SaA1_$SN&8IterableCv17759ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsE.rFnE", scope: !21, file: !21, line: 240, type: !116, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!116 = !DISubroutineType(types: !117)
!117 = !{null, !112}
!118 = !DILocalVariable(name: "self", arg: 1, scope: !115, file: !1, line: 240, type: !112)
!119 = !DILocation(line: 240, column: 5, scope: !115)
!120 = !DILocation(line: 232, column: 31, scope: !115)
!121 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::to_string", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&9to_stringCv17377SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 603, type: !63, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!122 = !DILocalVariable(name: "self", arg: 2, scope: !121, file: !1, line: 603, type: !65)
!123 = !DILocation(line: 603, column: 8, scope: !121)
!124 = !DILocalVariable(name: "base", scope: !121, file: !1, line: 605, type: !24)
!125 = !DILocation(line: 605, column: 11, scope: !121)
!126 = !DILocation(line: 605, column: 22, scope: !121)
!127 = !DILocation(line: 606, column: 36, scope: !121)
!128 = !DILocation(line: 606, column: 35, scope: !121)
!129 = !DILocation(line: 606, column: 7, scope: !121)
!130 = !DILocation(line: 607, column: 22, scope: !121)
!131 = !DILocation(line: 607, column: 19, scope: !121)
!132 = !DILocation(line: 607, column: 27, scope: !121)
!133 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator +", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17368SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17031ClsGStA1T4charClsEFnE", scope: !21, file: !21, line: 594, type: !134, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!134 = !DISubroutineType(types: !135)
!135 = !{!24, !65, !24}
!136 = !DILocalVariable(name: "self", arg: 2, scope: !133, file: !1, line: 594, type: !65)
!137 = !DILocation(line: 594, column: 14, scope: !133)
!138 = !DILocalVariable(name: "other", arg: 3, scope: !133, file: !1, line: 594, type: !24)
!139 = !DILocalVariable(name: "result", scope: !133, file: !1, line: 596, type: !9)
!140 = !DILocation(line: 596, column: 11, scope: !133)
!141 = !DILocation(line: 596, column: 20, scope: !133)
!142 = !DILocation(line: 597, column: 23, scope: !133)
!143 = !DILocation(line: 597, column: 18, scope: !133)
!144 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator +", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&3#PlCv17339SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !21, file: !21, line: 579, type: !145, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!145 = !DISubroutineType(types: !146)
!146 = !{!24, !65, !9}
!147 = !DILocalVariable(name: "self", arg: 2, scope: !144, file: !1, line: 579, type: !65)
!148 = !DILocation(line: 579, column: 14, scope: !144)
!149 = !DILocalVariable(name: "other", arg: 3, scope: !144, file: !1, line: 579, type: !9)
!150 = !DILocalVariable(name: "len1", scope: !144, file: !1, line: 581, type: !11)
!151 = !DILocation(line: 581, column: 11, scope: !144)
!152 = !DILocalVariable(name: "len2", scope: !144, file: !1, line: 582, type: !11)
!153 = !DILocation(line: 582, column: 11, scope: !144)
!154 = !DILocalVariable(name: "res", scope: !144, file: !1, line: 583, type: !9)
!155 = !DILocation(line: 583, column: 11, scope: !144)
!156 = !DILocation(line: 582, column: 41, scope: !144)
!157 = !DILocation(line: 582, column: 18, scope: !144)
!158 = !DILocation(line: 583, column: 42, scope: !144)
!159 = !DILocation(line: 583, column: 49, scope: !144)
!160 = !DILocation(line: 583, column: 55, scope: !144)
!161 = !DILocation(line: 583, column: 17, scope: !144)
!162 = !DILocation(line: 584, column: 23, scope: !144)
!163 = !DILocation(line: 584, column: 18, scope: !144)
!164 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::concat", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&6concatCv17350SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rA3T4char.rA4T3i32A5T3i32FnE", scope: !21, file: !21, line: 653, type: !165, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!165 = !DISubroutineType(types: !166)
!166 = !{!9, !65, !9, !9, !11, !11}
!167 = !DILocalVariable(name: "self", arg: 1, scope: !164, file: !1, line: 653, type: !65)
!168 = !DILocation(line: 653, column: 8, scope: !164)
!169 = !DILocalVariable(name: "str1", arg: 2, scope: !164, file: !1, line: 653, type: !9)
!170 = !DILocalVariable(name: "str2", arg: 3, scope: !164, file: !1, line: 653, type: !9)
!171 = !DILocalVariable(name: "len1", arg: 4, scope: !164, file: !1, line: 653, type: !11)
!172 = !DILocalVariable(name: "len2", arg: 5, scope: !164, file: !1, line: 653, type: !11)
!173 = !DILocalVariable(name: "sum", scope: !164, file: !1, line: 656, type: !11)
!174 = !DILocation(line: 656, column: 11, scope: !164)
!175 = !DILocalVariable(name: "buffer", scope: !164, file: !1, line: 657, type: !9)
!176 = !DILocation(line: 657, column: 11, scope: !164)
!177 = !DILocation(line: 656, column: 24, scope: !164)
!178 = !DILocation(line: 657, column: 33, scope: !164)
!179 = !DILocation(line: 657, column: 20, scope: !164)
!180 = !DILocation(line: 658, column: 20, scope: !164)
!181 = !DILocation(line: 658, column: 36, scope: !164)
!182 = !DILocation(line: 658, column: 50, scope: !164)
!183 = !DILocation(line: 658, column: 7, scope: !164)
!184 = !DILocation(line: 659, column: 30, scope: !164)
!185 = !DILocation(line: 659, column: 28, scope: !164)
!186 = !DILocation(line: 659, column: 45, scope: !164)
!187 = !DILocation(line: 659, column: 59, scope: !164)
!188 = !DILocation(line: 659, column: 7, scope: !164)
!189 = !DILocation(line: 660, column: 14, scope: !164)
!190 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::next", linkageName: "_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4nextCv17312SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 358, type: !191, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!191 = !DISubroutineType(types: !192)
!192 = !{!48, !193}
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64)
!194 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Range<i32>", scope: !21, file: !21, line: 319, baseType: !45, elements: !12)
!195 = !DILocalVariable(name: "self", arg: 2, scope: !190, file: !1, line: 358, type: !193)
!196 = !DILocation(line: 358, column: 13, scope: !190)
!197 = !DILocalVariable(name: "iter", scope: !190, file: !1, line: 365, type: !198)
!198 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<i32>", scope: !21, file: !21, line: 262, elements: !12)
!199 = !DILocation(line: 365, column: 11, scope: !190)
!200 = !DILocation(line: 360, column: 43, scope: !190)
!201 = !DILocation(line: 361, column: 29, scope: !190)
!202 = !DILocation(line: 363, column: 16, scope: !190)
!203 = !DILocation(line: 365, column: 18, scope: !190)
!204 = !DILocation(line: 366, column: 14, scope: !190)
!205 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::end", linkageName: "_$SN&5RangeCv17203ClsGStA1T3i32ClsE&3endCv17308SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 352, type: !206, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!206 = !DISubroutineType(types: !207)
!207 = !{!11, !193}
!208 = !DILocalVariable(name: "self", arg: 1, scope: !205, file: !1, line: 352, type: !193)
!209 = !DILocation(line: 352, column: 8, scope: !205)
!210 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::constructor", linkageName: "_$SN&5RangeCv17203ClsGStA1T3i32ClsE&4#NwCCv17282SaA1_$SN&5RangeCv17203ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE", scope: !21, file: !21, line: 326, type: !211, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!211 = !DISubroutineType(types: !212)
!212 = !{null, !193, !11, !11}
!213 = !DILocalVariable(name: "self", arg: 1, scope: !210, file: !1, line: 326, type: !193)
!214 = !DILocation(line: 326, column: 5, scope: !210)
!215 = !DILocalVariable(name: "start", arg: 2, scope: !210, file: !1, line: 326, type: !11)
!216 = !DILocalVariable(name: "end", arg: 3, scope: !210, file: !1, line: 326, type: !11)
!217 = !DILocation(line: 232, column: 31, scope: !210)
!218 = !DILocation(line: 375, column: 32, scope: !210)
!219 = !DILocation(line: 327, column: 23, scope: !210)
!220 = !DILocation(line: 327, column: 36, scope: !210)
!221 = !DILocation(line: 329, column: 37, scope: !210)
!222 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::next", linkageName: "_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4nextCv17260SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 245, type: !223, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!223 = !DISubroutineType(types: !224)
!224 = !{!198, !225}
!225 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64)
!226 = !DILocalVariable(name: "self", arg: 2, scope: !222, file: !1, line: 245, type: !225)
!227 = !DILocation(line: 245, column: 13, scope: !222)
!228 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::constructor", linkageName: "_$SN&8IterableCv17204ClsGStA1T3i32ClsE&4#NwCCv17255SaA1_$SN&8IterableCv17204ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 240, type: !229, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!229 = !DISubroutineType(types: !230)
!230 = !{null, !225}
!231 = !DILocalVariable(name: "self", arg: 1, scope: !228, file: !1, line: 240, type: !225)
!232 = !DILocation(line: 240, column: 5, scope: !228)
!233 = !DILocation(line: 232, column: 31, scope: !228)
!234 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::valid", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&5validCv17240SaA1T3i32FnE", scope: !21, file: !21, line: 308, type: !235, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!235 = !DISubroutineType(types: !236)
!236 = !{!198, !11}
!237 = !DILocalVariable(name: "val", arg: 2, scope: !234, file: !1, line: 308, type: !11)
!238 = !DILocation(line: 308, column: 15, scope: !234)
!239 = !DILocation(line: 309, column: 40, scope: !234)
!240 = !DILocation(line: 309, column: 20, scope: !234)
!241 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::invalid", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&7invalidCv17238SaFnE", scope: !21, file: !21, line: 302, type: !242, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!242 = !DISubroutineType(types: !243)
!243 = !{!198}
!244 = !DILocation(line: 303, column: 20, scope: !241)
!245 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::is_valid", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&8is_validCv17234SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 295, type: !246, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!246 = !DISubroutineType(types: !247)
!247 = !{!248, !249}
!248 = !DIBasicType(name: "bool", size: 8, encoding: DW_ATE_signed)
!249 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !198, size: 64)
!250 = !DILocalVariable(name: "self", arg: 1, scope: !245, file: !1, line: 295, type: !249)
!251 = !DILocation(line: 295, column: 8, scope: !245)
!252 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::value", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&5valueCv17227SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 283, type: !253, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!253 = !DISubroutineType(types: !254)
!254 = !{!11, !249}
!255 = !DILocalVariable(name: "self", arg: 1, scope: !252, file: !1, line: 283, type: !249)
!256 = !DILocation(line: 283, column: 8, scope: !252)
!257 = !DILocation(line: 287, column: 19, scope: !252)
!258 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17219SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !21, file: !21, line: 277, type: !259, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!259 = !DISubroutineType(types: !260)
!260 = !{null, !249, !11}
!261 = !DILocalVariable(name: "self", arg: 1, scope: !258, file: !1, line: 277, type: !249)
!262 = !DILocation(line: 277, column: 5, scope: !258)
!263 = !DILocalVariable(name: "value", arg: 2, scope: !258, file: !1, line: 277, type: !11)
!264 = !DILocation(line: 264, column: 24, scope: !258)
!265 = !DILocation(line: 266, column: 33, scope: !258)
!266 = !DILocation(line: 277, column: 41, scope: !258)
!267 = !DILocation(line: 278, column: 14, scope: !258)
!268 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17205ClsGStA1T3i32ClsE&4#NwCCv17213SaA1_$SN&4IterCv17205ClsGStA1T3i32ClsE.rFnE", scope: !21, file: !21, line: 272, type: !269, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!269 = !DISubroutineType(types: !270)
!270 = !{null, !249}
!271 = !DILocalVariable(name: "self", arg: 1, scope: !268, file: !1, line: 272, type: !249)
!272 = !DILocation(line: 272, column: 5, scope: !268)
!273 = !DILocation(line: 264, column: 24, scope: !268)
!274 = !DILocation(line: 266, column: 33, scope: !268)
!275 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&5c_strCv17193SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 549, type: !276, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!276 = !DISubroutineType(types: !277)
!277 = !{!9, !65}
!278 = !DILocalVariable(name: "self", arg: 1, scope: !275, file: !1, line: 549, type: !65)
!279 = !DILocation(line: 549, column: 8, scope: !275)
!280 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17031ClsGStA1T4charClsE&4#NwCCv17158SaA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !21, file: !21, line: 523, type: !281, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!281 = !DISubroutineType(types: !282)
!282 = !{null, !65, !9}
!283 = !DILocalVariable(name: "self", arg: 1, scope: !280, file: !1, line: 523, type: !65)
!284 = !DILocation(line: 523, column: 5, scope: !280)
!285 = !DILocalVariable(name: "buffer", arg: 2, scope: !280, file: !1, line: 523, type: !9)
!286 = !DILocation(line: 232, column: 31, scope: !280)
!287 = !DILocation(line: 611, column: 29, scope: !280)
!288 = !DILocation(line: 613, column: 27, scope: !280)
!289 = !DILocation(line: 615, column: 30, scope: !280)
!290 = !DILocation(line: 524, column: 23, scope: !280)
!291 = !DILocation(line: 524, column: 62, scope: !280)
!292 = !DILocation(line: 524, column: 39, scope: !280)
!293 = !DILocation(line: 525, column: 39, scope: !280)
!294 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::next", linkageName: "_$SN&8IterableCv17032ClsGStA1T4charClsE&4nextCv17120SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 245, type: !295, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!295 = !DISubroutineType(types: !296)
!296 = !{!297, !298}
!297 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<char>", scope: !21, file: !21, line: 262, elements: !12)
!298 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64)
!299 = !DILocalVariable(name: "self", arg: 2, scope: !294, file: !1, line: 245, type: !298)
!300 = !DILocation(line: 245, column: 13, scope: !294)
!301 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::constructor", linkageName: "_$SN&8IterableCv17032ClsGStA1T4charClsE&4#NwCCv17115SaA1_$SN&8IterableCv17032ClsGStA1T4charClsE.rFnE", scope: !21, file: !21, line: 240, type: !302, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!302 = !DISubroutineType(types: !303)
!303 = !{null, !298}
!304 = !DILocalVariable(name: "self", arg: 1, scope: !301, file: !1, line: 240, type: !298)
!305 = !DILocation(line: 240, column: 5, scope: !301)
!306 = !DILocation(line: 232, column: 31, scope: !301)
!307 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::constructor", linkageName: "_$SN&9ExceptionCv17060ClsE&4#NwCCv17065SaA1_$SN&9ExceptionCv17060ClsE.rA2T4char.rFnE", scope: !21, file: !21, line: 193, type: !308, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!308 = !DISubroutineType(types: !309)
!309 = !{null, !310, !9}
!310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !311, size: 64)
!311 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Exception", scope: !21, file: !21, line: 187, elements: !12)
!312 = !DILocalVariable(name: "self", arg: 1, scope: !307, file: !1, line: 193, type: !310)
!313 = !DILocation(line: 193, column: 5, scope: !307)
!314 = !DILocalVariable(name: "m", arg: 2, scope: !307, file: !1, line: 193, type: !9)
!315 = !DILocation(line: 193, column: 31, scope: !307)
!316 = distinct !DISubprogram(name: "char::to_string", linkageName: "_$SNT4char&9to_stringCv17425SaA1T4char.rFnE", scope: !21, file: !21, line: 10, type: !317, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!317 = !DISubroutineType(types: !318)
!318 = !{!24, !9}
!319 = !DILocalVariable(name: "self", arg: 2, scope: !316, file: !1, line: 10, type: !9)
!320 = !DILocation(line: 10, column: 8, scope: !316)
!321 = !DILocation(line: 11, column: 27, scope: !316)
!322 = !DILocation(line: 11, column: 20, scope: !316)
!323 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv17929SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEFnE", scope: !324, file: !324, line: 27, type: !325, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!324 = !DIFile(filename: "System.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!325 = !DISubroutineType(types: !326)
!326 = !{!11, !26}
!327 = !DILocalVariable(name: "msg", arg: 1, scope: !323, file: !1, line: 27, type: !26)
!328 = !DILocation(line: 27, column: 15, scope: !323)
!329 = !DILocation(line: 28, column: 20, scope: !323)
!330 = !DILocation(line: 28, column: 14, scope: !323)
!331 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv17933SaA1_$SN&6VectorCv17758ClsGStA1_$SN&10StringViewCv17031ClsGStA1T4charClsE.rClsEA2T4char.rFnE", scope: !324, file: !324, line: 16, type: !332, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!332 = !DISubroutineType(types: !333)
!333 = !{!11, !26, !9}
!334 = !DILocalVariable(name: "msg", arg: 1, scope: !331, file: !1, line: 16, type: !26)
!335 = !DILocation(line: 16, column: 15, scope: !331)
!336 = !DILocalVariable(name: "end", arg: 2, scope: !331, file: !1, line: 16, type: !9)
!337 = !DILocalVariable(name: "m", scope: !331, file: !1, line: 17, type: !9)
!338 = !DILocation(line: 17, column: 9, scope: !331)
!339 = !DILocation(line: 17, column: 26, scope: !331)
!340 = !DILocation(line: 17, column: 13, scope: !331)
!341 = !DILocation(line: 18, column: 33, scope: !331)
!342 = !DILocation(line: 18, column: 36, scope: !331)
!343 = !DILocation(line: 18, column: 12, scope: !331)
!344 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 19, type: !15, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!345 = !DILocalVariable(name: "a", scope: !344, file: !1, line: 21, type: !26)
!346 = !DILocation(line: 21, column: 13, scope: !344)
!347 = !DILocation(line: 21, column: 21, scope: !344)
!348 = !DILocation(line: 22, column: 13, scope: !344)
!349 = !DILocation(line: 22, column: 5, scope: !344)
!350 = !DILocation(line: 23, column: 13, scope: !344)
!351 = !DILocation(line: 23, column: 5, scope: !344)
!352 = !DILocation(line: 24, column: 13, scope: !344)
!353 = !DILocation(line: 24, column: 5, scope: !344)
!354 = !DILocation(line: 25, column: 21, scope: !344)
!355 = !DILocation(line: 25, column: 5, scope: !344)
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
