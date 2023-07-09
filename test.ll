[2K[1;32m      Compiling[0m [>                                                                     ] 0 %[2K[1;32m      Compiling[0m [=====================>                                                ] 30 %[2K[1;32m      Compiling[0m [===================================>                                  ] 50 %[2K[1;32m      Compiling[0m [======================================>                               ] 55 %[2K[1;32m      Compiling[0m [=================================================>                    ] 69 %[2K[1;32m      Compiling[0m [===============================================================>      ] 89 %[2K[1;32m      Compiling[0m [======================================================================] 100 %[2K; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class._$SN&10StringViewCv15430ClsGStA1T4charClsE" = type { %"vtable._$SN&10StringViewCv15430ClsGStA1T4charClsE"*, i32, i32, i8* }
%"vtable._$SN&10StringViewCv15430ClsGStA1T4charClsE" = type {}
%"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE" = type { %"vtable._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"*, i32, i32, %"struct._$SN&14UniversalArrayCv15386ClsE"* }
%"vtable._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE" = type {}
%"struct._$SN&14UniversalArrayCv15386ClsE" = type { i8** }

@.str = private unnamed_addr constant [6 x i8] c"hello\00", align 1

define i32 @main() !dbg !3 {
entry:
  %0 = alloca %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* %0, metadata !8, metadata !DIExpression()), !dbg !12
  %1 = alloca %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE", align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* %1, metadata !13, metadata !DIExpression()), !dbg !16
  %2 = alloca %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"*, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"** %2, metadata !17, metadata !DIExpression()), !dbg !19
  br label %body

body:                                             ; preds = %entry
  %3 = alloca %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE", align 8, !dbg !20
  %4 = call %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE" @"_$SN&10StringViewCv15430ClsGStA1T4charClsE&4fromCv15536SaA1T4char.pFnE"(i8* noundef nonnull align 8 dereferenceable(64) getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0)) #1, !dbg !21
  store %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE" %4, %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* %3, align 8, !dbg !21
  %5 = load %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE", %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* %3, align 8, !dbg !21
  store %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE" %5, %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* %0, align 8, !dbg !21
  %6 = alloca %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE", align 8, !dbg !22
  call void @"_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE&4#NwCCv15570SaA1_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE.pFnE"(%"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* noundef nonnull align 8 dereferenceable(64) %6), !dbg !22
  %7 = load %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE", %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* %6, align 8, !dbg !22
  store %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE" %7, %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* %1, align 8, !dbg !22
  %8 = load %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE", %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* %1, align 8, !dbg !16
  %9 = load %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE", %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* %0, align 8, !dbg !23
  call void @"_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE&4pushCv15576SaA1_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE.pA2_$SN&10StringViewCv15430ClsGStA1T4charClsE.pFnE"(%"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* noundef nonnull align 8 dereferenceable(64) %1, %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* noundef nonnull align 8 dereferenceable(64) %0), !dbg !24
  %10 = load %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE", %"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* %1, align 8, !dbg !16
  store i32 0, %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"** %2, align 4, !dbg !25
  %11 = load %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"*, %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"** %2, align 8, !dbg !19
  %12 = call i8* @"_$SN&10StringViewCv15430ClsGStA1T4charClsE&5c_strCv15474SaA1_$SN&10StringViewCv15430ClsGStA1T4charClsE.pFnE"(%"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* noundef nonnull align 8 dereferenceable(64) %11) #1, !dbg !26
  %13 = call i32 @"_$SN@sn.Core.System&7printlnCv15636SaA1T4char.pFnE"(i8* noundef nonnull align 8 dereferenceable(64) %12) #1, !dbg !27
  ret i32 0
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: alwaysinline
declare !dbg !28 internal %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE" @"_$SN&10StringViewCv15430ClsGStA1T4charClsE&4fromCv15536SaA1T4char.pFnE"(i8* noundef nonnull align 8 dereferenceable(64)) #1

declare !dbg !34 void @"_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE&4#NwCCv15570SaA1_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE.pFnE"(%"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* noundef nonnull align 8 dereferenceable(64))

declare !dbg !39 internal void @"_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE&4pushCv15576SaA1_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE.pA2_$SN&10StringViewCv15430ClsGStA1T4charClsE.pFnE"(%"class._$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE"* noundef nonnull align 8 dereferenceable(64), %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* noundef nonnull align 8 dereferenceable(64))

; Function Attrs: alwaysinline
declare !dbg !43 internal i32 @"_$SN@sn.Core.System&7printlnCv15636SaA1T4char.pFnE"(i8* noundef nonnull align 8 dereferenceable(64)) #1

; Function Attrs: alwaysinline
declare !dbg !48 internal i8* @"_$SN&10StringViewCv15430ClsGStA1T4charClsE&5c_strCv15474SaA1_$SN&10StringViewCv15430ClsGStA1T4charClsE.pFnE"(%"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"* noundef nonnull align 8 dereferenceable(64)) #1

attributes #0 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #1 = { alwaysinline }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Snowball version 0.0.7", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "main.sn", directory: "tests")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 3, type: !4, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!7 = !{}
!8 = !DILocalVariable(name: "s", scope: !3, file: !1, line: 4, type: !9)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::StringView<char>", scope: !10, file: !10, line: 227, baseType: !11, elements: !7)
!10 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/.snowball/stdlib")
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<char>", scope: !10, file: !10, line: 125, elements: !7)
!12 = !DILocation(line: 4, column: 7, scope: !3)
!13 = !DILocalVariable(name: "a", scope: !3, file: !1, line: 5, type: !14)
!14 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>>", scope: !10, file: !10, line: 143, baseType: !15, elements: !7)
!15 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<Core::_$core::Core::StringView<char>*>", scope: !10, file: !10, line: 125, elements: !7)
!16 = !DILocation(line: 5, column: 7, scope: !3)
!17 = !DILocalVariable(name: "x", scope: !3, file: !1, line: 8, type: !18)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!19 = !DILocation(line: 8, column: 7, scope: !3)
!20 = !DILocation(line: 4, column: 24, scope: !3)
!21 = !DILocation(line: 4, column: 11, scope: !3)
!22 = !DILocation(line: 5, column: 15, scope: !3)
!23 = !DILocation(line: 7, column: 11, scope: !3)
!24 = !DILocation(line: 7, column: 3, scope: !3)
!25 = !DILocation(line: 8, column: 13, scope: !3)
!26 = !DILocation(line: 10, column: 19, scope: !3)
!27 = !DILocation(line: 10, column: 3, scope: !3)
!28 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv15430ClsGStA1T4charClsE&4fromCv15536SaA1T4char.pFnE", scope: !10, file: !10, line: 266, type: !29, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !33)
!29 = !DISubroutineType(types: !30)
!30 = !{!9, !31}
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64)
!32 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed)
!33 = <temporary!> !{}
!34 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>>::constructor", linkageName: "_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE&4#NwCCv15570SaA1_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE.pFnE", scope: !10, file: !10, line: 149, type: !35, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !38)
!35 = !DISubroutineType(types: !36)
!36 = !{null, !37}
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!38 = <temporary!> !{}
!39 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<Core::_$core::Core::StringView<char>>::push", linkageName: "_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE&4pushCv15576SaA1_$SN&6VectorCv15542ClsGStA1_$SN&10StringViewCv15430ClsGStA1T4charClsEClsE.pA2_$SN&10StringViewCv15430ClsGStA1T4charClsE.pFnE", scope: !10, file: !10, line: 155, type: !40, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !42)
!40 = !DISubroutineType(types: !41)
!41 = !{null, !37, !18}
!42 = <temporary!> !{}
!43 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv15636SaA1T4char.pFnE", scope: !44, file: !44, line: 28, type: !45, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !47)
!44 = !DIFile(filename: "System.sn", directory: "/home/mauro/.snowball/stdlib")
!45 = !DISubroutineType(types: !46)
!46 = !{!6, !31}
!47 = <temporary!> !{}
!48 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv15430ClsGStA1T4charClsE&5c_strCv15474SaA1_$SN&10StringViewCv15430ClsGStA1T4charClsE.pFnE", scope: !10, file: !10, line: 250, type: !49, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !51)
!49 = !DISubroutineType(types: !50)
!50 = !{!31, !18}
!51 = <temporary!> !{}

[1;31merror[0m: ([0;31mLLVM internal error[0m) [1mStored value type does not match pointer operand type!
  store i32 0, %"class._$SN&10StringViewCv15430ClsGStA1T4charClsE"** %2, align 4, !dbg !25
 i32[0m
