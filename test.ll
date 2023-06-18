; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&1BCv4780ClsE" = type {}
%"vtable._$SN&1ACv4767ClsE" = type {}
%"class._$SN&1BCv4780ClsE" = type { %"vtable._$SN&1BCv4780ClsE"* }
%"class._$SN&1ACv4767ClsE" = type { %"vtable._$SN&1ACv4767ClsE"* }
%"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE" = type { %"vtable._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"*, i32, %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE" }
%"vtable._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE" = type {}
%"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE" = type { %"vtable._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* }
%"vtable._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE" = type {}
%"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE" = type { %"vtable._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"*, i32, %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE" }
%"vtable._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE" = type {}
%"class._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE" = type { %"vtable._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE"* }
%"vtable._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE" = type {}

@"vtable._$SN&1BCv4780ClsE" = global %"vtable._$SN&1BCv4780ClsE" zeroinitializer
@"vtable._$SN&1ACv4767ClsE" = global %"vtable._$SN&1ACv4767ClsE" zeroinitializer

; Function Attrs: noinline
define i32 @main() #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !3 {
entry:
  %0 = alloca %"class._$SN&1BCv4780ClsE"*, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1BCv4780ClsE"** %0, metadata !8, metadata !DIExpression()), !dbg !12
  %1 = alloca %"class._$SN&1ACv4767ClsE"*, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1ACv4767ClsE"** %1, metadata !13, metadata !DIExpression()), !dbg !15
  br label %body

body:                                             ; preds = %entry
  %2 = call i8* @sn.alloca(i32 8), !dbg !16
  %3 = bitcast i8* %2 to %"class._$SN&1BCv4780ClsE"*, !dbg !16
  %4 = getelementptr inbounds %"class._$SN&1BCv4780ClsE", %"class._$SN&1BCv4780ClsE"* %3, i32 0, i32 0, !dbg !16
  store %"vtable._$SN&1BCv4780ClsE"* @"vtable._$SN&1BCv4780ClsE", %"vtable._$SN&1BCv4780ClsE"** %4, align 8, !dbg !16
  call void @"_$SN&1BCv4780ClsE&4#NwCCv4785SaA1_$SN&1BCv4780ClsE.pFnE"(%"class._$SN&1BCv4780ClsE"* %3), !dbg !16
  %5 = load %"class._$SN&1BCv4780ClsE"*, %"class._$SN&1BCv4780ClsE"* %3, align 8, !dbg !16
  store %"class._$SN&1BCv4780ClsE"* %5, %"class._$SN&1BCv4780ClsE"** %0, align 8, !dbg !16
  %6 = call i8* @sn.alloca(i32 8), !dbg !17
  %7 = bitcast i8* %6 to %"class._$SN&1ACv4767ClsE"*, !dbg !17
  %8 = getelementptr inbounds %"class._$SN&1ACv4767ClsE", %"class._$SN&1ACv4767ClsE"* %7, i32 0, i32 0, !dbg !17
  store %"vtable._$SN&1ACv4767ClsE"* @"vtable._$SN&1ACv4767ClsE", %"vtable._$SN&1ACv4767ClsE"** %8, align 8, !dbg !17
  call void @"_$SN&1ACv4767ClsE&4#NwCCv4768SaA1_$SN&1ACv4767ClsE.pFnE"(%"class._$SN&1ACv4767ClsE"* %7), !dbg !17
  %9 = load %"class._$SN&1ACv4767ClsE"*, %"class._$SN&1ACv4767ClsE"* %7, align 8, !dbg !17
  store %"class._$SN&1ACv4767ClsE"* %9, %"class._$SN&1ACv4767ClsE"** %1, align 8, !dbg !17
  %10 = load %"class._$SN&1ACv4767ClsE"*, %"class._$SN&1ACv4767ClsE"** %1, align 8, !dbg !15
  call void @"_$SN&1ACv4767ClsE&5helloCv4773SaA1_$SN&1ACv4767ClsE.pFnE"(%"class._$SN&1ACv4767ClsE"* %10), !dbg !18
  %11 = load %"class._$SN&1BCv4780ClsE"*, %"class._$SN&1BCv4780ClsE"** %0, align 8, !dbg !12
  call void @"_$SN&1ACv4767ClsE&5helloCv4782SaA1_$SN&1BCv4780ClsE.pFnE"(%"class._$SN&1BCv4780ClsE"* %11), !dbg !19
  ret i32 0
}

; Function Attrs: noinline
define void @"_$SN&1BCv4780ClsE&5helloCv4790SaA1_$SN&1BCv4780ClsE.pFnE"(%"class._$SN&1BCv4780ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !20 {
entry:
  %1 = alloca %"class._$SN&1BCv4780ClsE"*, align 8
  store %"class._$SN&1BCv4780ClsE"* %0, %"class._$SN&1BCv4780ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1BCv4780ClsE"** %1, metadata !23, metadata !DIExpression()), !dbg !24
  br label %body

body:                                             ; preds = %entry
  %2 = call i32 @putchar(i8 66), !dbg !25
  ret void
}

; Function Attrs: noinline
define void @"_$SN&1BCv4780ClsE&4#NwCCv4785SaA1_$SN&1BCv4780ClsE.pFnE"(%"class._$SN&1BCv4780ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !26 {
entry:
  %1 = alloca %"class._$SN&1BCv4780ClsE"*, align 8
  store %"class._$SN&1BCv4780ClsE"* %0, %"class._$SN&1BCv4780ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1BCv4780ClsE"** %1, metadata !27, metadata !DIExpression()), !dbg !28
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define void @"_$SN&1ACv4767ClsE&5helloCv4782SaA1_$SN&1BCv4780ClsE.pFnE"(%"class._$SN&1BCv4780ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !29 {
entry:
  %1 = alloca %"class._$SN&1BCv4780ClsE"*, align 8
  store %"class._$SN&1BCv4780ClsE"* %0, %"class._$SN&1BCv4780ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1BCv4780ClsE"** %1, metadata !30, metadata !DIExpression()), !dbg !31
  br label %body

body:                                             ; preds = %entry
  %2 = call i32 @putchar(i8 97), !dbg !32
  ret void
}

; Function Attrs: noinline
define void @"_$SN&1ACv4767ClsE&5helloCv4773SaA1_$SN&1ACv4767ClsE.pFnE"(%"class._$SN&1ACv4767ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !33 {
entry:
  %1 = alloca %"class._$SN&1ACv4767ClsE"*, align 8
  store %"class._$SN&1ACv4767ClsE"* %0, %"class._$SN&1ACv4767ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1ACv4767ClsE"** %1, metadata !36, metadata !DIExpression()), !dbg !37
  br label %body

body:                                             ; preds = %entry
  %2 = call i32 @putchar(i8 97), !dbg !38
  ret void
}

; Function Attrs: noinline
define void @"_$SN&1ACv4767ClsE&4#NwCCv4768SaA1_$SN&1ACv4767ClsE.pFnE"(%"class._$SN&1ACv4767ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !39 {
entry:
  %1 = alloca %"class._$SN&1ACv4767ClsE"*, align 8
  store %"class._$SN&1ACv4767ClsE"* %0, %"class._$SN&1ACv4767ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&1ACv4767ClsE"** %1, metadata !40, metadata !DIExpression()), !dbg !41
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: nofree noinline nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline
declare i8* @sn.alloca(i32) #0

; Function Attrs: noinline
declare i32 @sn.core.eh.personality(i32, i32, i64, i8*, i8*) #0

; Function Attrs: noinline
declare i32 @putchar(i8) #0

; Function Attrs: noinline
define void @"_$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE&4#NwCCv4761SaA1_$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !42 {
entry:
  %1 = alloca %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"* %0, %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"** %1, metadata !49, metadata !DIExpression()), !dbg !50
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"** %1, align 8, !dbg !50
  %3 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"* %2, i32 0, i32 1, !dbg !50
  %4 = load i32, i32* %3, align 4, !dbg !50
  store i32 0, i32* %3, align 4, !dbg !51
  %5 = load %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"** %1, align 8, !dbg !50
  %6 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE"* %5, i32 0, i32 2, !dbg !50
  %7 = load %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %6, align 8, !dbg !50
  %8 = alloca %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE", align 8, !dbg !52
  call void @"_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE&4#NwCCv4746SaA1_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %8), !dbg !52
  %9 = load %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %8, align 8, !dbg !52
  store %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE" %9, %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %6, align 8, !dbg !52
  ret void
}

; Function Attrs: noinline
define void @"_$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE&4#NwCCv4753SaA1_$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !53 {
entry:
  %1 = alloca %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"* %0, %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"** %1, metadata !54, metadata !DIExpression()), !dbg !55
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"** %1, align 8, !dbg !55
  %3 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"* %2, i32 0, i32 1, !dbg !55
  %4 = load i32, i32* %3, align 4, !dbg !55
  store i32 0, i32* %3, align 4, !dbg !56
  %5 = load %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"** %1, align 8, !dbg !55
  %6 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE"* %5, i32 0, i32 2, !dbg !55
  %7 = load %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %6, align 8, !dbg !55
  %8 = alloca %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE", align 8, !dbg !57
  call void @"_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE&4#NwCCv4746SaA1_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %8), !dbg !57
  %9 = load %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %8, align 8, !dbg !57
  store %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE" %9, %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %6, align 8, !dbg !57
  ret void
}

; Function Attrs: noinline
define void @"_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE&4#NwCCv4746SaA1_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !58 {
entry:
  %1 = alloca %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"* %0, %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE"** %1, metadata !63, metadata !DIExpression()), !dbg !64
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define void @"_$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE&4#NwCCv4739SaA1_$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !65 {
entry:
  %1 = alloca %"class._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE"* %0, %"class._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE"** %1, metadata !69, metadata !DIExpression()), !dbg !70
  br label %body

body:                                             ; preds = %entry
  ret void
}

attributes #0 = { noinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #1 = { nofree noinline nosync nounwind readnone speculatable willreturn "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Snowball version 0.0.1", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "main.sn", directory: "tests")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 24, type: !4, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!7 = !{}
!8 = !DILocalVariable(name: "b", scope: !3, file: !1, line: 25, type: !9)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "B", scope: !1, file: !1, line: 13, baseType: !11, elements: !7)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "A", scope: !1, file: !1, line: 3, elements: !7)
!12 = !DILocation(line: 25, column: 9, scope: !3)
!13 = !DILocalVariable(name: "a", scope: !3, file: !1, line: 26, type: !14)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!15 = !DILocation(line: 26, column: 9, scope: !3)
!16 = !DILocation(line: 25, column: 17, scope: !3)
!17 = !DILocation(line: 26, column: 17, scope: !3)
!18 = !DILocation(line: 28, column: 5, scope: !3)
!19 = !DILocation(line: 29, column: 5, scope: !3)
!20 = distinct !DISubprogram(name: "B::hello", linkageName: "_$SN&1BCv4780ClsE&5helloCv4790SaA1_$SN&1BCv4780ClsE.pFnE", scope: !1, file: !1, line: 19, type: !21, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!21 = !DISubroutineType(types: !22)
!22 = !{null, !9}
!23 = !DILocalVariable(name: "self", scope: !20, file: !1, line: 19, type: !9)
!24 = !DILocation(line: 19, column: 8, scope: !20)
!25 = !DILocation(line: 20, column: 7, scope: !20)
!26 = distinct !DISubprogram(name: "B::constructor", linkageName: "_$SN&1BCv4780ClsE&4#NwCCv4785SaA1_$SN&1BCv4780ClsE.pFnE", scope: !1, file: !1, line: 15, type: !21, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!27 = !DILocalVariable(name: "self", scope: !26, file: !1, line: 15, type: !9)
!28 = !DILocation(line: 15, column: 5, scope: !26)
!29 = distinct !DISubprogram(name: "A::hello", linkageName: "_$SN&1ACv4767ClsE&5helloCv4782SaA1_$SN&1BCv4780ClsE.pFnE", scope: !1, file: !1, line: 8, type: !21, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!30 = !DILocalVariable(name: "self", scope: !29, file: !1, line: 8, type: !9)
!31 = !DILocation(line: 8, column: 8, scope: !29)
!32 = !DILocation(line: 9, column: 7, scope: !29)
!33 = distinct !DISubprogram(name: "A::hello", linkageName: "_$SN&1ACv4767ClsE&5helloCv4773SaA1_$SN&1ACv4767ClsE.pFnE", scope: !1, file: !1, line: 8, type: !34, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!34 = !DISubroutineType(types: !35)
!35 = !{null, !14}
!36 = !DILocalVariable(name: "self", scope: !33, file: !1, line: 8, type: !14)
!37 = !DILocation(line: 8, column: 8, scope: !33)
!38 = !DILocation(line: 9, column: 7, scope: !33)
!39 = distinct !DISubprogram(name: "A::constructor", linkageName: "_$SN&1ACv4767ClsE&4#NwCCv4768SaA1_$SN&1ACv4767ClsE.pFnE", scope: !1, file: !1, line: 5, type: !34, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!40 = !DILocalVariable(name: "self", scope: !39, file: !1, line: 5, type: !14)
!41 = !DILocation(line: 5, column: 5, scope: !39)
!42 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::StringView<char*>::constructor", linkageName: "_$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE&4#NwCCv4761SaA1_$SN&24Core::_$core::StringViewCv4760ClsGStA1T4char.pClsE.pFnE", scope: !43, file: !43, line: 32, type: !44, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!43 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/.snowball/libs")
!44 = !DISubroutineType(types: !45)
!45 = !{null, !46}
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64)
!47 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::StringView<char*>", scope: !43, file: !43, line: 25, baseType: !48, elements: !7)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::Iterable<char*>", scope: !43, file: !43, line: 2, elements: !7)
!49 = !DILocalVariable(name: "self", scope: !42, file: !43, line: 32, type: !46)
!50 = !DILocation(line: 32, column: 5, scope: !42)
!51 = !DILocation(line: 33, column: 21, scope: !42)
!52 = !DILocation(line: 34, column: 25, scope: !42)
!53 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::StringView<char*>::constructor", linkageName: "_$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE&4#NwCCv4753SaA1_$SN&24Core::_$core::StringViewCv4752ClsGStA1T4char.pClsE.pFnE", scope: !43, file: !43, line: 32, type: !44, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!54 = !DILocalVariable(name: "self", scope: !53, file: !43, line: 32, type: !46)
!55 = !DILocation(line: 32, column: 5, scope: !53)
!56 = !DILocation(line: 33, column: 21, scope: !53)
!57 = !DILocation(line: 34, column: 25, scope: !53)
!58 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::Vector<char*>::constructor", linkageName: "_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE&4#NwCCv4746SaA1_$SN&20Core::_$core::VectorCv4745ClsGStA1T4char.pClsE.pFnE", scope: !43, file: !43, line: 9, type: !59, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!59 = !DISubroutineType(types: !60)
!60 = !{null, !61}
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64)
!62 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::Vector<char*>", scope: !43, file: !43, line: 7, baseType: !48, elements: !7)
!63 = !DILocalVariable(name: "self", scope: !58, file: !43, line: 9, type: !61)
!64 = !DILocation(line: 9, column: 5, scope: !58)
!65 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::Iterable<char*>::constructor", linkageName: "_$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE&4#NwCCv4739SaA1_$SN&22Core::_$core::IterableCv4738ClsGStA1T4char.pClsE.pFnE", scope: !43, file: !43, line: 4, type: !66, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!66 = !DISubroutineType(types: !67)
!67 = !{null, !68}
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64)
!69 = !DILocalVariable(name: "self", scope: !65, file: !43, line: 4, type: !68)
!70 = !DILocation(line: 4, column: 5, scope: !65)
aa