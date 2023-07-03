[2K
[1;32m      Compiling[0m [>                                                                     ] 0 %
[2K
[1;32m      Compiling[0m [=====================>                                                ] 30 %
[2K
[1;32m      Compiling[0m [===================================>                                  ] 50 %
[2K
[1;32m      Compiling[0m [======================================>                               ] 55 %
[2K
[1;32m      Compiling[0m [==========================================>                           ] 60 %
[2K
[1;32m      Compiling[0m [=================================================>                    ] 69 %
[2K
[1;32m      Compiling[0m [========================================================>             ] 80 %
[2K
[1;32m      Compiling[0m [===============================================================>      ] 89 %
[2K
; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&6ParentCv4934ClsE" = type {}
%"class._$SN&6ParentCv4934ClsE" = type { %"vtable._$SN&6ParentCv4934ClsE"*, i32, i32 }
%"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE" = type { %"vtable._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"*, i32, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE" }
%"vtable._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE" = type {}
%"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE" = type { %"vtable._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* }
%"vtable._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE" = type {}
%"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE" = type { %"vtable._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"* }
%"vtable._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE" = type {}
%"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE" = type { %"vtable._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"*, i32, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE" }
%"vtable._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE" = type {}

@"vtable._$SN&6ParentCv4934ClsE" = global %"vtable._$SN&6ParentCv4934ClsE" zeroinitializer

; Function Attrs: noinline
define i32 @main() #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !3 {
entry:
  %0 = alloca %"class._$SN&6ParentCv4934ClsE"*, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&6ParentCv4934ClsE"** %0, metadata !8, metadata !DIExpression()), !dbg !11
  %1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %1, metadata !12, metadata !DIExpression()), !dbg !13
  br label %body

body:                                             ; preds = %entry
  %2 = call i8* @sn.alloca(i32 8), !dbg !14
  %3 = bitcast i8* %2 to %"class._$SN&6ParentCv4934ClsE"*, !dbg !14
  %4 = getelementptr inbounds %"class._$SN&6ParentCv4934ClsE", %"class._$SN&6ParentCv4934ClsE"* %3, i32 0, i32 0, !dbg !14
  store %"vtable._$SN&6ParentCv4934ClsE"* @"vtable._$SN&6ParentCv4934ClsE", %"vtable._$SN&6ParentCv4934ClsE"** %4, align 8, !dbg !14
  call void @"_$SN&6ParentCv4934ClsE&4#NwCCv4935SaA1_$SN&6ParentCv4934ClsE.pFnE"(%"class._$SN&6ParentCv4934ClsE"* noundef nonnull align 8 dereferenceable(64) %3), !dbg !14
  store %"class._$SN&6ParentCv4934ClsE"* %3, %"class._$SN&6ParentCv4934ClsE"** %0, align 8, !dbg !14
  store i32 0, i32* %1, align 4, !dbg !15
  br label %5, !dbg !16

5:                                                ; preds = %8, %body
  %6 = load i32, i32* %1, align 4, !dbg !13
  %7 = icmp slt i32 %6, 10, !dbg !17
  br i1 %7, label %8, label %17, !dbg !17

8:                                                ; preds = %5
  %9 = load %"class._$SN&6ParentCv4934ClsE"*, %"class._$SN&6ParentCv4934ClsE"** %0, align 8, !dbg !11
  %10 = getelementptr inbounds %"class._$SN&6ParentCv4934ClsE", %"class._$SN&6ParentCv4934ClsE"* %9, i32 0, i32 2, !dbg !11
  %11 = load i32, i32* %10, align 4, !dbg !11
  %12 = trunc i32 %11 to i8, !dbg !11
  %13 = call i32 @putchar(i8 %12), !dbg !18
  %14 = load i32, i32* %1, align 4, !dbg !13
  %15 = load i32, i32* %1, align 4, !dbg !13
  %16 = add i32 %15, 1, !dbg !19
  store i32 %16, i32* %1, align 4, !dbg !19
  br label %5, !dbg !19

17:                                               ; preds = %5
  ret i32 0
}

; Function Attrs: noinline
define void @"_$SN&6ParentCv4934ClsE&4#NwCCv4935SaA1_$SN&6ParentCv4934ClsE.pFnE"(%"class._$SN&6ParentCv4934ClsE"* noundef nonnull align 8 dereferenceable(64) %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !20 {
entry:
  %1 = alloca %"class._$SN&6ParentCv4934ClsE"*, align 8
  store %"class._$SN&6ParentCv4934ClsE"* %0, %"class._$SN&6ParentCv4934ClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&6ParentCv4934ClsE"** %1, metadata !23, metadata !DIExpression()), !dbg !24
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&6ParentCv4934ClsE"*, %"class._$SN&6ParentCv4934ClsE"** %1, align 8, !dbg !24
  %3 = getelementptr inbounds %"class._$SN&6ParentCv4934ClsE", %"class._$SN&6ParentCv4934ClsE"* %2, i32 0, i32 2, !dbg !24 ; get a
  %4 = load i32, i32* %3, align 4, !dbg !24
  %5 = load %"class._$SN&6ParentCv4934ClsE"*, %"class._$SN&6ParentCv4934ClsE"** %1, align 8, !dbg !24
  %6 = getelementptr inbounds %"class._$SN&6ParentCv4934ClsE", %"class._$SN&6ParentCv4934ClsE"* %5, i32 0, i32 1, !dbg !24 ; get b
  %7 = load i32, i32* %6, align 4, !dbg !24                                                                                       
  store i32 %7, i32* %3, align 4, !dbg !24                                                                                 ; insert b into a (b is not set yet)
  %8 = load %"class._$SN&6ParentCv4934ClsE"*, %"class._$SN&6ParentCv4934ClsE"** %1, align 8, !dbg !24                    
  %9 = getelementptr inbounds %"class._$SN&6ParentCv4934ClsE", %"class._$SN&6ParentCv4934ClsE"* %8, i32 0, i32 1, !dbg !24 ; get b (again)
  %10 = load i32, i32* %9, align 4, !dbg !24                                
  store i32 120, i32* %9, align 4, !dbg !25                                                                                ; inser 120 ('x') into b
  ret void
}

; Function Attrs: nofree noinline nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline
declare noalias noundef nonnull i8* @sn.alloca(i32) #0

; Function Attrs: noinline
declare i32 @putchar(i8) #0

; Function Attrs: noinline
declare i32 @sn.core.eh.personality(i32, i32, i64, i8*, i8*) #0

; Function Attrs: noinline
define void @"_$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE&4#NwCCv4920SaA1_$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !26 {
entry:
  %1 = alloca %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"* %0, %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"** %1, metadata !33, metadata !DIExpression()), !dbg !34
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"** %1, align 8, !dbg !34
  %3 = bitcast %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"* %2 to %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"*, !dbg !34
  call void @"_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE&4#NwCCv4872SaA1_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %3), !dbg !34
  %4 = load %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"** %1, align 8, !dbg !34
  %5 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"* %4, i32 0, i32 1, !dbg !34
  %6 = load i32, i32* %5, align 4, !dbg !34
  store i32 0, i32* %5, align 4, !dbg !35
  %7 = load %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"** %1, align 8, !dbg !34
  %8 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE"* %7, i32 0, i32 2, !dbg !34
  %9 = load %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %8, align 8, !dbg !34
  %10 = alloca %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE", align 8, !dbg !36
  call void @"_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE&4#NwCCv4885SaA1_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %10), !dbg !36
  %11 = load %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %10, align 8, !dbg !36
  store %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE" %11, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %8, align 8, !dbg !36
  ret void
}

; Function Attrs: noinline
define void @"_$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE&4#NwCCv4904SaA1_$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !37 {
entry:
  %1 = alloca %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"* %0, %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"** %1, metadata !38, metadata !DIExpression()), !dbg !39
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"** %1, align 8, !dbg !39
  %3 = bitcast %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"* %2 to %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"*, !dbg !39
  call void @"_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE&4#NwCCv4872SaA1_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %3), !dbg !39
  %4 = load %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"** %1, align 8, !dbg !39
  %5 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"* %4, i32 0, i32 1, !dbg !39
  %6 = load i32, i32* %5, align 4, !dbg !39
  store i32 0, i32* %5, align 4, !dbg !40
  %7 = load %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"*, %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"** %1, align 8, !dbg !39
  %8 = getelementptr inbounds %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE", %"class._$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE"* %7, i32 0, i32 2, !dbg !39
  %9 = load %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %8, align 8, !dbg !39
  %10 = alloca %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE", align 8, !dbg !41
  call void @"_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE&4#NwCCv4885SaA1_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %10), !dbg !41
  %11 = load %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE", %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %10, align 8, !dbg !41
  store %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE" %11, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %8, align 8, !dbg !41
  ret void
}

; Function Attrs: noinline
define void @"_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE&9push_backCv4891SaA1_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE.pA2T4char.pFnE"(%"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %0, i8* noundef nonnull align 8 dereferenceable(64) %1) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !42 {
entry:
  %2 = alloca %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %0, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"** %2, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"** %2, metadata !49, metadata !DIExpression()), !dbg !50
  %3 = alloca i8*, align 8
  store i8* %1, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !51, metadata !DIExpression()), !dbg !50
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: noinline
define void @"_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE&4#NwCCv4885SaA1_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !52 {
entry:
  %1 = alloca %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %0, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"** %1, metadata !55, metadata !DIExpression()), !dbg !56
  br label %body

body:                                             ; preds = %entry
  %2 = load %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"*, %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"** %1, align 8, !dbg !56
  %3 = bitcast %"class._$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE"* %2 to %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"*, !dbg !56
  call void @"_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE&4#NwCCv4872SaA1_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %3), !dbg !56
  ret void
}

; Function Attrs: noinline
define void @"_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE&4#NwCCv4872SaA1_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE.pFnE"(%"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"* noundef nonnull align 8 dereferenceable(64) %0) #0 personality i32 (i32, i32, i64, i8*, i8*)* @sn.core.eh.personality !dbg !57 {
entry:
  %1 = alloca %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"*, align 8
  store %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"* %0, %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"** %1, align 8
  call void @llvm.dbg.declare(metadata %"class._$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE"** %1, metadata !61, metadata !DIExpression()), !dbg !62
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
!3 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 11, type: !4, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!7 = !{}
!8 = !DILocalVariable(name: "p", scope: !3, file: !1, line: 12, type: !9)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "Parent", scope: !1, file: !1, line: 3, elements: !7)
!11 = !DILocation(line: 12, column: 9, scope: !3)
!12 = !DILocalVariable(name: "i", scope: !3, file: !1, line: 14, type: !6)
!13 = !DILocation(line: 14, column: 13, scope: !3)
!14 = !DILocation(line: 12, column: 17, scope: !3)
!15 = !DILocation(line: 14, column: 17, scope: !3)
!16 = !DILocation(line: 15, column: 5, scope: !3)
!17 = !DILocation(line: 15, column: 15, scope: !3)
!18 = !DILocation(line: 16, column: 7, scope: !3)
!19 = !DILocation(line: 17, column: 15, scope: !3)
!20 = distinct !DISubprogram(name: "Parent::constructor", linkageName: "_$SN&6ParentCv4934ClsE&4#NwCCv4935SaA1_$SN&6ParentCv4934ClsE.pFnE", scope: !1, file: !1, line: 7, type: !21, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!21 = !DISubroutineType(types: !22)
!22 = !{null, !9}
!23 = !DILocalVariable(name: "self", scope: !20, file: !1, line: 7, type: !9)
!24 = !DILocation(line: 7, column: 5, scope: !20)
!25 = !DILocation(line: 5, column: 22, scope: !20)
!26 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::StringView<char*>::constructor", linkageName: "_$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE&4#NwCCv4920SaA1_$SN&24Core::_$core::StringViewCv4918ClsGStA1T4char.pClsE.pFnE", scope: !27, file: !27, line: 34, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!27 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/.snowball/libs")
!28 = !DISubroutineType(types: !29)
!29 = !{null, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::StringView<char*>", scope: !27, file: !27, line: 27, baseType: !32, elements: !7)
!32 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::Iterable<char*>", scope: !27, file: !27, line: 2, elements: !7)
!33 = !DILocalVariable(name: "self", scope: !26, file: !1, line: 34, type: !30)
!34 = !DILocation(line: 34, column: 5, scope: !26)
!35 = !DILocation(line: 35, column: 21, scope: !26)
!36 = !DILocation(line: 36, column: 25, scope: !26)
!37 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::StringView<char*>::constructor", linkageName: "_$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE&4#NwCCv4904SaA1_$SN&24Core::_$core::StringViewCv4869ClsGStA1T4char.pClsE.pFnE", scope: !27, file: !27, line: 34, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!38 = !DILocalVariable(name: "self", scope: !37, file: !1, line: 34, type: !30)
!39 = !DILocation(line: 34, column: 5, scope: !37)
!40 = !DILocation(line: 35, column: 21, scope: !37)
!41 = !DILocation(line: 36, column: 25, scope: !37)
!42 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Vector<char*>::push_back", linkageName: "_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE&9push_backCv4891SaA1_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE.pA2T4char.pFnE", scope: !27, file: !27, line: 11, type: !43, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!43 = !DISubroutineType(types: !44)
!44 = !{null, !45, !47}
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64)
!46 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::_$core::Vector<char*>", scope: !27, file: !27, line: 7, baseType: !32, elements: !7)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64)
!48 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed)
!49 = !DILocalVariable(name: "self", scope: !42, file: !1, line: 11, type: !45)
!50 = !DILocation(line: 11, column: 8, scope: !42)
!51 = !DILocalVariable(name: "value", arg: 1, scope: !42, file: !1, line: 11, type: !47)
!52 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Vector<char*>::constructor", linkageName: "_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE&4#NwCCv4885SaA1_$SN&20Core::_$core::VectorCv4884ClsGStA1T4char.pClsE.pFnE", scope: !27, file: !27, line: 9, type: !53, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!53 = !DISubroutineType(types: !54)
!54 = !{null, !45}
!55 = !DILocalVariable(name: "self", scope: !52, file: !1, line: 9, type: !45)
!56 = !DILocation(line: 9, column: 5, scope: !52)
!57 = distinct !DISubprogram(name: "Core::_$core::Core::_$core::Iterable<char*>::constructor", linkageName: "_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE&4#NwCCv4872SaA1_$SN&22Core::_$core::IterableCv4871ClsGStA1T4char.pClsE.pFnE", scope: !27, file: !27, line: 4, type: !58, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !7)
!58 = !DISubroutineType(types: !59)
!59 = !{null, !60}
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64)
!61 = !DILocalVariable(name: "self", scope: !57, file: !1, line: 4, type: !60)
!62 = !DILocation(line: 4, column: 5, scope: !57)
          