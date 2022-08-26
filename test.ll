; ModuleID = 'llvm_snowball_compile_mod_tests_main_sn'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%i\0A\00", align 1
@.str.6 = private unnamed_addr constant [46 x i8] c"OMG, A STDLIB WRITTEN BY SNOWBALL!??!??!?!?!?\00", align 1

; Function Attrs: nofree nounwind
declare void @printf(i8* nocapture readonly, ...) local_unnamed_addr #0

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@6StringP"(i8* nocapture readonly %__message) local_unnamed_addr #0 {
body:
  %puts = tail call i32 @puts(i8* nonnull dereferenceable(1) %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i16P"(i16 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i16 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i32P"(i32 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i32 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3f32P"(float %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), float %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3f64P"(double %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), double %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i64P"(i64 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0), i64 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define i32 @main() local_unnamed_addr #0 {
body:
  %puts.i = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([46 x i8], [46 x i8]* @.str.6, i64 0, i64 0)) #1
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), float 0x4016666660000000) #1
  ret i32 add (i32 sitofp (float 0x4016666660000000 to i32), i32 2)
}

; Function Attrs: nofree nounwind
declare i32 @puts(i8* nocapture readonly) local_unnamed_addr #0

attributes #0 = { nofree nounwind }
attributes #1 = { nounwind }
[2K[1;32m   compiling[0m [>                                                                     ] 0 %[2K[1;32m   compiling[0m [=====================>                                                ] 30 %[2K[1;32m   compiling[0m [===================================>                                  ] 50 %[2K[1;32m   compiling[0m [======================================>                               ] 55 %[2K[1;32m   compiling[0m [==========================================>                           ] 60 %[2K[1;32m   compiling[0m [=================================================>                    ] 69 %[2K[1;32m   compiling[0m [========================================================>             ] 80 %[2K[1;32m   compiling[0m [=======>                                                              ] 10 %[2KBytecode:
------------------
; ModuleID = 'llvm_snowball_compile_mod_tests_main_sn'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%i\0A\00", align 1
@.str.6 = private unnamed_addr constant [46 x i8] c"OMG, A STDLIB WRITTEN BY SNOWBALL!??!??!?!?!?\00", align 1

; Function Attrs: nofree nounwind
declare void @printf(i8* nocapture readonly, ...) local_unnamed_addr #0

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@6StringP"(i8* nocapture readonly %__message) local_unnamed_addr #0 {
body:
  %puts = tail call i32 @puts(i8* nonnull dereferenceable(1) %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i16P"(i16 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i16 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i32P"(i32 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i32 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3f32P"(float %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), float %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3f64P"(double %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), double %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i64P"(i64 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0), i64 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define i32 @main() local_unnamed_addr #0 {
body:
  %puts.i = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([46 x i8], [46 x i8]* @.str.6, i64 0, i64 0)) #1
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), float 0x4016666660000000) #1
  ret i32 add (i32 sitofp (float 0x4016666660000000 to i32), i32 2)
}

; Function Attrs: nofree nounwind
declare i32 @puts(i8* nocapture readonly) local_unnamed_addr #0

attributes #0 = { nofree nounwind }
attributes #1 = { nounwind }
------------------
[2K[1;32m   compiling[0m [>                                                                     ] 0 %[2K[1;32m   compiling[0m [=====================>                                                ] 30 %[2K[1;32m   compiling[0m [===================================>                                  ] 50 %[2K[1;32m   compiling[0m [======================================>                               ] 55 %[2K[1;32m   compiling[0m [==========================================>                           ] 60 %[2K[1;32m   compiling[0m [=================================================>                    ] 69 %[2K[1;32m   compiling[0m [========================================================>             ] 80 %[2K[1;32m   compiling[0m [=======>                                                              ] 10 %[2KBytecode:
------------------
; ModuleID = 'llvm_snowball_compile_mod_tests_main_sn'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%i\0A\00", align 1
@.str.6 = private unnamed_addr constant [46 x i8] c"OMG, A STDLIB WRITTEN BY SNOWBALL!??!??!?!?!?\00", align 1

; Function Attrs: nofree nounwind
declare void @printf(i8* nocapture readonly, ...) local_unnamed_addr #0

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@6StringP"(i8* nocapture readonly %__message) local_unnamed_addr #0 {
body:
  %puts = tail call i32 @puts(i8* nonnull dereferenceable(1) %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i16P"(i16 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i16 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i32P"(i32 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i32 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3f32P"(float %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), float %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3f64P"(double %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), double %__message)
  ret void
}

; Function Attrs: nofree nounwind
define void @"_M$6System$7println@3i64P"(i64 %__message) local_unnamed_addr #0 {
body:
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0), i64 %__message)
  ret void
}

; Function Attrs: nofree nounwind
define i32 @main() local_unnamed_addr #0 {
body:
  %puts.i = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([46 x i8], [46 x i8]* @.str.6, i64 0, i64 0)) #1
  tail call void (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i64 0, i64 0), float 0x4016666660000000) #1
  ret i32 add (i32 sitofp (float 0x4016666660000000 to i32), i32 2)
}

; Function Attrs: nofree nounwind
declare i32 @puts(i8* nocapture readonly) local_unnamed_addr #0

attributes #0 = { nofree nounwind }
attributes #1 = { nounwind }
------------------
