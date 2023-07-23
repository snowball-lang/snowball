Lexer: 0.000100s
Parser: 0.000638s
Lexer: 0.000703s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Parser: 0.001835s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Lexer: 0.000196s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Parser: 0.000184s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Lexer: 0.000073s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Parser: 0.000187s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Simplifier: 0.007869s
Passes: 0.000038s
TypeChecker: 0.000034s (Core::CLib::c_string)
TypeChecker: 0.000057s (Core::CLib::__internal)
TypeChecker: 0.000015s (Core::CLib)
TypeChecker: 0.000008s (Core::_$core::Core::UA)
TypeChecker: 0.000002s (Core::_$core::Core::__internal)
TypeChecker: 0.000174s (Core::_$core::Core)
TypeChecker: 0.000003s (Core::_$core)
TypeChecker: 0.000050s (Core::System)
TypeChecker: 0.000026s ($main)
; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" = type { i32, i32, ptr }
%"class._$SN&9ExceptionCv15034ClsE" = type { ptr }

@.str.3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@.str.7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@.str.9 = private unnamed_addr constant [14 x i8] c"Hello, World!\00", align 1
@0 = private unnamed_addr constant [9 x i8] c"error: \0A\00", align 1
@"snowball.typeidx._$SN&9ExceptionCv15034ClsE.r" = private unnamed_addr constant { i32 } { i32 1000 }
@.str.10 = private unnamed_addr constant [19 x i8] c"Hello, World! 2222\00", align 1

; Function Attrs: noinline
declare i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64)) #0

; Function Attrs: nocallback nofree noinline nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline
declare i32 @sn.eh.personality(i32, i32, i64, ptr, ptr) #0

; Function Attrs: noinline
declare i32 @printf(ptr noundef nonnull align 8 dereferenceable(64), ...) #0

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15251SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !5 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %0, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !14, metadata !DIExpression()), !dbg !15
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.buffer, align 8, !dbg !16
  %2 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !17
  call void @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !17
  %3 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %2, align 8, !dbg !17
  ret %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %3, !dbg !17
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15232SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !18 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %0, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !19, metadata !DIExpression()), !dbg !20
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.buffer, align 8, !dbg !21
  %2 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !22
  call void @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !22
  %3 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %2, align 8, !dbg !22
  ret %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %3, !dbg !22
}

; Function Attrs: noinline
define internal ptr @"_$SN&9ExceptionCv15034ClsE&4whatCv15186SaA1_$SN&9ExceptionCv15034ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !23 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !28, metadata !DIExpression()), !dbg !29
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !29
  %2 = load %"class._$SN&9ExceptionCv15034ClsE", ptr %1, align 8, !dbg !29
  %3 = extractvalue %"class._$SN&9ExceptionCv15034ClsE" %2, 0, !dbg !29
  ret ptr %3, !dbg !29
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !30 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !34, metadata !DIExpression()), !dbg !35
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !35
  %2 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %1, align 8, !dbg !35
  %3 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %2, 2, !dbg !35
  ret ptr %3, !dbg !35
}

; Function Attrs: noinline
define internal void @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !36 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !39, metadata !DIExpression()), !dbg !40
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !41, metadata !DIExpression()), !dbg !40
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !40
  call void @"_$SN&8IterableCv15053ClsGStA1T4charClsE&4#NwCCv15056SaA1_$SN&8IterableCv15053ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !40
  %3 = load ptr, ptr %arg.self, align 8, !dbg !40
  %4 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !40
  %5 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, 0, !dbg !40
  %6 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, i32 10, 0, !dbg !42
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %6, ptr %3, align 8, !dbg !42
  %7 = load ptr, ptr %arg.self, align 8, !dbg !40
  %8 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %7, align 8, !dbg !40
  %9 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %8, 1, !dbg !40
  %10 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %8, i32 0, 1, !dbg !43
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %10, ptr %7, align 8, !dbg !43
  %11 = load ptr, ptr %arg.self, align 8, !dbg !40
  %12 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %11, align 8, !dbg !40
  %13 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %12, 2, !dbg !40
  %14 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %12, ptr @.str.3, 2, !dbg !44
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %14, ptr %11, align 8, !dbg !44
  %15 = load ptr, ptr %arg.self, align 8, !dbg !40
  %16 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %15, align 8, !dbg !40
  %17 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %16, 2, !dbg !40
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !45
  %19 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %16, ptr %18, 2, !dbg !45
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %19, ptr %15, align 8, !dbg !45
  %20 = load ptr, ptr %arg.self, align 8, !dbg !40
  %21 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %20, align 8, !dbg !40
  %22 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %21, 1, !dbg !40
  %23 = load ptr, ptr %arg.buffer, align 8, !dbg !46
  %24 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %23), !dbg !47
  %25 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %21, i32 %24, 1, !dbg !47
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %25, ptr %20, align 8, !dbg !47
  %26 = load ptr, ptr %arg.self, align 8, !dbg !40
  %27 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %26, align 8, !dbg !40
  %28 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %27, 0, !dbg !40
  %29 = load ptr, ptr %arg.self, align 8, !dbg !40
  %30 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %29, align 8, !dbg !40
  %31 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %30, 1, !dbg !40
  %32 = add i32 %31, 10, !dbg !48
  %33 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %27, i32 %32, 0, !dbg !48
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %33, ptr %26, align 8, !dbg !48
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv15053ClsGStA1T4charClsE&4#NwCCv15056SaA1_$SN&8IterableCv15053ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !49 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !53, metadata !DIExpression()), !dbg !54
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&9ExceptionCv15034ClsE&4#NwCCv15040SaA1_$SN&9ExceptionCv15034ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !55 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !58, metadata !DIExpression()), !dbg !59
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !60, metadata !DIExpression()), !dbg !59
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !59
  %3 = load %"class._$SN&9ExceptionCv15034ClsE", ptr %2, align 8, !dbg !59
  %4 = extractvalue %"class._$SN&9ExceptionCv15034ClsE" %3, 0, !dbg !59
  %5 = load ptr, ptr %arg.m, align 8, !dbg !61
  %6 = insertvalue %"class._$SN&9ExceptionCv15034ClsE" %3, ptr %5, 0, !dbg !61
  store %"class._$SN&9ExceptionCv15034ClsE" %6, ptr %2, align 8, !dbg !61
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv15240SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !62 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !67, metadata !DIExpression()), !dbg !68
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !69
  %2 = call i32 @"_$SN@sn.Core.System&5printCv15244SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.5) #5, !dbg !70
  ret i32 %2, !dbg !70
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv15244SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !71 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !74, metadata !DIExpression()), !dbg !75
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !76, metadata !DIExpression()), !dbg !75
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !77, metadata !DIExpression()), !dbg !78
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !79
  %3 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !79
  %4 = call %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15251SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !80
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !80
  %5 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !80
  %6 = call ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #5, !dbg !80
  store ptr %6, ptr %var.m, align 8, !dbg !80
  %7 = load ptr, ptr %var.m, align 8, !dbg !81
  %8 = load ptr, ptr %arg.end, align 8, !dbg !82
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.6, ptr %7, ptr %8), !dbg !83
  ret i32 %9, !dbg !83
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv15221SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !84 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !85, metadata !DIExpression()), !dbg !86
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !87
  %2 = call i32 @"_$SN@sn.Core.System&5printCv15225SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.7) #5, !dbg !88
  ret i32 %2, !dbg !88
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv15225SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !89 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !90, metadata !DIExpression()), !dbg !91
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !92, metadata !DIExpression()), !dbg !91
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !93, metadata !DIExpression()), !dbg !94
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !95
  %3 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !95
  %4 = call %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15232SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !96
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !96
  %5 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !96
  %6 = call ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #5, !dbg !96
  store ptr %6, ptr %var.m, align 8, !dbg !96
  %7 = load ptr, ptr %var.m, align 8, !dbg !97
  %8 = load ptr, ptr %arg.end, align 8, !dbg !98
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.8, ptr %7, ptr %8), !dbg !99
  ret i32 %9, !dbg !99
}

; Function Attrs: noinline
define i32 @main() #0 personality ptr @sn.eh.personality !dbg !100 {
entry:
  call void @sn.runtime.initialize()
  %var.e = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.e, metadata !103, metadata !DIExpression()), !dbg !104
  %0 = alloca i8, align 1
  %1 = alloca ptr, align 8
  %2 = alloca ptr, align 8
  %3 = alloca { ptr, i32 }, align 8
  store { ptr, i32 } zeroinitializer, ptr %3, align 8
  br label %body

body:                                             ; preds = %entry
  br label %try, !dbg !104

try:                                              ; preds = %body
  %4 = call ptr @sn.alloca(i32 8), !dbg !105
  invoke void @"_$SN&9ExceptionCv15034ClsE&4#NwCCv15040SaA1_$SN&9ExceptionCv15034ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, ptr noundef nonnull align 8 dereferenceable(64) @.str.9)
          to label %invoke.normal unwind label %catch, !dbg !105

catch:                                            ; preds = %invoke.normal, %try
  %5 = landingpad { ptr, i32 }
          cleanup
          catch ptr @"snowball.typeidx._$SN&9ExceptionCv15034ClsE.r", !dbg !105
  %6 = call i32 (ptr, ...) @printf(ptr @0), !dbg !105
  %7 = extractvalue { ptr, i32 } %5, 0, !dbg !105
  %8 = extractvalue { ptr, i32 } %5, 1, !dbg !105
  store { ptr, i32 } %5, ptr %3, align 8, !dbg !105
  store ptr %2, ptr %2, align 8, !dbg !105
  store ptr %7, ptr %1, align 8, !dbg !105
  store i8 1, ptr %0, align 1, !dbg !105
  %9 = getelementptr inbounds { i64 }, ptr %7, i32 0, i32 0, !dbg !105
  %10 = load i64, ptr %9, align 8, !dbg !105
  %11 = icmp eq i64 %10, 31351929828503040, !dbg !105
  br i1 %11, label %catch.route, label %catch.external, !dbg !105

catch.route:                                      ; preds = %catch
  %12 = load { ptr, i32 }, ptr %3, align 8, !dbg !105
  %13 = extractvalue { ptr, i32 } %12, 0, !dbg !105
  %14 = getelementptr i8, ptr %13, i64 -16, !dbg !105
  %15 = load { { i32 }, ptr }, ptr %14, align 8, !dbg !105
  %16 = extractvalue { { i32 }, ptr } %15, 0, !dbg !105
  %17 = extractvalue { i32 } %16, 0, !dbg !105
  %18 = extractvalue { { i32 }, ptr } %15, 1, !dbg !105
  switch i32 %17, label %trycatch.fdepth [
    i32 1001, label %catch.block
  ], !dbg !105

catch.external:                                   ; preds = %catch
  unreachable, !dbg !105

catch.unwind:                                     ; No predecessors!
  %19 = load { ptr, i32 }, ptr %3, align 8, !dbg !105
  resume { ptr, i32 } %19, !dbg !105

try.end:                                          ; preds = %catch.block, %trycatch.fdepth, %invoke.normal1
  ret i32 0

invoke.normal:                                    ; preds = %try
  %20 = call ptr @sn.eh.create(ptr %4, i32 1000), !dbg !105
  invoke void @sn.eh.throw(ptr %20)
          to label %invoke.normal1 unwind label %catch, !dbg !105

invoke.normal1:                                   ; preds = %invoke.normal
  br label %try.end, !dbg !105

catch.block:                                      ; preds = %catch.route
  store ptr %18, ptr %var.e, align 8, !dbg !105
  %21 = call i32 @"_$SN@sn.Core.System&7printlnCv15221SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) @.str.10) #5, !dbg !106
  %22 = load ptr, ptr %var.e, align 8
  %23 = call ptr @"_$SN&9ExceptionCv15034ClsE&4whatCv15186SaA1_$SN&9ExceptionCv15034ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %22), !dbg !107
  %24 = call i32 @"_$SN@sn.Core.System&7printlnCv15240SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %23) #5, !dbg !108
  br label %try.end, !dbg !108

trycatch.fdepth:                                  ; preds = %catch.route
  br label %try.end, !dbg !105
}

; Function Attrs: noinline
declare noalias noundef nonnull ptr @sn.alloca(i32) #0

; Function Attrs: noinline nounwind
declare noalias noundef nonnull ptr @sn.eh.create(ptr, i32) #3

; Function Attrs: noinline
declare void @sn.eh.throw(ptr) #0

; Function Attrs: alwaysinline nounwind
declare void @sn.runtime.initialize() #4

attributes #0 = { noinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #1 = { nocallback nofree noinline nosync nounwind speculatable willreturn memory(none) "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #2 = { alwaysinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #3 = { noinline nounwind "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #4 = { alwaysinline nounwind "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #5 = { alwaysinline }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Snowball version 0.0.7", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "main.sn", directory: "tests")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 2, !"Snowball Compiler ID", i32 7}
!4 = !{i32 2, !"Snowball Compiler Version", [6 x i8] c"0.0.7\00"}
!5 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15251SaA1T4char.rFnE", scope: !6, file: !6, line: 391, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!6 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !12}
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::StringView<char>", scope: !6, file: !6, line: 315, baseType: !10, elements: !11)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<char>", scope: !6, file: !6, line: 177, elements: !11)
!11 = !{}
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!13 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed)
!14 = !DILocalVariable(name: "buffer", arg: 1, scope: !5, file: !1, line: 391, type: !12)
!15 = !DILocation(line: 391, column: 15, scope: !5)
!16 = !DILocation(line: 392, column: 54, scope: !5)
!17 = !DILocation(line: 392, column: 37, scope: !5)
!18 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15232SaA1T4char.rFnE", scope: !6, file: !6, line: 391, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!19 = !DILocalVariable(name: "buffer", arg: 1, scope: !18, file: !1, line: 391, type: !12)
!20 = !DILocation(line: 391, column: 15, scope: !18)
!21 = !DILocation(line: 392, column: 54, scope: !18)
!22 = !DILocation(line: 392, column: 37, scope: !18)
!23 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::what", linkageName: "_$SN&9ExceptionCv15034ClsE&4whatCv15186SaA1_$SN&9ExceptionCv15034ClsE.rFnE", scope: !6, file: !6, line: 152, type: !24, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!24 = !DISubroutineType(types: !25)
!25 = !{!12, !26}
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Exception", scope: !6, file: !6, line: 134, elements: !11)
!28 = !DILocalVariable(name: "self", arg: 1, scope: !23, file: !1, line: 152, type: !26)
!29 = !DILocation(line: 152, column: 8, scope: !23)
!30 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE", scope: !6, file: !6, line: 345, type: !31, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!31 = !DISubroutineType(types: !32)
!32 = !{!12, !33}
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!34 = !DILocalVariable(name: "self", arg: 1, scope: !30, file: !1, line: 345, type: !33)
!35 = !DILocation(line: 345, column: 8, scope: !30)
!36 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !6, file: !6, line: 327, type: !37, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!37 = !DISubroutineType(types: !38)
!38 = !{null, !33, !12}
!39 = !DILocalVariable(name: "self", arg: 1, scope: !36, file: !1, line: 327, type: !33)
!40 = !DILocation(line: 327, column: 5, scope: !36)
!41 = !DILocalVariable(name: "buffer", arg: 2, scope: !36, file: !1, line: 327, type: !12)
!42 = !DILocation(line: 349, column: 29, scope: !36)
!43 = !DILocation(line: 351, column: 27, scope: !36)
!44 = !DILocation(line: 353, column: 30, scope: !36)
!45 = !DILocation(line: 328, column: 23, scope: !36)
!46 = !DILocation(line: 328, column: 62, scope: !36)
!47 = !DILocation(line: 328, column: 39, scope: !36)
!48 = !DILocation(line: 329, column: 39, scope: !36)
!49 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::constructor", linkageName: "_$SN&8IterableCv15053ClsGStA1T4charClsE&4#NwCCv15056SaA1_$SN&8IterableCv15053ClsGStA1T4charClsE.rFnE", scope: !6, file: !6, line: 179, type: !50, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!50 = !DISubroutineType(types: !51)
!51 = !{null, !52}
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!53 = !DILocalVariable(name: "self", arg: 1, scope: !49, file: !1, line: 179, type: !52)
!54 = !DILocation(line: 179, column: 5, scope: !49)
!55 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::constructor", linkageName: "_$SN&9ExceptionCv15034ClsE&4#NwCCv15040SaA1_$SN&9ExceptionCv15034ClsE.rA2T4char.rFnE", scope: !6, file: !6, line: 140, type: !56, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!56 = !DISubroutineType(types: !57)
!57 = !{null, !26, !12}
!58 = !DILocalVariable(name: "self", arg: 1, scope: !55, file: !1, line: 140, type: !26)
!59 = !DILocation(line: 140, column: 5, scope: !55)
!60 = !DILocalVariable(name: "m", arg: 2, scope: !55, file: !1, line: 140, type: !12)
!61 = !DILocation(line: 140, column: 31, scope: !55)
!62 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv15240SaA1T4char.rFnE", scope: !63, file: !63, line: 27, type: !64, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!63 = !DIFile(filename: "System.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!64 = !DISubroutineType(types: !65)
!65 = !{!66, !12}
!66 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!67 = !DILocalVariable(name: "msg", arg: 1, scope: !62, file: !1, line: 27, type: !12)
!68 = !DILocation(line: 27, column: 15, scope: !62)
!69 = !DILocation(line: 28, column: 20, scope: !62)
!70 = !DILocation(line: 28, column: 14, scope: !62)
!71 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv15244SaA1T4char.rA2T4char.rFnE", scope: !63, file: !63, line: 16, type: !72, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!72 = !DISubroutineType(types: !73)
!73 = !{!66, !12, !12}
!74 = !DILocalVariable(name: "msg", arg: 1, scope: !71, file: !1, line: 16, type: !12)
!75 = !DILocation(line: 16, column: 15, scope: !71)
!76 = !DILocalVariable(name: "end", arg: 2, scope: !71, file: !1, line: 16, type: !12)
!77 = !DILocalVariable(name: "m", scope: !71, file: !1, line: 17, type: !12)
!78 = !DILocation(line: 17, column: 9, scope: !71)
!79 = !DILocation(line: 17, column: 26, scope: !71)
!80 = !DILocation(line: 17, column: 13, scope: !71)
!81 = !DILocation(line: 18, column: 33, scope: !71)
!82 = !DILocation(line: 18, column: 36, scope: !71)
!83 = !DILocation(line: 18, column: 12, scope: !71)
!84 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv15221SaA1T4char.rFnE", scope: !63, file: !63, line: 27, type: !64, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!85 = !DILocalVariable(name: "msg", arg: 1, scope: !84, file: !1, line: 27, type: !12)
!86 = !DILocation(line: 27, column: 15, scope: !84)
!87 = !DILocation(line: 28, column: 20, scope: !84)
!88 = !DILocation(line: 28, column: 14, scope: !84)
!89 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv15225SaA1T4char.rA2T4char.rFnE", scope: !63, file: !63, line: 16, type: !72, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!90 = !DILocalVariable(name: "msg", arg: 1, scope: !89, file: !1, line: 16, type: !12)
!91 = !DILocation(line: 16, column: 15, scope: !89)
!92 = !DILocalVariable(name: "end", arg: 2, scope: !89, file: !1, line: 16, type: !12)
!93 = !DILocalVariable(name: "m", scope: !89, file: !1, line: 17, type: !12)
!94 = !DILocation(line: 17, column: 9, scope: !89)
!95 = !DILocation(line: 17, column: 26, scope: !89)
!96 = !DILocation(line: 17, column: 13, scope: !89)
!97 = !DILocation(line: 18, column: 33, scope: !89)
!98 = !DILocation(line: 18, column: 36, scope: !89)
!99 = !DILocation(line: 18, column: 12, scope: !89)
!100 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 14, type: !101, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!101 = !DISubroutineType(types: !102)
!102 = !{!66}
!103 = !DILocalVariable(name: "e", scope: !100, file: !1, line: 15, type: !26)
!104 = !DILocation(line: 15, column: 5, scope: !100)
!105 = !DILocation(line: 16, column: 19, scope: !100)
!106 = !DILocation(line: 18, column: 9, scope: !100)
!107 = !DILocation(line: 19, column: 25, scope: !100)
!108 = !DILocation(line: 19, column: 9, scope: !100)

[1;31merror[1;37m: Unhandled exception: [0mHello, World!
 [1;32minfo[0m: You can export the enviroment variable `SN_BACKTRACE=1` to enable backtrace logging.

