[2K[1;32m      Compiling[0m [>                                                                     ] 0 %[2K[1;32m      Compiling[0m [=====================>                                                ] 30 %[2K[1;32m      Compiling[0m [===================================>                                  ] 50 %[2K[1;32m      Compiling[0m [======================================>                               ] 55 %[2K[1;32m      Compiling[0m [==========================================>                           ] 60 %[2K[1;32m      Compiling[0m [=================================================>                    ] 69 %[2K[1;32m      Compiling[0m [========================================================>             ] 80 %[2K[1;32m      Compiling[0m [===============================================================>      ] 89 %[2K; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&6ParentCv4771ClsE" = type {}
%"vtable._$SN&5ChildCv4784ClsE" = type {}
%"class._$SN&6ParentCv4771ClsE" = type { %"vtable._$SN&6ParentCv4771ClsE"* }
%"class._$SN&5ChildCv4784ClsE" = type { %"vtable._$SN&5ChildCv4784ClsE"* }
%"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE" = type { %"vtable._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"*, i32, %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE" }
%"vtable._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE" = type {}
%"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE" = type { %"vtable._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* }
%"vtable._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE" = type {}
%"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE" = type { %"vtable._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"*, i32, %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE" }
%"vtable._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE" = type {}
%"class._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE" = type { %"vtable._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE"* }
%"vtable._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE" = type {}

@"vtable._$SN&6ParentCv4771ClsE" = global %"vtable._$SN&6ParentCv4771ClsE" zeroinitializer
@"vtable._$SN&5ChildCv4784ClsE" = global %"vtable._$SN&5ChildCv4784ClsE" zeroinitializer

; Function Attrs: noinline
define i32 @main() #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !3 {
entry:
  %0 = alloca %"class._$SN&6ParentCv4771ClsE"*, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&6ParentCv4771ClsE"** %0, metadata !8, metadata !DIExpression()), !dbg !11
  %1 = alloca %"class._$SN&5ChildCv4784ClsE"*, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&5ChildCv4784ClsE"** %1, metadata !12, metadata !DIExpression()), !dbg !15
  br label %body

body:                                             ; preds = %entry
  %2 = call i8* @sn.alloca(i32 8), !dbg !16
  %3 = bitcast i8* %2 to %"class._$SN&6ParentCv4771ClsE"*, !dbg !16
  %4 = getelementptr inbounds %"class._$SN&6ParentCv4771ClsE", %"class._$SN&6ParentCv4771ClsE"* %3, i32 0, i32 0, !dbg !16
  store %"vtable._$SN&6ParentCv4771ClsE"* @"vtable._$SN&6ParentCv4771ClsE", %"vtable._$SN&6ParentCv4771ClsE"** %4, align 8, !dbg !16
  call void @"_$SN&6ParentCv4771ClsE&4#NwCCv4772SaA1_$SN&6ParentCv4771ClsE.pFnE"(%"class._$SN&6ParentCv4771ClsE"* %3), !dbg !16
  %5 = load %"class._$SN&6ParentCv4771ClsE"*, %"class._$SN&6ParentCv4771ClsE"* %3, align 8, !dbg !16
  store %"class._$SN&6ParentCv4771ClsE"* %5, %"class._$SN&6ParentCv4771ClsE"** %0, align 8, !dbg !16
  %6 = call i8* @sn.alloca(i32 8), !dbg !17
  %7 = bitcast i8* %6 to %"class._$SN&5ChildCv4784ClsE"*, !dbg !17
  %8 = getelementptr inbounds %"class._$SN&5ChildCv4784ClsE", %"class._$SN&5ChildCv4784ClsE"* %7, i32 0, i32 0, !dbg !17
  store %"vtable._$SN&5ChildCv4784ClsE"* @"vtable._$SN&5ChildCv4784ClsE", %"vtable._$SN&5ChildCv4784ClsE"** %8, align 8, !dbg !17
  call void @"_$SN&5ChildCv4784ClsE&4#NwCCv4785SaA1_$SN&5ChildCv4784ClsE.pFnE"(%"class._$SN&5ChildCv4784ClsE"* %7), !dbg !17
  %9 = load %"class._$SN&5ChildCv4784ClsE"*, %"class._$SN&5ChildCv4784ClsE"* %7, align 8, !dbg !17
  store %"class._$SN&5ChildCv4784ClsE"* %9, %"class._$SN&5ChildCv4784ClsE"** %1, align 8, !dbg !17
  %10 = load %"class._$SN&6ParentCv4771ClsE"*, %"class._$SN&6ParentCv4771ClsE"** %0, align 8, !dbg !11
  call void @"_$SN&6ParentCv4771ClsE&4testCv4777SaA1_$SN&6ParentCv4771ClsE.pFnE"(%"class._$SN&6ParentCv4771ClsE"* %10), !dbg !18
  %11 = load %"class._$SN&5ChildCv4784ClsE"*, %"class._$SN&5ChildCv4784ClsE"** %1, align 8, !dbg !15
  %12 = bitcast %"class._$SN&5ChildCv4784ClsE"* %11 to %"class._$SN&6ParentCv4771ClsE"*, !dbg !15
  call void @"_$SN&6ParentCv4771ClsE&4testCv4777SaA1_$SN&6ParentCv4771ClsE.pFnE"(%"class._$SN&6ParentCv4771ClsE"* %12), !dbg !19
  ret i32 0
}

; Function Attrs: noinline
define void @"_$SN&5ChildCv4784ClsE&4#NwCCv4785SaA1_$SN&5ChildCv4784ClsE.pFnE"(%"class._$SN&5ChildCv4784ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !20 {
entry:
  %1 = alloca %"class._$SN&5ChildCv4784ClsE"*, align 8
  store %"class._$SN&5ChildCv4784ClsE"* %0, %"class._$SN&5ChildCv4784ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&5ChildCv4784ClsE"** %1, metadata !23, metadata !DIExpression()), !dbg !24
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define void @"_$SN&6ParentCv4771ClsE&4testCv4777SaA1_$SN&6ParentCv4771ClsE.pFnE"(%"class._$SN&6ParentCv4771ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !25 {
entry:
  %1 = alloca %"class._$SN&6ParentCv4771ClsE"*, align 8
  store %"class._$SN&6ParentCv4771ClsE"* %0, %"class._$SN&6ParentCv4771ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&6ParentCv4771ClsE"** %1, metadata !28, metadata !DIExpression()), !dbg !29
  br label %body

body:                                             ; preds = %entry
  %2 = call i32 @putchar(i8 80), !dbg !30
  ret void
}

; Function Attrs: noinline
define void @"_$SN&6ParentCv4771ClsE&4#NwCCv4772SaA1_$SN&6ParentCv4771ClsE.pFnE"(%"class._$SN&6ParentCv4771ClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !31 {
entry:
  %1 = alloca %"class._$SN&6ParentCv4771ClsE"*, align 8
  store %"class._$SN&6ParentCv4771ClsE"* %0, %"class._$SN&6ParentCv4771ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&6ParentCv4771ClsE"** %1, metadata !32, metadata !DIExpression()), !dbg !33
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
define void @"_$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE&4#NwCCv4765SaA1_$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !34 {
entry:
  %1 = alloca %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"* %0, %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"** %1, metadata !41, metadata !DIExpression()), !dbg !42
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"** %1, align 8, !dbg !42
  %3 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"* %2, i32 0, i32 1, !dbg !42
  %4 = load i32, i32* %3, align 4, !dbg !42
  store i32 0, i32* %3, align 4, !dbg !43
  %5 = load %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"** %1, align 8, !dbg !42
  %6 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE"* %5, i32 0, i32 2, !dbg !42
  %7 = load %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %6, align 8, !dbg !42
  %8 = alloca %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE", align 8, !dbg !44
  call void @"_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE&4#NwCCv4750SaA1_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %8), !dbg !44
  %9 = load %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %8, align 8, !dbg !44
  store %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE" %9, %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %6, align 8, !dbg !44
  ret void
}

; Function Attrs: noinline
define void @"_$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE&4#NwCCv4757SaA1_$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !45 {
entry:
  %1 = alloca %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"* %0, %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"** %1, metadata !46, metadata !DIExpression()), !dbg !47
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"** %1, align 8, !dbg !47
  %3 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"* %2, i32 0, i32 1, !dbg !47
  %4 = load i32, i32* %3, align 4, !dbg !47
  store i32 0, i32* %3, align 4, !dbg !48
  %5 = load %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"** %1, align 8, !dbg !47
  %6 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE"* %5, i32 0, i32 2, !dbg !47
  %7 = load %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %6, align 8, !dbg !47
  %8 = alloca %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE", align 8, !dbg !49
  call void @"_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE&4#NwCCv4750SaA1_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %8), !dbg !49
  %9 = load %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %8, align 8, !dbg !49
  store %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE" %9, %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %6, align 8, !dbg !49
  ret void
}

; Function Attrs: noinline
define void @"_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE&4#NwCCv4750SaA1_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !50 {
entry:
  %1 = alloca %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"* %0, %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE"** %1, metadata !55, metadata !DIExpression()), !dbg !56
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define void @"_$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE&4#NwCCv4743SaA1_$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE"* %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !57 {
entry:
  %1 = alloca %"class._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE"* %0, %"class._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE"** %1, metadata !61, metadata !DIExpression()), !dbg !62
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
!3 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 18, type: !4, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!7 = !{}
!8 = !DILocalVariable(name: "p", scope: !3, file: !1, line: 19, type: !9)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "Parent", scope: !1, file: !1, line: 3, elements: !7)
!11 = !DILocation(line: 19, column: 9, scope: !3)
!12 = !DILocalVariable(name: "c", scope: !3, file: !1, line: 20, type: !13)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!14 = !DICompositeType(tag: DW_TAG_structure_type, name: "Child", scope: !1, file: !1, line: 12, baseType: !10, elements: !7)
!15 = !DILocation(line: 20, column: 9, scope: !3)
!16 = !DILocation(line: 19, column: 17, scope: !3)
!17 = !DILocation(line: 20, column: 17, scope: !3)
!18 = !DILocation(line: 22, column: 5, scope: !3)
!19 = !DILocation(line: 23, column: 5, scope: !3)
!20 = distinct !DISubprogram(name: "Child::constructor", linkageName: "_$SN&5ChildCv4784ClsE&4#NwCCv4785SaA1_$SN&5ChildCv4784ClsE.pFnE", scope: !1, file: !1, line: 14, type: !21, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!21 = !DISubroutineType(types: !22)
!22 = !{null, !13}
!23 = !DILocalVariable(name: "self", scope: !20, file: !1, line: 14, type: !13)
!24 = !DILocation(line: 14, column: 9, scope: !20)
!25 = distinct !DISubprogram(name: "Parent::test", linkageName: "_$SN&6ParentCv4771ClsE&4testCv4777SaA1_$SN&6ParentCv4771ClsE.pFnE", scope: !1, file: !1, line: 7, type: !26, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!26 = !DISubroutineType(types: !27)
!27 = !{null, !9}
!28 = !DILocalVariable(name: "self", scope: !25, file: !1, line: 7, type: !9)
!29 = !DILocation(line: 7, column: 12, scope: !25)
!30 = !DILocation(line: 8, column: 13, scope: !25)
!31 = distinct !DISubprogram(name: "Parent::constructor", linkageName: "_$SN&6ParentCv4771ClsE&4#NwCCv4772SaA1_$SN&6ParentCv4771ClsE.pFnE", scope: !1, file: !1, line: 5, type: !26, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!32 = !DILocalVariable(name: "self", scope: !31, file: !1, line: 5, type: !9)
!33 = !DILocation(line: 5, column: 9, scope: !31)
!34 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::StringView<char*>::constructor", linkageName: "_$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE&4#NwCCv4765SaA1_$SN&24Core::_$core::StringViewCv4764ClsGStA1T4char.pClsE.pFnE", scope: !35, file: !35, line: 32, type: !36, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!35 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/.snowball/libs")
!36 = !DISubroutineType(types: !37)
!37 = !{null, !38}
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64)
!39 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::StringView<char*>", scope: !35, file: !35, line: 25, baseType: !40, elements: !7)
!40 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::Iterable<char*>", scope: !35, file: !35, line: 2, elements: !7)
!41 = !DILocalVariable(name: "self", scope: !34, file: !35, line: 32, type: !38)
!42 = !DILocation(line: 32, column: 5, scope: !34)
!43 = !DILocation(line: 33, column: 21, scope: !34)
!44 = !DILocation(line: 34, column: 25, scope: !34)
!45 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::StringView<char*>::constructor", linkageName: "_$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE&4#NwCCv4757SaA1_$SN&24Core::_$core::StringViewCv4756ClsGStA1T4char.pClsE.pFnE", scope: !35, file: !35, line: 32, type: !36, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!46 = !DILocalVariable(name: "self", scope: !45, file: !35, line: 32, type: !38)
!47 = !DILocation(line: 32, column: 5, scope: !45)
!48 = !DILocation(line: 33, column: 21, scope: !45)
!49 = !DILocation(line: 34, column: 25, scope: !45)
!50 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::Vector<char*>::constructor", linkageName: "_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE&4#NwCCv4750SaA1_$SN&20Core::_$core::VectorCv4749ClsGStA1T4char.pClsE.pFnE", scope: !35, file: !35, line: 9, type: !51, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!51 = !DISubroutineType(types: !52)
!52 = !{null, !53}
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64)
!54 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::Vector<char*>", scope: !35, file: !35, line: 7, baseType: !40, elements: !7)
!55 = !DILocalVariable(name: "self", scope: !50, file: !35, line: 9, type: !53)
!56 = !DILocation(line: 9, column: 5, scope: !50)
!57 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Core::_$core::Iterable<char*>::constructor", linkageName: "_$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE&4#NwCCv4743SaA1_$SN&22Core::_$core::IterableCv4742ClsGStA1T4char.pClsE.pFnE", scope: !35, file: !35, line: 4, type: !58, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!58 = !DISubroutineType(types: !59)
!59 = !{null, !60}
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64)
!61 = !DILocalVariable(name: "self", scope: !57, file: !35, line: 4, type: !60)
!62 = !DILocation(line: 4, column: 5, scope: !57)
PP