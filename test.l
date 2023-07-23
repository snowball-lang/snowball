Lexer: 0.000088s
Parser: 0.000616s
Lexer: 0.000739s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Parser: 0.002062s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Lexer: 0.000228s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Parser: 0.000192s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Lexer: 0.000071s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Parser: 0.000258s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Simplifier: 0.009640s
Passes: 0.000030s
TypeChecker: 0.000030s (Core::CLib::c_string)
TypeChecker: 0.000055s (Core::CLib::__internal)
TypeChecker: 0.000020s (Core::CLib)
TypeChecker: 0.000011s (Core::_$core::Core::UA)
TypeChecker: 0.000002s (Core::_$core::Core::__internal)
TypeChecker: 0.000163s (Core::_$core::Core)
TypeChecker: 0.000004s (Core::_$core)
TypeChecker: 0.000073s (Core::System)
TypeChecker: 0.000043s ($main)
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
@.str.9 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.10 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@.str.11 = private unnamed_addr constant [14 x i8] c"Hello, World!\00", align 1
@.str.12 = private unnamed_addr constant [14 x i8] c"Hello, World!\00", align 1
@"snowball.typeidx._$SN&9ExceptionCv15034ClsE.r" = private unnamed_addr constant { i32 } { i32 1000 }
@0 = private unnamed_addr constant [11 x i8] c"error: %i\0A\00", align 1
@.str.13 = private unnamed_addr constant [19 x i8] c"Hello, World! 2222\00", align 1

; Function Attrs: noinline
declare i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64)) #0

; Function Attrs: nocallback nofree noinline nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline
declare i32 @sn.eh.personality(i32, i32, i64, ptr, ptr) #0

; Function Attrs: noinline
declare i32 @printf(ptr noundef nonnull align 8 dereferenceable(64), ...) #0

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15271SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !5 {
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
define internal %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15252SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !18 {
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

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15226SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !23 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %0, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !24, metadata !DIExpression()), !dbg !25
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.buffer, align 8, !dbg !26
  %2 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !27
  call void @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !27
  %3 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %2, align 8, !dbg !27
  ret %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %3, !dbg !27
}

; Function Attrs: noinline
define internal ptr @"_$SN&9ExceptionCv15034ClsE&4whatCv15186SaA1_$SN&9ExceptionCv15034ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !28 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !33, metadata !DIExpression()), !dbg !34
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !34
  %2 = load %"class._$SN&9ExceptionCv15034ClsE", ptr %1, align 8, !dbg !34
  %3 = extractvalue %"class._$SN&9ExceptionCv15034ClsE" %2, 0, !dbg !34
  ret ptr %3, !dbg !34
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !35 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !39, metadata !DIExpression()), !dbg !40
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !40
  %2 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %1, align 8, !dbg !40
  %3 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %2, 2, !dbg !40
  ret ptr %3, !dbg !40
}

; Function Attrs: noinline
define internal void @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !41 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !44, metadata !DIExpression()), !dbg !45
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !46, metadata !DIExpression()), !dbg !45
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !45
  call void @"_$SN&8IterableCv15053ClsGStA1T4charClsE&4#NwCCv15056SaA1_$SN&8IterableCv15053ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !45
  %3 = load ptr, ptr %arg.self, align 8, !dbg !45
  %4 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !45
  %5 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, 0, !dbg !45
  %6 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, i32 10, 0, !dbg !47
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %6, ptr %3, align 8, !dbg !47
  %7 = load ptr, ptr %arg.self, align 8, !dbg !45
  %8 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %7, align 8, !dbg !45
  %9 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %8, 1, !dbg !45
  %10 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %8, i32 0, 1, !dbg !48
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %10, ptr %7, align 8, !dbg !48
  %11 = load ptr, ptr %arg.self, align 8, !dbg !45
  %12 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %11, align 8, !dbg !45
  %13 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %12, 2, !dbg !45
  %14 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %12, ptr @.str.3, 2, !dbg !49
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %14, ptr %11, align 8, !dbg !49
  %15 = load ptr, ptr %arg.self, align 8, !dbg !45
  %16 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %15, align 8, !dbg !45
  %17 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %16, 2, !dbg !45
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !50
  %19 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %16, ptr %18, 2, !dbg !50
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %19, ptr %15, align 8, !dbg !50
  %20 = load ptr, ptr %arg.self, align 8, !dbg !45
  %21 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %20, align 8, !dbg !45
  %22 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %21, 1, !dbg !45
  %23 = load ptr, ptr %arg.buffer, align 8, !dbg !51
  %24 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %23), !dbg !52
  %25 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %21, i32 %24, 1, !dbg !52
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %25, ptr %20, align 8, !dbg !52
  %26 = load ptr, ptr %arg.self, align 8, !dbg !45
  %27 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %26, align 8, !dbg !45
  %28 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %27, 0, !dbg !45
  %29 = load ptr, ptr %arg.self, align 8, !dbg !45
  %30 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %29, align 8, !dbg !45
  %31 = extractvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %30, 1, !dbg !45
  %32 = add i32 %31, 10, !dbg !53
  %33 = insertvalue %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %27, i32 %32, 0, !dbg !53
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %33, ptr %26, align 8, !dbg !53
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv15053ClsGStA1T4charClsE&4#NwCCv15056SaA1_$SN&8IterableCv15053ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !54 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !58, metadata !DIExpression()), !dbg !59
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&9ExceptionCv15034ClsE&4#NwCCv15040SaA1_$SN&9ExceptionCv15034ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !60 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !63, metadata !DIExpression()), !dbg !64
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !65, metadata !DIExpression()), !dbg !64
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !64
  %3 = load %"class._$SN&9ExceptionCv15034ClsE", ptr %2, align 8, !dbg !64
  %4 = extractvalue %"class._$SN&9ExceptionCv15034ClsE" %3, 0, !dbg !64
  %5 = load ptr, ptr %arg.m, align 8, !dbg !66
  %6 = insertvalue %"class._$SN&9ExceptionCv15034ClsE" %3, ptr %5, 0, !dbg !66
  store %"class._$SN&9ExceptionCv15034ClsE" %6, ptr %2, align 8, !dbg !66
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv15260SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !67 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !72, metadata !DIExpression()), !dbg !73
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !74
  %2 = call i32 @"_$SN@sn.Core.System&5printCv15264SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.5) #5, !dbg !75
  ret i32 %2, !dbg !75
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv15264SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !76 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !79, metadata !DIExpression()), !dbg !80
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !81, metadata !DIExpression()), !dbg !80
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !82, metadata !DIExpression()), !dbg !83
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !84
  %3 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !84
  %4 = call %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15271SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !85
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !85
  %5 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !85
  %6 = call ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #5, !dbg !85
  store ptr %6, ptr %var.m, align 8, !dbg !85
  %7 = load ptr, ptr %var.m, align 8, !dbg !86
  %8 = load ptr, ptr %arg.end, align 8, !dbg !87
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.6, ptr %7, ptr %8), !dbg !88
  ret i32 %9, !dbg !88
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv15241SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !89 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !90, metadata !DIExpression()), !dbg !91
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !92
  %2 = call i32 @"_$SN@sn.Core.System&5printCv15245SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.7) #5, !dbg !93
  ret i32 %2, !dbg !93
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv15245SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !94 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !95, metadata !DIExpression()), !dbg !96
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !97, metadata !DIExpression()), !dbg !96
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !98, metadata !DIExpression()), !dbg !99
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !100
  %3 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !100
  %4 = call %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15252SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !101
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !101
  %5 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !101
  %6 = call ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #5, !dbg !101
  store ptr %6, ptr %var.m, align 8, !dbg !101
  %7 = load ptr, ptr %var.m, align 8, !dbg !102
  %8 = load ptr, ptr %arg.end, align 8, !dbg !103
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.8, ptr %7, ptr %8), !dbg !104
  ret i32 %9, !dbg !104
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv15215SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #2 personality ptr @sn.eh.personality !dbg !105 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !106, metadata !DIExpression()), !dbg !107
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !108
  %2 = call i32 @"_$SN@sn.Core.System&5printCv15219SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.9) #5, !dbg !109
  ret i32 %2, !dbg !109
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv15219SaA1T4char.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #2 personality ptr @sn.eh.personality !dbg !110 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !111, metadata !DIExpression()), !dbg !112
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !113, metadata !DIExpression()), !dbg !112
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !114, metadata !DIExpression()), !dbg !115
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !116
  %3 = alloca %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", align 8, !dbg !116
  %4 = call %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15226SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !117
  store %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !117
  %5 = load %"class._$SN&10StringViewCv15052ClsGStA1T4charClsE", ptr %3, align 8, !dbg !117
  %6 = call ptr @"_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #5, !dbg !117
  store ptr %6, ptr %var.m, align 8, !dbg !117
  %7 = load ptr, ptr %var.m, align 8, !dbg !118
  %8 = load ptr, ptr %arg.end, align 8, !dbg !119
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.10, ptr %7, ptr %8), !dbg !120
  ret i32 %9, !dbg !120
}

; Function Attrs: noinline
define i32 @main() #0 personality ptr @sn.eh.personality !dbg !121 {
entry:
  call void @sn.runtime.initialize()
  %var.e = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.e, metadata !124, metadata !DIExpression()), !dbg !125
  %0 = alloca { ptr, i32 }, align 8
  br label %body

body:                                             ; preds = %entry
  br label %try, !dbg !125

try:                                              ; preds = %body
  %1 = invoke i32 @"_$SN@sn.Core.System&7printlnCv15215SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) @.str.11) #5
          to label %invoke.normal unwind label %catch, !dbg !126

catch.route:                                      ; preds = %catch
  %2 = load { ptr, i32 }, ptr %0, align 8, !dbg !127
  %3 = extractvalue { ptr, i32 } %2, 0, !dbg !127
  %4 = getelementptr i8, ptr %3, i64 -16, !dbg !127
  %5 = load { ptr, ptr }, ptr %4, align 8, !dbg !127
  %6 = extractvalue { ptr, ptr } %5, 0, !dbg !127
  %7 = load i32, ptr %6, align 4, !dbg !127
  %8 = extractvalue { ptr, ptr } %5, 1, !dbg !127
  %9 = call i32 (ptr, ...) @printf(ptr @0, i32 %7), !dbg !127
  switch i32 %7, label %trycatch.fdepth [
    i32 1001, label %catch.block
  ], !dbg !127

catch:                                            ; preds = %invoke.normal1, %invoke.normal, %try
  %10 = landingpad { ptr, i32 }
          cleanup
          catch ptr @"snowball.typeidx._$SN&9ExceptionCv15034ClsE.r", !dbg !127
  %11 = extractvalue { ptr, i32 } %10, 0, !dbg !127
  store { ptr, i32 } %10, ptr %0, align 8, !dbg !127
  %12 = getelementptr inbounds { i64 }, ptr %11, i32 0, i32 0, !dbg !127
  %13 = load i64, ptr %12, align 8, !dbg !127
  %14 = icmp eq i64 %13, 31351929828503040, !dbg !127
  br i1 %14, label %catch.route, label %catch.external, !dbg !127

catch.external:                                   ; preds = %catch
  unreachable, !dbg !127

catch.unwind:                                     ; No predecessors!
  %15 = load { ptr, i32 }, ptr %0, align 8, !dbg !127
  resume { ptr, i32 } %15, !dbg !127

try.end:                                          ; preds = %catch.block, %trycatch.fdepth, %invoke.normal2
  ret i32 0

catch.block:                                      ; preds = %catch.route
  store ptr %8, ptr %var.e, align 8, !dbg !127
  %16 = call i32 @"_$SN@sn.Core.System&7printlnCv15241SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) @.str.13) #5, !dbg !128
  %17 = load ptr, ptr %var.e, align 8
  %18 = call ptr @"_$SN&9ExceptionCv15034ClsE&4whatCv15186SaA1_$SN&9ExceptionCv15034ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %17), !dbg !129
  %19 = call i32 @"_$SN@sn.Core.System&7printlnCv15260SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %18) #5, !dbg !130
  br label %try.end, !dbg !130

invoke.normal:                                    ; preds = %try
  %20 = call ptr @sn.alloca(i32 8), !dbg !127
  invoke void @"_$SN&9ExceptionCv15034ClsE&4#NwCCv15040SaA1_$SN&9ExceptionCv15034ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %20, ptr noundef nonnull align 8 dereferenceable(64) @.str.12)
          to label %invoke.normal1 unwind label %catch, !dbg !127

invoke.normal1:                                   ; preds = %invoke.normal
  %21 = call ptr @sn.eh.create(ptr %20, i32 1000), !dbg !127
  invoke void @sn.eh.throw(ptr %21)
          to label %invoke.normal2 unwind label %catch, !dbg !127

invoke.normal2:                                   ; preds = %invoke.normal1
  br label %try.end, !dbg !127

trycatch.fdepth:                                  ; preds = %catch.route
  br label %try.end, !dbg !127
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
!5 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15271SaA1T4char.rFnE", scope: !6, file: !6, line: 391, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
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
!18 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15252SaA1T4char.rFnE", scope: !6, file: !6, line: 391, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!19 = !DILocalVariable(name: "buffer", arg: 1, scope: !18, file: !1, line: 391, type: !12)
!20 = !DILocation(line: 391, column: 15, scope: !18)
!21 = !DILocation(line: 392, column: 54, scope: !18)
!22 = !DILocation(line: 392, column: 37, scope: !18)
!23 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4fromCv15226SaA1T4char.rFnE", scope: !6, file: !6, line: 391, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!24 = !DILocalVariable(name: "buffer", arg: 1, scope: !23, file: !1, line: 391, type: !12)
!25 = !DILocation(line: 391, column: 15, scope: !23)
!26 = !DILocation(line: 392, column: 54, scope: !23)
!27 = !DILocation(line: 392, column: 37, scope: !23)
!28 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::what", linkageName: "_$SN&9ExceptionCv15034ClsE&4whatCv15186SaA1_$SN&9ExceptionCv15034ClsE.rFnE", scope: !6, file: !6, line: 152, type: !29, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!29 = !DISubroutineType(types: !30)
!30 = !{!12, !31}
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64)
!32 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Exception", scope: !6, file: !6, line: 134, elements: !11)
!33 = !DILocalVariable(name: "self", arg: 1, scope: !28, file: !1, line: 152, type: !31)
!34 = !DILocation(line: 152, column: 8, scope: !28)
!35 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&5c_strCv15110SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rFnE", scope: !6, file: !6, line: 345, type: !36, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!36 = !DISubroutineType(types: !37)
!37 = !{!12, !38}
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!39 = !DILocalVariable(name: "self", arg: 1, scope: !35, file: !1, line: 345, type: !38)
!40 = !DILocation(line: 345, column: 8, scope: !35)
!41 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv15052ClsGStA1T4charClsE&4#NwCCv15085SaA1_$SN&10StringViewCv15052ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !6, file: !6, line: 327, type: !42, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!42 = !DISubroutineType(types: !43)
!43 = !{null, !38, !12}
!44 = !DILocalVariable(name: "self", arg: 1, scope: !41, file: !1, line: 327, type: !38)
!45 = !DILocation(line: 327, column: 5, scope: !41)
!46 = !DILocalVariable(name: "buffer", arg: 2, scope: !41, file: !1, line: 327, type: !12)
!47 = !DILocation(line: 349, column: 29, scope: !41)
!48 = !DILocation(line: 351, column: 27, scope: !41)
!49 = !DILocation(line: 353, column: 30, scope: !41)
!50 = !DILocation(line: 328, column: 23, scope: !41)
!51 = !DILocation(line: 328, column: 62, scope: !41)
!52 = !DILocation(line: 328, column: 39, scope: !41)
!53 = !DILocation(line: 329, column: 39, scope: !41)
!54 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::constructor", linkageName: "_$SN&8IterableCv15053ClsGStA1T4charClsE&4#NwCCv15056SaA1_$SN&8IterableCv15053ClsGStA1T4charClsE.rFnE", scope: !6, file: !6, line: 179, type: !55, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!55 = !DISubroutineType(types: !56)
!56 = !{null, !57}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!58 = !DILocalVariable(name: "self", arg: 1, scope: !54, file: !1, line: 179, type: !57)
!59 = !DILocation(line: 179, column: 5, scope: !54)
!60 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::constructor", linkageName: "_$SN&9ExceptionCv15034ClsE&4#NwCCv15040SaA1_$SN&9ExceptionCv15034ClsE.rA2T4char.rFnE", scope: !6, file: !6, line: 140, type: !61, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!61 = !DISubroutineType(types: !62)
!62 = !{null, !31, !12}
!63 = !DILocalVariable(name: "self", arg: 1, scope: !60, file: !1, line: 140, type: !31)
!64 = !DILocation(line: 140, column: 5, scope: !60)
!65 = !DILocalVariable(name: "m", arg: 2, scope: !60, file: !1, line: 140, type: !12)
!66 = !DILocation(line: 140, column: 31, scope: !60)
!67 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv15260SaA1T4char.rFnE", scope: !68, file: !68, line: 27, type: !69, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!68 = !DIFile(filename: "System.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!69 = !DISubroutineType(types: !70)
!70 = !{!71, !12}
!71 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!72 = !DILocalVariable(name: "msg", arg: 1, scope: !67, file: !1, line: 27, type: !12)
!73 = !DILocation(line: 27, column: 15, scope: !67)
!74 = !DILocation(line: 28, column: 20, scope: !67)
!75 = !DILocation(line: 28, column: 14, scope: !67)
!76 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv15264SaA1T4char.rA2T4char.rFnE", scope: !68, file: !68, line: 16, type: !77, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!77 = !DISubroutineType(types: !78)
!78 = !{!71, !12, !12}
!79 = !DILocalVariable(name: "msg", arg: 1, scope: !76, file: !1, line: 16, type: !12)
!80 = !DILocation(line: 16, column: 15, scope: !76)
!81 = !DILocalVariable(name: "end", arg: 2, scope: !76, file: !1, line: 16, type: !12)
!82 = !DILocalVariable(name: "m", scope: !76, file: !1, line: 17, type: !12)
!83 = !DILocation(line: 17, column: 9, scope: !76)
!84 = !DILocation(line: 17, column: 26, scope: !76)
!85 = !DILocation(line: 17, column: 13, scope: !76)
!86 = !DILocation(line: 18, column: 33, scope: !76)
!87 = !DILocation(line: 18, column: 36, scope: !76)
!88 = !DILocation(line: 18, column: 12, scope: !76)
!89 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv15241SaA1T4char.rFnE", scope: !68, file: !68, line: 27, type: !69, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!90 = !DILocalVariable(name: "msg", arg: 1, scope: !89, file: !1, line: 27, type: !12)
!91 = !DILocation(line: 27, column: 15, scope: !89)
!92 = !DILocation(line: 28, column: 20, scope: !89)
!93 = !DILocation(line: 28, column: 14, scope: !89)
!94 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv15245SaA1T4char.rA2T4char.rFnE", scope: !68, file: !68, line: 16, type: !77, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!95 = !DILocalVariable(name: "msg", arg: 1, scope: !94, file: !1, line: 16, type: !12)
!96 = !DILocation(line: 16, column: 15, scope: !94)
!97 = !DILocalVariable(name: "end", arg: 2, scope: !94, file: !1, line: 16, type: !12)
!98 = !DILocalVariable(name: "m", scope: !94, file: !1, line: 17, type: !12)
!99 = !DILocation(line: 17, column: 9, scope: !94)
!100 = !DILocation(line: 17, column: 26, scope: !94)
!101 = !DILocation(line: 17, column: 13, scope: !94)
!102 = !DILocation(line: 18, column: 33, scope: !94)
!103 = !DILocation(line: 18, column: 36, scope: !94)
!104 = !DILocation(line: 18, column: 12, scope: !94)
!105 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv15215SaA1T4char.rFnE", scope: !68, file: !68, line: 27, type: !69, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!106 = !DILocalVariable(name: "msg", arg: 1, scope: !105, file: !1, line: 27, type: !12)
!107 = !DILocation(line: 27, column: 15, scope: !105)
!108 = !DILocation(line: 28, column: 20, scope: !105)
!109 = !DILocation(line: 28, column: 14, scope: !105)
!110 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv15219SaA1T4char.rA2T4char.rFnE", scope: !68, file: !68, line: 16, type: !77, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!111 = !DILocalVariable(name: "msg", arg: 1, scope: !110, file: !1, line: 16, type: !12)
!112 = !DILocation(line: 16, column: 15, scope: !110)
!113 = !DILocalVariable(name: "end", arg: 2, scope: !110, file: !1, line: 16, type: !12)
!114 = !DILocalVariable(name: "m", scope: !110, file: !1, line: 17, type: !12)
!115 = !DILocation(line: 17, column: 9, scope: !110)
!116 = !DILocation(line: 17, column: 26, scope: !110)
!117 = !DILocation(line: 17, column: 13, scope: !110)
!118 = !DILocation(line: 18, column: 33, scope: !110)
!119 = !DILocation(line: 18, column: 36, scope: !110)
!120 = !DILocation(line: 18, column: 12, scope: !110)
!121 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 14, type: !122, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!122 = !DISubroutineType(types: !123)
!123 = !{!71}
!124 = !DILocalVariable(name: "e", scope: !121, file: !1, line: 15, type: !31)
!125 = !DILocation(line: 15, column: 5, scope: !121)
!126 = !DILocation(line: 16, column: 9, scope: !121)
!127 = !DILocation(line: 17, column: 19, scope: !121)
!128 = !DILocation(line: 19, column: 9, scope: !121)
!129 = !DILocation(line: 20, column: 25, scope: !121)
!130 = !DILocation(line: 20, column: 9, scope: !121)

[1;31merror[1;37m: Unhandled exception: [0mHello, World!
 [1;32minfo[0m: You can export the enviroment variable `SN_BACKTRACE=1` to enable backtrace logging.

