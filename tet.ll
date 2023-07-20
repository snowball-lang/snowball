[1;32m        Project[0m main v1.0.0 [[1moptimized[0m]
Lexer: 0.000076s
Parser: 0.000126s
Lexer: 0.000659s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Parser: 0.002101s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Lexer: 0.000200s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Parser: 0.000188s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Lexer: 0.000123s (/home/mauro/work/snowball/tests/vector.sn)
Parser: 0.000310s (/home/mauro/work/snowball/tests/vector.sn)
Lexer: 0.000085s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Parser: 0.000153s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Lexer: 0.000086s (/home/mauro/work/snowball/tests/string.sn)
Parser: 0.000285s (/home/mauro/work/snowball/tests/string.sn)
Lexer: 0.001152s (/home/mauro/work/snowball/tests/chars.sn)
Parser: 0.002540s (/home/mauro/work/snowball/tests/chars.sn)
Lexer: 0.000301s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Parser: 0.001658s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Simplifier: 0.442544s
Passes: 0.000004s
TypeChecker: 0.000059s (Core::CLib::c_string)
TypeChecker: 0.000096s (Core::CLib::__internal)
TypeChecker: 0.000019s (Core::CLib)
TypeChecker: 0.000010s (Core::_$core::Core::UA)
TypeChecker: 0.000096s (Core::_$core::Core::__internal)
TypeChecker: 0.000348s (Core::_$core::Core)
TypeChecker: 0.000004s (Core::_$core)
TypeChecker: 0.000002s (Core::Assert)
TypeChecker: 0.000097s (pkg::vector::tests)
TypeChecker: 0.000004s (pkg::vector)
TypeChecker: 0.000040s (pkg::string::tests)
TypeChecker: 0.000004s (pkg::string)
TypeChecker: 0.000068s (Core::Char)
TypeChecker: 0.002865s (pkg::chars::tests)
TypeChecker: 0.000008s (pkg::chars)
TypeChecker: 0.000002s ($main)
; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"struct._$SN&14UniversalArrayCv15008ClsE" = type { i8** }

@.str = private unnamed_addr constant [12 x i8] c"should pass\00", align 1
@.str.1 = private unnamed_addr constant [23 x i8] c"expecting \1B[1m`%i`\1B[0m\00", align 1
@.str.2 = private unnamed_addr constant [30 x i8] c" Testing \1B[1m%s\1B[0m [%s] ... \00", align 1
@.str.6 = private unnamed_addr constant [58 x i8] c"   --> Expected a success return value (%i) but got `%i`\0A\00", align 1
@.str.16 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@test.alloca = private unnamed_addr constant [26 x i8] c"pkg::vector::tests::empty\00", align 1
@test.alloca.262 = private unnamed_addr constant [25 x i8] c"pkg::vector::tests::push\00", align 1
@test.alloca.263 = private unnamed_addr constant [27 x i8] c"pkg::vector::tests::insert\00", align 1
@test.alloca.264 = private unnamed_addr constant [26 x i8] c"pkg::string::tests::empty\00", align 1
@test.alloca.265 = private unnamed_addr constant [25 x i8] c"pkg::string::tests::size\00", align 1
@test.alloca.266 = private unnamed_addr constant [28 x i8] c"pkg::chars::tests::is_space\00", align 1
@test.alloca.267 = private unnamed_addr constant [28 x i8] c"pkg::chars::tests::is_digit\00", align 1
@test.alloca.268 = private unnamed_addr constant [28 x i8] c"pkg::chars::tests::is_upper\00", align 1
@test.alloca.269 = private unnamed_addr constant [28 x i8] c"pkg::chars::tests::is_lower\00", align 1
@test.alloca.270 = private unnamed_addr constant [26 x i8] c"pkg::chars::tests::is_hex\00", align 1
@test.alloca.271 = private unnamed_addr constant [26 x i8] c"pkg::chars::tests::is_oct\00", align 1
@test.alloca.272 = private unnamed_addr constant [28 x i8] c"pkg::chars::tests::is_alpha\00", align 1
@test.alloca.273 = private unnamed_addr constant [32 x i8] c"pkg::chars::tests::is_alpha_num\00", align 1
@test.alloca.274 = private unnamed_addr constant [30 x i8] c"pkg::chars::tests::is_control\00", align 1
@test.alloca.275 = private unnamed_addr constant [28 x i8] c"pkg::chars::tests::is_print\00", align 1
@test.alloca.276 = private unnamed_addr constant [27 x i8] c"pkg::chars::tests::is_punc\00", align 1
@test.alloca.277 = private unnamed_addr constant [26 x i8] c"pkg::chars::tests::is_sym\00", align 1
@test.alloca.278 = private unnamed_addr constant [27 x i8] c"pkg::chars::tests::is_mark\00", align 1
@test.msg.280 = private unnamed_addr constant [35 x i8] c"  \1B[1;32m+ %i\1B[0m test(s) passed; \00", align 1
@test.msg.281 = private unnamed_addr constant [36 x i8] c"\0A  \1B[1;31m- %i\1B[0m test(s) failed; \00", align 1
@test.msg.282 = private unnamed_addr constant [37 x i8] c"\0A  \1B[1;33m? %i\1B[0m test(s) skipped; \00", align 1
@test.msg.283 = private unnamed_addr constant [41 x i8] c"\0A  \1B[1m= %i\1B[0m executed test(s) total\0A\0A\00", align 1
@str = private unnamed_addr constant [15 x i8] c"\1B[1;33mwip\1B[0m\00", align 1
@str.284 = private unnamed_addr constant [14 x i8] c"\1B[1;31merror \00", align 1
@str.285 = private unnamed_addr constant [21 x i8] c"\0A UNEXPECTED RESULT:\00", align 1
@str.286 = private unnamed_addr constant [5 x i8] c"\1B[0m\00", align 1
@str.287 = private unnamed_addr constant [17 x i8] c"\1B[1;32mnice!\1B[0m\00", align 1
@str.288 = private unnamed_addr constant [36 x i8] c"\0AExecuting \1B[1;34m18\1B[0m test(s)...\00", align 1
@str.289 = private unnamed_addr constant [15 x i8] c"\0ATest results:\00", align 1

declare i32 @strlen(i8* noundef nonnull align 8 dereferenceable(64)) local_unnamed_addr

; Function Attrs: inaccessiblememonly mustprogress nofree nounwind willreturn
declare noalias noundef i8* @malloc(i32 noundef) local_unnamed_addr #0

declare i32 @snprintf(i8* noundef nonnull align 8 dereferenceable(64), i32, i8* noundef nonnull align 8 dereferenceable(64), ...) local_unnamed_addr

declare i32 @sn.eh.personality(i32, i32, i64, i8*, i8*)

; Function Attrs: nofree nounwind
declare noundef i32 @printf(i8* nocapture noundef nonnull readonly align 8 dereferenceable(64), ...) local_unnamed_addr #1

declare i8* @sn.ua.get(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64), i32) local_unnamed_addr

declare void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64), i32, i8*) local_unnamed_addr

; Function Attrs: noinline
declare %"struct._$SN&14UniversalArrayCv15008ClsE"* @sn.ua.alloc(i32) local_unnamed_addr #2

; Function Attrs: noinline
define i32 @sn.test.try(i32 ()* nocapture readonly %0, i8* noundef nonnull align 8 dereferenceable(64) %1, i1 %2, i32 %3) local_unnamed_addr #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
entry:
  %.not = icmp eq i32 %3, 1
  br i1 %.not, label %7, label %4

4:                                                ; preds = %entry
  %5 = tail call dereferenceable_or_null(25) i8* @malloc(i32 25)
  %6 = tail call i32 (i8*, i32, i8*, ...) @snprintf(i8* noundef nonnull align 8 dereferenceable(64) %5, i32 25, i8* noundef nonnull align 8 dereferenceable(64) getelementptr inbounds ([23 x i8], [23 x i8]* @.str.1, i64 0, i64 0), i32 %3)
  br label %7

7:                                                ; preds = %entry, %4
  %var.tty.0 = phi i8* [ %5, %4 ], [ getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i64 0, i64 0), %entry ]
  %8 = tail call i32 (i8*, ...) @printf(i8* noundef nonnull align 8 dereferenceable(64) getelementptr inbounds ([30 x i8], [30 x i8]* @.str.2, i64 0, i64 0), i8* nonnull %1, i8* %var.tty.0)
  br i1 %2, label %common.ret, label %9

9:                                                ; preds = %7
  %10 = tail call i32 %0()
  %11 = icmp eq i32 %10, %3
  br i1 %11, label %common.ret, label %12

common.ret:                                       ; preds = %7, %9, %12
  %.sink = phi i8* [ getelementptr inbounds ([5 x i8], [5 x i8]* @str.286, i64 0, i64 0), %12 ], [ getelementptr inbounds ([17 x i8], [17 x i8]* @str.287, i64 0, i64 0), %9 ], [ getelementptr inbounds ([15 x i8], [15 x i8]* @str, i64 0, i64 0), %7 ]
  %common.ret.op = phi i32 [ 0, %12 ], [ 1, %9 ], [ 1, %7 ]
  %puts10 = tail call i32 @puts(i8* nonnull dereferenceable(1) %.sink)
  ret i32 %common.ret.op

12:                                               ; preds = %9
  %puts7 = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([14 x i8], [14 x i8]* @str.284, i64 0, i64 0))
  %puts8 = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([21 x i8], [21 x i8]* @str.285, i64 0, i64 0))
  %13 = tail call i32 (i8*, ...) @printf(i8* noundef nonnull align 8 dereferenceable(64) getelementptr inbounds ([58 x i8], [58 x i8]* @.str.6, i64 0, i64 0), i32 %3, i32 %10)
  br label %common.ret
}

declare noalias noundef nonnull i8* @sn.alloca(i32) local_unnamed_addr

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::vector.sn.tests&6insertCv15357SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
"_$SN&6VectorCv15254ClsGStA1T3i32ClsE&2atCv15306SaA1_$SN&6VectorCv15254ClsGStA1T3i32ClsE.rA2T3i32FnE.exit":
  %0 = tail call i8* @sn.alloca(i32 8)
  %1 = tail call %"struct._$SN&14UniversalArrayCv15008ClsE"* @sn.ua.alloc(i32 10) #2
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 0, i8* nonnull inttoptr (i64 5 to i8*))
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 1, i8* nonnull inttoptr (i64 10 to i8*))
  %2 = tail call i8* @sn.ua.get(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 1)
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 1, i8* nonnull inttoptr (i64 20 to i8*))
  %3 = ptrtoint i8* %2 to i64
  %phi.bo42 = and i64 %3, 4294967295
  %phi.cast43 = inttoptr i64 %phi.bo42 to i8*
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 2, i8* %phi.cast43)
  %4 = tail call i8* @sn.ua.get(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 1)
  %5 = ptrtoint i8* %4 to i64
  %6 = trunc i64 %5 to i32
  ret i32 %6
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::vector.sn.tests&4pushCv15348SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
"_$SN&6VectorCv15254ClsGStA1T3i32ClsE&4pushCv15285SaA1_$SN&6VectorCv15254ClsGStA1T3i32ClsE.rA2T3i32FnE.exit.4":
  %0 = tail call i8* @sn.alloca(i32 8)
  %1 = tail call %"struct._$SN&14UniversalArrayCv15008ClsE"* @sn.ua.alloc(i32 10) #2
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 0, i8* null)
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 1, i8* nonnull inttoptr (i64 1 to i8*))
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 2, i8* nonnull inttoptr (i64 2 to i8*))
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 3, i8* nonnull inttoptr (i64 3 to i8*))
  tail call void @sn.ua.set(%"struct._$SN&14UniversalArrayCv15008ClsE"* noundef nonnull align 8 dereferenceable(64) %1, i32 4, i8* nonnull inttoptr (i64 4 to i8*))
  ret i32 5
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::vector.sn.tests&5emptyCv15252SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
entry:
  %0 = tail call i8* @sn.alloca(i32 8)
  %1 = tail call %"struct._$SN&14UniversalArrayCv15008ClsE"* @sn.ua.alloc(i32 10) #2
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::string.sn.tests&4sizeCv15371SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
entry:
  %0 = tail call i8* @sn.alloca(i32 8)
  %1 = tail call i32 @strlen(i8* noundef nonnull align 8 dereferenceable(64) getelementptr inbounds ([6 x i8], [6 x i8]* @.str.16, i64 0, i64 0))
  ret i32 %1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::string.sn.tests&5emptyCv15367SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
entry:
  %0 = tail call i8* @sn.alloca(i32 8)
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&7is_markCv16065SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&6is_symCv16013SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&7is_puncCv15913SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_printCv15897SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&10is_controlCv15881SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&12is_alpha_numCv15850SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_alphaCv15795SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&6is_octCv15725SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&6is_hexCv15655SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_lowerCv15567SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_upperCv15479SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_digitCv15439SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: noinline
define internal i32 @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_spaceCv15417SaFnE"() #2 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
  ret i32 1
}

; Function Attrs: alwaysinline nounwind
declare void @sn.runtime.initialize() local_unnamed_addr #3

; Function Attrs: noinline optnone
define i32 @main() local_unnamed_addr #4 personality i32 (i32, i32, i64, i8*, i8*)* @sn.eh.personality {
entry:
  tail call void @sn.runtime.initialize()
  %puts = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([36 x i8], [36 x i8]* @str.288, i64 0, i64 0))
  %0 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::vector.sn.tests&5emptyCv15252SaFnE", i8* getelementptr inbounds ([26 x i8], [26 x i8]* @test.alloca, i64 0, i64 0), i1 false, i32 1)
  %1 = icmp eq i32 %0, 1
  %. = zext i1 %1 to i32
  %not. = xor i1 %1, true
  %.91 = zext i1 %not. to i32
  %2 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::vector.sn.tests&4pushCv15348SaFnE", i8* getelementptr inbounds ([25 x i8], [25 x i8]* @test.alloca.262, i64 0, i64 0), i1 false, i32 5)
  %3 = icmp eq i32 %2, 1
  %4 = select i1 %1, i32 2, i32 1
  %5 = select i1 %1, i32 1, i32 2
  %success.count.1 = select i1 %3, i32 %4, i32 %.
  %fail.count.1 = select i1 %3, i32 %.91, i32 %5
  %6 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::vector.sn.tests&6insertCv15357SaFnE", i8* getelementptr inbounds ([27 x i8], [27 x i8]* @test.alloca.263, i64 0, i64 0), i1 false, i32 20)
  %7 = icmp eq i32 %6, 1
  %8 = zext i1 %7 to i32
  %success.count.2 = add nuw nsw i32 %success.count.1, %8
  %not.92 = xor i1 %7, true
  %9 = zext i1 %not.92 to i32
  %fail.count.2 = add nuw nsw i32 %fail.count.1, %9
  %10 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::string.sn.tests&5emptyCv15367SaFnE", i8* getelementptr inbounds ([26 x i8], [26 x i8]* @test.alloca.264, i64 0, i64 0), i1 false, i32 1)
  %11 = icmp eq i32 %10, 1
  %12 = zext i1 %11 to i32
  %success.count.3 = add nuw nsw i32 %success.count.2, %12
  %not.93 = xor i1 %11, true
  %13 = zext i1 %not.93 to i32
  %fail.count.3 = add nuw nsw i32 %fail.count.2, %13
  %14 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::string.sn.tests&4sizeCv15371SaFnE", i8* getelementptr inbounds ([25 x i8], [25 x i8]* @test.alloca.265, i64 0, i64 0), i1 false, i32 5)
  %15 = icmp eq i32 %14, 1
  %16 = zext i1 %15 to i32
  %success.count.4 = add nuw nsw i32 %success.count.3, %16
  %not.94 = xor i1 %15, true
  %17 = zext i1 %not.94 to i32
  %fail.count.4 = add nuw nsw i32 %fail.count.3, %17
  %18 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_spaceCv15417SaFnE", i8* getelementptr inbounds ([28 x i8], [28 x i8]* @test.alloca.266, i64 0, i64 0), i1 false, i32 1)
  %19 = icmp eq i32 %18, 1
  %20 = zext i1 %19 to i32
  %success.count.5 = add nuw nsw i32 %success.count.4, %20
  %not.95 = xor i1 %19, true
  %21 = zext i1 %not.95 to i32
  %fail.count.5 = add nuw nsw i32 %fail.count.4, %21
  %22 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_digitCv15439SaFnE", i8* getelementptr inbounds ([28 x i8], [28 x i8]* @test.alloca.267, i64 0, i64 0), i1 false, i32 1)
  %23 = icmp eq i32 %22, 1
  %24 = zext i1 %23 to i32
  %success.count.6 = add nuw nsw i32 %success.count.5, %24
  %not.96 = xor i1 %23, true
  %25 = zext i1 %not.96 to i32
  %fail.count.6 = add nuw nsw i32 %fail.count.5, %25
  %26 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_upperCv15479SaFnE", i8* getelementptr inbounds ([28 x i8], [28 x i8]* @test.alloca.268, i64 0, i64 0), i1 false, i32 1)
  %27 = icmp eq i32 %26, 1
  %28 = zext i1 %27 to i32
  %success.count.7 = add nuw nsw i32 %success.count.6, %28
  %not.97 = xor i1 %27, true
  %29 = zext i1 %not.97 to i32
  %fail.count.7 = add nuw nsw i32 %fail.count.6, %29
  %30 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_lowerCv15567SaFnE", i8* getelementptr inbounds ([28 x i8], [28 x i8]* @test.alloca.269, i64 0, i64 0), i1 false, i32 1)
  %31 = icmp eq i32 %30, 1
  %32 = zext i1 %31 to i32
  %success.count.8 = add nuw nsw i32 %success.count.7, %32
  %not.98 = xor i1 %31, true
  %33 = zext i1 %not.98 to i32
  %fail.count.8 = add nuw nsw i32 %fail.count.7, %33
  %34 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&6is_hexCv15655SaFnE", i8* getelementptr inbounds ([26 x i8], [26 x i8]* @test.alloca.270, i64 0, i64 0), i1 false, i32 1)
  %35 = icmp eq i32 %34, 1
  %36 = zext i1 %35 to i32
  %success.count.9 = add nuw nsw i32 %success.count.8, %36
  %not.99 = xor i1 %35, true
  %37 = zext i1 %not.99 to i32
  %fail.count.9 = add nuw nsw i32 %fail.count.8, %37
  %38 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&6is_octCv15725SaFnE", i8* getelementptr inbounds ([26 x i8], [26 x i8]* @test.alloca.271, i64 0, i64 0), i1 false, i32 1)
  %39 = icmp eq i32 %38, 1
  %40 = zext i1 %39 to i32
  %success.count.10 = add nuw nsw i32 %success.count.9, %40
  %not.100 = xor i1 %39, true
  %41 = zext i1 %not.100 to i32
  %fail.count.10 = add nuw nsw i32 %fail.count.9, %41
  %42 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_alphaCv15795SaFnE", i8* getelementptr inbounds ([28 x i8], [28 x i8]* @test.alloca.272, i64 0, i64 0), i1 false, i32 1)
  %43 = icmp eq i32 %42, 1
  %44 = zext i1 %43 to i32
  %success.count.11 = add nuw nsw i32 %success.count.10, %44
  %not.101 = xor i1 %43, true
  %45 = zext i1 %not.101 to i32
  %fail.count.11 = add nuw nsw i32 %fail.count.10, %45
  %46 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&12is_alpha_numCv15850SaFnE", i8* getelementptr inbounds ([32 x i8], [32 x i8]* @test.alloca.273, i64 0, i64 0), i1 false, i32 1)
  %47 = icmp eq i32 %46, 1
  %48 = zext i1 %47 to i32
  %success.count.12 = add nuw nsw i32 %success.count.11, %48
  %not.102 = xor i1 %47, true
  %49 = zext i1 %not.102 to i32
  %fail.count.12 = add nuw nsw i32 %fail.count.11, %49
  %50 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&10is_controlCv15881SaFnE", i8* getelementptr inbounds ([30 x i8], [30 x i8]* @test.alloca.274, i64 0, i64 0), i1 false, i32 1)
  %51 = icmp eq i32 %50, 1
  %52 = zext i1 %51 to i32
  %success.count.13 = add nuw nsw i32 %success.count.12, %52
  %not.103 = xor i1 %51, true
  %53 = zext i1 %not.103 to i32
  %fail.count.13 = add nuw nsw i32 %fail.count.12, %53
  %54 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&8is_printCv15897SaFnE", i8* getelementptr inbounds ([28 x i8], [28 x i8]* @test.alloca.275, i64 0, i64 0), i1 false, i32 1)
  %55 = icmp eq i32 %54, 1
  %56 = zext i1 %55 to i32
  %success.count.14 = add nuw nsw i32 %success.count.13, %56
  %not.104 = xor i1 %55, true
  %57 = zext i1 %not.104 to i32
  %fail.count.14 = add nuw nsw i32 %fail.count.13, %57
  %58 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&7is_puncCv15913SaFnE", i8* getelementptr inbounds ([27 x i8], [27 x i8]* @test.alloca.276, i64 0, i64 0), i1 false, i32 1)
  %59 = icmp eq i32 %58, 1
  %60 = zext i1 %59 to i32
  %success.count.15 = add nuw nsw i32 %success.count.14, %60
  %not.105 = xor i1 %59, true
  %61 = zext i1 %not.105 to i32
  %fail.count.15 = add nuw nsw i32 %fail.count.14, %61
  %62 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&6is_symCv16013SaFnE", i8* getelementptr inbounds ([26 x i8], [26 x i8]* @test.alloca.277, i64 0, i64 0), i1 false, i32 1)
  %63 = icmp eq i32 %62, 1
  %64 = zext i1 %63 to i32
  %success.count.16 = add nuw nsw i32 %success.count.15, %64
  %not.106 = xor i1 %63, true
  %65 = zext i1 %not.106 to i32
  %fail.count.16 = add nuw nsw i32 %fail.count.15, %65
  %66 = tail call i32 @sn.test.try(i32 ()* nonnull @"_$SNpkg::home::mauro::work::snowball::tests::chars.sn.tests&7is_markCv16065SaFnE", i8* getelementptr inbounds ([27 x i8], [27 x i8]* @test.alloca.278, i64 0, i64 0), i1 false, i32 1)
  %67 = icmp eq i32 %66, 1
  %68 = zext i1 %67 to i32
  %success.count.17 = add nuw nsw i32 %success.count.16, %68
  %not.107 = xor i1 %67, true
  %69 = zext i1 %not.107 to i32
  %fail.count.17 = add nuw nsw i32 %fail.count.16, %69
  %puts90 = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([15 x i8], [15 x i8]* @str.289, i64 0, i64 0))
  %70 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @test.msg.280, i64 0, i64 0), i32 %success.count.17)
  %71 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @test.msg.281, i64 0, i64 0), i32 %fail.count.17)
  %72 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @test.msg.282, i64 0, i64 0), i32 0)
  %73 = add nuw nsw i32 %success.count.17, %fail.count.17
  %74 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @test.msg.283, i64 0, i64 0), i32 %73)
  ret i32 0
}

; Function Attrs: nofree nounwind
declare noundef i32 @puts(i8* nocapture noundef readonly) local_unnamed_addr #1

attributes #0 = { inaccessiblememonly mustprogress nofree nounwind willreturn }
attributes #1 = { nofree nounwind }
attributes #2 = { noinline }
attributes #3 = { alwaysinline nounwind }
attributes #4 = { noinline optnone }

!llvm.module.flags = !{!0, !1, !2}

!0 = !{i32 2, !"Debug Info Version", i32 3}
!1 = !{i32 2, !"Snowball Compiler ID", i32 7}
!2 = !{i32 2, !"Snowball Compiler Version", [6 x i8] c"0.0.7\00"}
[1;32m       Finished[0m test target(s) in [1m601[0mms
[1;32m        Running[0m unittests (tests/main.sn)

Executing [1;34m18[0m test(s)...
 Testing [1mpkg::vector::tests::empty[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::vector::tests::push[0m [expecting [1m`5`[0m] ... [1;32mnice![0m
 Testing [1mpkg::vector::tests::insert[0m [expecting [1m`20`[0m] ... [1;32mnice![0m
 Testing [1mpkg::string::tests::empty[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::string::tests::size[0m [expecting [1m`5`[0m] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_space[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_digit[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_upper[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_lower[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_hex[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_oct[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_alpha[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_alpha_num[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_control[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_print[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_punc[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_sym[0m [should pass] ... [1;32mnice![0m
 Testing [1mpkg::chars::tests::is_mark[0m [should pass] ... [1;32mnice![0m

Test results:
  [1;32m+ 18[0m test(s) passed; 
  [1;31m- 0[0m test(s) failed; 
  [1;33m? 0[0m test(s) skipped; 
  [1m= 18[0m executed test(s) total

