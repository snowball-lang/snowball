Lexer: 0.000151s
Parser: 0.000640s
Lexer: 0.001215s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Parser: 0.003510s (/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn)
Lexer: 0.000297s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Parser: 0.000349s (/home/mauro/work/snowball/bin/Debug/../../stdlib/CLib.sn)
Lexer: 0.000142s (/home/mauro/work/snowball/tests/option.sn)
Parser: 0.000442s (/home/mauro/work/snowball/tests/option.sn)
Lexer: 0.000131s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Optional.sn)
Parser: 0.000331s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Optional.sn)
Lexer: 0.000093s (/home/mauro/work/snowball/tests/vector.sn)
Parser: 0.000300s (/home/mauro/work/snowball/tests/vector.sn)
Lexer: 0.000040s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Parser: 0.000136s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Assert.sn)
Lexer: 0.001240s (/home/mauro/work/snowball/tests/chars.sn)
Parser: 0.003091s (/home/mauro/work/snowball/tests/chars.sn)
Lexer: 0.000296s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Parser: 0.000885s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Char.sn)
Lexer: 0.000193s (/home/mauro/work/snowball/tests/cls.sn)
Parser: 0.000821s (/home/mauro/work/snowball/tests/cls.sn)
Lexer: 0.000040s (/home/mauro/work/snowball/tests/string.sn)
Parser: 0.000126s (/home/mauro/work/snowball/tests/string.sn)
Lexer: 0.000083s (/home/mauro/work/snowball/tests/macros.sn)
Parser: 0.000234s (/home/mauro/work/snowball/tests/macros.sn)
Lexer: 0.000248s (/home/mauro/work/snowball/tests/syntax.sn)
Parser: 0.001014s (/home/mauro/work/snowball/tests/syntax.sn)
Lexer: 0.000080s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Parser: 0.000177s (/home/mauro/work/snowball/bin/Debug/../../stdlib/System.sn)
Lexer: 0.000177s (/home/mauro/work/snowball/tests/clib.sn)
Parser: 0.000381s (/home/mauro/work/snowball/tests/clib.sn)
Lexer: 0.000101s (/home/mauro/work/snowball/tests/tuples.sn)
Parser: 0.000396s (/home/mauro/work/snowball/tests/tuples.sn)
Lexer: 0.000173s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Tuples.sn)
Parser: 0.000277s (/home/mauro/work/snowball/bin/Debug/../../stdlib/Tuples.sn)
Simplifier: 0.094400s
Passes: 0.000065s
TypeChecker: 0.000076s (Core::CLib::c_string)
TypeChecker: 0.000109s (Core::CLib::__internal)
TypeChecker: 0.000056s (Core::CLib)
TypeChecker: 0.000012s (Core::_$core::Core::UA)
TypeChecker: 0.000003s (Core::_$core::Core::__internal)
TypeChecker: 0.001196s (Core::_$core::Core)
TypeChecker: 0.000066s (Core::_$core)
TypeChecker: 0.000004s (Core::Optional)
TypeChecker: 0.000002s (pkg::option::tests)
TypeChecker: 0.000002s (pkg::option)
TypeChecker: 0.000002s (Core::Assert)
TypeChecker: 0.000001s (pkg::vector::tests)
TypeChecker: 0.000002s (pkg::vector)
TypeChecker: 0.000063s (Core::Char)
TypeChecker: 0.000004s (pkg::chars::tests)
TypeChecker: 0.000002s (pkg::chars)
TypeChecker: 0.000032s (pkg::cls::test)
TypeChecker: 0.000002s (pkg::cls)
TypeChecker: 0.000002s (pkg::string::tests)
TypeChecker: 0.000002s (pkg::string)
TypeChecker: 0.000002s (pkg::macros::tests)
TypeChecker: 0.000002s (pkg::macros)
TypeChecker: 0.000043s (Core::System)
TypeChecker: 0.000003s (pkg::syntax::tests)
TypeChecker: 0.000002s (pkg::syntax)
TypeChecker: 0.000001s (pkg::clib::tests)
TypeChecker: 0.000002s (pkg::clib)
TypeChecker: 0.000002s (Core::Tuples)
TypeChecker: 0.000002s (pkg::tuples::tests)
TypeChecker: 0.000002s (pkg::tuples)
TypeChecker: 0.000026s ($main)
; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17519SaA1T3i32A2T4char.rA3T3i64FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i64 %2) #0 !dbg !5 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !14, metadata !DIExpression()), !dbg !15
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !16, metadata !DIExpression()), !dbg !15
  %arg.value = alloca i64, align 8
  store i64 %2, ptr %arg.value, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !17, metadata !DIExpression()), !dbg !15
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !18, metadata !DIExpression()), !dbg !19
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !20
  %4 = call ptr @malloc(i32 %3), !dbg !21
  store ptr %4, ptr %var.buffer, align 8, !dbg !21
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !22
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !23
  %7 = load ptr, ptr %arg.format, align 8, !dbg !24
  %8 = load i64, ptr %arg.value, align 8, !dbg !25
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i64 %8), !dbg !26
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !27
  ret ptr %10, !dbg !27
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i32 %2) #0 !dbg !28 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !31, metadata !DIExpression()), !dbg !32
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !33, metadata !DIExpression()), !dbg !32
  %arg.value = alloca i32, align 4
  store i32 %2, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !34, metadata !DIExpression()), !dbg !32
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !35, metadata !DIExpression()), !dbg !36
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !37
  %4 = call ptr @malloc(i32 %3), !dbg !38
  store ptr %4, ptr %var.buffer, align 8, !dbg !38
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !39
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !40
  %7 = load ptr, ptr %arg.format, align 8, !dbg !41
  %8 = load i32, ptr %arg.value, align 4, !dbg !42
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i32 %8), !dbg !43
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !44
  ret ptr %10, !dbg !44
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17441SaA1T3i32A2T4char.rA3T3i16FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i16 %2) #0 !dbg !45 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !49, metadata !DIExpression()), !dbg !50
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !51, metadata !DIExpression()), !dbg !50
  %arg.value = alloca i16, align 2
  store i16 %2, ptr %arg.value, align 2
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !52, metadata !DIExpression()), !dbg !50
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !53, metadata !DIExpression()), !dbg !54
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !55
  %4 = call ptr @malloc(i32 %3), !dbg !56
  store ptr %4, ptr %var.buffer, align 8, !dbg !56
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !57
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !58
  %7 = load ptr, ptr %arg.format, align 8, !dbg !59
  %8 = load i16, ptr %arg.value, align 2, !dbg !60
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i16 %8), !dbg !61
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !62
  ret ptr %10, !dbg !62
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17402SaA1T3i32A2T4char.rA3T2i8FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i8 %2) #0 !dbg !63 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !67, metadata !DIExpression()), !dbg !68
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !69, metadata !DIExpression()), !dbg !68
  %arg.value = alloca i8, align 1
  store i8 %2, ptr %arg.value, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !70, metadata !DIExpression()), !dbg !68
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !71, metadata !DIExpression()), !dbg !72
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !73
  %4 = call ptr @malloc(i32 %3), !dbg !74
  store ptr %4, ptr %var.buffer, align 8, !dbg !74
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !75
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !76
  %7 = load ptr, ptr %arg.format, align 8, !dbg !77
  %8 = load i8, ptr %arg.value, align 1, !dbg !78
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i8 %8), !dbg !79
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !80
  ret ptr %10, !dbg !80
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE"() #0 !dbg !81 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !84
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE"() #0 !dbg !85 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !86
}

; Function Attrs: alwaysinline
define internal i8 @"_$SN@sn.Core.CLib&8null_ptrCv17039SaFnE"() #0 !dbg !87 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i8 0, !dbg !90
}

; Function Attrs: alwaysinline
define internal i8 @"_$SN@sn.Core.CLib&8null_ptrCv17031SaFnE"() #0 !dbg !91 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i8 0, !dbg !92
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.CLib&7is_nullCv16985SaA1T4cobjFnE"(ptr %0) #0 !dbg !93 {
entry:
  %arg.ptr = alloca ptr, align 8
  store ptr %0, ptr %arg.ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.ptr, metadata !98, metadata !DIExpression()), !dbg !99
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.ptr, align 8, !dbg !99
  %2 = call ptr @"_$SN@sn.Core.CLib&8null_ptrCv16988SaFnE"() #0, !dbg !100
  %3 = icmp eq ptr %1, %2, !dbg !100
  ret i1 %3, !dbg !100
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib&8null_ptrCv16988SaFnE"() #0 !dbg !101 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret ptr null, !dbg !104
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !105 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %0, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !114, metadata !DIExpression()), !dbg !115
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.buffer, align 8, !dbg !115
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !115
  %3 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !116
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %2, align 8, !dbg !116
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !116
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !116
}

define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !117 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !118, metadata !DIExpression()), !dbg !119
  %var.result = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.result, metadata !120, metadata !DIExpression()), !dbg !122
  %"var.$iter" = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !123, metadata !DIExpression()), !dbg !125
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !126, metadata !DIExpression()), !dbg !125
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !128, metadata !DIExpression()), !dbg !125
  br label %body

body:                                             ; preds = %entry
  %1 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !129
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !129
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !129
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str), !dbg !129
  %3 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, align 8, !dbg !129
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %var.result, align 8, !dbg !129
  %4 = load ptr, ptr %arg.self, align 8, !dbg !119
  %5 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 3, !dbg !119
  %6 = load i32, ptr %5, align 4, !dbg !119
  %7 = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8, !dbg !125
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 0, !dbg !125
  store ptr @"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %8, align 8, !dbg !125
  call void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %7, i32 0, i32 %6), !dbg !125
  %9 = load %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, align 8, !dbg !125
  store %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" %9, ptr %"var.$iter", align 8, !dbg !125
  %10 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !125
  %11 = load ptr, ptr %"var.$iter", align 8, !dbg !125
  %12 = getelementptr inbounds ptr, ptr %11, i32 1, !dbg !125
  %13 = load ptr, ptr %12, align 8, !dbg !125
  %14 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %13(ptr %"var.$iter"), !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %14, ptr %10, align 4, !dbg !125
  %15 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %10, align 4, !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %15, ptr %"var.$iter_value", align 4, !dbg !125
  br label %16, !dbg !125

16:                                               ; preds = %45, %body
  %17 = call i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !125
  br i1 %17, label %18, label %35, !dbg !125

18:                                               ; preds = %16
  %19 = call i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !125
  store i32 %19, ptr %var.i, align 4, !dbg !125
  %20 = load ptr, ptr %arg.self, align 8, !dbg !119
  %21 = load i32, ptr %var.i, align 4, !dbg !130
  %22 = call i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %21), !dbg !131
  %23 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !131
  %24 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE"(i32 %22) #0, !dbg !132
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %24, ptr %23, align 8, !dbg !132
  %25 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %23, align 8, !dbg !132
  %26 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !132
  %27 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.result, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %25) #0, !dbg !133
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %27, ptr %26, align 8, !dbg !133
  %28 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %26, align 8, !dbg !133
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %28, ptr %var.result, align 8, !dbg !133
  %29 = load i32, ptr %var.i, align 4, !dbg !125
  %30 = load ptr, ptr %arg.self, align 8, !dbg !119
  %31 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %30, i32 0, i32 3, !dbg !119
  %32 = load i32, ptr %31, align 4, !dbg !119
  %33 = sub i32 %32, 1, !dbg !134
  %34 = icmp ne i32 %29, %33, !dbg !134
  br i1 %34, label %37, label %44, !dbg !134

35:                                               ; preds = %16
  %36 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %var.result, align 8, !dbg !135
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %36, !dbg !135

37:                                               ; preds = %18
  %38 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !136
  %39 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %38, i32 0, i32 0, !dbg !136
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %39, align 8, !dbg !136
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %38, ptr noundef nonnull align 8 dereferenceable(64) @.str.2), !dbg !136
  %40 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %38, align 8, !dbg !136
  %41 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !136
  %42 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.result, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %40) #0, !dbg !137
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %42, ptr %41, align 8, !dbg !137
  %43 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %41, align 8, !dbg !137
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %43, ptr %var.result, align 8, !dbg !137
  br label %45, !dbg !137

44:                                               ; preds = %18
  br label %45, !dbg !137

45:                                               ; preds = %44, %37
  %46 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !125
  %47 = load ptr, ptr %"var.$iter", align 8, !dbg !125
  %48 = getelementptr inbounds ptr, ptr %47, i32 1, !dbg !125
  %49 = load ptr, ptr %48, align 8, !dbg !125
  %50 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %49(ptr %"var.$iter"), !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %50, ptr %46, align 4, !dbg !125
  %.load = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %46, align 4, !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %.load, ptr %"var.$iter_value", align 4, !dbg !125
  br label %16, !dbg !125
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1) #0 !dbg !138 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !142, metadata !DIExpression()), !dbg !143
  %arg.other = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !144, metadata !DIExpression()), !dbg !143
  %var.len1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len1, metadata !145, metadata !DIExpression()), !dbg !146
  %var.len2 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len2, metadata !147, metadata !DIExpression()), !dbg !148
  %var.sum = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.sum, metadata !149, metadata !DIExpression()), !dbg !150
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !151, metadata !DIExpression()), !dbg !152
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !143
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 3, !dbg !143
  %4 = load i32, ptr %3, align 4, !dbg !143
  store i32 %4, ptr %var.len1, align 4, !dbg !143
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !143
  %6 = load i32, ptr %5, align 4, !dbg !143
  store i32 %6, ptr %var.len2, align 4, !dbg !143
  %7 = load i32, ptr %var.len1, align 4, !dbg !146
  %8 = load i32, ptr %var.len2, align 4, !dbg !153
  %9 = add i32 %7, %8, !dbg !153
  store i32 %9, ptr %var.sum, align 4, !dbg !153
  %10 = load i32, ptr %var.sum, align 4, !dbg !154
  %11 = call ptr @malloc(i32 %10), !dbg !155
  store ptr %11, ptr %var.buffer, align 8, !dbg !155
  %12 = load ptr, ptr %var.buffer, align 8, !dbg !156
  %13 = load ptr, ptr %arg.self, align 8, !dbg !143
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %13, i32 0, i32 4, !dbg !143
  %15 = load ptr, ptr %14, align 8, !dbg !143
  %16 = load i32, ptr %var.len1, align 4, !dbg !157
  call void @memcpy.1(ptr noundef nonnull align 8 dereferenceable(64) %12, ptr noundef nonnull align 8 dereferenceable(64) %15, i32 %16), !dbg !158
  %17 = load ptr, ptr %var.buffer, align 8, !dbg !152
  %18 = load i32, ptr %var.len1, align 4, !dbg !159
  %19 = call ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18) #0, !dbg !160
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !143
  %21 = load ptr, ptr %20, align 8, !dbg !143
  %22 = load i32, ptr %var.len2, align 4, !dbg !161
  call void @memcpy(ptr noundef nonnull align 8 dereferenceable(64) %19, ptr noundef nonnull align 8 dereferenceable(64) %21, i32 %22), !dbg !162
  %23 = load ptr, ptr %var.buffer, align 8, !dbg !163
  %24 = load i32, ptr %var.sum, align 4, !dbg !164
  %25 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !165
  %26 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %25, i32 0, i32 0, !dbg !165
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %26, align 8, !dbg !165
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %25, ptr noundef nonnull align 8 dereferenceable(64) %23, i32 %24), !dbg !165
  %27 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %25, align 8, !dbg !165
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %27, !dbg !165
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE"(i32 %0) #0 !dbg !166 {
entry:
  %arg.buffer = alloca i32, align 4
  store i32 %0, ptr %arg.buffer, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !169, metadata !DIExpression()), !dbg !170
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.buffer, align 4, !dbg !170
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !170
  %3 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %arg.buffer) #0, !dbg !171
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %2, align 8, !dbg !171
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !171
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !171
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6insertCv17751SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) !dbg !172 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !175, metadata !DIExpression()), !dbg !176
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !177, metadata !DIExpression()), !dbg !176
  %arg.value = alloca i32, align 4
  store i32 %2, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !178, metadata !DIExpression()), !dbg !176
  %var.cur = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.cur, metadata !179, metadata !DIExpression()), !dbg !180
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.index, align 4, !dbg !176
  %4 = load ptr, ptr %arg.self, align 8, !dbg !176
  %5 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 3, !dbg !176
  %6 = load i32, ptr %5, align 4, !dbg !176
  %7 = icmp sge i32 %3, %6, !dbg !176
  br i1 %7, label %8, label %11, !dbg !176

8:                                                ; preds = %body
  %9 = load ptr, ptr %arg.self, align 8, !dbg !176
  %10 = load i32, ptr %arg.value, align 4, !dbg !181
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %9, i32 %10), !dbg !182
  ret void, !dbg !183

11:                                               ; preds = %body
  br label %12, !dbg !183

12:                                               ; preds = %11
  %13 = load ptr, ptr %arg.self, align 8, !dbg !176
  %14 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 4, !dbg !176
  %15 = load ptr, ptr %14, align 8, !dbg !176
  %16 = load i32, ptr %arg.index, align 4, !dbg !184
  %17 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %15, i32 %16), !dbg !185
  %18 = ptrtoint ptr %17 to i32, !dbg !185
  store i32 %18, ptr %var.cur, align 4, !dbg !185
  %19 = load ptr, ptr %arg.self, align 8, !dbg !176
  %20 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %19, i32 0, i32 4, !dbg !176
  %21 = load ptr, ptr %20, align 8, !dbg !176
  %22 = load i32, ptr %arg.index, align 4, !dbg !186
  %23 = load i32, ptr %arg.value, align 4, !dbg !187
  %24 = inttoptr i32 %23 to ptr, !dbg !187
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %21, i32 %22, ptr %24), !dbg !188
  %25 = load ptr, ptr %arg.self, align 8, !dbg !176
  %26 = load i32, ptr %arg.index, align 4, !dbg !176
  %27 = add i32 %26, 1, !dbg !189
  %28 = load i32, ptr %var.cur, align 4, !dbg !190
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6insertCv17751SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %25, i32 %27, i32 %28), !dbg !191
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#IdxCv17745SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 !dbg !192 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !195, metadata !DIExpression()), !dbg !196
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !197, metadata !DIExpression()), !dbg !196
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !196
  %3 = load i32, ptr %arg.index, align 4, !dbg !198
  %4 = call i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3), !dbg !199
  ret i32 %4, !dbg !199
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4dataCv17740SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !200 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !204, metadata !DIExpression()), !dbg !205
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !205
  %2 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 4, !dbg !205
  %3 = load ptr, ptr %2, align 8, !dbg !205
  %4 = getelementptr inbounds %"struct._$SN&14UniversalArrayCv17533ClsE", ptr %3, i32 0, i32 0, !dbg !205
  %5 = load ptr, ptr %4, align 8, !dbg !205
  %6 = load ptr, ptr %5, align 8, !dbg !205
  ret ptr %6, !dbg !205
}

define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) !dbg !206 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !207, metadata !DIExpression()), !dbg !208
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !209, metadata !DIExpression()), !dbg !208
  br label %body

body:                                             ; preds = %entry
  %2 = load i32, ptr %arg.index, align 4, !dbg !208
  %3 = icmp slt i32 %2, 0, !dbg !210
  %4 = load i32, ptr %arg.index, align 4, !dbg !208
  %5 = load ptr, ptr %arg.self, align 8, !dbg !208
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 3, !dbg !208
  %7 = load i32, ptr %6, align 4, !dbg !208
  %8 = icmp sge i32 %4, %7, !dbg !208
  %9 = or i1 %3, %8, !dbg !208
  br i1 %9, label %10, label %13, !dbg !208

10:                                               ; preds = %body
  %11 = call ptr @sn.alloca(i32 8), !dbg !211
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, ptr noundef nonnull align 8 dereferenceable(64) @.str.3), !dbg !211
  %12 = call ptr @sn.eh.create(ptr %11, i32 1000), !dbg !211
  call void @sn.eh.throw(ptr %12), !dbg !211
  br label %14, !dbg !211

13:                                               ; preds = %body
  br label %14, !dbg !211

14:                                               ; preds = %13, %10
  %15 = load ptr, ptr %arg.self, align 8, !dbg !208
  %16 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %15, i32 0, i32 4, !dbg !208
  %17 = load ptr, ptr %16, align 8, !dbg !208
  %18 = load i32, ptr %arg.index, align 4, !dbg !212
  %19 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18), !dbg !213
  %20 = ptrtoint ptr %19 to i32, !dbg !213
  ret i32 %20, !dbg !213
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17722SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) !dbg !214 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !217, metadata !DIExpression()), !dbg !218
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !219, metadata !DIExpression()), !dbg !218
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !218
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 2, !dbg !218
  %4 = load i32, ptr %3, align 4, !dbg !218
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !220
  store i32 %5, ptr %3, align 4, !dbg !220
  %6 = load ptr, ptr %arg.self, align 8, !dbg !218
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 4, !dbg !218
  %8 = load ptr, ptr %7, align 8, !dbg !218
  %9 = load ptr, ptr %arg.self, align 8, !dbg !218
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 4, !dbg !218
  %11 = load ptr, ptr %10, align 8, !dbg !218
  %12 = load ptr, ptr %arg.self, align 8, !dbg !218
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !218
  %14 = load i32, ptr %13, align 4, !dbg !218
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !221
  store ptr %15, ptr %7, align 8, !dbg !221
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4sizeCv17718SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !222 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !225, metadata !DIExpression()), !dbg !226
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !226
  %2 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !226
  %3 = load i32, ptr %2, align 4, !dbg !226
  ret i32 %3, !dbg !226
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) !dbg !227 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !228, metadata !DIExpression()), !dbg !229
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !230, metadata !DIExpression()), !dbg !229
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !229
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 3, !dbg !229
  %4 = load i32, ptr %3, align 4, !dbg !229
  %5 = add i32 %4, 1, !dbg !231
  %6 = load ptr, ptr %arg.self, align 8, !dbg !229
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 2, !dbg !229
  %8 = load i32, ptr %7, align 4, !dbg !229
  %9 = icmp sge i32 %5, %8, !dbg !229
  br i1 %9, label %10, label %16, !dbg !229

10:                                               ; preds = %body
  %11 = load ptr, ptr %arg.self, align 8, !dbg !229
  %12 = load ptr, ptr %arg.self, align 8, !dbg !229
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !229
  %14 = load i32, ptr %13, align 4, !dbg !229
  %15 = add i32 %14, 10, !dbg !232
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %15), !dbg !233
  br label %17, !dbg !233

16:                                               ; preds = %body
  br label %17, !dbg !233

17:                                               ; preds = %16, %10
  %18 = load ptr, ptr %arg.self, align 8, !dbg !229
  %19 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 4, !dbg !229
  %20 = load ptr, ptr %19, align 8, !dbg !229
  %21 = load ptr, ptr %arg.self, align 8, !dbg !229
  %22 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 3, !dbg !229
  %23 = load i32, ptr %22, align 4, !dbg !229
  %24 = load i32, ptr %arg.value, align 4, !dbg !234
  %25 = inttoptr i32 %24 to ptr, !dbg !234
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %23, ptr %25), !dbg !235
  %26 = load ptr, ptr %arg.self, align 8, !dbg !229
  %27 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %26, i32 0, i32 3, !dbg !229
  %28 = load i32, ptr %27, align 4, !dbg !229
  %29 = load ptr, ptr %arg.self, align 8, !dbg !229
  %30 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %29, i32 0, i32 3, !dbg !229
  %31 = load i32, ptr %30, align 4, !dbg !229
  %32 = add i32 %31, 1, !dbg !236
  store i32 %32, ptr %27, align 4, !dbg !236
  ret void
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) !dbg !237 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !238, metadata !DIExpression()), !dbg !239
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !240, metadata !DIExpression()), !dbg !239
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !239
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 2, !dbg !239
  %4 = load i32, ptr %3, align 4, !dbg !239
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !241
  store i32 %5, ptr %3, align 4, !dbg !241
  %6 = load ptr, ptr %arg.self, align 8, !dbg !239
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 4, !dbg !239
  %8 = load ptr, ptr %7, align 8, !dbg !239
  %9 = load ptr, ptr %arg.self, align 8, !dbg !239
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 4, !dbg !239
  %11 = load ptr, ptr %10, align 8, !dbg !239
  %12 = load ptr, ptr %arg.self, align 8, !dbg !239
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !239
  %14 = load i32, ptr %13, align 4, !dbg !239
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !242
  store ptr %15, ptr %7, align 8, !dbg !242
  ret void
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !243 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !246, metadata !DIExpression()), !dbg !247
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !247
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !247
  %2 = load ptr, ptr %arg.self, align 8, !dbg !247
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 1, !dbg !247
  %4 = load i32, ptr %3, align 4, !dbg !247
  store i32 0, ptr %3, align 4, !dbg !248
  %5 = load ptr, ptr %arg.self, align 8, !dbg !247
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 2, !dbg !247
  %7 = load i32, ptr %6, align 4, !dbg !247
  store i32 10, ptr %6, align 4, !dbg !249
  %8 = load ptr, ptr %arg.self, align 8, !dbg !247
  %9 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %8, i32 0, i32 3, !dbg !247
  %10 = load i32, ptr %9, align 4, !dbg !247
  store i32 0, ptr %9, align 4, !dbg !250
  %11 = load ptr, ptr %arg.self, align 8, !dbg !247
  %12 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %11, i32 0, i32 4, !dbg !247
  %13 = load ptr, ptr %12, align 8, !dbg !247
  %14 = load ptr, ptr %arg.self, align 8, !dbg !247
  %15 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 2, !dbg !247
  %16 = load i32, ptr %15, align 4, !dbg !247
  %17 = call ptr @sn.ua.alloc(i32 %16) #2, !dbg !251
  store ptr %17, ptr %12, align 8, !dbg !251
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17511SaA1T3i64A2T4char.rFnE"(i64 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 !dbg !252 {
entry:
  %arg.num = alloca i64, align 8
  store i64 %0, ptr %arg.num, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !255, metadata !DIExpression()), !dbg !256
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !257, metadata !DIExpression()), !dbg !256
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !258, metadata !DIExpression()), !dbg !259
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !260
  %3 = load i64, ptr %arg.num, align 8, !dbg !261
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17519SaA1T3i32A2T4char.rA3T3i64FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i64 %3) #0, !dbg !262
  store ptr %4, ptr %var.buffer, align 8, !dbg !262
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !263
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !264
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !264
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !264
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !264
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !264
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !264
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 !dbg !265 {
entry:
  %arg.num = alloca i32, align 4
  store i32 %0, ptr %arg.num, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !268, metadata !DIExpression()), !dbg !269
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !270, metadata !DIExpression()), !dbg !269
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !271, metadata !DIExpression()), !dbg !272
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !273
  %3 = load i32, ptr %arg.num, align 4, !dbg !274
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3) #0, !dbg !275
  store ptr %4, ptr %var.buffer, align 8, !dbg !275
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !276
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !277
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !277
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !277
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !277
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !277
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !277
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17433SaA1T3i16A2T4char.rFnE"(i16 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 !dbg !278 {
entry:
  %arg.num = alloca i16, align 2
  store i16 %0, ptr %arg.num, align 2
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !281, metadata !DIExpression()), !dbg !282
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !283, metadata !DIExpression()), !dbg !282
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !284, metadata !DIExpression()), !dbg !285
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !286
  %3 = load i16, ptr %arg.num, align 2, !dbg !287
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17441SaA1T3i32A2T4char.rA3T3i16FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i16 %3) #0, !dbg !288
  store ptr %4, ptr %var.buffer, align 8, !dbg !288
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !289
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !290
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !290
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !290
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !290
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !290
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !290
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17394SaA1T2i8A2T4char.rFnE"(i8 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 !dbg !291 {
entry:
  %arg.num = alloca i8, align 1
  store i8 %0, ptr %arg.num, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !294, metadata !DIExpression()), !dbg !295
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !296, metadata !DIExpression()), !dbg !295
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !297, metadata !DIExpression()), !dbg !298
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !299
  %3 = load i8, ptr %arg.num, align 1, !dbg !300
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17402SaA1T3i32A2T4char.rA3T2i8FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i8 %3) #0, !dbg !301
  store ptr %4, ptr %var.buffer, align 8, !dbg !301
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !302
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !303
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !303
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !303
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !303
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !303
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !303
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&9to_stringCv17327SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !304 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !307, metadata !DIExpression()), !dbg !308
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !309
  %2 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, align 8, !dbg !309
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %2, !dbg !309
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5#DbEqCv17180SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1) #0 !dbg !310 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !313, metadata !DIExpression()), !dbg !314
  %arg.other = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !315, metadata !DIExpression()), !dbg !314
  %"var.$iter" = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !316, metadata !DIExpression()), !dbg !317
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !318, metadata !DIExpression()), !dbg !317
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !319, metadata !DIExpression()), !dbg !317
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !314
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 3, !dbg !314
  %4 = load i32, ptr %3, align 4, !dbg !314
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !314
  %6 = load i32, ptr %5, align 4, !dbg !314
  %7 = icmp ne i32 %4, %6, !dbg !314
  br i1 %7, label %8, label %9, !dbg !314

8:                                                ; preds = %body
  ret i1 false, !dbg !320

9:                                                ; preds = %body
  br label %10, !dbg !320

10:                                               ; preds = %9
  %11 = load ptr, ptr %arg.self, align 8, !dbg !314
  %12 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %11, i32 0, i32 3, !dbg !314
  %13 = load i32, ptr %12, align 4, !dbg !314
  %14 = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8, !dbg !317
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 0, !dbg !317
  store ptr @"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %15, align 8, !dbg !317
  call void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %14, i32 0, i32 %13), !dbg !317
  %16 = load %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, align 8, !dbg !317
  store %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" %16, ptr %"var.$iter", align 8, !dbg !317
  %17 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !317
  %18 = load ptr, ptr %"var.$iter", align 8, !dbg !317
  %19 = getelementptr inbounds ptr, ptr %18, i32 1, !dbg !317
  %20 = load ptr, ptr %19, align 8, !dbg !317
  %21 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %20(ptr %"var.$iter"), !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %21, ptr %17, align 4, !dbg !317
  %22 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %17, align 4, !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %22, ptr %"var.$iter_value", align 4, !dbg !317
  br label %23, !dbg !317

23:                                               ; preds = %40, %10
  %24 = call i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !317
  br i1 %24, label %25, label %37, !dbg !317

25:                                               ; preds = %23
  %26 = call i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !317
  store i32 %26, ptr %var.i, align 4, !dbg !317
  %27 = load ptr, ptr %arg.self, align 8, !dbg !314
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 4, !dbg !314
  %29 = load ptr, ptr %28, align 8, !dbg !314
  %30 = load i32, ptr %var.i, align 4, !dbg !321
  %31 = call ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %29, i32 %30) #0, !dbg !321
  %32 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !314
  %33 = load ptr, ptr %32, align 8, !dbg !314
  %34 = load i32, ptr %var.i, align 4, !dbg !322
  %35 = call ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %33, i32 %34) #0, !dbg !322
  %36 = icmp ne ptr %31, %35, !dbg !322
  br i1 %36, label %38, label %39, !dbg !322

37:                                               ; preds = %23
  ret i1 true, !dbg !323

38:                                               ; preds = %25
  ret i1 false, !dbg !324

39:                                               ; preds = %25
  br label %40, !dbg !324

40:                                               ; preds = %39
  %41 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !317
  %42 = load ptr, ptr %"var.$iter", align 8, !dbg !317
  %43 = getelementptr inbounds ptr, ptr %42, i32 1, !dbg !317
  %44 = load ptr, ptr %43, align 8, !dbg !317
  %45 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %44(ptr %"var.$iter"), !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %45, ptr %41, align 4, !dbg !317
  %.load = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %41, align 4, !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %.load, ptr %"var.$iter_value", align 4, !dbg !317
  br label %23, !dbg !317
}

; Function Attrs: alwaysinline
define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&5resetCv17301SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !325 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !330, metadata !DIExpression()), !dbg !331
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !331
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !331
  %3 = load i32, ptr %2, align 4, !dbg !331
  %4 = load ptr, ptr %arg.self, align 8, !dbg !331
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 2, !dbg !331
  %6 = load i32, ptr %5, align 4, !dbg !331
  store i32 %6, ptr %2, align 4, !dbg !331
  ret void
}

define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !332 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !335, metadata !DIExpression()), !dbg !336
  %var.iter = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.iter, metadata !337, metadata !DIExpression()), !dbg !339
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !336
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !336
  %3 = load i32, ptr %2, align 4, !dbg !336
  %4 = load ptr, ptr %arg.self, align 8, !dbg !336
  %5 = call i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %4) #0, !dbg !340
  %6 = icmp sgt i32 %3, %5, !dbg !340
  br i1 %6, label %7, label %11, !dbg !340

7:                                                ; preds = %body
  %8 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !341
  %9 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE"() #0, !dbg !341
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %9, ptr %8, align 4, !dbg !341
  %10 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %8, align 4, !dbg !341
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %10, !dbg !341

11:                                               ; preds = %body
  br label %12, !dbg !341

12:                                               ; preds = %11
  %13 = load ptr, ptr %arg.self, align 8, !dbg !336
  %14 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 1, !dbg !336
  %15 = load i32, ptr %14, align 4, !dbg !336
  %16 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !336
  %17 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE"(i32 %15) #0, !dbg !342
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %17, ptr %16, align 4, !dbg !342
  %18 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %16, align 4, !dbg !342
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %18, ptr %var.iter, align 4, !dbg !342
  %19 = load ptr, ptr %arg.self, align 8, !dbg !336
  %20 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %19, i32 0, i32 1, !dbg !336
  %21 = load i32, ptr %20, align 4, !dbg !336
  %22 = load ptr, ptr %arg.self, align 8, !dbg !336
  %23 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %22, i32 0, i32 1, !dbg !336
  %24 = load i32, ptr %23, align 4, !dbg !336
  %25 = add i32 %24, 1, !dbg !343
  store i32 %25, ptr %20, align 4, !dbg !343
  %26 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %var.iter, align 4, !dbg !344
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %26, !dbg !344
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !345 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !348, metadata !DIExpression()), !dbg !349
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !349
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !349
  %3 = load i32, ptr %2, align 4, !dbg !349
  ret i32 %3, !dbg !349
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&5beginCv17287SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !350 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !351, metadata !DIExpression()), !dbg !352
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !352
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 2, !dbg !352
  %3 = load i32, ptr %2, align 4, !dbg !352
  ret i32 %3, !dbg !352
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4sizeCv17283SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !353 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !354, metadata !DIExpression()), !dbg !355
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !355
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !355
  %3 = load i32, ptr %2, align 4, !dbg !355
  %4 = load ptr, ptr %arg.self, align 8, !dbg !355
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 2, !dbg !355
  %6 = load i32, ptr %5, align 4, !dbg !355
  %7 = sub i32 %3, %6, !dbg !355
  ret i32 %7, !dbg !355
}

define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17275SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) !dbg !356 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !359, metadata !DIExpression()), !dbg !360
  %arg.end = alloca i32, align 4
  store i32 %1, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !361, metadata !DIExpression()), !dbg !360
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !360
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !360
  %3 = load ptr, ptr %arg.self, align 8, !dbg !360
  %4 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %3, i32 0, i32 1, !dbg !360
  %5 = load i32, ptr %4, align 4, !dbg !360
  store i32 0, ptr %4, align 4, !dbg !362
  %6 = load ptr, ptr %arg.self, align 8, !dbg !360
  %7 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 2, !dbg !360
  %8 = load i32, ptr %7, align 4, !dbg !360
  store i32 0, ptr %7, align 4, !dbg !363
  %9 = load ptr, ptr %arg.self, align 8, !dbg !360
  %10 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 3, !dbg !360
  %11 = load i32, ptr %10, align 4, !dbg !360
  %12 = load i32, ptr %arg.end, align 4, !dbg !364
  store i32 %12, ptr %10, align 4, !dbg !364
  ret void
}

define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) !dbg !365 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !368, metadata !DIExpression()), !dbg !369
  %arg.start = alloca i32, align 4
  store i32 %1, ptr %arg.start, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.start, metadata !370, metadata !DIExpression()), !dbg !369
  %arg.end = alloca i32, align 4
  store i32 %2, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !371, metadata !DIExpression()), !dbg !369
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !369
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !369
  %4 = load ptr, ptr %arg.self, align 8, !dbg !369
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !369
  %6 = load i32, ptr %5, align 4, !dbg !369
  store i32 0, ptr %5, align 4, !dbg !372
  %7 = load ptr, ptr %arg.self, align 8, !dbg !369
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 2, !dbg !369
  %9 = load i32, ptr %8, align 4, !dbg !369
  store i32 0, ptr %8, align 4, !dbg !373
  %10 = load ptr, ptr %arg.self, align 8, !dbg !369
  %11 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 2, !dbg !369
  %12 = load i32, ptr %11, align 4, !dbg !369
  %13 = load i32, ptr %arg.start, align 4, !dbg !374
  store i32 %13, ptr %11, align 4, !dbg !374
  %14 = load ptr, ptr %arg.self, align 8, !dbg !369
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 3, !dbg !369
  %16 = load i32, ptr %15, align 4, !dbg !369
  %17 = load i32, ptr %arg.end, align 4, !dbg !375
  store i32 %17, ptr %15, align 4, !dbg !375
  %18 = load ptr, ptr %arg.self, align 8, !dbg !369
  %19 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 1, !dbg !369
  %20 = load i32, ptr %19, align 4, !dbg !369
  %21 = load ptr, ptr %arg.self, align 8, !dbg !369
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 2, !dbg !369
  %23 = load i32, ptr %22, align 4, !dbg !369
  store i32 %23, ptr %19, align 4, !dbg !369
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&5resetCv17247SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !376 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !380, metadata !DIExpression()), !dbg !381
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !381
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !381
  %3 = load i32, ptr %2, align 4, !dbg !381
  store i32 0, ptr %2, align 4, !dbg !382
  ret void
}

define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !383 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !386, metadata !DIExpression()), !dbg !387
  br label %body

body:                                             ; preds = %entry
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" zeroinitializer
}

define internal void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !388 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !389, metadata !DIExpression()), !dbg !390
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !390
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !390
  %3 = load i32, ptr %2, align 4, !dbg !390
  store i32 0, ptr %2, align 4, !dbg !391
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE"(i32 %0) #0 !dbg !392 {
entry:
  %arg.val = alloca i32, align 4
  store i32 %0, ptr %arg.val, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !395, metadata !DIExpression()), !dbg !396
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.val, align 4, !dbg !397
  %2 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !398
  call void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %1), !dbg !398
  %3 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %2, align 4, !dbg !398
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %3, !dbg !398
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE"() #0 !dbg !399 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !402
  call void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !402
  %1 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !402
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %1, !dbg !402
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !403 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !407, metadata !DIExpression()), !dbg !408
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !408
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !408
  %3 = load i1, ptr %2, align 1, !dbg !408
  ret i1 %3, !dbg !408
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !409 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !412, metadata !DIExpression()), !dbg !413
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !413
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !413
  %3 = load i1, ptr %2, align 1, !dbg !413
  %4 = icmp eq i1 %3, false, !dbg !413
  br i1 %4, label %5, label %8, !dbg !413

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !414
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.4), !dbg !414
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !414
  call void @sn.eh.throw(ptr %7), !dbg !414
  br label %9, !dbg !414

8:                                                ; preds = %body
  br label %9, !dbg !414

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !413
  %11 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 1, !dbg !413
  %12 = load i32, ptr %11, align 4, !dbg !413
  ret i32 %12, !dbg !413
}

define internal void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) !dbg !415 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !418, metadata !DIExpression()), !dbg !419
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !420, metadata !DIExpression()), !dbg !419
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !419
  %3 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 0, !dbg !419
  %4 = load i1, ptr %3, align 1, !dbg !419
  store i1 false, ptr %3, align 1, !dbg !421
  %5 = load ptr, ptr %arg.self, align 8, !dbg !419
  %6 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 1, !dbg !419
  %7 = load i32, ptr %6, align 4, !dbg !419
  %8 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE"() #0, !dbg !422
  store i32 %8, ptr %6, align 4, !dbg !422
  %9 = load ptr, ptr %arg.self, align 8, !dbg !419
  %10 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 1, !dbg !419
  %11 = load i32, ptr %10, align 4, !dbg !419
  %12 = load i32, ptr %arg.value, align 4, !dbg !423
  store i32 %12, ptr %10, align 4, !dbg !423
  %13 = load ptr, ptr %arg.self, align 8, !dbg !419
  %14 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 0, !dbg !419
  %15 = load i1, ptr %14, align 1, !dbg !419
  store i1 true, ptr %14, align 1, !dbg !424
  ret void
}

define internal void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !425 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !428, metadata !DIExpression()), !dbg !429
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !429
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !429
  %3 = load i1, ptr %2, align 1, !dbg !429
  store i1 false, ptr %2, align 1, !dbg !430
  %4 = load ptr, ptr %arg.self, align 8, !dbg !429
  %5 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !429
  %6 = load i32, ptr %5, align 4, !dbg !429
  %7 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE"() #0, !dbg !431
  store i32 %7, ptr %5, align 4, !dbg !431
  ret void
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !432 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !435, metadata !DIExpression()), !dbg !436
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !436
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 4, !dbg !436
  %3 = load ptr, ptr %2, align 8, !dbg !436
  ret ptr %3, !dbg !436
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4sizeCv17172SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !437 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !440, metadata !DIExpression()), !dbg !441
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !441
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 3, !dbg !441
  %3 = load i32, ptr %2, align 4, !dbg !441
  ret i32 %3, !dbg !441
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i32 %2) !dbg !442 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !445, metadata !DIExpression()), !dbg !446
  %arg.other = alloca ptr, align 8
  store ptr %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !447, metadata !DIExpression()), !dbg !446
  %arg.length = alloca i32, align 4
  store i32 %2, ptr %arg.length, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.length, metadata !448, metadata !DIExpression()), !dbg !446
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !446
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !446
  %4 = load ptr, ptr %arg.self, align 8, !dbg !446
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %4, i32 0, i32 1, !dbg !446
  %6 = load i32, ptr %5, align 4, !dbg !446
  store i32 0, ptr %5, align 4, !dbg !449
  %7 = load ptr, ptr %arg.self, align 8, !dbg !446
  %8 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, i32 0, i32 2, !dbg !446
  %9 = load i32, ptr %8, align 4, !dbg !446
  store i32 10, ptr %8, align 4, !dbg !450
  %10 = load ptr, ptr %arg.self, align 8, !dbg !446
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %10, i32 0, i32 3, !dbg !446
  %12 = load i32, ptr %11, align 4, !dbg !446
  store i32 0, ptr %11, align 4, !dbg !451
  %13 = load ptr, ptr %arg.self, align 8, !dbg !446
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %13, i32 0, i32 4, !dbg !446
  %15 = load ptr, ptr %14, align 8, !dbg !446
  store ptr @.str.5, ptr %14, align 8, !dbg !452
  %16 = load ptr, ptr %arg.self, align 8, !dbg !446
  %17 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %16, i32 0, i32 4, !dbg !446
  %18 = load ptr, ptr %17, align 8, !dbg !446
  %19 = load ptr, ptr %arg.other, align 8, !dbg !453
  store ptr %19, ptr %17, align 8, !dbg !453
  %20 = load ptr, ptr %arg.self, align 8, !dbg !446
  %21 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %20, i32 0, i32 3, !dbg !446
  %22 = load i32, ptr %21, align 4, !dbg !446
  %23 = load i32, ptr %arg.length, align 4, !dbg !454
  store i32 %23, ptr %21, align 4, !dbg !454
  %24 = load ptr, ptr %arg.self, align 8, !dbg !446
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !446
  %26 = load i32, ptr %25, align 4, !dbg !446
  %27 = load i32, ptr %arg.length, align 4, !dbg !446
  %28 = add i32 %27, 10, !dbg !455
  store i32 %28, ptr %25, align 4, !dbg !455
  ret void
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17151SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) !dbg !456 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !459, metadata !DIExpression()), !dbg !460
  %arg.other = alloca ptr, align 8
  store ptr %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !461, metadata !DIExpression()), !dbg !460
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !460
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !460
  %3 = load ptr, ptr %arg.self, align 8, !dbg !460
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !460
  %5 = load i32, ptr %4, align 4, !dbg !460
  store i32 0, ptr %4, align 4, !dbg !462
  %6 = load ptr, ptr %arg.self, align 8, !dbg !460
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !460
  %8 = load i32, ptr %7, align 4, !dbg !460
  store i32 10, ptr %7, align 4, !dbg !463
  %9 = load ptr, ptr %arg.self, align 8, !dbg !460
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !460
  %11 = load i32, ptr %10, align 4, !dbg !460
  store i32 0, ptr %10, align 4, !dbg !464
  %12 = load ptr, ptr %arg.self, align 8, !dbg !460
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !460
  %14 = load ptr, ptr %13, align 8, !dbg !460
  store ptr @.str.6, ptr %13, align 8, !dbg !465
  %15 = load ptr, ptr %arg.self, align 8, !dbg !460
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !460
  %17 = load ptr, ptr %16, align 8, !dbg !460
  %18 = load ptr, ptr %arg.other, align 8, !dbg !460
  %19 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %18, i32 0, i32 4, !dbg !460
  %20 = load ptr, ptr %19, align 8, !dbg !460
  store ptr %20, ptr %16, align 8, !dbg !460
  %21 = load ptr, ptr %arg.self, align 8, !dbg !460
  %22 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %21, i32 0, i32 3, !dbg !460
  %23 = load i32, ptr %22, align 4, !dbg !460
  %24 = load ptr, ptr %arg.other, align 8, !dbg !460
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 3, !dbg !460
  %26 = load i32, ptr %25, align 4, !dbg !460
  store i32 %26, ptr %22, align 4, !dbg !460
  %27 = load ptr, ptr %arg.self, align 8, !dbg !460
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 2, !dbg !460
  %29 = load i32, ptr %28, align 4, !dbg !460
  %30 = load ptr, ptr %arg.other, align 8, !dbg !460
  %31 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %30, i32 0, i32 2, !dbg !460
  %32 = load i32, ptr %31, align 4, !dbg !460
  store i32 %32, ptr %28, align 4, !dbg !460
  ret void
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) !dbg !466 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !469, metadata !DIExpression()), !dbg !470
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !471, metadata !DIExpression()), !dbg !470
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !470
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !470
  %3 = load ptr, ptr %arg.self, align 8, !dbg !470
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !470
  %5 = load i32, ptr %4, align 4, !dbg !470
  store i32 0, ptr %4, align 4, !dbg !472
  %6 = load ptr, ptr %arg.self, align 8, !dbg !470
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !470
  %8 = load i32, ptr %7, align 4, !dbg !470
  store i32 10, ptr %7, align 4, !dbg !473
  %9 = load ptr, ptr %arg.self, align 8, !dbg !470
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !470
  %11 = load i32, ptr %10, align 4, !dbg !470
  store i32 0, ptr %10, align 4, !dbg !474
  %12 = load ptr, ptr %arg.self, align 8, !dbg !470
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !470
  %14 = load ptr, ptr %13, align 8, !dbg !470
  store ptr @.str.7, ptr %13, align 8, !dbg !475
  %15 = load ptr, ptr %arg.self, align 8, !dbg !470
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !470
  %17 = load ptr, ptr %16, align 8, !dbg !470
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !476
  store ptr %18, ptr %16, align 8, !dbg !476
  %19 = load ptr, ptr %arg.self, align 8, !dbg !470
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %19, i32 0, i32 3, !dbg !470
  %21 = load i32, ptr %20, align 4, !dbg !470
  %22 = load ptr, ptr %arg.buffer, align 8, !dbg !477
  %23 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %22), !dbg !478
  store i32 %23, ptr %20, align 4, !dbg !478
  %24 = load ptr, ptr %arg.self, align 8, !dbg !470
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !470
  %26 = load i32, ptr %25, align 4, !dbg !470
  %27 = load ptr, ptr %arg.self, align 8, !dbg !470
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 3, !dbg !470
  %29 = load i32, ptr %28, align 4, !dbg !470
  %30 = add i32 %29, 10, !dbg !479
  store i32 %30, ptr %25, align 4, !dbg !479
  ret void
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17134SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !480 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !483, metadata !DIExpression()), !dbg !484
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !484
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !484
  %2 = load ptr, ptr %arg.self, align 8, !dbg !484
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 1, !dbg !484
  %4 = load i32, ptr %3, align 4, !dbg !484
  store i32 0, ptr %3, align 4, !dbg !485
  %5 = load ptr, ptr %arg.self, align 8, !dbg !484
  %6 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %5, i32 0, i32 2, !dbg !484
  %7 = load i32, ptr %6, align 4, !dbg !484
  store i32 10, ptr %6, align 4, !dbg !486
  %8 = load ptr, ptr %arg.self, align 8, !dbg !484
  %9 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %8, i32 0, i32 3, !dbg !484
  %10 = load i32, ptr %9, align 4, !dbg !484
  store i32 0, ptr %9, align 4, !dbg !487
  %11 = load ptr, ptr %arg.self, align 8, !dbg !484
  %12 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %11, i32 0, i32 4, !dbg !484
  %13 = load ptr, ptr %12, align 8, !dbg !484
  store ptr @.str.8, ptr %12, align 8, !dbg !488
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&5resetCv17110SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !489 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !493, metadata !DIExpression()), !dbg !494
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !494
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17018ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !494
  %3 = load i32, ptr %2, align 4, !dbg !494
  store i32 0, ptr %2, align 4, !dbg !495
  ret void
}

define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !496 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !500, metadata !DIExpression()), !dbg !501
  br label %body

body:                                             ; preds = %entry
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" zeroinitializer
}

define internal void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !502 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !503, metadata !DIExpression()), !dbg !504
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !504
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17018ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !504
  %3 = load i32, ptr %2, align 4, !dbg !504
  store i32 0, ptr %2, align 4, !dbg !505
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&4IterCv17019ClsGStA1T4charClsE&5validCv17086SaA1T4charFnE"(i8 %0) #0 !dbg !506 {
entry:
  %arg.val = alloca i8, align 1
  store i8 %0, ptr %arg.val, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !509, metadata !DIExpression()), !dbg !510
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.val, align 1, !dbg !511
  %2 = alloca %"class._$SN&4IterCv17019ClsGStA1T4charClsE", align 8, !dbg !512
  call void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17033SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rA2T4charFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i8 %1), !dbg !512
  %3 = load %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %2, align 1, !dbg !512
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" %3, !dbg !512
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&4IterCv17019ClsGStA1T4charClsE&7invalidCv17084SaFnE"() #0 !dbg !513 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = alloca %"class._$SN&4IterCv17019ClsGStA1T4charClsE", align 8, !dbg !516
  call void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17027SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !516
  %1 = load %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %0, align 1, !dbg !516
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" %1, !dbg !516
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17019ClsGStA1T4charClsE&8is_validCv17080SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !517 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !521, metadata !DIExpression()), !dbg !522
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !522
  %2 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !522
  %3 = load i1, ptr %2, align 1, !dbg !522
  ret i1 %3, !dbg !522
}

; Function Attrs: alwaysinline
define internal i8 @"_$SN&4IterCv17019ClsGStA1T4charClsE&5valueCv17041SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !523 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !526, metadata !DIExpression()), !dbg !527
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !527
  %2 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !527
  %3 = load i1, ptr %2, align 1, !dbg !527
  %4 = icmp eq i1 %3, false, !dbg !527
  br i1 %4, label %5, label %8, !dbg !527

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !528
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.9), !dbg !528
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !528
  call void @sn.eh.throw(ptr %7), !dbg !528
  br label %9, !dbg !528

8:                                                ; preds = %body
  br label %9, !dbg !528

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !527
  %11 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %10, i32 0, i32 1, !dbg !527
  %12 = load i8, ptr %11, align 1, !dbg !527
  ret i8 %12, !dbg !527
}

define internal ptr @"_$SN&9ExceptionCv17046ClsE&4whatCv17060SaA1_$SN&9ExceptionCv17046ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !529 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !534, metadata !DIExpression()), !dbg !535
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !535
  %2 = getelementptr inbounds %"class._$SN&9ExceptionCv17046ClsE", ptr %1, i32 0, i32 0, !dbg !535
  %3 = load ptr, ptr %2, align 8, !dbg !535
  ret ptr %3, !dbg !535
}

define internal void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) !dbg !536 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !539, metadata !DIExpression()), !dbg !540
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !541, metadata !DIExpression()), !dbg !540
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !540
  %3 = getelementptr inbounds %"class._$SN&9ExceptionCv17046ClsE", ptr %2, i32 0, i32 0, !dbg !540
  %4 = load ptr, ptr %3, align 8, !dbg !540
  %5 = load ptr, ptr %arg.m, align 8, !dbg !542
  store ptr %5, ptr %3, align 8, !dbg !542
  ret void
}

define internal void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17033SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rA2T4charFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i8 %1) !dbg !543 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !546, metadata !DIExpression()), !dbg !547
  %arg.value = alloca i8, align 1
  store i8 %1, ptr %arg.value, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !548, metadata !DIExpression()), !dbg !547
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !547
  %3 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %2, i32 0, i32 0, !dbg !547
  %4 = load i1, ptr %3, align 1, !dbg !547
  store i1 false, ptr %3, align 1, !dbg !549
  %5 = load ptr, ptr %arg.self, align 8, !dbg !547
  %6 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %5, i32 0, i32 1, !dbg !547
  %7 = load i8, ptr %6, align 1, !dbg !547
  %8 = call i8 @"_$SN@sn.Core.CLib&8null_ptrCv17039SaFnE"() #0, !dbg !550
  store i8 %8, ptr %6, align 1, !dbg !550
  %9 = load ptr, ptr %arg.self, align 8, !dbg !547
  %10 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %9, i32 0, i32 1, !dbg !547
  %11 = load i8, ptr %10, align 1, !dbg !547
  %12 = load i8, ptr %arg.value, align 1, !dbg !551
  store i8 %12, ptr %10, align 1, !dbg !551
  %13 = load ptr, ptr %arg.self, align 8, !dbg !547
  %14 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %13, i32 0, i32 0, !dbg !547
  %15 = load i1, ptr %14, align 1, !dbg !547
  store i1 true, ptr %14, align 1, !dbg !552
  ret void
}

define internal void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17027SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !553 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !556, metadata !DIExpression()), !dbg !557
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !557
  %2 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !557
  %3 = load i1, ptr %2, align 1, !dbg !557
  store i1 false, ptr %2, align 1, !dbg !558
  %4 = load ptr, ptr %arg.self, align 8, !dbg !557
  %5 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %4, i32 0, i32 1, !dbg !557
  %6 = load i8, ptr %5, align 1, !dbg !557
  %7 = call i8 @"_$SN@sn.Core.CLib&8null_ptrCv17031SaFnE"() #0, !dbg !559
  store i8 %7, ptr %5, align 1, !dbg !559
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i64&9to_stringCv17501SaA1T3i64.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !570 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !574, metadata !DIExpression()), !dbg !575
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !576
  %2 = load i64, ptr %1, align 8, !dbg !576
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !577
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17511SaA1T3i64A2T4char.rFnE"(i64 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.10) #0, !dbg !578
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !578
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !578
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !578
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !564 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !567, metadata !DIExpression()), !dbg !568
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !569
  %2 = load i32, ptr %1, align 4, !dbg !569
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !570
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE"(i32 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.11) #0, !dbg !571
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !571
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !571
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !571
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i16&9to_stringCv17423SaA1T3i16.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !583 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !587, metadata !DIExpression()), !dbg !588
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !589
  %2 = load i16, ptr %1, align 2, !dbg !589
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !590
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17433SaA1T3i16A2T4char.rFnE"(i16 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.12) #0, !dbg !591
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !591
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !591
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !591
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT2i8&9to_stringCv17384SaA1T2i8.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !592 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !596, metadata !DIExpression()), !dbg !597
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !598
  %2 = load i8, ptr %1, align 1, !dbg !598
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !599
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17394SaA1T2i8A2T4char.rFnE"(i8 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.13) #0, !dbg !600
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !600
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !600
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !600
}

; Function Attrs: alwaysinline
declare !dbg !601 internal ptr @"_$SNT4char&4#IdxCv17374SaA1T4char.rA2T3i32FnE.15"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0

; Function Attrs: noinline
define private ptr @"_$SNT4char&4#IdxCv17374SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %index) #2 !dbg !607 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %index
  ret ptr %0
}

; Function Attrs: alwaysinline
declare !dbg !560 internal ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE.17"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0

; Function Attrs: noinline
define private ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %other) #2 !dbg !607 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %other
  ret ptr %0
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT4char&9to_stringCv17345SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !599 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !602, metadata !DIExpression()), !dbg !603
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !604
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !605
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 0, !dbg !605
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !605
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !605
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !605
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !605
}

; Function Attrs: alwaysinline
declare !dbg !568 internal ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE.19"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0

; Function Attrs: noinline
define private ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %index) #2 !dbg !610 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %index
  ret ptr %0
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&7is_markCv17616SaA1T4charFnE"(i8 %0) #0 !dbg !610 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !614, metadata !DIExpression()), !dbg !615
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !615
  %2 = icmp eq i8 %1, 96, !dbg !616
  %3 = load i8, ptr %arg.c, align 1, !dbg !615
  %4 = icmp eq i8 %3, 39, !dbg !617
  %5 = or i1 %2, %4, !dbg !617
  %6 = load i8, ptr %arg.c, align 1, !dbg !615
  %7 = icmp eq i8 %6, 94, !dbg !618
  %8 = or i1 %5, %7, !dbg !618
  %9 = load i8, ptr %arg.c, align 1, !dbg !615
  %10 = icmp eq i8 %9, 34, !dbg !619
  %11 = or i1 %8, %10, !dbg !619
  %12 = load i8, ptr %arg.c, align 1, !dbg !615
  %13 = icmp eq i8 %12, 126, !dbg !620
  %14 = or i1 %11, %13, !dbg !620
  %15 = load i8, ptr %arg.c, align 1, !dbg !615
  %16 = icmp eq i8 %15, 46, !dbg !621
  %17 = or i1 %14, %16, !dbg !621
  %18 = load i8, ptr %arg.c, align 1, !dbg !615
  %19 = icmp eq i8 %18, 45, !dbg !622
  %20 = or i1 %17, %19, !dbg !622
  %21 = load i8, ptr %arg.c, align 1, !dbg !615
  %22 = icmp eq i8 %21, 95, !dbg !623
  %23 = or i1 %20, %22, !dbg !623
  %24 = load i8, ptr %arg.c, align 1, !dbg !615
  %25 = icmp eq i8 %24, 42, !dbg !624
  %26 = or i1 %23, %25, !dbg !624
  %27 = load i8, ptr %arg.c, align 1, !dbg !615
  %28 = icmp eq i8 %27, 43, !dbg !625
  %29 = or i1 %26, %28, !dbg !625
  %30 = load i8, ptr %arg.c, align 1, !dbg !615
  %31 = icmp eq i8 %30, 61, !dbg !626
  %32 = or i1 %29, %31, !dbg !626
  %33 = load i8, ptr %arg.c, align 1, !dbg !615
  %34 = icmp eq i8 %33, 60, !dbg !627
  %35 = or i1 %32, %34, !dbg !627
  %36 = load i8, ptr %arg.c, align 1, !dbg !615
  %37 = icmp eq i8 %36, 62, !dbg !628
  %38 = or i1 %35, %37, !dbg !628
  %39 = load i8, ptr %arg.c, align 1, !dbg !615
  %40 = icmp eq i8 %39, 64, !dbg !629
  %41 = or i1 %38, %40, !dbg !629
  %42 = load i8, ptr %arg.c, align 1, !dbg !615
  %43 = icmp eq i8 %42, 58, !dbg !630
  %44 = or i1 %41, %43, !dbg !630
  %45 = load i8, ptr %arg.c, align 1, !dbg !615
  %46 = icmp eq i8 %45, 47, !dbg !631
  %47 = or i1 %44, %46, !dbg !631
  %48 = load i8, ptr %arg.c, align 1, !dbg !615
  %49 = icmp eq i8 %48, 92, !dbg !632
  %50 = or i1 %47, %49, !dbg !632
  %51 = load i8, ptr %arg.c, align 1, !dbg !615
  %52 = icmp eq i8 %51, 124, !dbg !633
  %53 = or i1 %50, %52, !dbg !633
  %54 = load i8, ptr %arg.c, align 1, !dbg !615
  %55 = icmp eq i8 %54, 33, !dbg !634
  %56 = or i1 %53, %55, !dbg !634
  %57 = load i8, ptr %arg.c, align 1, !dbg !615
  %58 = icmp eq i8 %57, 63, !dbg !635
  %59 = or i1 %56, %58, !dbg !635
  %60 = load i8, ptr %arg.c, align 1, !dbg !615
  %61 = icmp eq i8 %60, 35, !dbg !636
  %62 = or i1 %59, %61, !dbg !636
  %63 = load i8, ptr %arg.c, align 1, !dbg !615
  %64 = icmp eq i8 %63, 36, !dbg !637
  %65 = or i1 %62, %64, !dbg !637
  %66 = load i8, ptr %arg.c, align 1, !dbg !615
  %67 = icmp eq i8 %66, 37, !dbg !638
  %68 = or i1 %65, %67, !dbg !638
  %69 = load i8, ptr %arg.c, align 1, !dbg !615
  %70 = icmp eq i8 %69, 38, !dbg !639
  %71 = or i1 %68, %70, !dbg !639
  %72 = load i8, ptr %arg.c, align 1, !dbg !615
  %73 = icmp eq i8 %72, 40, !dbg !640
  %74 = or i1 %71, %73, !dbg !640
  %75 = load i8, ptr %arg.c, align 1, !dbg !615
  %76 = icmp eq i8 %75, 41, !dbg !641
  %77 = or i1 %74, %76, !dbg !641
  %78 = load i8, ptr %arg.c, align 1, !dbg !615
  %79 = icmp eq i8 %78, 91, !dbg !642
  %80 = or i1 %77, %79, !dbg !642
  %81 = load i8, ptr %arg.c, align 1, !dbg !615
  %82 = icmp eq i8 %81, 93, !dbg !643
  %83 = or i1 %80, %82, !dbg !643
  %84 = load i8, ptr %arg.c, align 1, !dbg !615
  %85 = icmp eq i8 %84, 123, !dbg !644
  %86 = or i1 %83, %85, !dbg !644
  %87 = load i8, ptr %arg.c, align 1, !dbg !615
  %88 = icmp eq i8 %87, 125, !dbg !645
  %89 = or i1 %86, %88, !dbg !645
  ret i1 %89, !dbg !645
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&6is_symCv17613SaA1T4charFnE"(i8 %0) #0 !dbg !646 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !647, metadata !DIExpression()), !dbg !648
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !648
  %2 = icmp eq i8 %1, 43, !dbg !649
  %3 = load i8, ptr %arg.c, align 1, !dbg !648
  %4 = icmp eq i8 %3, 45, !dbg !650
  %5 = or i1 %2, %4, !dbg !650
  %6 = load i8, ptr %arg.c, align 1, !dbg !648
  %7 = icmp eq i8 %6, 42, !dbg !651
  %8 = or i1 %5, %7, !dbg !651
  %9 = load i8, ptr %arg.c, align 1, !dbg !648
  %10 = icmp eq i8 %9, 47, !dbg !652
  %11 = or i1 %8, %10, !dbg !652
  %12 = load i8, ptr %arg.c, align 1, !dbg !648
  %13 = icmp eq i8 %12, 92, !dbg !653
  %14 = or i1 %11, %13, !dbg !653
  %15 = load i8, ptr %arg.c, align 1, !dbg !648
  %16 = icmp eq i8 %15, 124, !dbg !654
  %17 = or i1 %14, %16, !dbg !654
  %18 = load i8, ptr %arg.c, align 1, !dbg !648
  %19 = icmp eq i8 %18, 38, !dbg !655
  %20 = or i1 %17, %19, !dbg !655
  %21 = load i8, ptr %arg.c, align 1, !dbg !648
  %22 = icmp eq i8 %21, 94, !dbg !656
  %23 = or i1 %20, %22, !dbg !656
  %24 = load i8, ptr %arg.c, align 1, !dbg !648
  %25 = icmp eq i8 %24, 60, !dbg !657
  %26 = or i1 %23, %25, !dbg !657
  %27 = load i8, ptr %arg.c, align 1, !dbg !648
  %28 = icmp eq i8 %27, 62, !dbg !658
  %29 = or i1 %26, %28, !dbg !658
  %30 = load i8, ptr %arg.c, align 1, !dbg !648
  %31 = icmp eq i8 %30, 61, !dbg !659
  %32 = or i1 %29, %31, !dbg !659
  %33 = load i8, ptr %arg.c, align 1, !dbg !648
  %34 = icmp eq i8 %33, 126, !dbg !660
  %35 = or i1 %32, %34, !dbg !660
  %36 = load i8, ptr %arg.c, align 1, !dbg !648
  %37 = icmp eq i8 %36, 64, !dbg !661
  %38 = or i1 %35, %37, !dbg !661
  %39 = load i8, ptr %arg.c, align 1, !dbg !648
  %40 = icmp eq i8 %39, 36, !dbg !662
  %41 = or i1 %38, %40, !dbg !662
  %42 = load i8, ptr %arg.c, align 1, !dbg !648
  %43 = icmp eq i8 %42, 37, !dbg !663
  %44 = or i1 %41, %43, !dbg !663
  %45 = load i8, ptr %arg.c, align 1, !dbg !648
  %46 = icmp eq i8 %45, 33, !dbg !664
  %47 = or i1 %44, %46, !dbg !664
  %48 = load i8, ptr %arg.c, align 1, !dbg !648
  %49 = icmp eq i8 %48, 63, !dbg !665
  %50 = or i1 %47, %49, !dbg !665
  ret i1 %50, !dbg !665
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&7is_puncCv17610SaA1T4charFnE"(i8 %0) #0 !dbg !666 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !667, metadata !DIExpression()), !dbg !668
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !668
  %2 = icmp eq i8 %1, 33, !dbg !669
  %3 = load i8, ptr %arg.c, align 1, !dbg !668
  %4 = icmp eq i8 %3, 34, !dbg !670
  %5 = or i1 %2, %4, !dbg !670
  %6 = load i8, ptr %arg.c, align 1, !dbg !668
  %7 = icmp eq i8 %6, 35, !dbg !671
  %8 = or i1 %5, %7, !dbg !671
  %9 = load i8, ptr %arg.c, align 1, !dbg !668
  %10 = icmp eq i8 %9, 36, !dbg !672
  %11 = or i1 %8, %10, !dbg !672
  %12 = load i8, ptr %arg.c, align 1, !dbg !668
  %13 = icmp eq i8 %12, 37, !dbg !673
  %14 = or i1 %11, %13, !dbg !673
  %15 = load i8, ptr %arg.c, align 1, !dbg !668
  %16 = icmp eq i8 %15, 38, !dbg !674
  %17 = or i1 %14, %16, !dbg !674
  %18 = load i8, ptr %arg.c, align 1, !dbg !668
  %19 = icmp eq i8 %18, 39, !dbg !675
  %20 = or i1 %17, %19, !dbg !675
  %21 = load i8, ptr %arg.c, align 1, !dbg !668
  %22 = icmp eq i8 %21, 40, !dbg !676
  %23 = or i1 %20, %22, !dbg !676
  %24 = load i8, ptr %arg.c, align 1, !dbg !668
  %25 = icmp eq i8 %24, 41, !dbg !677
  %26 = or i1 %23, %25, !dbg !677
  %27 = load i8, ptr %arg.c, align 1, !dbg !668
  %28 = icmp eq i8 %27, 42, !dbg !678
  %29 = or i1 %26, %28, !dbg !678
  %30 = load i8, ptr %arg.c, align 1, !dbg !668
  %31 = icmp eq i8 %30, 43, !dbg !679
  %32 = or i1 %29, %31, !dbg !679
  %33 = load i8, ptr %arg.c, align 1, !dbg !668
  %34 = icmp eq i8 %33, 44, !dbg !680
  %35 = or i1 %32, %34, !dbg !680
  %36 = load i8, ptr %arg.c, align 1, !dbg !668
  %37 = icmp eq i8 %36, 45, !dbg !681
  %38 = or i1 %35, %37, !dbg !681
  %39 = load i8, ptr %arg.c, align 1, !dbg !668
  %40 = icmp eq i8 %39, 46, !dbg !682
  %41 = or i1 %38, %40, !dbg !682
  %42 = load i8, ptr %arg.c, align 1, !dbg !668
  %43 = icmp eq i8 %42, 47, !dbg !683
  %44 = or i1 %41, %43, !dbg !683
  %45 = load i8, ptr %arg.c, align 1, !dbg !668
  %46 = icmp eq i8 %45, 58, !dbg !684
  %47 = or i1 %44, %46, !dbg !684
  %48 = load i8, ptr %arg.c, align 1, !dbg !668
  %49 = icmp eq i8 %48, 59, !dbg !685
  %50 = or i1 %47, %49, !dbg !685
  %51 = load i8, ptr %arg.c, align 1, !dbg !668
  %52 = icmp eq i8 %51, 60, !dbg !686
  %53 = or i1 %50, %52, !dbg !686
  %54 = load i8, ptr %arg.c, align 1, !dbg !668
  %55 = icmp eq i8 %54, 61, !dbg !687
  %56 = or i1 %53, %55, !dbg !687
  %57 = load i8, ptr %arg.c, align 1, !dbg !668
  %58 = icmp eq i8 %57, 62, !dbg !688
  %59 = or i1 %56, %58, !dbg !688
  %60 = load i8, ptr %arg.c, align 1, !dbg !668
  %61 = icmp eq i8 %60, 63, !dbg !689
  %62 = or i1 %59, %61, !dbg !689
  %63 = load i8, ptr %arg.c, align 1, !dbg !668
  %64 = icmp eq i8 %63, 64, !dbg !690
  %65 = or i1 %62, %64, !dbg !690
  %66 = load i8, ptr %arg.c, align 1, !dbg !668
  %67 = icmp eq i8 %66, 91, !dbg !691
  %68 = or i1 %65, %67, !dbg !691
  %69 = load i8, ptr %arg.c, align 1, !dbg !668
  %70 = icmp eq i8 %69, 92, !dbg !692
  %71 = or i1 %68, %70, !dbg !692
  %72 = load i8, ptr %arg.c, align 1, !dbg !668
  %73 = icmp eq i8 %72, 93, !dbg !693
  %74 = or i1 %71, %73, !dbg !693
  %75 = load i8, ptr %arg.c, align 1, !dbg !668
  %76 = icmp eq i8 %75, 94, !dbg !694
  %77 = or i1 %74, %76, !dbg !694
  %78 = load i8, ptr %arg.c, align 1, !dbg !668
  %79 = icmp eq i8 %78, 95, !dbg !695
  %80 = or i1 %77, %79, !dbg !695
  %81 = load i8, ptr %arg.c, align 1, !dbg !668
  %82 = icmp eq i8 %81, 96, !dbg !696
  %83 = or i1 %80, %82, !dbg !696
  %84 = load i8, ptr %arg.c, align 1, !dbg !668
  %85 = icmp eq i8 %84, 123, !dbg !697
  %86 = or i1 %83, %85, !dbg !697
  %87 = load i8, ptr %arg.c, align 1, !dbg !668
  %88 = icmp eq i8 %87, 124, !dbg !698
  %89 = or i1 %86, %88, !dbg !698
  %90 = load i8, ptr %arg.c, align 1, !dbg !668
  %91 = icmp eq i8 %90, 125, !dbg !699
  %92 = or i1 %89, %91, !dbg !699
  %93 = load i8, ptr %arg.c, align 1, !dbg !668
  %94 = icmp eq i8 %93, 126, !dbg !700
  %95 = or i1 %92, %94, !dbg !700
  ret i1 %95, !dbg !700
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_printCv17607SaA1T4charFnE"(i8 %0) #0 !dbg !701 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !702, metadata !DIExpression()), !dbg !703
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !704
  %2 = call i1 @"_$SN@sn.Core.Char&10is_controlCv17604SaA1T4charFnE"(i8 %1) #0, !dbg !705
  %3 = icmp eq i1 %2, false, !dbg !705
  ret i1 %3, !dbg !705
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&10is_controlCv17604SaA1T4charFnE"(i8 %0) #0 !dbg !706 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !707, metadata !DIExpression()), !dbg !708
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !708
  %2 = icmp slt i8 %1, 32, !dbg !709
  %3 = load i8, ptr %arg.c, align 1, !dbg !708
  %4 = icmp eq i8 %3, 127, !dbg !710
  %5 = or i1 %2, %4, !dbg !710
  ret i1 %5, !dbg !710
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&12is_alpha_numCv17601SaA1T4charFnE"(i8 %0) #0 !dbg !711 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !712, metadata !DIExpression()), !dbg !713
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !714
  %2 = call i1 @"_$SN@sn.Core.Char&8is_alphaCv17598SaA1T4charFnE"(i8 %1) #0, !dbg !715
  %3 = load i8, ptr %arg.c, align 1, !dbg !716
  %4 = call i1 @"_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE"(i8 %3) #0, !dbg !717
  %5 = or i1 %2, %4, !dbg !717
  ret i1 %5, !dbg !717
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_alphaCv17598SaA1T4charFnE"(i8 %0) #0 !dbg !718 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !719, metadata !DIExpression()), !dbg !720
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !721
  %2 = call i1 @"_$SN@sn.Core.Char&8is_upperCv17583SaA1T4charFnE"(i8 %1) #0, !dbg !722
  %3 = load i8, ptr %arg.c, align 1, !dbg !723
  %4 = call i1 @"_$SN@sn.Core.Char&8is_lowerCv17586SaA1T4charFnE"(i8 %3) #0, !dbg !724
  %5 = or i1 %2, %4, !dbg !724
  ret i1 %5, !dbg !724
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&6is_octCv17595SaA1T4charFnE"(i8 %0) #0 !dbg !725 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !726, metadata !DIExpression()), !dbg !727
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !727
  %2 = icmp sge i8 %1, 48, !dbg !728
  %3 = load i8, ptr %arg.c, align 1, !dbg !727
  %4 = icmp sle i8 %3, 55, !dbg !729
  %5 = and i1 %2, %4, !dbg !729
  ret i1 %5, !dbg !729
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&6is_hexCv17592SaA1T4charFnE"(i8 %0) #0 !dbg !730 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !731, metadata !DIExpression()), !dbg !732
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !733
  %2 = call i1 @"_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE"(i8 %1) #0, !dbg !734
  %3 = load i8, ptr %arg.c, align 1, !dbg !732
  %4 = icmp sge i8 %3, 97, !dbg !735
  %5 = load i8, ptr %arg.c, align 1, !dbg !732
  %6 = icmp sle i8 %5, 102, !dbg !736
  %7 = and i1 %4, %6, !dbg !736
  %8 = or i1 %2, %7, !dbg !736
  %9 = load i8, ptr %arg.c, align 1, !dbg !732
  %10 = icmp sge i8 %9, 65, !dbg !737
  %11 = load i8, ptr %arg.c, align 1, !dbg !732
  %12 = icmp sle i8 %11, 70, !dbg !738
  %13 = and i1 %10, %12, !dbg !738
  %14 = or i1 %8, %13, !dbg !738
  ret i1 %14, !dbg !738
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE"(i8 %0) #0 !dbg !739 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !740, metadata !DIExpression()), !dbg !741
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !741
  %2 = icmp sge i8 %1, 48, !dbg !742
  %3 = load i8, ptr %arg.c, align 1, !dbg !741
  %4 = icmp sle i8 %3, 57, !dbg !743
  %5 = and i1 %2, %4, !dbg !743
  ret i1 %5, !dbg !743
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_lowerCv17586SaA1T4charFnE"(i8 %0) #0 !dbg !744 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !745, metadata !DIExpression()), !dbg !746
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !746
  %2 = icmp sge i8 %1, 97, !dbg !747
  %3 = load i8, ptr %arg.c, align 1, !dbg !746
  %4 = icmp sle i8 %3, 122, !dbg !748
  %5 = and i1 %2, %4, !dbg !748
  ret i1 %5, !dbg !748
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_upperCv17583SaA1T4charFnE"(i8 %0) #0 !dbg !749 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !750, metadata !DIExpression()), !dbg !751
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !751
  %2 = icmp sge i8 %1, 65, !dbg !752
  %3 = load i8, ptr %arg.c, align 1, !dbg !751
  %4 = icmp sle i8 %3, 90, !dbg !753
  %5 = and i1 %2, %4, !dbg !753
  ret i1 %5, !dbg !753
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_spaceCv17580SaA1T4charFnE"(i8 %0) #0 !dbg !754 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !755, metadata !DIExpression()), !dbg !756
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !756
  %2 = icmp eq i8 %1, 32, !dbg !757
  %3 = load i8, ptr %arg.c, align 1, !dbg !756
  %4 = icmp eq i8 %3, 9, !dbg !758
  %5 = or i1 %2, %4, !dbg !758
  %6 = load i8, ptr %arg.c, align 1, !dbg !756
  %7 = icmp eq i8 %6, 10, !dbg !759
  %8 = or i1 %5, %7, !dbg !759
  %9 = load i8, ptr %arg.c, align 1, !dbg !756
  %10 = icmp eq i8 %9, 13, !dbg !760
  %11 = or i1 %8, %10, !dbg !760
  ret i1 %11, !dbg !760
}

define internal void @"_$SN&19TypeInsideClassTestCv17666ClsE&4#NwCCv17670SaA1_$SN&19TypeInsideClassTestCv17666ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !761 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !767, metadata !DIExpression()), !dbg !768
  br label %body

body:                                             ; preds = %entry
  ret void
}

define internal i32 @"_$SN&11VirtualTestCv17647ClsE&4testCv17656SaA1_$SN&11VirtualTestCv17647ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !769 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !774, metadata !DIExpression()), !dbg !775
  br label %body

body:                                             ; preds = %entry
  ret i32 1, !dbg !776
}

define internal void @"_$SN&11VirtualTestCv17647ClsE&4#NwCCv17651SaA1_$SN&11VirtualTestCv17647ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !777 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !780, metadata !DIExpression()), !dbg !781
  br label %body

body:                                             ; preds = %entry
  ret void
}

define internal void @"_$SN&15ValueAccessTestCv17633ClsE&4#NwCCv17636SaA1_$SN&15ValueAccessTestCv17633ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !782 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !787, metadata !DIExpression()), !dbg !788
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !788
  %2 = getelementptr inbounds %"class._$SN&15ValueAccessTestCv17633ClsE", ptr %1, i32 0, i32 0, !dbg !788
  %3 = load i32, ptr %2, align 4, !dbg !788
  store i32 0, ptr %2, align 4, !dbg !789
  ret void
}

define internal void @"_$SN&4TestCv17619ClsE&4#NwCCv17622SaA1_$SN&4TestCv17619ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) !dbg !790 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !795, metadata !DIExpression()), !dbg !796
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 !dbg !797 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !799, metadata !DIExpression()), !dbg !800
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !801
  %2 = call i32 @"_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.20) #0, !dbg !802
  ret i32 %2, !dbg !802
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 !dbg !803 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !806, metadata !DIExpression()), !dbg !807
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !808, metadata !DIExpression()), !dbg !807
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !809, metadata !DIExpression()), !dbg !810
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !811
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !811
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #0, !dbg !812
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !812
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !812
  %6 = call ptr @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #0, !dbg !812
  store ptr %6, ptr %var.m, align 8, !dbg !812
  %7 = load ptr, ptr %var.m, align 8, !dbg !813
  %8 = load ptr, ptr %arg.end, align 8, !dbg !814
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.21, ptr %7, ptr %8), !dbg !815
  ret i32 %9, !dbg !815
}

define internal void @"_$SN@sn.Core.System&7printlnCv17684SaFnE"() !dbg !816 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = call i32 @putchar(i8 10), !dbg !819
  ret void
}

define internal void @"_$SN@sn.Core.System&4exitCv17681SaA1T3i32FnE"(i32 %0) !dbg !820 {
entry:
  %arg.exitCode = alloca i32, align 4
  store i32 %0, ptr %arg.exitCode, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.exitCode, metadata !823, metadata !DIExpression()), !dbg !824
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.exitCode, align 4, !dbg !825
  call void @exit(i32 %1), !dbg !826
  ret void
}

define i32 @main() !dbg !827 {
entry:
  %var.a = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.a, metadata !828, metadata !DIExpression()), !dbg !829
  br label %body

body:                                             ; preds = %entry
  %0 = call ptr @sn.alloca(i32 32), !dbg !830
  %1 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %0, i32 0, i32 0, !dbg !830
  store ptr @"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, align 8, !dbg !830
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !830
  store ptr %0, ptr %var.a, align 8, !dbg !830
  %2 = load ptr, ptr %var.a, align 8, !dbg !829
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 1), !dbg !831
  %3 = load ptr, ptr %var.a, align 8, !dbg !829
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, i32 2), !dbg !832
  %4 = load ptr, ptr %var.a, align 8, !dbg !829
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, i32 3), !dbg !833
  %5 = load ptr, ptr %var.a, align 8, !dbg !834
  %6 = call i32 @"_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %5) #0, !dbg !835
  ret i32 0
}

; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE" = type { ptr }
%"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE" = type { ptr, ptr }
%"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE" = type { ptr }
%"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" = type { ptr, i32, i32, i32 }
%"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" = type { i1, i32 }
%"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE" = type { ptr, i32, i32, i32, ptr }
%"struct._$SN&14UniversalArrayCv17533ClsE" = type { ptr }
%"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE" = type { ptr, i32 }
%"class._$SN&8IterableCv17018ClsGStA1T4charClsE" = type { ptr, i32 }
%"class._$SN&4IterCv17019ClsGStA1T4charClsE" = type { i1, i8 }
%"class._$SN&9ExceptionCv17046ClsE" = type { ptr }
%"class._$SN&15ValueAccessTestCv17633ClsE" = type { i32 }

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE" = global %"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE" { ptr @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE" }
@"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE" = global %"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE" { ptr @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", ptr @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE" }
@.str.2 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.3 = private unnamed_addr constant [21 x i8] c"Index out of bounds.\00", align 1
@.str.4 = private unnamed_addr constant [25 x i8] c"Invalid iterator access!\00", align 1
@.str.5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.9 = private unnamed_addr constant [25 x i8] c"Invalid iterator access!\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.12 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.13 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.20 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.21 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE" = global %"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE" { ptr @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE" }

declare ptr @strcat(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64))

declare ptr @strcpy(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64))

declare i1 @strcmp(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64))

declare i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64))

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17519SaA1T3i32A2T4char.rA3T3i64FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i64 %2) #0 personality ptr @sn.eh.personality !dbg !5 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !14, metadata !DIExpression()), !dbg !15
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !16, metadata !DIExpression()), !dbg !15
  %arg.value = alloca i64, align 8
  store i64 %2, ptr %arg.value, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !17, metadata !DIExpression()), !dbg !15
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !18, metadata !DIExpression()), !dbg !19
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !20
  %4 = call ptr @malloc(i32 %3), !dbg !21
  store ptr %4, ptr %var.buffer, align 8, !dbg !21
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !22
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !23
  %7 = load ptr, ptr %arg.format, align 8, !dbg !24
  %8 = load i64, ptr %arg.value, align 8, !dbg !25
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i64 %8), !dbg !26
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !27
  ret ptr %10, !dbg !27
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i32 %2) #0 personality ptr @sn.eh.personality !dbg !28 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !31, metadata !DIExpression()), !dbg !32
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !33, metadata !DIExpression()), !dbg !32
  %arg.value = alloca i32, align 4
  store i32 %2, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !34, metadata !DIExpression()), !dbg !32
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !35, metadata !DIExpression()), !dbg !36
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !37
  %4 = call ptr @malloc(i32 %3), !dbg !38
  store ptr %4, ptr %var.buffer, align 8, !dbg !38
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !39
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !40
  %7 = load ptr, ptr %arg.format, align 8, !dbg !41
  %8 = load i32, ptr %arg.value, align 4, !dbg !42
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i32 %8), !dbg !43
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !44
  ret ptr %10, !dbg !44
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17441SaA1T3i32A2T4char.rA3T3i16FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i16 %2) #0 personality ptr @sn.eh.personality !dbg !45 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !49, metadata !DIExpression()), !dbg !50
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !51, metadata !DIExpression()), !dbg !50
  %arg.value = alloca i16, align 2
  store i16 %2, ptr %arg.value, align 2
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !52, metadata !DIExpression()), !dbg !50
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !53, metadata !DIExpression()), !dbg !54
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !55
  %4 = call ptr @malloc(i32 %3), !dbg !56
  store ptr %4, ptr %var.buffer, align 8, !dbg !56
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !57
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !58
  %7 = load ptr, ptr %arg.format, align 8, !dbg !59
  %8 = load i16, ptr %arg.value, align 2, !dbg !60
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i16 %8), !dbg !61
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !62
  ret ptr %10, !dbg !62
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17402SaA1T3i32A2T4char.rA3T2i8FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i8 %2) #0 personality ptr @sn.eh.personality !dbg !63 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !67, metadata !DIExpression()), !dbg !68
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !69, metadata !DIExpression()), !dbg !68
  %arg.value = alloca i8, align 1
  store i8 %2, ptr %arg.value, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !70, metadata !DIExpression()), !dbg !68
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !71, metadata !DIExpression()), !dbg !72
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !73
  %4 = call ptr @malloc(i32 %3), !dbg !74
  store ptr %4, ptr %var.buffer, align 8, !dbg !74
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !75
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !76
  %7 = load ptr, ptr %arg.format, align 8, !dbg !77
  %8 = load i8, ptr %arg.value, align 1, !dbg !78
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i8 %8), !dbg !79
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !80
  ret ptr %10, !dbg !80
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare ptr @malloc(i32)

declare i32 @snprintf(ptr noundef nonnull align 8 dereferenceable(64), i32, ptr noundef nonnull align 8 dereferenceable(64), ...)

declare i32 @sn.eh.personality(i32, i32, i64, ptr, ptr)

declare void @memcpy(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64), i32)

declare void @memcpy.1(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64), i32)

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE"() #0 personality ptr @sn.eh.personality !dbg !81 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !84
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE"() #0 personality ptr @sn.eh.personality !dbg !85 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !86
}

; Function Attrs: alwaysinline
define internal i8 @"_$SN@sn.Core.CLib&8null_ptrCv17039SaFnE"() #0 personality ptr @sn.eh.personality !dbg !87 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i8 0, !dbg !90
}

; Function Attrs: alwaysinline
define internal i8 @"_$SN@sn.Core.CLib&8null_ptrCv17031SaFnE"() #0 personality ptr @sn.eh.personality !dbg !91 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i8 0, !dbg !92
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.CLib&7is_nullCv16985SaA1T4cobjFnE"(ptr %0) #0 personality ptr @sn.eh.personality !dbg !93 {
entry:
  %arg.ptr = alloca ptr, align 8
  store ptr %0, ptr %arg.ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.ptr, metadata !98, metadata !DIExpression()), !dbg !99
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.ptr, align 8, !dbg !99
  %2 = call ptr @"_$SN@sn.Core.CLib&8null_ptrCv16988SaFnE"() #0, !dbg !100
  %3 = icmp eq ptr %1, %2, !dbg !100
  ret i1 %3, !dbg !100
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib&8null_ptrCv16988SaFnE"() #0 personality ptr @sn.eh.personality !dbg !101 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret ptr null, !dbg !104
}

declare void @exit(i32)

declare i32 @printf(ptr noundef nonnull align 8 dereferenceable(64), ...)

declare i8 @getchar()

declare i32 @putchar(i8)

declare i32 @puts(ptr noundef nonnull align 8 dereferenceable(64))

declare void @free(ptr)

declare ptr @realloc(ptr, i32)

declare ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64), i32)

declare void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64), i32, ptr)

declare ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64), i32)

; Function Attrs: noinline
declare ptr @sn.ua.alloc(i32) #2

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !105 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %0, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !114, metadata !DIExpression()), !dbg !115
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.buffer, align 8, !dbg !115
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !115
  %3 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !116
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %2, align 8, !dbg !116
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !116
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !116
}

define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !117 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !118, metadata !DIExpression()), !dbg !119
  %var.result = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.result, metadata !120, metadata !DIExpression()), !dbg !122
  %"var.$iter" = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !123, metadata !DIExpression()), !dbg !125
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !126, metadata !DIExpression()), !dbg !125
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !128, metadata !DIExpression()), !dbg !125
  br label %body

body:                                             ; preds = %entry
  %1 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !129
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !129
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !129
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str), !dbg !129
  %3 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, align 8, !dbg !129
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %var.result, align 8, !dbg !129
  %4 = load ptr, ptr %arg.self, align 8, !dbg !119
  %5 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 3, !dbg !119
  %6 = load i32, ptr %5, align 4, !dbg !119
  %7 = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8, !dbg !125
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 0, !dbg !125
  store ptr @"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %8, align 8, !dbg !125
  call void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %7, i32 0, i32 %6), !dbg !125
  %9 = load %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, align 8, !dbg !125
  store %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" %9, ptr %"var.$iter", align 8, !dbg !125
  %10 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !125
  %11 = load ptr, ptr %"var.$iter", align 8, !dbg !125
  %12 = getelementptr inbounds ptr, ptr %11, i32 1, !dbg !125
  %13 = load ptr, ptr %12, align 8, !dbg !125
  %14 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %13(ptr %"var.$iter"), !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %14, ptr %10, align 4, !dbg !125
  %15 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %10, align 4, !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %15, ptr %"var.$iter_value", align 4, !dbg !125
  br label %16, !dbg !125

16:                                               ; preds = %45, %body
  %17 = call i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !125
  br i1 %17, label %18, label %35, !dbg !125

18:                                               ; preds = %16
  %19 = call i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !125
  store i32 %19, ptr %var.i, align 4, !dbg !125
  %20 = load ptr, ptr %arg.self, align 8, !dbg !119
  %21 = load i32, ptr %var.i, align 4, !dbg !130
  %22 = call i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %21), !dbg !131
  %23 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !131
  %24 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE"(i32 %22) #0, !dbg !132
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %24, ptr %23, align 8, !dbg !132
  %25 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %23, align 8, !dbg !132
  %26 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !132
  %27 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.result, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %25) #0, !dbg !133
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %27, ptr %26, align 8, !dbg !133
  %28 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %26, align 8, !dbg !133
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %28, ptr %var.result, align 8, !dbg !133
  %29 = load i32, ptr %var.i, align 4, !dbg !125
  %30 = load ptr, ptr %arg.self, align 8, !dbg !119
  %31 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %30, i32 0, i32 3, !dbg !119
  %32 = load i32, ptr %31, align 4, !dbg !119
  %33 = sub i32 %32, 1, !dbg !134
  %34 = icmp ne i32 %29, %33, !dbg !134
  br i1 %34, label %37, label %44, !dbg !134

35:                                               ; preds = %16
  %36 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %var.result, align 8, !dbg !135
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %36, !dbg !135

37:                                               ; preds = %18
  %38 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !136
  %39 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %38, i32 0, i32 0, !dbg !136
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %39, align 8, !dbg !136
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %38, ptr noundef nonnull align 8 dereferenceable(64) @.str.2), !dbg !136
  %40 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %38, align 8, !dbg !136
  %41 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !136
  %42 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.result, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %40) #0, !dbg !137
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %42, ptr %41, align 8, !dbg !137
  %43 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %41, align 8, !dbg !137
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %43, ptr %var.result, align 8, !dbg !137
  br label %45, !dbg !137

44:                                               ; preds = %18
  br label %45, !dbg !137

45:                                               ; preds = %44, %37
  %46 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !125
  %47 = load ptr, ptr %"var.$iter", align 8, !dbg !125
  %48 = getelementptr inbounds ptr, ptr %47, i32 1, !dbg !125
  %49 = load ptr, ptr %48, align 8, !dbg !125
  %50 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %49(ptr %"var.$iter"), !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %50, ptr %46, align 4, !dbg !125
  %.load = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %46, align 4, !dbg !125
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %.load, ptr %"var.$iter_value", align 4, !dbg !125
  br label %16, !dbg !125
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1) #0 personality ptr @sn.eh.personality !dbg !138 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !142, metadata !DIExpression()), !dbg !143
  %arg.other = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !144, metadata !DIExpression()), !dbg !143
  %var.len1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len1, metadata !145, metadata !DIExpression()), !dbg !146
  %var.len2 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len2, metadata !147, metadata !DIExpression()), !dbg !148
  %var.sum = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.sum, metadata !149, metadata !DIExpression()), !dbg !150
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !151, metadata !DIExpression()), !dbg !152
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !143
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 3, !dbg !143
  %4 = load i32, ptr %3, align 4, !dbg !143
  store i32 %4, ptr %var.len1, align 4, !dbg !143
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !143
  %6 = load i32, ptr %5, align 4, !dbg !143
  store i32 %6, ptr %var.len2, align 4, !dbg !143
  %7 = load i32, ptr %var.len1, align 4, !dbg !146
  %8 = load i32, ptr %var.len2, align 4, !dbg !153
  %9 = add i32 %7, %8, !dbg !153
  store i32 %9, ptr %var.sum, align 4, !dbg !153
  %10 = load i32, ptr %var.sum, align 4, !dbg !154
  %11 = call ptr @malloc(i32 %10), !dbg !155
  store ptr %11, ptr %var.buffer, align 8, !dbg !155
  %12 = load ptr, ptr %var.buffer, align 8, !dbg !156
  %13 = load ptr, ptr %arg.self, align 8, !dbg !143
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %13, i32 0, i32 4, !dbg !143
  %15 = load ptr, ptr %14, align 8, !dbg !143
  %16 = load i32, ptr %var.len1, align 4, !dbg !157
  call void @memcpy.1(ptr noundef nonnull align 8 dereferenceable(64) %12, ptr noundef nonnull align 8 dereferenceable(64) %15, i32 %16), !dbg !158
  %17 = load ptr, ptr %var.buffer, align 8, !dbg !152
  %18 = load i32, ptr %var.len1, align 4, !dbg !159
  %19 = call ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18) #0, !dbg !160
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !143
  %21 = load ptr, ptr %20, align 8, !dbg !143
  %22 = load i32, ptr %var.len2, align 4, !dbg !161
  call void @memcpy(ptr noundef nonnull align 8 dereferenceable(64) %19, ptr noundef nonnull align 8 dereferenceable(64) %21, i32 %22), !dbg !162
  %23 = load ptr, ptr %var.buffer, align 8, !dbg !163
  %24 = load i32, ptr %var.sum, align 4, !dbg !164
  %25 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !165
  %26 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %25, i32 0, i32 0, !dbg !165
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %26, align 8, !dbg !165
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %25, ptr noundef nonnull align 8 dereferenceable(64) %23, i32 %24), !dbg !165
  %27 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %25, align 8, !dbg !165
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %27, !dbg !165
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE"(i32 %0) #0 personality ptr @sn.eh.personality !dbg !166 {
entry:
  %arg.buffer = alloca i32, align 4
  store i32 %0, ptr %arg.buffer, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !169, metadata !DIExpression()), !dbg !170
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.buffer, align 4, !dbg !170
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !170
  %3 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %arg.buffer) #0, !dbg !171
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %2, align 8, !dbg !171
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !171
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !171
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6insertCv17751SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) personality ptr @sn.eh.personality !dbg !172 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !175, metadata !DIExpression()), !dbg !176
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !177, metadata !DIExpression()), !dbg !176
  %arg.value = alloca i32, align 4
  store i32 %2, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !178, metadata !DIExpression()), !dbg !176
  %var.cur = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.cur, metadata !179, metadata !DIExpression()), !dbg !180
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.index, align 4, !dbg !176
  %4 = load ptr, ptr %arg.self, align 8, !dbg !176
  %5 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 3, !dbg !176
  %6 = load i32, ptr %5, align 4, !dbg !176
  %7 = icmp sge i32 %3, %6, !dbg !176
  br i1 %7, label %8, label %11, !dbg !176

8:                                                ; preds = %body
  %9 = load ptr, ptr %arg.self, align 8, !dbg !176
  %10 = load i32, ptr %arg.value, align 4, !dbg !181
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %9, i32 %10), !dbg !182
  ret void, !dbg !183

11:                                               ; preds = %body
  br label %12, !dbg !183

12:                                               ; preds = %11
  %13 = load ptr, ptr %arg.self, align 8, !dbg !176
  %14 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 4, !dbg !176
  %15 = load ptr, ptr %14, align 8, !dbg !176
  %16 = load i32, ptr %arg.index, align 4, !dbg !184
  %17 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %15, i32 %16), !dbg !185
  %18 = ptrtoint ptr %17 to i32, !dbg !185
  store i32 %18, ptr %var.cur, align 4, !dbg !185
  %19 = load ptr, ptr %arg.self, align 8, !dbg !176
  %20 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %19, i32 0, i32 4, !dbg !176
  %21 = load ptr, ptr %20, align 8, !dbg !176
  %22 = load i32, ptr %arg.index, align 4, !dbg !186
  %23 = load i32, ptr %arg.value, align 4, !dbg !187
  %24 = inttoptr i32 %23 to ptr, !dbg !187
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %21, i32 %22, ptr %24), !dbg !188
  %25 = load ptr, ptr %arg.self, align 8, !dbg !176
  %26 = load i32, ptr %arg.index, align 4, !dbg !176
  %27 = add i32 %26, 1, !dbg !189
  %28 = load i32, ptr %var.cur, align 4, !dbg !190
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6insertCv17751SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %25, i32 %27, i32 %28), !dbg !191
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#IdxCv17745SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !192 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !195, metadata !DIExpression()), !dbg !196
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !197, metadata !DIExpression()), !dbg !196
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !196
  %3 = load i32, ptr %arg.index, align 4, !dbg !198
  %4 = call i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3), !dbg !199
  ret i32 %4, !dbg !199
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4dataCv17740SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !200 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !204, metadata !DIExpression()), !dbg !205
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !205
  %2 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 4, !dbg !205
  %3 = load ptr, ptr %2, align 8, !dbg !205
  %4 = getelementptr inbounds %"struct._$SN&14UniversalArrayCv17533ClsE", ptr %3, i32 0, i32 0, !dbg !205
  %5 = load ptr, ptr %4, align 8, !dbg !205
  %6 = load ptr, ptr %5, align 8, !dbg !205
  ret ptr %6, !dbg !205
}

define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) personality ptr @sn.eh.personality !dbg !206 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !207, metadata !DIExpression()), !dbg !208
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !209, metadata !DIExpression()), !dbg !208
  br label %body

body:                                             ; preds = %entry
  %2 = load i32, ptr %arg.index, align 4, !dbg !208
  %3 = icmp slt i32 %2, 0, !dbg !210
  %4 = load i32, ptr %arg.index, align 4, !dbg !208
  %5 = load ptr, ptr %arg.self, align 8, !dbg !208
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 3, !dbg !208
  %7 = load i32, ptr %6, align 4, !dbg !208
  %8 = icmp sge i32 %4, %7, !dbg !208
  %9 = or i1 %3, %8, !dbg !208
  br i1 %9, label %10, label %13, !dbg !208

10:                                               ; preds = %body
  %11 = call ptr @sn.alloca(i32 8), !dbg !211
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, ptr noundef nonnull align 8 dereferenceable(64) @.str.3), !dbg !211
  %12 = call ptr @sn.eh.create(ptr %11, i32 1000), !dbg !211
  call void @sn.eh.throw(ptr %12), !dbg !211
  br label %14, !dbg !211

13:                                               ; preds = %body
  br label %14, !dbg !211

14:                                               ; preds = %13, %10
  %15 = load ptr, ptr %arg.self, align 8, !dbg !208
  %16 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %15, i32 0, i32 4, !dbg !208
  %17 = load ptr, ptr %16, align 8, !dbg !208
  %18 = load i32, ptr %arg.index, align 4, !dbg !212
  %19 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18), !dbg !213
  %20 = ptrtoint ptr %19 to i32, !dbg !213
  ret i32 %20, !dbg !213
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17722SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) personality ptr @sn.eh.personality !dbg !214 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !217, metadata !DIExpression()), !dbg !218
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !219, metadata !DIExpression()), !dbg !218
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !218
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 2, !dbg !218
  %4 = load i32, ptr %3, align 4, !dbg !218
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !220
  store i32 %5, ptr %3, align 4, !dbg !220
  %6 = load ptr, ptr %arg.self, align 8, !dbg !218
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 4, !dbg !218
  %8 = load ptr, ptr %7, align 8, !dbg !218
  %9 = load ptr, ptr %arg.self, align 8, !dbg !218
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 4, !dbg !218
  %11 = load ptr, ptr %10, align 8, !dbg !218
  %12 = load ptr, ptr %arg.self, align 8, !dbg !218
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !218
  %14 = load i32, ptr %13, align 4, !dbg !218
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !221
  store ptr %15, ptr %7, align 8, !dbg !221
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4sizeCv17718SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !222 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !225, metadata !DIExpression()), !dbg !226
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !226
  %2 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !226
  %3 = load i32, ptr %2, align 4, !dbg !226
  ret i32 %3, !dbg !226
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) personality ptr @sn.eh.personality !dbg !227 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !228, metadata !DIExpression()), !dbg !229
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !230, metadata !DIExpression()), !dbg !229
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !229
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 3, !dbg !229
  %4 = load i32, ptr %3, align 4, !dbg !229
  %5 = add i32 %4, 1, !dbg !231
  %6 = load ptr, ptr %arg.self, align 8, !dbg !229
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 2, !dbg !229
  %8 = load i32, ptr %7, align 4, !dbg !229
  %9 = icmp sge i32 %5, %8, !dbg !229
  br i1 %9, label %10, label %16, !dbg !229

10:                                               ; preds = %body
  %11 = load ptr, ptr %arg.self, align 8, !dbg !229
  %12 = load ptr, ptr %arg.self, align 8, !dbg !229
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !229
  %14 = load i32, ptr %13, align 4, !dbg !229
  %15 = add i32 %14, 10, !dbg !232
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %15), !dbg !233
  br label %17, !dbg !233

16:                                               ; preds = %body
  br label %17, !dbg !233

17:                                               ; preds = %16, %10
  %18 = load ptr, ptr %arg.self, align 8, !dbg !229
  %19 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 4, !dbg !229
  %20 = load ptr, ptr %19, align 8, !dbg !229
  %21 = load ptr, ptr %arg.self, align 8, !dbg !229
  %22 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 3, !dbg !229
  %23 = load i32, ptr %22, align 4, !dbg !229
  %24 = load i32, ptr %arg.value, align 4, !dbg !234
  %25 = inttoptr i32 %24 to ptr, !dbg !234
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %23, ptr %25), !dbg !235
  %26 = load ptr, ptr %arg.self, align 8, !dbg !229
  %27 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %26, i32 0, i32 3, !dbg !229
  %28 = load i32, ptr %27, align 4, !dbg !229
  %29 = load ptr, ptr %arg.self, align 8, !dbg !229
  %30 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %29, i32 0, i32 3, !dbg !229
  %31 = load i32, ptr %30, align 4, !dbg !229
  %32 = add i32 %31, 1, !dbg !236
  store i32 %32, ptr %27, align 4, !dbg !236
  ret void
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) personality ptr @sn.eh.personality !dbg !237 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !238, metadata !DIExpression()), !dbg !239
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !240, metadata !DIExpression()), !dbg !239
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !239
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 2, !dbg !239
  %4 = load i32, ptr %3, align 4, !dbg !239
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !241
  store i32 %5, ptr %3, align 4, !dbg !241
  %6 = load ptr, ptr %arg.self, align 8, !dbg !239
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 4, !dbg !239
  %8 = load ptr, ptr %7, align 8, !dbg !239
  %9 = load ptr, ptr %arg.self, align 8, !dbg !239
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 4, !dbg !239
  %11 = load ptr, ptr %10, align 8, !dbg !239
  %12 = load ptr, ptr %arg.self, align 8, !dbg !239
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !239
  %14 = load i32, ptr %13, align 4, !dbg !239
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !242
  store ptr %15, ptr %7, align 8, !dbg !242
  ret void
}

define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !243 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !246, metadata !DIExpression()), !dbg !247
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !247
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !247
  %2 = load ptr, ptr %arg.self, align 8, !dbg !247
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 1, !dbg !247
  %4 = load i32, ptr %3, align 4, !dbg !247
  store i32 0, ptr %3, align 4, !dbg !248
  %5 = load ptr, ptr %arg.self, align 8, !dbg !247
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 2, !dbg !247
  %7 = load i32, ptr %6, align 4, !dbg !247
  store i32 10, ptr %6, align 4, !dbg !249
  %8 = load ptr, ptr %arg.self, align 8, !dbg !247
  %9 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %8, i32 0, i32 3, !dbg !247
  %10 = load i32, ptr %9, align 4, !dbg !247
  store i32 0, ptr %9, align 4, !dbg !250
  %11 = load ptr, ptr %arg.self, align 8, !dbg !247
  %12 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %11, i32 0, i32 4, !dbg !247
  %13 = load ptr, ptr %12, align 8, !dbg !247
  %14 = load ptr, ptr %arg.self, align 8, !dbg !247
  %15 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 2, !dbg !247
  %16 = load i32, ptr %15, align 4, !dbg !247
  %17 = call ptr @sn.ua.alloc(i32 %16) #2, !dbg !251
  store ptr %17, ptr %12, align 8, !dbg !251
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17511SaA1T3i64A2T4char.rFnE"(i64 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !252 {
entry:
  %arg.num = alloca i64, align 8
  store i64 %0, ptr %arg.num, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !255, metadata !DIExpression()), !dbg !256
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !257, metadata !DIExpression()), !dbg !256
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !258, metadata !DIExpression()), !dbg !259
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !260
  %3 = load i64, ptr %arg.num, align 8, !dbg !261
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17519SaA1T3i32A2T4char.rA3T3i64FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i64 %3) #0, !dbg !262
  store ptr %4, ptr %var.buffer, align 8, !dbg !262
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !263
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !264
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !264
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !264
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !264
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !264
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !264
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !265 {
entry:
  %arg.num = alloca i32, align 4
  store i32 %0, ptr %arg.num, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !268, metadata !DIExpression()), !dbg !269
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !270, metadata !DIExpression()), !dbg !269
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !271, metadata !DIExpression()), !dbg !272
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !273
  %3 = load i32, ptr %arg.num, align 4, !dbg !274
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3) #0, !dbg !275
  store ptr %4, ptr %var.buffer, align 8, !dbg !275
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !276
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !277
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !277
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !277
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !277
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !277
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !277
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17433SaA1T3i16A2T4char.rFnE"(i16 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !278 {
entry:
  %arg.num = alloca i16, align 2
  store i16 %0, ptr %arg.num, align 2
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !281, metadata !DIExpression()), !dbg !282
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !283, metadata !DIExpression()), !dbg !282
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !284, metadata !DIExpression()), !dbg !285
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !286
  %3 = load i16, ptr %arg.num, align 2, !dbg !287
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17441SaA1T3i32A2T4char.rA3T3i16FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i16 %3) #0, !dbg !288
  store ptr %4, ptr %var.buffer, align 8, !dbg !288
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !289
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !290
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !290
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !290
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !290
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !290
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !290
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17394SaA1T2i8A2T4char.rFnE"(i8 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !291 {
entry:
  %arg.num = alloca i8, align 1
  store i8 %0, ptr %arg.num, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !294, metadata !DIExpression()), !dbg !295
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !296, metadata !DIExpression()), !dbg !295
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !297, metadata !DIExpression()), !dbg !298
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !299
  %3 = load i8, ptr %arg.num, align 1, !dbg !300
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17402SaA1T3i32A2T4char.rA3T2i8FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i8 %3) #0, !dbg !301
  store ptr %4, ptr %var.buffer, align 8, !dbg !301
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !302
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !303
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !303
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !303
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !303
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !303
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !303
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&9to_stringCv17327SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !304 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !307, metadata !DIExpression()), !dbg !308
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !309
  %2 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, align 8, !dbg !309
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %2, !dbg !309
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5#DbEqCv17180SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1) #0 personality ptr @sn.eh.personality !dbg !310 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !313, metadata !DIExpression()), !dbg !314
  %arg.other = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !315, metadata !DIExpression()), !dbg !314
  %"var.$iter" = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !316, metadata !DIExpression()), !dbg !317
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !318, metadata !DIExpression()), !dbg !317
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !319, metadata !DIExpression()), !dbg !317
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !314
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 3, !dbg !314
  %4 = load i32, ptr %3, align 4, !dbg !314
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !314
  %6 = load i32, ptr %5, align 4, !dbg !314
  %7 = icmp ne i32 %4, %6, !dbg !314
  br i1 %7, label %8, label %9, !dbg !314

8:                                                ; preds = %body
  ret i1 false, !dbg !320

9:                                                ; preds = %body
  br label %10, !dbg !320

10:                                               ; preds = %9
  %11 = load ptr, ptr %arg.self, align 8, !dbg !314
  %12 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %11, i32 0, i32 3, !dbg !314
  %13 = load i32, ptr %12, align 4, !dbg !314
  %14 = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8, !dbg !317
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 0, !dbg !317
  store ptr @"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %15, align 8, !dbg !317
  call void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %14, i32 0, i32 %13), !dbg !317
  %16 = load %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, align 8, !dbg !317
  store %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" %16, ptr %"var.$iter", align 8, !dbg !317
  %17 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !317
  %18 = load ptr, ptr %"var.$iter", align 8, !dbg !317
  %19 = getelementptr inbounds ptr, ptr %18, i32 1, !dbg !317
  %20 = load ptr, ptr %19, align 8, !dbg !317
  %21 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %20(ptr %"var.$iter"), !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %21, ptr %17, align 4, !dbg !317
  %22 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %17, align 4, !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %22, ptr %"var.$iter_value", align 4, !dbg !317
  br label %23, !dbg !317

23:                                               ; preds = %40, %10
  %24 = call i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !317
  br i1 %24, label %25, label %37, !dbg !317

25:                                               ; preds = %23
  %26 = call i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #0, !dbg !317
  store i32 %26, ptr %var.i, align 4, !dbg !317
  %27 = load ptr, ptr %arg.self, align 8, !dbg !314
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 4, !dbg !314
  %29 = load ptr, ptr %28, align 8, !dbg !314
  %30 = load i32, ptr %var.i, align 4, !dbg !321
  %31 = call ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %29, i32 %30) #0, !dbg !321
  %32 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !314
  %33 = load ptr, ptr %32, align 8, !dbg !314
  %34 = load i32, ptr %var.i, align 4, !dbg !322
  %35 = call ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %33, i32 %34) #0, !dbg !322
  %36 = icmp ne ptr %31, %35, !dbg !322
  br i1 %36, label %38, label %39, !dbg !322

37:                                               ; preds = %23
  ret i1 true, !dbg !323

38:                                               ; preds = %25
  ret i1 false, !dbg !324

39:                                               ; preds = %25
  br label %40, !dbg !324

40:                                               ; preds = %39
  %41 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !317
  %42 = load ptr, ptr %"var.$iter", align 8, !dbg !317
  %43 = getelementptr inbounds ptr, ptr %42, i32 1, !dbg !317
  %44 = load ptr, ptr %43, align 8, !dbg !317
  %45 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %44(ptr %"var.$iter"), !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %45, ptr %41, align 4, !dbg !317
  %.load = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %41, align 4, !dbg !317
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %.load, ptr %"var.$iter_value", align 4, !dbg !317
  br label %23, !dbg !317
}

; Function Attrs: alwaysinline
define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&5resetCv17301SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !325 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !330, metadata !DIExpression()), !dbg !331
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !331
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !331
  %3 = load i32, ptr %2, align 4, !dbg !331
  %4 = load ptr, ptr %arg.self, align 8, !dbg !331
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 2, !dbg !331
  %6 = load i32, ptr %5, align 4, !dbg !331
  store i32 %6, ptr %2, align 4, !dbg !331
  ret void
}

define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !332 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !335, metadata !DIExpression()), !dbg !336
  %var.iter = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.iter, metadata !337, metadata !DIExpression()), !dbg !339
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !336
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !336
  %3 = load i32, ptr %2, align 4, !dbg !336
  %4 = load ptr, ptr %arg.self, align 8, !dbg !336
  %5 = call i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %4) #0, !dbg !340
  %6 = icmp sgt i32 %3, %5, !dbg !340
  br i1 %6, label %7, label %11, !dbg !340

7:                                                ; preds = %body
  %8 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !341
  %9 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE"() #0, !dbg !341
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %9, ptr %8, align 4, !dbg !341
  %10 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %8, align 4, !dbg !341
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %10, !dbg !341

11:                                               ; preds = %body
  br label %12, !dbg !341

12:                                               ; preds = %11
  %13 = load ptr, ptr %arg.self, align 8, !dbg !336
  %14 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 1, !dbg !336
  %15 = load i32, ptr %14, align 4, !dbg !336
  %16 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !336
  %17 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE"(i32 %15) #0, !dbg !342
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %17, ptr %16, align 4, !dbg !342
  %18 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %16, align 4, !dbg !342
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %18, ptr %var.iter, align 4, !dbg !342
  %19 = load ptr, ptr %arg.self, align 8, !dbg !336
  %20 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %19, i32 0, i32 1, !dbg !336
  %21 = load i32, ptr %20, align 4, !dbg !336
  %22 = load ptr, ptr %arg.self, align 8, !dbg !336
  %23 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %22, i32 0, i32 1, !dbg !336
  %24 = load i32, ptr %23, align 4, !dbg !336
  %25 = add i32 %24, 1, !dbg !343
  store i32 %25, ptr %20, align 4, !dbg !343
  %26 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %var.iter, align 4, !dbg !344
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %26, !dbg !344
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !345 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !348, metadata !DIExpression()), !dbg !349
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !349
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !349
  %3 = load i32, ptr %2, align 4, !dbg !349
  ret i32 %3, !dbg !349
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&5beginCv17287SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !350 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !351, metadata !DIExpression()), !dbg !352
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !352
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 2, !dbg !352
  %3 = load i32, ptr %2, align 4, !dbg !352
  ret i32 %3, !dbg !352
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4sizeCv17283SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !353 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !354, metadata !DIExpression()), !dbg !355
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !355
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !355
  %3 = load i32, ptr %2, align 4, !dbg !355
  %4 = load ptr, ptr %arg.self, align 8, !dbg !355
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 2, !dbg !355
  %6 = load i32, ptr %5, align 4, !dbg !355
  %7 = sub i32 %3, %6, !dbg !355
  ret i32 %7, !dbg !355
}

define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17275SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) personality ptr @sn.eh.personality !dbg !356 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !359, metadata !DIExpression()), !dbg !360
  %arg.end = alloca i32, align 4
  store i32 %1, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !361, metadata !DIExpression()), !dbg !360
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !360
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !360
  %3 = load ptr, ptr %arg.self, align 8, !dbg !360
  %4 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %3, i32 0, i32 1, !dbg !360
  %5 = load i32, ptr %4, align 4, !dbg !360
  store i32 0, ptr %4, align 4, !dbg !362
  %6 = load ptr, ptr %arg.self, align 8, !dbg !360
  %7 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 2, !dbg !360
  %8 = load i32, ptr %7, align 4, !dbg !360
  store i32 0, ptr %7, align 4, !dbg !363
  %9 = load ptr, ptr %arg.self, align 8, !dbg !360
  %10 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 3, !dbg !360
  %11 = load i32, ptr %10, align 4, !dbg !360
  %12 = load i32, ptr %arg.end, align 4, !dbg !364
  store i32 %12, ptr %10, align 4, !dbg !364
  ret void
}

define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) personality ptr @sn.eh.personality !dbg !365 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !368, metadata !DIExpression()), !dbg !369
  %arg.start = alloca i32, align 4
  store i32 %1, ptr %arg.start, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.start, metadata !370, metadata !DIExpression()), !dbg !369
  %arg.end = alloca i32, align 4
  store i32 %2, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !371, metadata !DIExpression()), !dbg !369
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !369
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !369
  %4 = load ptr, ptr %arg.self, align 8, !dbg !369
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !369
  %6 = load i32, ptr %5, align 4, !dbg !369
  store i32 0, ptr %5, align 4, !dbg !372
  %7 = load ptr, ptr %arg.self, align 8, !dbg !369
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 2, !dbg !369
  %9 = load i32, ptr %8, align 4, !dbg !369
  store i32 0, ptr %8, align 4, !dbg !373
  %10 = load ptr, ptr %arg.self, align 8, !dbg !369
  %11 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 2, !dbg !369
  %12 = load i32, ptr %11, align 4, !dbg !369
  %13 = load i32, ptr %arg.start, align 4, !dbg !374
  store i32 %13, ptr %11, align 4, !dbg !374
  %14 = load ptr, ptr %arg.self, align 8, !dbg !369
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 3, !dbg !369
  %16 = load i32, ptr %15, align 4, !dbg !369
  %17 = load i32, ptr %arg.end, align 4, !dbg !375
  store i32 %17, ptr %15, align 4, !dbg !375
  %18 = load ptr, ptr %arg.self, align 8, !dbg !369
  %19 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 1, !dbg !369
  %20 = load i32, ptr %19, align 4, !dbg !369
  %21 = load ptr, ptr %arg.self, align 8, !dbg !369
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 2, !dbg !369
  %23 = load i32, ptr %22, align 4, !dbg !369
  store i32 %23, ptr %19, align 4, !dbg !369
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&5resetCv17247SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !376 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !380, metadata !DIExpression()), !dbg !381
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !381
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !381
  %3 = load i32, ptr %2, align 4, !dbg !381
  store i32 0, ptr %2, align 4, !dbg !382
  ret void
}

define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !383 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !386, metadata !DIExpression()), !dbg !387
  br label %body

body:                                             ; preds = %entry
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" zeroinitializer
}

define internal void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !388 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !389, metadata !DIExpression()), !dbg !390
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !390
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !390
  %3 = load i32, ptr %2, align 4, !dbg !390
  store i32 0, ptr %2, align 4, !dbg !391
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE"(i32 %0) #0 personality ptr @sn.eh.personality !dbg !392 {
entry:
  %arg.val = alloca i32, align 4
  store i32 %0, ptr %arg.val, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !395, metadata !DIExpression()), !dbg !396
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.val, align 4, !dbg !397
  %2 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !398
  call void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %1), !dbg !398
  %3 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %2, align 4, !dbg !398
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %3, !dbg !398
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE"() #0 personality ptr @sn.eh.personality !dbg !399 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !402
  call void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !402
  %1 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !402
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %1, !dbg !402
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !403 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !407, metadata !DIExpression()), !dbg !408
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !408
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !408
  %3 = load i1, ptr %2, align 1, !dbg !408
  ret i1 %3, !dbg !408
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !409 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !412, metadata !DIExpression()), !dbg !413
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !413
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !413
  %3 = load i1, ptr %2, align 1, !dbg !413
  %4 = icmp eq i1 %3, false, !dbg !413
  br i1 %4, label %5, label %8, !dbg !413

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !414
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.4), !dbg !414
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !414
  call void @sn.eh.throw(ptr %7), !dbg !414
  br label %9, !dbg !414

8:                                                ; preds = %body
  br label %9, !dbg !414

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !413
  %11 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 1, !dbg !413
  %12 = load i32, ptr %11, align 4, !dbg !413
  ret i32 %12, !dbg !413
}

define internal void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) personality ptr @sn.eh.personality !dbg !415 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !418, metadata !DIExpression()), !dbg !419
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !420, metadata !DIExpression()), !dbg !419
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !419
  %3 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 0, !dbg !419
  %4 = load i1, ptr %3, align 1, !dbg !419
  store i1 false, ptr %3, align 1, !dbg !421
  %5 = load ptr, ptr %arg.self, align 8, !dbg !419
  %6 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 1, !dbg !419
  %7 = load i32, ptr %6, align 4, !dbg !419
  %8 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE"() #0, !dbg !422
  store i32 %8, ptr %6, align 4, !dbg !422
  %9 = load ptr, ptr %arg.self, align 8, !dbg !419
  %10 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 1, !dbg !419
  %11 = load i32, ptr %10, align 4, !dbg !419
  %12 = load i32, ptr %arg.value, align 4, !dbg !423
  store i32 %12, ptr %10, align 4, !dbg !423
  %13 = load ptr, ptr %arg.self, align 8, !dbg !419
  %14 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 0, !dbg !419
  %15 = load i1, ptr %14, align 1, !dbg !419
  store i1 true, ptr %14, align 1, !dbg !424
  ret void
}

define internal void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !425 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !428, metadata !DIExpression()), !dbg !429
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !429
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !429
  %3 = load i1, ptr %2, align 1, !dbg !429
  store i1 false, ptr %2, align 1, !dbg !430
  %4 = load ptr, ptr %arg.self, align 8, !dbg !429
  %5 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !429
  %6 = load i32, ptr %5, align 4, !dbg !429
  %7 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE"() #0, !dbg !431
  store i32 %7, ptr %5, align 4, !dbg !431
  ret void
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !432 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !435, metadata !DIExpression()), !dbg !436
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !436
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 4, !dbg !436
  %3 = load ptr, ptr %2, align 8, !dbg !436
  ret ptr %3, !dbg !436
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4sizeCv17172SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !437 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !440, metadata !DIExpression()), !dbg !441
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !441
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 3, !dbg !441
  %3 = load i32, ptr %2, align 4, !dbg !441
  ret i32 %3, !dbg !441
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i32 %2) personality ptr @sn.eh.personality !dbg !442 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !445, metadata !DIExpression()), !dbg !446
  %arg.other = alloca ptr, align 8
  store ptr %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !447, metadata !DIExpression()), !dbg !446
  %arg.length = alloca i32, align 4
  store i32 %2, ptr %arg.length, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.length, metadata !448, metadata !DIExpression()), !dbg !446
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !446
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !446
  %4 = load ptr, ptr %arg.self, align 8, !dbg !446
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %4, i32 0, i32 1, !dbg !446
  %6 = load i32, ptr %5, align 4, !dbg !446
  store i32 0, ptr %5, align 4, !dbg !449
  %7 = load ptr, ptr %arg.self, align 8, !dbg !446
  %8 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, i32 0, i32 2, !dbg !446
  %9 = load i32, ptr %8, align 4, !dbg !446
  store i32 10, ptr %8, align 4, !dbg !450
  %10 = load ptr, ptr %arg.self, align 8, !dbg !446
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %10, i32 0, i32 3, !dbg !446
  %12 = load i32, ptr %11, align 4, !dbg !446
  store i32 0, ptr %11, align 4, !dbg !451
  %13 = load ptr, ptr %arg.self, align 8, !dbg !446
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %13, i32 0, i32 4, !dbg !446
  %15 = load ptr, ptr %14, align 8, !dbg !446
  store ptr @.str.5, ptr %14, align 8, !dbg !452
  %16 = load ptr, ptr %arg.self, align 8, !dbg !446
  %17 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %16, i32 0, i32 4, !dbg !446
  %18 = load ptr, ptr %17, align 8, !dbg !446
  %19 = load ptr, ptr %arg.other, align 8, !dbg !453
  store ptr %19, ptr %17, align 8, !dbg !453
  %20 = load ptr, ptr %arg.self, align 8, !dbg !446
  %21 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %20, i32 0, i32 3, !dbg !446
  %22 = load i32, ptr %21, align 4, !dbg !446
  %23 = load i32, ptr %arg.length, align 4, !dbg !454
  store i32 %23, ptr %21, align 4, !dbg !454
  %24 = load ptr, ptr %arg.self, align 8, !dbg !446
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !446
  %26 = load i32, ptr %25, align 4, !dbg !446
  %27 = load i32, ptr %arg.length, align 4, !dbg !446
  %28 = add i32 %27, 10, !dbg !455
  store i32 %28, ptr %25, align 4, !dbg !455
  ret void
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17151SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) personality ptr @sn.eh.personality !dbg !456 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !459, metadata !DIExpression()), !dbg !460
  %arg.other = alloca ptr, align 8
  store ptr %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !461, metadata !DIExpression()), !dbg !460
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !460
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !460
  %3 = load ptr, ptr %arg.self, align 8, !dbg !460
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !460
  %5 = load i32, ptr %4, align 4, !dbg !460
  store i32 0, ptr %4, align 4, !dbg !462
  %6 = load ptr, ptr %arg.self, align 8, !dbg !460
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !460
  %8 = load i32, ptr %7, align 4, !dbg !460
  store i32 10, ptr %7, align 4, !dbg !463
  %9 = load ptr, ptr %arg.self, align 8, !dbg !460
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !460
  %11 = load i32, ptr %10, align 4, !dbg !460
  store i32 0, ptr %10, align 4, !dbg !464
  %12 = load ptr, ptr %arg.self, align 8, !dbg !460
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !460
  %14 = load ptr, ptr %13, align 8, !dbg !460
  store ptr @.str.6, ptr %13, align 8, !dbg !465
  %15 = load ptr, ptr %arg.self, align 8, !dbg !460
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !460
  %17 = load ptr, ptr %16, align 8, !dbg !460
  %18 = load ptr, ptr %arg.other, align 8, !dbg !460
  %19 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %18, i32 0, i32 4, !dbg !460
  %20 = load ptr, ptr %19, align 8, !dbg !460
  store ptr %20, ptr %16, align 8, !dbg !460
  %21 = load ptr, ptr %arg.self, align 8, !dbg !460
  %22 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %21, i32 0, i32 3, !dbg !460
  %23 = load i32, ptr %22, align 4, !dbg !460
  %24 = load ptr, ptr %arg.other, align 8, !dbg !460
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 3, !dbg !460
  %26 = load i32, ptr %25, align 4, !dbg !460
  store i32 %26, ptr %22, align 4, !dbg !460
  %27 = load ptr, ptr %arg.self, align 8, !dbg !460
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 2, !dbg !460
  %29 = load i32, ptr %28, align 4, !dbg !460
  %30 = load ptr, ptr %arg.other, align 8, !dbg !460
  %31 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %30, i32 0, i32 2, !dbg !460
  %32 = load i32, ptr %31, align 4, !dbg !460
  store i32 %32, ptr %28, align 4, !dbg !460
  ret void
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) personality ptr @sn.eh.personality !dbg !466 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !469, metadata !DIExpression()), !dbg !470
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !471, metadata !DIExpression()), !dbg !470
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !470
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !470
  %3 = load ptr, ptr %arg.self, align 8, !dbg !470
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !470
  %5 = load i32, ptr %4, align 4, !dbg !470
  store i32 0, ptr %4, align 4, !dbg !472
  %6 = load ptr, ptr %arg.self, align 8, !dbg !470
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !470
  %8 = load i32, ptr %7, align 4, !dbg !470
  store i32 10, ptr %7, align 4, !dbg !473
  %9 = load ptr, ptr %arg.self, align 8, !dbg !470
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !470
  %11 = load i32, ptr %10, align 4, !dbg !470
  store i32 0, ptr %10, align 4, !dbg !474
  %12 = load ptr, ptr %arg.self, align 8, !dbg !470
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !470
  %14 = load ptr, ptr %13, align 8, !dbg !470
  store ptr @.str.7, ptr %13, align 8, !dbg !475
  %15 = load ptr, ptr %arg.self, align 8, !dbg !470
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !470
  %17 = load ptr, ptr %16, align 8, !dbg !470
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !476
  store ptr %18, ptr %16, align 8, !dbg !476
  %19 = load ptr, ptr %arg.self, align 8, !dbg !470
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %19, i32 0, i32 3, !dbg !470
  %21 = load i32, ptr %20, align 4, !dbg !470
  %22 = load ptr, ptr %arg.buffer, align 8, !dbg !477
  %23 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %22), !dbg !478
  store i32 %23, ptr %20, align 4, !dbg !478
  %24 = load ptr, ptr %arg.self, align 8, !dbg !470
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !470
  %26 = load i32, ptr %25, align 4, !dbg !470
  %27 = load ptr, ptr %arg.self, align 8, !dbg !470
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 3, !dbg !470
  %29 = load i32, ptr %28, align 4, !dbg !470
  %30 = add i32 %29, 10, !dbg !479
  store i32 %30, ptr %25, align 4, !dbg !479
  ret void
}

define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17134SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !480 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !483, metadata !DIExpression()), !dbg !484
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !484
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !484
  %2 = load ptr, ptr %arg.self, align 8, !dbg !484
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 1, !dbg !484
  %4 = load i32, ptr %3, align 4, !dbg !484
  store i32 0, ptr %3, align 4, !dbg !485
  %5 = load ptr, ptr %arg.self, align 8, !dbg !484
  %6 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %5, i32 0, i32 2, !dbg !484
  %7 = load i32, ptr %6, align 4, !dbg !484
  store i32 10, ptr %6, align 4, !dbg !486
  %8 = load ptr, ptr %arg.self, align 8, !dbg !484
  %9 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %8, i32 0, i32 3, !dbg !484
  %10 = load i32, ptr %9, align 4, !dbg !484
  store i32 0, ptr %9, align 4, !dbg !487
  %11 = load ptr, ptr %arg.self, align 8, !dbg !484
  %12 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %11, i32 0, i32 4, !dbg !484
  %13 = load ptr, ptr %12, align 8, !dbg !484
  store ptr @.str.8, ptr %12, align 8, !dbg !488
  ret void
}

; Function Attrs: alwaysinline
define internal void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&5resetCv17110SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !489 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !493, metadata !DIExpression()), !dbg !494
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !494
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17018ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !494
  %3 = load i32, ptr %2, align 4, !dbg !494
  store i32 0, ptr %2, align 4, !dbg !495
  ret void
}

define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !496 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !500, metadata !DIExpression()), !dbg !501
  br label %body

body:                                             ; preds = %entry
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" zeroinitializer
}

define internal void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !502 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !503, metadata !DIExpression()), !dbg !504
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !504
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17018ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !504
  %3 = load i32, ptr %2, align 4, !dbg !504
  store i32 0, ptr %2, align 4, !dbg !505
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&4IterCv17019ClsGStA1T4charClsE&5validCv17086SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !506 {
entry:
  %arg.val = alloca i8, align 1
  store i8 %0, ptr %arg.val, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !509, metadata !DIExpression()), !dbg !510
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.val, align 1, !dbg !511
  %2 = alloca %"class._$SN&4IterCv17019ClsGStA1T4charClsE", align 8, !dbg !512
  call void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17033SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rA2T4charFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i8 %1), !dbg !512
  %3 = load %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %2, align 1, !dbg !512
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" %3, !dbg !512
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&4IterCv17019ClsGStA1T4charClsE&7invalidCv17084SaFnE"() #0 personality ptr @sn.eh.personality !dbg !513 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = alloca %"class._$SN&4IterCv17019ClsGStA1T4charClsE", align 8, !dbg !516
  call void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17027SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !516
  %1 = load %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %0, align 1, !dbg !516
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" %1, !dbg !516
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17019ClsGStA1T4charClsE&8is_validCv17080SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !517 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !521, metadata !DIExpression()), !dbg !522
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !522
  %2 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !522
  %3 = load i1, ptr %2, align 1, !dbg !522
  ret i1 %3, !dbg !522
}

; Function Attrs: alwaysinline
define internal i8 @"_$SN&4IterCv17019ClsGStA1T4charClsE&5valueCv17041SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !523 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !526, metadata !DIExpression()), !dbg !527
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !527
  %2 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !527
  %3 = load i1, ptr %2, align 1, !dbg !527
  %4 = icmp eq i1 %3, false, !dbg !527
  br i1 %4, label %5, label %8, !dbg !527

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !528
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.9), !dbg !528
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !528
  call void @sn.eh.throw(ptr %7), !dbg !528
  br label %9, !dbg !528

8:                                                ; preds = %body
  br label %9, !dbg !528

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !527
  %11 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %10, i32 0, i32 1, !dbg !527
  %12 = load i8, ptr %11, align 1, !dbg !527
  ret i8 %12, !dbg !527
}

define internal ptr @"_$SN&9ExceptionCv17046ClsE&4whatCv17060SaA1_$SN&9ExceptionCv17046ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !529 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !534, metadata !DIExpression()), !dbg !535
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !535
  %2 = getelementptr inbounds %"class._$SN&9ExceptionCv17046ClsE", ptr %1, i32 0, i32 0, !dbg !535
  %3 = load ptr, ptr %2, align 8, !dbg !535
  ret ptr %3, !dbg !535
}

define internal void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) personality ptr @sn.eh.personality !dbg !536 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !539, metadata !DIExpression()), !dbg !540
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !541, metadata !DIExpression()), !dbg !540
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !540
  %3 = getelementptr inbounds %"class._$SN&9ExceptionCv17046ClsE", ptr %2, i32 0, i32 0, !dbg !540
  %4 = load ptr, ptr %3, align 8, !dbg !540
  %5 = load ptr, ptr %arg.m, align 8, !dbg !542
  store ptr %5, ptr %3, align 8, !dbg !542
  ret void
}

define internal void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17033SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rA2T4charFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i8 %1) personality ptr @sn.eh.personality !dbg !543 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !546, metadata !DIExpression()), !dbg !547
  %arg.value = alloca i8, align 1
  store i8 %1, ptr %arg.value, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !548, metadata !DIExpression()), !dbg !547
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !547
  %3 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %2, i32 0, i32 0, !dbg !547
  %4 = load i1, ptr %3, align 1, !dbg !547
  store i1 false, ptr %3, align 1, !dbg !549
  %5 = load ptr, ptr %arg.self, align 8, !dbg !547
  %6 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %5, i32 0, i32 1, !dbg !547
  %7 = load i8, ptr %6, align 1, !dbg !547
  %8 = call i8 @"_$SN@sn.Core.CLib&8null_ptrCv17039SaFnE"() #0, !dbg !550
  store i8 %8, ptr %6, align 1, !dbg !550
  %9 = load ptr, ptr %arg.self, align 8, !dbg !547
  %10 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %9, i32 0, i32 1, !dbg !547
  %11 = load i8, ptr %10, align 1, !dbg !547
  %12 = load i8, ptr %arg.value, align 1, !dbg !551
  store i8 %12, ptr %10, align 1, !dbg !551
  %13 = load ptr, ptr %arg.self, align 8, !dbg !547
  %14 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %13, i32 0, i32 0, !dbg !547
  %15 = load i1, ptr %14, align 1, !dbg !547
  store i1 true, ptr %14, align 1, !dbg !552
  ret void
}

define internal void @"_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17027SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !553 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !556, metadata !DIExpression()), !dbg !557
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !557
  %2 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !557
  %3 = load i1, ptr %2, align 1, !dbg !557
  store i1 false, ptr %2, align 1, !dbg !558
  %4 = load ptr, ptr %arg.self, align 8, !dbg !557
  %5 = getelementptr inbounds %"class._$SN&4IterCv17019ClsGStA1T4charClsE", ptr %4, i32 0, i32 1, !dbg !557
  %6 = load i8, ptr %5, align 1, !dbg !557
  %7 = call i8 @"_$SN@sn.Core.CLib&8null_ptrCv17031SaFnE"() #0, !dbg !559
  store i8 %7, ptr %5, align 1, !dbg !559
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !560 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !563, metadata !DIExpression()), !dbg !564
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !565
  %2 = load i32, ptr %1, align 4, !dbg !565
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !566
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE"(i32 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.11) #0, !dbg !567
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !567
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !567
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !567
}

declare noalias noundef nonnull ptr @sn.alloca(i32)

; Function Attrs: nounwind
declare noalias noundef nonnull ptr @sn.eh.create(ptr, i32) #3

declare void @sn.eh.throw(ptr)

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i64&9to_stringCv17501SaA1T3i64.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !568 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !572, metadata !DIExpression()), !dbg !573
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !574
  %2 = load i64, ptr %1, align 8, !dbg !574
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !575
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17511SaA1T3i64A2T4char.rFnE"(i64 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.10) #0, !dbg !576
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !576
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !576
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !576
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i16&9to_stringCv17423SaA1T3i16.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !577 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !581, metadata !DIExpression()), !dbg !582
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !583
  %2 = load i16, ptr %1, align 2, !dbg !583
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !584
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17433SaA1T3i16A2T4char.rFnE"(i16 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.12) #0, !dbg !585
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !585
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !585
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !585
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT2i8&9to_stringCv17384SaA1T2i8.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !586 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !590, metadata !DIExpression()), !dbg !591
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !592
  %2 = load i8, ptr %1, align 1, !dbg !592
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !593
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17394SaA1T2i8A2T4char.rFnE"(i8 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.13) #0, !dbg !594
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !594
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !594
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !594
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT4char&9to_stringCv17345SaA1T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !595 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !598, metadata !DIExpression()), !dbg !599
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !600
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !601
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 0, !dbg !601
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !601
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !601
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !601
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !601
}

; Function Attrs: noinline
define private ptr @"_$SNT4char&4#IdxCv17374SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %index) #2 !dbg !602 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %index
  ret ptr %0
}

; Function Attrs: noinline
define private ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %other) #2 !dbg !605 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %other
  ret ptr %0
}

; Function Attrs: noinline
define private ptr @"_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %index) #2 !dbg !606 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %index
  ret ptr %0
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&7is_markCv17616SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !607 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !611, metadata !DIExpression()), !dbg !612
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !612
  %2 = icmp eq i8 %1, 96, !dbg !613
  %3 = load i8, ptr %arg.c, align 1, !dbg !612
  %4 = icmp eq i8 %3, 39, !dbg !614
  %5 = or i1 %2, %4, !dbg !614
  %6 = load i8, ptr %arg.c, align 1, !dbg !612
  %7 = icmp eq i8 %6, 94, !dbg !615
  %8 = or i1 %5, %7, !dbg !615
  %9 = load i8, ptr %arg.c, align 1, !dbg !612
  %10 = icmp eq i8 %9, 34, !dbg !616
  %11 = or i1 %8, %10, !dbg !616
  %12 = load i8, ptr %arg.c, align 1, !dbg !612
  %13 = icmp eq i8 %12, 126, !dbg !617
  %14 = or i1 %11, %13, !dbg !617
  %15 = load i8, ptr %arg.c, align 1, !dbg !612
  %16 = icmp eq i8 %15, 46, !dbg !618
  %17 = or i1 %14, %16, !dbg !618
  %18 = load i8, ptr %arg.c, align 1, !dbg !612
  %19 = icmp eq i8 %18, 45, !dbg !619
  %20 = or i1 %17, %19, !dbg !619
  %21 = load i8, ptr %arg.c, align 1, !dbg !612
  %22 = icmp eq i8 %21, 95, !dbg !620
  %23 = or i1 %20, %22, !dbg !620
  %24 = load i8, ptr %arg.c, align 1, !dbg !612
  %25 = icmp eq i8 %24, 42, !dbg !621
  %26 = or i1 %23, %25, !dbg !621
  %27 = load i8, ptr %arg.c, align 1, !dbg !612
  %28 = icmp eq i8 %27, 43, !dbg !622
  %29 = or i1 %26, %28, !dbg !622
  %30 = load i8, ptr %arg.c, align 1, !dbg !612
  %31 = icmp eq i8 %30, 61, !dbg !623
  %32 = or i1 %29, %31, !dbg !623
  %33 = load i8, ptr %arg.c, align 1, !dbg !612
  %34 = icmp eq i8 %33, 60, !dbg !624
  %35 = or i1 %32, %34, !dbg !624
  %36 = load i8, ptr %arg.c, align 1, !dbg !612
  %37 = icmp eq i8 %36, 62, !dbg !625
  %38 = or i1 %35, %37, !dbg !625
  %39 = load i8, ptr %arg.c, align 1, !dbg !612
  %40 = icmp eq i8 %39, 64, !dbg !626
  %41 = or i1 %38, %40, !dbg !626
  %42 = load i8, ptr %arg.c, align 1, !dbg !612
  %43 = icmp eq i8 %42, 58, !dbg !627
  %44 = or i1 %41, %43, !dbg !627
  %45 = load i8, ptr %arg.c, align 1, !dbg !612
  %46 = icmp eq i8 %45, 47, !dbg !628
  %47 = or i1 %44, %46, !dbg !628
  %48 = load i8, ptr %arg.c, align 1, !dbg !612
  %49 = icmp eq i8 %48, 92, !dbg !629
  %50 = or i1 %47, %49, !dbg !629
  %51 = load i8, ptr %arg.c, align 1, !dbg !612
  %52 = icmp eq i8 %51, 124, !dbg !630
  %53 = or i1 %50, %52, !dbg !630
  %54 = load i8, ptr %arg.c, align 1, !dbg !612
  %55 = icmp eq i8 %54, 33, !dbg !631
  %56 = or i1 %53, %55, !dbg !631
  %57 = load i8, ptr %arg.c, align 1, !dbg !612
  %58 = icmp eq i8 %57, 63, !dbg !632
  %59 = or i1 %56, %58, !dbg !632
  %60 = load i8, ptr %arg.c, align 1, !dbg !612
  %61 = icmp eq i8 %60, 35, !dbg !633
  %62 = or i1 %59, %61, !dbg !633
  %63 = load i8, ptr %arg.c, align 1, !dbg !612
  %64 = icmp eq i8 %63, 36, !dbg !634
  %65 = or i1 %62, %64, !dbg !634
  %66 = load i8, ptr %arg.c, align 1, !dbg !612
  %67 = icmp eq i8 %66, 37, !dbg !635
  %68 = or i1 %65, %67, !dbg !635
  %69 = load i8, ptr %arg.c, align 1, !dbg !612
  %70 = icmp eq i8 %69, 38, !dbg !636
  %71 = or i1 %68, %70, !dbg !636
  %72 = load i8, ptr %arg.c, align 1, !dbg !612
  %73 = icmp eq i8 %72, 40, !dbg !637
  %74 = or i1 %71, %73, !dbg !637
  %75 = load i8, ptr %arg.c, align 1, !dbg !612
  %76 = icmp eq i8 %75, 41, !dbg !638
  %77 = or i1 %74, %76, !dbg !638
  %78 = load i8, ptr %arg.c, align 1, !dbg !612
  %79 = icmp eq i8 %78, 91, !dbg !639
  %80 = or i1 %77, %79, !dbg !639
  %81 = load i8, ptr %arg.c, align 1, !dbg !612
  %82 = icmp eq i8 %81, 93, !dbg !640
  %83 = or i1 %80, %82, !dbg !640
  %84 = load i8, ptr %arg.c, align 1, !dbg !612
  %85 = icmp eq i8 %84, 123, !dbg !641
  %86 = or i1 %83, %85, !dbg !641
  %87 = load i8, ptr %arg.c, align 1, !dbg !612
  %88 = icmp eq i8 %87, 125, !dbg !642
  %89 = or i1 %86, %88, !dbg !642
  ret i1 %89, !dbg !642
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&6is_symCv17613SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !643 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !644, metadata !DIExpression()), !dbg !645
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !645
  %2 = icmp eq i8 %1, 43, !dbg !646
  %3 = load i8, ptr %arg.c, align 1, !dbg !645
  %4 = icmp eq i8 %3, 45, !dbg !647
  %5 = or i1 %2, %4, !dbg !647
  %6 = load i8, ptr %arg.c, align 1, !dbg !645
  %7 = icmp eq i8 %6, 42, !dbg !648
  %8 = or i1 %5, %7, !dbg !648
  %9 = load i8, ptr %arg.c, align 1, !dbg !645
  %10 = icmp eq i8 %9, 47, !dbg !649
  %11 = or i1 %8, %10, !dbg !649
  %12 = load i8, ptr %arg.c, align 1, !dbg !645
  %13 = icmp eq i8 %12, 92, !dbg !650
  %14 = or i1 %11, %13, !dbg !650
  %15 = load i8, ptr %arg.c, align 1, !dbg !645
  %16 = icmp eq i8 %15, 124, !dbg !651
  %17 = or i1 %14, %16, !dbg !651
  %18 = load i8, ptr %arg.c, align 1, !dbg !645
  %19 = icmp eq i8 %18, 38, !dbg !652
  %20 = or i1 %17, %19, !dbg !652
  %21 = load i8, ptr %arg.c, align 1, !dbg !645
  %22 = icmp eq i8 %21, 94, !dbg !653
  %23 = or i1 %20, %22, !dbg !653
  %24 = load i8, ptr %arg.c, align 1, !dbg !645
  %25 = icmp eq i8 %24, 60, !dbg !654
  %26 = or i1 %23, %25, !dbg !654
  %27 = load i8, ptr %arg.c, align 1, !dbg !645
  %28 = icmp eq i8 %27, 62, !dbg !655
  %29 = or i1 %26, %28, !dbg !655
  %30 = load i8, ptr %arg.c, align 1, !dbg !645
  %31 = icmp eq i8 %30, 61, !dbg !656
  %32 = or i1 %29, %31, !dbg !656
  %33 = load i8, ptr %arg.c, align 1, !dbg !645
  %34 = icmp eq i8 %33, 126, !dbg !657
  %35 = or i1 %32, %34, !dbg !657
  %36 = load i8, ptr %arg.c, align 1, !dbg !645
  %37 = icmp eq i8 %36, 64, !dbg !658
  %38 = or i1 %35, %37, !dbg !658
  %39 = load i8, ptr %arg.c, align 1, !dbg !645
  %40 = icmp eq i8 %39, 36, !dbg !659
  %41 = or i1 %38, %40, !dbg !659
  %42 = load i8, ptr %arg.c, align 1, !dbg !645
  %43 = icmp eq i8 %42, 37, !dbg !660
  %44 = or i1 %41, %43, !dbg !660
  %45 = load i8, ptr %arg.c, align 1, !dbg !645
  %46 = icmp eq i8 %45, 33, !dbg !661
  %47 = or i1 %44, %46, !dbg !661
  %48 = load i8, ptr %arg.c, align 1, !dbg !645
  %49 = icmp eq i8 %48, 63, !dbg !662
  %50 = or i1 %47, %49, !dbg !662
  ret i1 %50, !dbg !662
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&7is_puncCv17610SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !663 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !664, metadata !DIExpression()), !dbg !665
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !665
  %2 = icmp eq i8 %1, 33, !dbg !666
  %3 = load i8, ptr %arg.c, align 1, !dbg !665
  %4 = icmp eq i8 %3, 34, !dbg !667
  %5 = or i1 %2, %4, !dbg !667
  %6 = load i8, ptr %arg.c, align 1, !dbg !665
  %7 = icmp eq i8 %6, 35, !dbg !668
  %8 = or i1 %5, %7, !dbg !668
  %9 = load i8, ptr %arg.c, align 1, !dbg !665
  %10 = icmp eq i8 %9, 36, !dbg !669
  %11 = or i1 %8, %10, !dbg !669
  %12 = load i8, ptr %arg.c, align 1, !dbg !665
  %13 = icmp eq i8 %12, 37, !dbg !670
  %14 = or i1 %11, %13, !dbg !670
  %15 = load i8, ptr %arg.c, align 1, !dbg !665
  %16 = icmp eq i8 %15, 38, !dbg !671
  %17 = or i1 %14, %16, !dbg !671
  %18 = load i8, ptr %arg.c, align 1, !dbg !665
  %19 = icmp eq i8 %18, 39, !dbg !672
  %20 = or i1 %17, %19, !dbg !672
  %21 = load i8, ptr %arg.c, align 1, !dbg !665
  %22 = icmp eq i8 %21, 40, !dbg !673
  %23 = or i1 %20, %22, !dbg !673
  %24 = load i8, ptr %arg.c, align 1, !dbg !665
  %25 = icmp eq i8 %24, 41, !dbg !674
  %26 = or i1 %23, %25, !dbg !674
  %27 = load i8, ptr %arg.c, align 1, !dbg !665
  %28 = icmp eq i8 %27, 42, !dbg !675
  %29 = or i1 %26, %28, !dbg !675
  %30 = load i8, ptr %arg.c, align 1, !dbg !665
  %31 = icmp eq i8 %30, 43, !dbg !676
  %32 = or i1 %29, %31, !dbg !676
  %33 = load i8, ptr %arg.c, align 1, !dbg !665
  %34 = icmp eq i8 %33, 44, !dbg !677
  %35 = or i1 %32, %34, !dbg !677
  %36 = load i8, ptr %arg.c, align 1, !dbg !665
  %37 = icmp eq i8 %36, 45, !dbg !678
  %38 = or i1 %35, %37, !dbg !678
  %39 = load i8, ptr %arg.c, align 1, !dbg !665
  %40 = icmp eq i8 %39, 46, !dbg !679
  %41 = or i1 %38, %40, !dbg !679
  %42 = load i8, ptr %arg.c, align 1, !dbg !665
  %43 = icmp eq i8 %42, 47, !dbg !680
  %44 = or i1 %41, %43, !dbg !680
  %45 = load i8, ptr %arg.c, align 1, !dbg !665
  %46 = icmp eq i8 %45, 58, !dbg !681
  %47 = or i1 %44, %46, !dbg !681
  %48 = load i8, ptr %arg.c, align 1, !dbg !665
  %49 = icmp eq i8 %48, 59, !dbg !682
  %50 = or i1 %47, %49, !dbg !682
  %51 = load i8, ptr %arg.c, align 1, !dbg !665
  %52 = icmp eq i8 %51, 60, !dbg !683
  %53 = or i1 %50, %52, !dbg !683
  %54 = load i8, ptr %arg.c, align 1, !dbg !665
  %55 = icmp eq i8 %54, 61, !dbg !684
  %56 = or i1 %53, %55, !dbg !684
  %57 = load i8, ptr %arg.c, align 1, !dbg !665
  %58 = icmp eq i8 %57, 62, !dbg !685
  %59 = or i1 %56, %58, !dbg !685
  %60 = load i8, ptr %arg.c, align 1, !dbg !665
  %61 = icmp eq i8 %60, 63, !dbg !686
  %62 = or i1 %59, %61, !dbg !686
  %63 = load i8, ptr %arg.c, align 1, !dbg !665
  %64 = icmp eq i8 %63, 64, !dbg !687
  %65 = or i1 %62, %64, !dbg !687
  %66 = load i8, ptr %arg.c, align 1, !dbg !665
  %67 = icmp eq i8 %66, 91, !dbg !688
  %68 = or i1 %65, %67, !dbg !688
  %69 = load i8, ptr %arg.c, align 1, !dbg !665
  %70 = icmp eq i8 %69, 92, !dbg !689
  %71 = or i1 %68, %70, !dbg !689
  %72 = load i8, ptr %arg.c, align 1, !dbg !665
  %73 = icmp eq i8 %72, 93, !dbg !690
  %74 = or i1 %71, %73, !dbg !690
  %75 = load i8, ptr %arg.c, align 1, !dbg !665
  %76 = icmp eq i8 %75, 94, !dbg !691
  %77 = or i1 %74, %76, !dbg !691
  %78 = load i8, ptr %arg.c, align 1, !dbg !665
  %79 = icmp eq i8 %78, 95, !dbg !692
  %80 = or i1 %77, %79, !dbg !692
  %81 = load i8, ptr %arg.c, align 1, !dbg !665
  %82 = icmp eq i8 %81, 96, !dbg !693
  %83 = or i1 %80, %82, !dbg !693
  %84 = load i8, ptr %arg.c, align 1, !dbg !665
  %85 = icmp eq i8 %84, 123, !dbg !694
  %86 = or i1 %83, %85, !dbg !694
  %87 = load i8, ptr %arg.c, align 1, !dbg !665
  %88 = icmp eq i8 %87, 124, !dbg !695
  %89 = or i1 %86, %88, !dbg !695
  %90 = load i8, ptr %arg.c, align 1, !dbg !665
  %91 = icmp eq i8 %90, 125, !dbg !696
  %92 = or i1 %89, %91, !dbg !696
  %93 = load i8, ptr %arg.c, align 1, !dbg !665
  %94 = icmp eq i8 %93, 126, !dbg !697
  %95 = or i1 %92, %94, !dbg !697
  ret i1 %95, !dbg !697
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_printCv17607SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !698 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !699, metadata !DIExpression()), !dbg !700
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !701
  %2 = call i1 @"_$SN@sn.Core.Char&10is_controlCv17604SaA1T4charFnE"(i8 %1) #0, !dbg !702
  %3 = icmp eq i1 %2, false, !dbg !702
  ret i1 %3, !dbg !702
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&10is_controlCv17604SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !703 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !704, metadata !DIExpression()), !dbg !705
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !705
  %2 = icmp slt i8 %1, 32, !dbg !706
  %3 = load i8, ptr %arg.c, align 1, !dbg !705
  %4 = icmp eq i8 %3, 127, !dbg !707
  %5 = or i1 %2, %4, !dbg !707
  ret i1 %5, !dbg !707
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&12is_alpha_numCv17601SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !708 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !709, metadata !DIExpression()), !dbg !710
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !711
  %2 = call i1 @"_$SN@sn.Core.Char&8is_alphaCv17598SaA1T4charFnE"(i8 %1) #0, !dbg !712
  %3 = load i8, ptr %arg.c, align 1, !dbg !713
  %4 = call i1 @"_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE"(i8 %3) #0, !dbg !714
  %5 = or i1 %2, %4, !dbg !714
  ret i1 %5, !dbg !714
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_alphaCv17598SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !715 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !716, metadata !DIExpression()), !dbg !717
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !718
  %2 = call i1 @"_$SN@sn.Core.Char&8is_upperCv17583SaA1T4charFnE"(i8 %1) #0, !dbg !719
  %3 = load i8, ptr %arg.c, align 1, !dbg !720
  %4 = call i1 @"_$SN@sn.Core.Char&8is_lowerCv17586SaA1T4charFnE"(i8 %3) #0, !dbg !721
  %5 = or i1 %2, %4, !dbg !721
  ret i1 %5, !dbg !721
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&6is_octCv17595SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !722 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !723, metadata !DIExpression()), !dbg !724
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !724
  %2 = icmp sge i8 %1, 48, !dbg !725
  %3 = load i8, ptr %arg.c, align 1, !dbg !724
  %4 = icmp sle i8 %3, 55, !dbg !726
  %5 = and i1 %2, %4, !dbg !726
  ret i1 %5, !dbg !726
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&6is_hexCv17592SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !727 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !728, metadata !DIExpression()), !dbg !729
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !730
  %2 = call i1 @"_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE"(i8 %1) #0, !dbg !731
  %3 = load i8, ptr %arg.c, align 1, !dbg !729
  %4 = icmp sge i8 %3, 97, !dbg !732
  %5 = load i8, ptr %arg.c, align 1, !dbg !729
  %6 = icmp sle i8 %5, 102, !dbg !733
  %7 = and i1 %4, %6, !dbg !733
  %8 = or i1 %2, %7, !dbg !733
  %9 = load i8, ptr %arg.c, align 1, !dbg !729
  %10 = icmp sge i8 %9, 65, !dbg !734
  %11 = load i8, ptr %arg.c, align 1, !dbg !729
  %12 = icmp sle i8 %11, 70, !dbg !735
  %13 = and i1 %10, %12, !dbg !735
  %14 = or i1 %8, %13, !dbg !735
  ret i1 %14, !dbg !735
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !736 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !737, metadata !DIExpression()), !dbg !738
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !738
  %2 = icmp sge i8 %1, 48, !dbg !739
  %3 = load i8, ptr %arg.c, align 1, !dbg !738
  %4 = icmp sle i8 %3, 57, !dbg !740
  %5 = and i1 %2, %4, !dbg !740
  ret i1 %5, !dbg !740
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_lowerCv17586SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !741 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !742, metadata !DIExpression()), !dbg !743
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !743
  %2 = icmp sge i8 %1, 97, !dbg !744
  %3 = load i8, ptr %arg.c, align 1, !dbg !743
  %4 = icmp sle i8 %3, 122, !dbg !745
  %5 = and i1 %2, %4, !dbg !745
  ret i1 %5, !dbg !745
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_upperCv17583SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !746 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !747, metadata !DIExpression()), !dbg !748
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !748
  %2 = icmp sge i8 %1, 65, !dbg !749
  %3 = load i8, ptr %arg.c, align 1, !dbg !748
  %4 = icmp sle i8 %3, 90, !dbg !750
  %5 = and i1 %2, %4, !dbg !750
  ret i1 %5, !dbg !750
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN@sn.Core.Char&8is_spaceCv17580SaA1T4charFnE"(i8 %0) #0 personality ptr @sn.eh.personality !dbg !751 {
entry:
  %arg.c = alloca i8, align 1
  store i8 %0, ptr %arg.c, align 1
  call void @llvm.dbg.declare(metadata ptr %arg.c, metadata !752, metadata !DIExpression()), !dbg !753
  br label %body

body:                                             ; preds = %entry
  %1 = load i8, ptr %arg.c, align 1, !dbg !753
  %2 = icmp eq i8 %1, 32, !dbg !754
  %3 = load i8, ptr %arg.c, align 1, !dbg !753
  %4 = icmp eq i8 %3, 9, !dbg !755
  %5 = or i1 %2, %4, !dbg !755
  %6 = load i8, ptr %arg.c, align 1, !dbg !753
  %7 = icmp eq i8 %6, 10, !dbg !756
  %8 = or i1 %5, %7, !dbg !756
  %9 = load i8, ptr %arg.c, align 1, !dbg !753
  %10 = icmp eq i8 %9, 13, !dbg !757
  %11 = or i1 %8, %10, !dbg !757
  ret i1 %11, !dbg !757
}

define internal void @"_$SN&19TypeInsideClassTestCv17666ClsE&4#NwCCv17670SaA1_$SN&19TypeInsideClassTestCv17666ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !758 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !764, metadata !DIExpression()), !dbg !765
  br label %body

body:                                             ; preds = %entry
  ret void
}

define internal i32 @"_$SN&11VirtualTestCv17647ClsE&4testCv17656SaA1_$SN&11VirtualTestCv17647ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !766 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !771, metadata !DIExpression()), !dbg !772
  br label %body

body:                                             ; preds = %entry
  ret i32 1, !dbg !773
}

define internal void @"_$SN&11VirtualTestCv17647ClsE&4#NwCCv17651SaA1_$SN&11VirtualTestCv17647ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !774 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !777, metadata !DIExpression()), !dbg !778
  br label %body

body:                                             ; preds = %entry
  ret void
}

define internal void @"_$SN&15ValueAccessTestCv17633ClsE&4#NwCCv17636SaA1_$SN&15ValueAccessTestCv17633ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !779 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !784, metadata !DIExpression()), !dbg !785
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !785
  %2 = getelementptr inbounds %"class._$SN&15ValueAccessTestCv17633ClsE", ptr %1, i32 0, i32 0, !dbg !785
  %3 = load i32, ptr %2, align 4, !dbg !785
  store i32 0, ptr %2, align 4, !dbg !786
  ret void
}

define internal void @"_$SN&4TestCv17619ClsE&4#NwCCv17622SaA1_$SN&4TestCv17619ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) personality ptr @sn.eh.personality !dbg !787 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !792, metadata !DIExpression()), !dbg !793
  br label %body

body:                                             ; preds = %entry
  ret void
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !794 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !796, metadata !DIExpression()), !dbg !797
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !798
  %2 = call i32 @"_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.20) #0, !dbg !799
  ret i32 %2, !dbg !799
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !800 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !803, metadata !DIExpression()), !dbg !804
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !805, metadata !DIExpression()), !dbg !804
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !806, metadata !DIExpression()), !dbg !807
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !808
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !808
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #0, !dbg !809
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !809
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !809
  %6 = call ptr @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #0, !dbg !809
  store ptr %6, ptr %var.m, align 8, !dbg !809
  %7 = load ptr, ptr %var.m, align 8, !dbg !810
  %8 = load ptr, ptr %arg.end, align 8, !dbg !811
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.21, ptr %7, ptr %8), !dbg !812
  ret i32 %9, !dbg !812
}

define internal void @"_$SN@sn.Core.System&7printlnCv17684SaFnE"() personality ptr @sn.eh.personality !dbg !813 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = call i32 @putchar(i8 10), !dbg !816
  ret void
}

define internal void @"_$SN@sn.Core.System&4exitCv17681SaA1T3i32FnE"(i32 %0) personality ptr @sn.eh.personality !dbg !817 {
entry:
  %arg.exitCode = alloca i32, align 4
  store i32 %0, ptr %arg.exitCode, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.exitCode, metadata !820, metadata !DIExpression()), !dbg !821
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.exitCode, align 4, !dbg !822
  call void @exit(i32 %1), !dbg !823
  ret void
}

define i32 @main() personality ptr @sn.eh.personality !dbg !824 {
entry:
  call void @sn.runtime.initialize()
  %var.a = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.a, metadata !825, metadata !DIExpression()), !dbg !826
  br label %body

body:                                             ; preds = %entry
  %0 = call ptr @sn.alloca(i32 32), !dbg !827
  %1 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %0, i32 0, i32 0, !dbg !827
  store ptr @"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, align 8, !dbg !827
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !827
  store ptr %0, ptr %var.a, align 8, !dbg !827
  %2 = load ptr, ptr %var.a, align 8, !dbg !826
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 1), !dbg !828
  %3 = load ptr, ptr %var.a, align 8, !dbg !826
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, i32 2), !dbg !829
  %4 = load ptr, ptr %var.a, align 8, !dbg !826
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, i32 3), !dbg !830
  %5 = load ptr, ptr %var.a, align 8, !dbg !831
  %6 = call i32 @"_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %5) #0, !dbg !832
  ret i32 0
}

; Function Attrs: alwaysinline nounwind
declare void @sn.runtime.initialize() #4

attributes #0 = { alwaysinline }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { noinline }
attributes #3 = { nounwind }
attributes #4 = { alwaysinline nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Snowball version 0.0.7", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "main.sn", directory: "tests")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 2, !"Snowball Compiler ID", i32 7}
!4 = !{i32 2, !"Snowball Compiler Version", [6 x i8] c"0.0.7\00"}
!5 = distinct !DISubprogram(name: "Core::CLib::__internal::alloca_and_snprintf", linkageName: "_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17519SaA1T3i32A2T4char.rA3T3i64FnE", scope: !6, file: !6, line: 193, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!6 = !DIFile(filename: "CLib.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !11, !9, !12}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed)
!11 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!12 = !DIBasicType(name: "i64", size: 64, encoding: DW_ATE_signed)
!13 = !{}
!14 = !DILocalVariable(name: "bytes", arg: 1, scope: !5, file: !1, line: 193, type: !11)
!15 = !DILocation(line: 193, column: 15, scope: !5)
!16 = !DILocalVariable(name: "format", arg: 2, scope: !5, file: !1, line: 193, type: !9)
!17 = !DILocalVariable(name: "value", arg: 3, scope: !5, file: !1, line: 193, type: !12)
!18 = !DILocalVariable(name: "buffer", scope: !5, file: !1, line: 196, type: !9)
!19 = !DILocation(line: 196, column: 9, scope: !5)
!20 = !DILocation(line: 196, column: 25, scope: !5)
!21 = !DILocation(line: 196, column: 18, scope: !5)
!22 = !DILocation(line: 197, column: 14, scope: !5)
!23 = !DILocation(line: 197, column: 22, scope: !5)
!24 = !DILocation(line: 197, column: 29, scope: !5)
!25 = !DILocation(line: 197, column: 37, scope: !5)
!26 = !DILocation(line: 197, column: 5, scope: !5)
!27 = !DILocation(line: 198, column: 12, scope: !5)
!28 = distinct !DISubprogram(name: "Core::CLib::__internal::alloca_and_snprintf", linkageName: "_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE", scope: !6, file: !6, line: 193, type: !29, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!29 = !DISubroutineType(types: !30)
!30 = !{!9, !11, !9, !11}
!31 = !DILocalVariable(name: "bytes", arg: 1, scope: !28, file: !1, line: 193, type: !11)
!32 = !DILocation(line: 193, column: 15, scope: !28)
!33 = !DILocalVariable(name: "format", arg: 2, scope: !28, file: !1, line: 193, type: !9)
!34 = !DILocalVariable(name: "value", arg: 3, scope: !28, file: !1, line: 193, type: !11)
!35 = !DILocalVariable(name: "buffer", scope: !28, file: !1, line: 196, type: !9)
!36 = !DILocation(line: 196, column: 9, scope: !28)
!37 = !DILocation(line: 196, column: 25, scope: !28)
!38 = !DILocation(line: 196, column: 18, scope: !28)
!39 = !DILocation(line: 197, column: 14, scope: !28)
!40 = !DILocation(line: 197, column: 22, scope: !28)
!41 = !DILocation(line: 197, column: 29, scope: !28)
!42 = !DILocation(line: 197, column: 37, scope: !28)
!43 = !DILocation(line: 197, column: 5, scope: !28)
!44 = !DILocation(line: 198, column: 12, scope: !28)
!45 = distinct !DISubprogram(name: "Core::CLib::__internal::alloca_and_snprintf", linkageName: "_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17441SaA1T3i32A2T4char.rA3T3i16FnE", scope: !6, file: !6, line: 193, type: !46, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!46 = !DISubroutineType(types: !47)
!47 = !{!9, !11, !9, !48}
!48 = !DIBasicType(name: "i16", size: 16, encoding: DW_ATE_signed)
!49 = !DILocalVariable(name: "bytes", arg: 1, scope: !45, file: !1, line: 193, type: !11)
!50 = !DILocation(line: 193, column: 15, scope: !45)
!51 = !DILocalVariable(name: "format", arg: 2, scope: !45, file: !1, line: 193, type: !9)
!52 = !DILocalVariable(name: "value", arg: 3, scope: !45, file: !1, line: 193, type: !48)
!53 = !DILocalVariable(name: "buffer", scope: !45, file: !1, line: 196, type: !9)
!54 = !DILocation(line: 196, column: 9, scope: !45)
!55 = !DILocation(line: 196, column: 25, scope: !45)
!56 = !DILocation(line: 196, column: 18, scope: !45)
!57 = !DILocation(line: 197, column: 14, scope: !45)
!58 = !DILocation(line: 197, column: 22, scope: !45)
!59 = !DILocation(line: 197, column: 29, scope: !45)
!60 = !DILocation(line: 197, column: 37, scope: !45)
!61 = !DILocation(line: 197, column: 5, scope: !45)
!62 = !DILocation(line: 198, column: 12, scope: !45)
!63 = distinct !DISubprogram(name: "Core::CLib::__internal::alloca_and_snprintf", linkageName: "_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17402SaA1T3i32A2T4char.rA3T2i8FnE", scope: !6, file: !6, line: 193, type: !64, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!64 = !DISubroutineType(types: !65)
!65 = !{!9, !11, !9, !66}
!66 = !DIBasicType(name: "i8", size: 8, encoding: DW_ATE_signed)
!67 = !DILocalVariable(name: "bytes", arg: 1, scope: !63, file: !1, line: 193, type: !11)
!68 = !DILocation(line: 193, column: 15, scope: !63)
!69 = !DILocalVariable(name: "format", arg: 2, scope: !63, file: !1, line: 193, type: !9)
!70 = !DILocalVariable(name: "value", arg: 3, scope: !63, file: !1, line: 193, type: !66)
!71 = !DILocalVariable(name: "buffer", scope: !63, file: !1, line: 196, type: !9)
!72 = !DILocation(line: 196, column: 9, scope: !63)
!73 = !DILocation(line: 196, column: 25, scope: !63)
!74 = !DILocation(line: 196, column: 18, scope: !63)
!75 = !DILocation(line: 197, column: 14, scope: !63)
!76 = !DILocation(line: 197, column: 22, scope: !63)
!77 = !DILocation(line: 197, column: 29, scope: !63)
!78 = !DILocation(line: 197, column: 37, scope: !63)
!79 = !DILocation(line: 197, column: 5, scope: !63)
!80 = !DILocation(line: 198, column: 12, scope: !63)
!81 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE", scope: !6, file: !6, line: 123, type: !82, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!82 = !DISubroutineType(types: !83)
!83 = !{!11}
!84 = !DILocation(line: 124, column: 12, scope: !81)
!85 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE", scope: !6, file: !6, line: 123, type: !82, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!86 = !DILocation(line: 124, column: 12, scope: !85)
!87 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17039SaFnE", scope: !6, file: !6, line: 123, type: !88, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!88 = !DISubroutineType(types: !89)
!89 = !{!10}
!90 = !DILocation(line: 124, column: 12, scope: !87)
!91 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17031SaFnE", scope: !6, file: !6, line: 123, type: !88, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!92 = !DILocation(line: 124, column: 12, scope: !91)
!93 = distinct !DISubprogram(name: "Core::CLib::is_null", linkageName: "_$SN@sn.Core.CLib&7is_nullCv16985SaA1T4cobjFnE", scope: !6, file: !6, line: 132, type: !94, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!94 = !DISubroutineType(types: !95)
!95 = !{!96, !97}
!96 = !DIBasicType(name: "bool", size: 8, encoding: DW_ATE_signed)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 8)
!98 = !DILocalVariable(name: "ptr", arg: 1, scope: !93, file: !1, line: 132, type: !97)
!99 = !DILocation(line: 132, column: 8, scope: !93)
!100 = !DILocation(line: 133, column: 19, scope: !93)
!101 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv16988SaFnE", scope: !6, file: !6, line: 123, type: !102, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!102 = !DISubroutineType(types: !103)
!103 = !{!97}
!104 = !DILocation(line: 124, column: 12, scope: !101)
!105 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 644, type: !107, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!106 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!107 = !DISubroutineType(types: !108)
!108 = !{!109, !111}
!109 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::StringView<char>", scope: !106, file: !106, line: 529, baseType: !110, elements: !13)
!110 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<char>", scope: !106, file: !106, line: 253, elements: !13)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64)
!112 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Vector<i32>", scope: !106, file: !106, line: 415, baseType: !113, elements: !13)
!113 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<i32>", scope: !106, file: !106, line: 253, elements: !13)
!114 = !DILocalVariable(name: "buffer", arg: 1, scope: !105, file: !1, line: 644, type: !111)
!115 = !DILocation(line: 644, column: 15, scope: !105)
!116 = !DILocation(line: 645, column: 33, scope: !105)
!117 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::to_string", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 496, type: !107, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!118 = !DILocalVariable(name: "self", arg: 1, scope: !117, file: !1, line: 496, type: !111)
!119 = !DILocation(line: 496, column: 8, scope: !117)
!120 = !DILocalVariable(name: "result", scope: !117, file: !1, line: 497, type: !121)
!121 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::StringView<char>", scope: !106, file: !106, line: 529, baseType: !110, elements: !13)
!122 = !DILocation(line: 497, column: 15, scope: !117)
!123 = !DILocalVariable(name: "$iter", scope: !117, file: !1, line: 498, type: !124)
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Range<i32>", scope: !106, file: !106, line: 342, baseType: !113, elements: !13)
!125 = !DILocation(line: 498, column: 17, scope: !117)
!126 = !DILocalVariable(name: "$iter_value", scope: !117, file: !1, line: 498, type: !127)
!127 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Iter<i32>", scope: !106, file: !106, line: 285, elements: !13)
!128 = !DILocalVariable(name: "i", scope: !117, file: !1, line: 498, type: !11)
!129 = !DILocation(line: 497, column: 28, scope: !117)
!130 = !DILocation(line: 499, column: 48, scope: !117)
!131 = !DILocation(line: 499, column: 40, scope: !117)
!132 = !DILocation(line: 499, column: 27, scope: !117)
!133 = !DILocation(line: 499, column: 25, scope: !117)
!134 = !DILocation(line: 500, column: 31, scope: !117)
!135 = !DILocation(line: 504, column: 14, scope: !117)
!136 = !DILocation(line: 501, column: 33, scope: !117)
!137 = !DILocation(line: 501, column: 27, scope: !117)
!138 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator +", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE", scope: !106, file: !106, line: 599, type: !139, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!139 = !DISubroutineType(types: !140)
!140 = !{!109, !141, !109}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64)
!142 = !DILocalVariable(name: "self", arg: 1, scope: !138, file: !1, line: 599, type: !141)
!143 = !DILocation(line: 599, column: 14, scope: !138)
!144 = !DILocalVariable(name: "other", arg: 2, scope: !138, file: !1, line: 599, type: !109)
!145 = !DILocalVariable(name: "len1", scope: !138, file: !1, line: 601, type: !11)
!146 = !DILocation(line: 601, column: 11, scope: !138)
!147 = !DILocalVariable(name: "len2", scope: !138, file: !1, line: 602, type: !11)
!148 = !DILocation(line: 602, column: 11, scope: !138)
!149 = !DILocalVariable(name: "sum", scope: !138, file: !1, line: 603, type: !11)
!150 = !DILocation(line: 603, column: 11, scope: !138)
!151 = !DILocalVariable(name: "buffer", scope: !138, file: !1, line: 604, type: !9)
!152 = !DILocation(line: 604, column: 11, scope: !138)
!153 = !DILocation(line: 603, column: 24, scope: !138)
!154 = !DILocation(line: 604, column: 33, scope: !138)
!155 = !DILocation(line: 604, column: 20, scope: !138)
!156 = !DILocation(line: 605, column: 20, scope: !138)
!157 = !DILocation(line: 605, column: 41, scope: !138)
!158 = !DILocation(line: 605, column: 7, scope: !138)
!159 = !DILocation(line: 606, column: 29, scope: !138)
!160 = !DILocation(line: 606, column: 27, scope: !138)
!161 = !DILocation(line: 606, column: 49, scope: !138)
!162 = !DILocation(line: 606, column: 7, scope: !138)
!163 = !DILocation(line: 607, column: 40, scope: !138)
!164 = !DILocation(line: 607, column: 48, scope: !138)
!165 = !DILocation(line: 607, column: 18, scope: !138)
!166 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE", scope: !106, file: !106, line: 644, type: !167, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!167 = !DISubroutineType(types: !168)
!168 = !{!109, !11}
!169 = !DILocalVariable(name: "buffer", arg: 1, scope: !166, file: !1, line: 644, type: !11)
!170 = !DILocation(line: 644, column: 15, scope: !166)
!171 = !DILocation(line: 645, column: 33, scope: !166)
!172 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::insert", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6insertCv17751SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE", scope: !106, file: !106, line: 481, type: !173, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!173 = !DISubroutineType(types: !174)
!174 = !{null, !111, !11, !11}
!175 = !DILocalVariable(name: "self", arg: 1, scope: !172, file: !1, line: 481, type: !111)
!176 = !DILocation(line: 481, column: 8, scope: !172)
!177 = !DILocalVariable(name: "index", arg: 2, scope: !172, file: !1, line: 481, type: !11)
!178 = !DILocalVariable(name: "value", arg: 3, scope: !172, file: !1, line: 481, type: !11)
!179 = !DILocalVariable(name: "cur", scope: !172, file: !1, line: 488, type: !11)
!180 = !DILocation(line: 488, column: 11, scope: !172)
!181 = !DILocation(line: 485, column: 19, scope: !172)
!182 = !DILocation(line: 485, column: 9, scope: !172)
!183 = !DILocation(line: 486, column: 9, scope: !172)
!184 = !DILocation(line: 488, column: 43, scope: !172)
!185 = !DILocation(line: 488, column: 17, scope: !172)
!186 = !DILocation(line: 489, column: 33, scope: !172)
!187 = !DILocation(line: 489, column: 40, scope: !172)
!188 = !DILocation(line: 489, column: 7, scope: !172)
!189 = !DILocation(line: 490, column: 27, scope: !172)
!190 = !DILocation(line: 490, column: 30, scope: !172)
!191 = !DILocation(line: 490, column: 7, scope: !172)
!192 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::operator []", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#IdxCv17745SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 474, type: !193, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!193 = !DISubroutineType(types: !194)
!194 = !{!11, !111, !11}
!195 = !DILocalVariable(name: "self", arg: 1, scope: !192, file: !1, line: 474, type: !111)
!196 = !DILocation(line: 474, column: 14, scope: !192)
!197 = !DILocalVariable(name: "index", arg: 2, scope: !192, file: !1, line: 474, type: !11)
!198 = !DILocation(line: 475, column: 24, scope: !192)
!199 = !DILocation(line: 475, column: 16, scope: !192)
!200 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::data", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4dataCv17740SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 466, type: !201, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!201 = !DISubroutineType(types: !202)
!202 = !{!203, !111}
!203 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!204 = !DILocalVariable(name: "self", arg: 1, scope: !200, file: !1, line: 466, type: !111)
!205 = !DILocation(line: 466, column: 8, scope: !200)
!206 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::at", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 454, type: !193, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!207 = !DILocalVariable(name: "self", arg: 1, scope: !206, file: !1, line: 454, type: !111)
!208 = !DILocation(line: 454, column: 8, scope: !206)
!209 = !DILocalVariable(name: "index", arg: 2, scope: !206, file: !1, line: 454, type: !11)
!210 = !DILocation(line: 456, column: 18, scope: !206)
!211 = !DILocation(line: 458, column: 19, scope: !206)
!212 = !DILocation(line: 460, column: 40, scope: !206)
!213 = !DILocation(line: 460, column: 14, scope: !206)
!214 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::resize", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17722SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 444, type: !215, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!215 = !DISubroutineType(types: !216)
!216 = !{null, !111, !11}
!217 = !DILocalVariable(name: "self", arg: 1, scope: !214, file: !1, line: 444, type: !111)
!218 = !DILocation(line: 444, column: 8, scope: !214)
!219 = !DILocalVariable(name: "capacity", arg: 2, scope: !214, file: !1, line: 444, type: !11)
!220 = !DILocation(line: 446, column: 23, scope: !214)
!221 = !DILocation(line: 447, column: 21, scope: !214)
!222 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::size", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4sizeCv17718SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 439, type: !223, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!223 = !DISubroutineType(types: !224)
!224 = !{!11, !111}
!225 = !DILocalVariable(name: "self", arg: 1, scope: !222, file: !1, line: 439, type: !111)
!226 = !DILocation(line: 439, column: 8, scope: !222)
!227 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::push", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 427, type: !215, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!228 = !DILocalVariable(name: "self", arg: 1, scope: !227, file: !1, line: 427, type: !111)
!229 = !DILocation(line: 427, column: 8, scope: !227)
!230 = !DILocalVariable(name: "value", arg: 2, scope: !227, file: !1, line: 427, type: !11)
!231 = !DILocation(line: 429, column: 24, scope: !227)
!232 = !DILocation(line: 431, column: 37, scope: !227)
!233 = !DILocation(line: 431, column: 9, scope: !227)
!234 = !DILocation(line: 433, column: 46, scope: !227)
!235 = !DILocation(line: 433, column: 7, scope: !227)
!236 = !DILocation(line: 434, column: 35, scope: !227)
!237 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::resize", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 444, type: !215, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!238 = !DILocalVariable(name: "self", arg: 1, scope: !237, file: !1, line: 444, type: !111)
!239 = !DILocation(line: 444, column: 8, scope: !237)
!240 = !DILocalVariable(name: "capacity", arg: 2, scope: !237, file: !1, line: 444, type: !11)
!241 = !DILocation(line: 446, column: 23, scope: !237)
!242 = !DILocation(line: 447, column: 21, scope: !237)
!243 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::constructor", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 421, type: !244, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!244 = !DISubroutineType(types: !245)
!245 = !{null, !111}
!246 = !DILocalVariable(name: "self", arg: 1, scope: !243, file: !1, line: 421, type: !111)
!247 = !DILocation(line: 421, column: 5, scope: !243)
!248 = !DILocation(line: 255, column: 31, scope: !243)
!249 = !DILocation(line: 509, column: 29, scope: !243)
!250 = !DILocation(line: 511, column: 27, scope: !243)
!251 = !DILocation(line: 422, column: 14, scope: !243)
!252 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::fromNumber", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17511SaA1T3i64A2T4char.rFnE", scope: !106, file: !106, line: 631, type: !253, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!253 = !DISubroutineType(types: !254)
!254 = !{!109, !12, !9}
!255 = !DILocalVariable(name: "num", arg: 1, scope: !252, file: !1, line: 631, type: !12)
!256 = !DILocation(line: 631, column: 15, scope: !252)
!257 = !DILocalVariable(name: "format", arg: 2, scope: !252, file: !1, line: 631, type: !9)
!258 = !DILocalVariable(name: "buffer", scope: !252, file: !1, line: 634, type: !9)
!259 = !DILocation(line: 634, column: 11, scope: !252)
!260 = !DILocation(line: 635, column: 51, scope: !252)
!261 = !DILocation(line: 635, column: 59, scope: !252)
!262 = !DILocation(line: 635, column: 9, scope: !252)
!263 = !DILocation(line: 636, column: 40, scope: !252)
!264 = !DILocation(line: 636, column: 18, scope: !252)
!265 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::fromNumber", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE", scope: !106, file: !106, line: 631, type: !266, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!266 = !DISubroutineType(types: !267)
!267 = !{!109, !11, !9}
!268 = !DILocalVariable(name: "num", arg: 1, scope: !265, file: !1, line: 631, type: !11)
!269 = !DILocation(line: 631, column: 15, scope: !265)
!270 = !DILocalVariable(name: "format", arg: 2, scope: !265, file: !1, line: 631, type: !9)
!271 = !DILocalVariable(name: "buffer", scope: !265, file: !1, line: 634, type: !9)
!272 = !DILocation(line: 634, column: 11, scope: !265)
!273 = !DILocation(line: 635, column: 51, scope: !265)
!274 = !DILocation(line: 635, column: 59, scope: !265)
!275 = !DILocation(line: 635, column: 9, scope: !265)
!276 = !DILocation(line: 636, column: 40, scope: !265)
!277 = !DILocation(line: 636, column: 18, scope: !265)
!278 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::fromNumber", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17433SaA1T3i16A2T4char.rFnE", scope: !106, file: !106, line: 631, type: !279, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!279 = !DISubroutineType(types: !280)
!280 = !{!109, !48, !9}
!281 = !DILocalVariable(name: "num", arg: 1, scope: !278, file: !1, line: 631, type: !48)
!282 = !DILocation(line: 631, column: 15, scope: !278)
!283 = !DILocalVariable(name: "format", arg: 2, scope: !278, file: !1, line: 631, type: !9)
!284 = !DILocalVariable(name: "buffer", scope: !278, file: !1, line: 634, type: !9)
!285 = !DILocation(line: 634, column: 11, scope: !278)
!286 = !DILocation(line: 635, column: 51, scope: !278)
!287 = !DILocation(line: 635, column: 59, scope: !278)
!288 = !DILocation(line: 635, column: 9, scope: !278)
!289 = !DILocation(line: 636, column: 40, scope: !278)
!290 = !DILocation(line: 636, column: 18, scope: !278)
!291 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::fromNumber", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17394SaA1T2i8A2T4char.rFnE", scope: !106, file: !106, line: 631, type: !292, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!292 = !DISubroutineType(types: !293)
!293 = !{!109, !66, !9}
!294 = !DILocalVariable(name: "num", arg: 1, scope: !291, file: !1, line: 631, type: !66)
!295 = !DILocation(line: 631, column: 15, scope: !291)
!296 = !DILocalVariable(name: "format", arg: 2, scope: !291, file: !1, line: 631, type: !9)
!297 = !DILocalVariable(name: "buffer", scope: !291, file: !1, line: 634, type: !9)
!298 = !DILocation(line: 634, column: 11, scope: !291)
!299 = !DILocation(line: 635, column: 51, scope: !291)
!300 = !DILocation(line: 635, column: 59, scope: !291)
!301 = !DILocation(line: 635, column: 9, scope: !291)
!302 = !DILocation(line: 636, column: 40, scope: !291)
!303 = !DILocation(line: 636, column: 18, scope: !291)
!304 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::to_string", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&9to_stringCv17327SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 613, type: !305, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!305 = !DISubroutineType(types: !306)
!306 = !{!109, !141}
!307 = !DILocalVariable(name: "self", arg: 1, scope: !304, file: !1, line: 613, type: !141)
!308 = !DILocation(line: 613, column: 8, scope: !304)
!309 = !DILocation(line: 614, column: 17, scope: !304)
!310 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator ==", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&5#DbEqCv17180SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE", scope: !106, file: !106, line: 576, type: !311, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!311 = !DISubroutineType(types: !312)
!312 = !{!96, !141, !109}
!313 = !DILocalVariable(name: "self", arg: 1, scope: !310, file: !1, line: 576, type: !141)
!314 = !DILocation(line: 576, column: 14, scope: !310)
!315 = !DILocalVariable(name: "other", arg: 2, scope: !310, file: !1, line: 576, type: !109)
!316 = !DILocalVariable(name: "$iter", scope: !310, file: !1, line: 582, type: !124)
!317 = !DILocation(line: 582, column: 17, scope: !310)
!318 = !DILocalVariable(name: "$iter_value", scope: !310, file: !1, line: 582, type: !127)
!319 = !DILocalVariable(name: "i", scope: !310, file: !1, line: 582, type: !11)
!320 = !DILocation(line: 580, column: 16, scope: !310)
!321 = !DILocation(line: 584, column: 24, scope: !310)
!322 = !DILocation(line: 584, column: 43, scope: !310)
!323 = !DILocation(line: 589, column: 14, scope: !310)
!324 = !DILocation(line: 586, column: 18, scope: !310)
!325 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::reset", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&5resetCv17301SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 394, type: !326, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!326 = !DISubroutineType(types: !327)
!327 = !{null, !328}
!328 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !329, size: 64)
!329 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Range<i32>", scope: !106, file: !106, line: 342, baseType: !113, elements: !13)
!330 = !DILocalVariable(name: "self", arg: 1, scope: !325, file: !1, line: 394, type: !328)
!331 = !DILocation(line: 394, column: 8, scope: !325)
!332 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::next", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 381, type: !333, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!333 = !DISubroutineType(types: !334)
!334 = !{!127, !328}
!335 = !DILocalVariable(name: "self", arg: 1, scope: !332, file: !1, line: 381, type: !328)
!336 = !DILocation(line: 381, column: 13, scope: !332)
!337 = !DILocalVariable(name: "iter", scope: !332, file: !1, line: 387, type: !338)
!338 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<i32>", scope: !106, file: !106, line: 285, elements: !13)
!339 = !DILocation(line: 387, column: 11, scope: !332)
!340 = !DILocation(line: 383, column: 28, scope: !332)
!341 = !DILocation(line: 385, column: 16, scope: !332)
!342 = !DILocation(line: 387, column: 18, scope: !332)
!343 = !DILocation(line: 388, column: 43, scope: !332)
!344 = !DILocation(line: 389, column: 14, scope: !332)
!345 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::end", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 375, type: !346, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!346 = !DISubroutineType(types: !347)
!347 = !{!11, !328}
!348 = !DILocalVariable(name: "self", arg: 1, scope: !345, file: !1, line: 375, type: !328)
!349 = !DILocation(line: 375, column: 8, scope: !345)
!350 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::begin", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&5beginCv17287SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 369, type: !346, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!351 = !DILocalVariable(name: "self", arg: 1, scope: !350, file: !1, line: 369, type: !328)
!352 = !DILocation(line: 369, column: 8, scope: !350)
!353 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::size", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4sizeCv17283SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 363, type: !346, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!354 = !DILocalVariable(name: "self", arg: 1, scope: !353, file: !1, line: 363, type: !328)
!355 = !DILocation(line: 363, column: 8, scope: !353)
!356 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::constructor", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17275SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 358, type: !357, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!357 = !DISubroutineType(types: !358)
!358 = !{null, !328, !11}
!359 = !DILocalVariable(name: "self", arg: 1, scope: !356, file: !1, line: 358, type: !328)
!360 = !DILocation(line: 358, column: 5, scope: !356)
!361 = !DILocalVariable(name: "end", arg: 2, scope: !356, file: !1, line: 358, type: !11)
!362 = !DILocation(line: 255, column: 31, scope: !356)
!363 = !DILocation(line: 398, column: 32, scope: !356)
!364 = !DILocation(line: 358, column: 46, scope: !356)
!365 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::constructor", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE", scope: !106, file: !106, line: 349, type: !366, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!366 = !DISubroutineType(types: !367)
!367 = !{null, !328, !11, !11}
!368 = !DILocalVariable(name: "self", arg: 1, scope: !365, file: !1, line: 349, type: !328)
!369 = !DILocation(line: 349, column: 5, scope: !365)
!370 = !DILocalVariable(name: "start", arg: 2, scope: !365, file: !1, line: 349, type: !11)
!371 = !DILocalVariable(name: "end", arg: 3, scope: !365, file: !1, line: 349, type: !11)
!372 = !DILocation(line: 255, column: 31, scope: !365)
!373 = !DILocation(line: 398, column: 32, scope: !365)
!374 = !DILocation(line: 350, column: 23, scope: !365)
!375 = !DILocation(line: 350, column: 36, scope: !365)
!376 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::reset", linkageName: "_$SN&8IterableCv17187ClsGStA1T3i32ClsE&5resetCv17247SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 272, type: !377, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!377 = !DISubroutineType(types: !378)
!378 = !{null, !379}
!379 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64)
!380 = !DILocalVariable(name: "self", arg: 1, scope: !376, file: !1, line: 272, type: !379)
!381 = !DILocation(line: 272, column: 8, scope: !376)
!382 = !DILocation(line: 273, column: 27, scope: !376)
!383 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::next", linkageName: "_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 268, type: !384, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!384 = !DISubroutineType(types: !385)
!385 = !{!338, !379}
!386 = !DILocalVariable(name: "self", arg: 1, scope: !383, file: !1, line: 268, type: !379)
!387 = !DILocation(line: 268, column: 13, scope: !383)
!388 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::constructor", linkageName: "_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 263, type: !377, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!389 = !DILocalVariable(name: "self", arg: 1, scope: !388, file: !1, line: 263, type: !379)
!390 = !DILocation(line: 263, column: 5, scope: !388)
!391 = !DILocation(line: 255, column: 31, scope: !388)
!392 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::valid", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE", scope: !106, file: !106, line: 331, type: !393, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!393 = !DISubroutineType(types: !394)
!394 = !{!338, !11}
!395 = !DILocalVariable(name: "val", arg: 1, scope: !392, file: !1, line: 331, type: !11)
!396 = !DILocation(line: 331, column: 15, scope: !392)
!397 = !DILocation(line: 332, column: 40, scope: !392)
!398 = !DILocation(line: 332, column: 20, scope: !392)
!399 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::invalid", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE", scope: !106, file: !106, line: 325, type: !400, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!400 = !DISubroutineType(types: !401)
!401 = !{!338}
!402 = !DILocation(line: 326, column: 20, scope: !399)
!403 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::is_valid", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 318, type: !404, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!404 = !DISubroutineType(types: !405)
!405 = !{!96, !406}
!406 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !338, size: 64)
!407 = !DILocalVariable(name: "self", arg: 1, scope: !403, file: !1, line: 318, type: !406)
!408 = !DILocation(line: 318, column: 8, scope: !403)
!409 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::value", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 306, type: !410, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!410 = !DISubroutineType(types: !411)
!411 = !{!11, !406}
!412 = !DILocalVariable(name: "self", arg: 1, scope: !409, file: !1, line: 306, type: !406)
!413 = !DILocation(line: 306, column: 8, scope: !409)
!414 = !DILocation(line: 310, column: 19, scope: !409)
!415 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !106, file: !106, line: 300, type: !416, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!416 = !DISubroutineType(types: !417)
!417 = !{null, !406, !11}
!418 = !DILocalVariable(name: "self", arg: 1, scope: !415, file: !1, line: 300, type: !406)
!419 = !DILocation(line: 300, column: 5, scope: !415)
!420 = !DILocalVariable(name: "value", arg: 2, scope: !415, file: !1, line: 300, type: !11)
!421 = !DILocation(line: 287, column: 24, scope: !415)
!422 = !DILocation(line: 289, column: 33, scope: !415)
!423 = !DILocation(line: 300, column: 41, scope: !415)
!424 = !DILocation(line: 301, column: 14, scope: !415)
!425 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE", scope: !106, file: !106, line: 295, type: !426, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!426 = !DISubroutineType(types: !427)
!427 = !{null, !406}
!428 = !DILocalVariable(name: "self", arg: 1, scope: !425, file: !1, line: 295, type: !406)
!429 = !DILocation(line: 295, column: 5, scope: !425)
!430 = !DILocation(line: 287, column: 24, scope: !425)
!431 = !DILocation(line: 289, column: 33, scope: !425)
!432 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 569, type: !433, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!433 = !DISubroutineType(types: !434)
!434 = !{!9, !141}
!435 = !DILocalVariable(name: "self", arg: 1, scope: !432, file: !1, line: 569, type: !141)
!436 = !DILocation(line: 569, column: 8, scope: !432)
!437 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::size", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4sizeCv17172SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 564, type: !438, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!438 = !DISubroutineType(types: !439)
!439 = !{!11, !141}
!440 = !DILocalVariable(name: "self", arg: 1, scope: !437, file: !1, line: 564, type: !141)
!441 = !DILocation(line: 564, column: 8, scope: !437)
!442 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE", scope: !106, file: !106, line: 558, type: !443, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!443 = !DISubroutineType(types: !444)
!444 = !{null, !141, !9, !11}
!445 = !DILocalVariable(name: "self", arg: 1, scope: !442, file: !1, line: 558, type: !141)
!446 = !DILocation(line: 558, column: 5, scope: !442)
!447 = !DILocalVariable(name: "other", arg: 2, scope: !442, file: !1, line: 558, type: !9)
!448 = !DILocalVariable(name: "length", arg: 3, scope: !442, file: !1, line: 558, type: !11)
!449 = !DILocation(line: 255, column: 31, scope: !442)
!450 = !DILocation(line: 617, column: 29, scope: !442)
!451 = !DILocation(line: 619, column: 27, scope: !442)
!452 = !DILocation(line: 621, column: 30, scope: !442)
!453 = !DILocation(line: 559, column: 23, scope: !442)
!454 = !DILocation(line: 559, column: 38, scope: !442)
!455 = !DILocation(line: 560, column: 25, scope: !442)
!456 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17151SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 550, type: !457, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!457 = !DISubroutineType(types: !458)
!458 = !{null, !141, !141}
!459 = !DILocalVariable(name: "self", arg: 1, scope: !456, file: !1, line: 550, type: !141)
!460 = !DILocation(line: 550, column: 5, scope: !456)
!461 = !DILocalVariable(name: "other", arg: 2, scope: !456, file: !1, line: 550, type: !141)
!462 = !DILocation(line: 255, column: 31, scope: !456)
!463 = !DILocation(line: 617, column: 29, scope: !456)
!464 = !DILocation(line: 619, column: 27, scope: !456)
!465 = !DILocation(line: 621, column: 30, scope: !456)
!466 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !106, file: !106, line: 543, type: !467, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!467 = !DISubroutineType(types: !468)
!468 = !{null, !141, !9}
!469 = !DILocalVariable(name: "self", arg: 1, scope: !466, file: !1, line: 543, type: !141)
!470 = !DILocation(line: 543, column: 5, scope: !466)
!471 = !DILocalVariable(name: "buffer", arg: 2, scope: !466, file: !1, line: 543, type: !9)
!472 = !DILocation(line: 255, column: 31, scope: !466)
!473 = !DILocation(line: 617, column: 29, scope: !466)
!474 = !DILocation(line: 619, column: 27, scope: !466)
!475 = !DILocation(line: 621, column: 30, scope: !466)
!476 = !DILocation(line: 544, column: 23, scope: !466)
!477 = !DILocation(line: 544, column: 62, scope: !466)
!478 = !DILocation(line: 544, column: 39, scope: !466)
!479 = !DILocation(line: 545, column: 39, scope: !466)
!480 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17134SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 537, type: !481, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!481 = !DISubroutineType(types: !482)
!482 = !{null, !141}
!483 = !DILocalVariable(name: "self", arg: 1, scope: !480, file: !1, line: 537, type: !141)
!484 = !DILocation(line: 537, column: 5, scope: !480)
!485 = !DILocation(line: 255, column: 31, scope: !480)
!486 = !DILocation(line: 617, column: 29, scope: !480)
!487 = !DILocation(line: 619, column: 27, scope: !480)
!488 = !DILocation(line: 621, column: 30, scope: !480)
!489 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::reset", linkageName: "_$SN&8IterableCv17018ClsGStA1T4charClsE&5resetCv17110SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 272, type: !490, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!490 = !DISubroutineType(types: !491)
!491 = !{null, !492}
!492 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64)
!493 = !DILocalVariable(name: "self", arg: 1, scope: !489, file: !1, line: 272, type: !492)
!494 = !DILocation(line: 272, column: 8, scope: !489)
!495 = !DILocation(line: 273, column: 27, scope: !489)
!496 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::next", linkageName: "_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 268, type: !497, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!497 = !DISubroutineType(types: !498)
!498 = !{!499, !492}
!499 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<char>", scope: !106, file: !106, line: 285, elements: !13)
!500 = !DILocalVariable(name: "self", arg: 1, scope: !496, file: !1, line: 268, type: !492)
!501 = !DILocation(line: 268, column: 13, scope: !496)
!502 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::constructor", linkageName: "_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 263, type: !490, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!503 = !DILocalVariable(name: "self", arg: 1, scope: !502, file: !1, line: 263, type: !492)
!504 = !DILocation(line: 263, column: 5, scope: !502)
!505 = !DILocation(line: 255, column: 31, scope: !502)
!506 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<char>::valid", linkageName: "_$SN&4IterCv17019ClsGStA1T4charClsE&5validCv17086SaA1T4charFnE", scope: !106, file: !106, line: 331, type: !507, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!507 = !DISubroutineType(types: !508)
!508 = !{!499, !10}
!509 = !DILocalVariable(name: "val", arg: 1, scope: !506, file: !1, line: 331, type: !10)
!510 = !DILocation(line: 331, column: 15, scope: !506)
!511 = !DILocation(line: 332, column: 40, scope: !506)
!512 = !DILocation(line: 332, column: 20, scope: !506)
!513 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<char>::invalid", linkageName: "_$SN&4IterCv17019ClsGStA1T4charClsE&7invalidCv17084SaFnE", scope: !106, file: !106, line: 325, type: !514, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!514 = !DISubroutineType(types: !515)
!515 = !{!499}
!516 = !DILocation(line: 326, column: 20, scope: !513)
!517 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<char>::is_valid", linkageName: "_$SN&4IterCv17019ClsGStA1T4charClsE&8is_validCv17080SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 318, type: !518, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!518 = !DISubroutineType(types: !519)
!519 = !{!96, !520}
!520 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !499, size: 64)
!521 = !DILocalVariable(name: "self", arg: 1, scope: !517, file: !1, line: 318, type: !520)
!522 = !DILocation(line: 318, column: 8, scope: !517)
!523 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<char>::value", linkageName: "_$SN&4IterCv17019ClsGStA1T4charClsE&5valueCv17041SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 306, type: !524, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!524 = !DISubroutineType(types: !525)
!525 = !{!10, !520}
!526 = !DILocalVariable(name: "self", arg: 1, scope: !523, file: !1, line: 306, type: !520)
!527 = !DILocation(line: 306, column: 8, scope: !523)
!528 = !DILocation(line: 310, column: 19, scope: !523)
!529 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::what", linkageName: "_$SN&9ExceptionCv17046ClsE&4whatCv17060SaA1_$SN&9ExceptionCv17046ClsE.rFnE", scope: !106, file: !106, line: 228, type: !530, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!530 = !DISubroutineType(types: !531)
!531 = !{!9, !532}
!532 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !533, size: 64)
!533 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Exception", scope: !106, file: !106, line: 210, elements: !13)
!534 = !DILocalVariable(name: "self", arg: 1, scope: !529, file: !1, line: 228, type: !532)
!535 = !DILocation(line: 228, column: 8, scope: !529)
!536 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::constructor", linkageName: "_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE", scope: !106, file: !106, line: 216, type: !537, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!537 = !DISubroutineType(types: !538)
!538 = !{null, !532, !9}
!539 = !DILocalVariable(name: "self", arg: 1, scope: !536, file: !1, line: 216, type: !532)
!540 = !DILocation(line: 216, column: 5, scope: !536)
!541 = !DILocalVariable(name: "m", arg: 2, scope: !536, file: !1, line: 216, type: !9)
!542 = !DILocation(line: 216, column: 31, scope: !536)
!543 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<char>::constructor", linkageName: "_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17033SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rA2T4charFnE", scope: !106, file: !106, line: 300, type: !544, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!544 = !DISubroutineType(types: !545)
!545 = !{null, !520, !10}
!546 = !DILocalVariable(name: "self", arg: 1, scope: !543, file: !1, line: 300, type: !520)
!547 = !DILocation(line: 300, column: 5, scope: !543)
!548 = !DILocalVariable(name: "value", arg: 2, scope: !543, file: !1, line: 300, type: !10)
!549 = !DILocation(line: 287, column: 24, scope: !543)
!550 = !DILocation(line: 289, column: 33, scope: !543)
!551 = !DILocation(line: 300, column: 41, scope: !543)
!552 = !DILocation(line: 301, column: 14, scope: !543)
!553 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<char>::constructor", linkageName: "_$SN&4IterCv17019ClsGStA1T4charClsE&4#NwCCv17027SaA1_$SN&4IterCv17019ClsGStA1T4charClsE.rFnE", scope: !106, file: !106, line: 295, type: !554, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!554 = !DISubroutineType(types: !555)
!555 = !{null, !520}
!556 = !DILocalVariable(name: "self", arg: 1, scope: !553, file: !1, line: 295, type: !520)
!557 = !DILocation(line: 295, column: 5, scope: !553)
!558 = !DILocation(line: 287, column: 24, scope: !553)
!559 = !DILocation(line: 289, column: 33, scope: !553)
!560 = distinct !DISubprogram(name: "i32::to_string", linkageName: "_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE", scope: !106, file: !106, line: 63, type: !561, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!561 = !DISubroutineType(types: !562)
!562 = !{!109, !203}
!563 = !DILocalVariable(name: "self", arg: 1, scope: !560, file: !1, line: 63, type: !203)
!564 = !DILocation(line: 63, column: 8, scope: !560)
!565 = !DILocation(line: 64, column: 36, scope: !560)
!566 = !DILocation(line: 64, column: 42, scope: !560)
!567 = !DILocation(line: 64, column: 16, scope: !560)
!568 = distinct !DISubprogram(name: "i64::to_string", linkageName: "_$SNT3i64&9to_stringCv17501SaA1T3i64.rFnE", scope: !106, file: !106, line: 73, type: !569, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!569 = !DISubroutineType(types: !570)
!570 = !{!109, !571}
!571 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64)
!572 = !DILocalVariable(name: "self", arg: 1, scope: !568, file: !1, line: 73, type: !571)
!573 = !DILocation(line: 73, column: 8, scope: !568)
!574 = !DILocation(line: 74, column: 36, scope: !568)
!575 = !DILocation(line: 74, column: 42, scope: !568)
!576 = !DILocation(line: 74, column: 16, scope: !568)
!577 = distinct !DISubprogram(name: "i16::to_string", linkageName: "_$SNT3i16&9to_stringCv17423SaA1T3i16.rFnE", scope: !106, file: !106, line: 53, type: !578, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!578 = !DISubroutineType(types: !579)
!579 = !{!109, !580}
!580 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64)
!581 = !DILocalVariable(name: "self", arg: 1, scope: !577, file: !1, line: 53, type: !580)
!582 = !DILocation(line: 53, column: 8, scope: !577)
!583 = !DILocation(line: 54, column: 36, scope: !577)
!584 = !DILocation(line: 54, column: 42, scope: !577)
!585 = !DILocation(line: 54, column: 16, scope: !577)
!586 = distinct !DISubprogram(name: "i8::to_string", linkageName: "_$SNT2i8&9to_stringCv17384SaA1T2i8.rFnE", scope: !106, file: !106, line: 43, type: !587, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!587 = !DISubroutineType(types: !588)
!588 = !{!109, !589}
!589 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64)
!590 = !DILocalVariable(name: "self", arg: 1, scope: !586, file: !1, line: 43, type: !589)
!591 = !DILocation(line: 43, column: 8, scope: !586)
!592 = !DILocation(line: 44, column: 36, scope: !586)
!593 = !DILocation(line: 44, column: 42, scope: !586)
!594 = !DILocation(line: 44, column: 16, scope: !586)
!595 = distinct !DISubprogram(name: "char::to_string", linkageName: "_$SNT4char&9to_stringCv17345SaA1T4char.rFnE", scope: !106, file: !106, line: 11, type: !596, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!596 = !DISubroutineType(types: !597)
!597 = !{!109, !9}
!598 = !DILocalVariable(name: "self", arg: 1, scope: !595, file: !1, line: 11, type: !9)
!599 = !DILocation(line: 11, column: 8, scope: !595)
!600 = !DILocation(line: 12, column: 27, scope: !595)
!601 = !DILocation(line: 12, column: 20, scope: !595)
!602 = distinct !DISubprogram(name: "char::operator []", linkageName: "_$SNT4char&4#IdxCv17374SaA1T4char.rA2T3i32FnE", scope: !106, file: !106, line: 30, type: !603, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!603 = !DISubroutineType(types: !604)
!604 = !{!9, !9, !11}
!605 = distinct !DISubprogram(name: "char::operator +", linkageName: "_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE", scope: !106, file: !106, line: 19, type: !603, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!606 = distinct !DISubprogram(name: "char::operator []", linkageName: "_$SNT4char&4#IdxCv17320SaA1T4char.rA2T3i32FnE", scope: !106, file: !106, line: 30, type: !603, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!607 = distinct !DISubprogram(name: "Core::Char::is_mark", linkageName: "_$SN@sn.Core.Char&7is_markCv17616SaA1T4charFnE", scope: !608, file: !608, line: 149, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!608 = !DIFile(filename: "Char.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!609 = !DISubroutineType(types: !610)
!610 = !{!96, !10}
!611 = !DILocalVariable(name: "c", arg: 1, scope: !607, file: !1, line: 149, type: !10)
!612 = !DILocation(line: 149, column: 8, scope: !607)
!613 = !DILocation(line: 150, column: 17, scope: !607)
!614 = !DILocation(line: 150, column: 30, scope: !607)
!615 = !DILocation(line: 150, column: 42, scope: !607)
!616 = !DILocation(line: 151, column: 15, scope: !607)
!617 = !DILocation(line: 151, column: 27, scope: !607)
!618 = !DILocation(line: 151, column: 39, scope: !607)
!619 = !DILocation(line: 152, column: 15, scope: !607)
!620 = !DILocation(line: 152, column: 27, scope: !607)
!621 = !DILocation(line: 152, column: 39, scope: !607)
!622 = !DILocation(line: 153, column: 15, scope: !607)
!623 = !DILocation(line: 153, column: 27, scope: !607)
!624 = !DILocation(line: 153, column: 39, scope: !607)
!625 = !DILocation(line: 154, column: 15, scope: !607)
!626 = !DILocation(line: 154, column: 27, scope: !607)
!627 = !DILocation(line: 154, column: 39, scope: !607)
!628 = !DILocation(line: 155, column: 15, scope: !607)
!629 = !DILocation(line: 155, column: 28, scope: !607)
!630 = !DILocation(line: 155, column: 40, scope: !607)
!631 = !DILocation(line: 156, column: 15, scope: !607)
!632 = !DILocation(line: 156, column: 27, scope: !607)
!633 = !DILocation(line: 156, column: 39, scope: !607)
!634 = !DILocation(line: 157, column: 15, scope: !607)
!635 = !DILocation(line: 157, column: 27, scope: !607)
!636 = !DILocation(line: 157, column: 39, scope: !607)
!637 = !DILocation(line: 158, column: 15, scope: !607)
!638 = !DILocation(line: 158, column: 27, scope: !607)
!639 = !DILocation(line: 158, column: 39, scope: !607)
!640 = !DILocation(line: 159, column: 15, scope: !607)
!641 = !DILocation(line: 159, column: 27, scope: !607)
!642 = !DILocation(line: 159, column: 39, scope: !607)
!643 = distinct !DISubprogram(name: "Core::Char::is_sym", linkageName: "_$SN@sn.Core.Char&6is_symCv17613SaA1T4charFnE", scope: !608, file: !608, line: 133, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!644 = !DILocalVariable(name: "c", arg: 1, scope: !643, file: !1, line: 133, type: !10)
!645 = !DILocation(line: 133, column: 8, scope: !643)
!646 = !DILocation(line: 134, column: 17, scope: !643)
!647 = !DILocation(line: 134, column: 29, scope: !643)
!648 = !DILocation(line: 134, column: 41, scope: !643)
!649 = !DILocation(line: 135, column: 15, scope: !643)
!650 = !DILocation(line: 135, column: 28, scope: !643)
!651 = !DILocation(line: 135, column: 40, scope: !643)
!652 = !DILocation(line: 136, column: 15, scope: !643)
!653 = !DILocation(line: 136, column: 27, scope: !643)
!654 = !DILocation(line: 136, column: 39, scope: !643)
!655 = !DILocation(line: 137, column: 15, scope: !643)
!656 = !DILocation(line: 137, column: 27, scope: !643)
!657 = !DILocation(line: 137, column: 39, scope: !643)
!658 = !DILocation(line: 138, column: 15, scope: !643)
!659 = !DILocation(line: 138, column: 27, scope: !643)
!660 = !DILocation(line: 138, column: 39, scope: !643)
!661 = !DILocation(line: 139, column: 15, scope: !643)
!662 = !DILocation(line: 139, column: 27, scope: !643)
!663 = distinct !DISubprogram(name: "Core::Char::is_punc", linkageName: "_$SN@sn.Core.Char&7is_puncCv17610SaA1T4charFnE", scope: !608, file: !608, line: 112, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!664 = !DILocalVariable(name: "c", arg: 1, scope: !663, file: !1, line: 112, type: !10)
!665 = !DILocation(line: 112, column: 8, scope: !663)
!666 = !DILocation(line: 113, column: 17, scope: !663)
!667 = !DILocation(line: 113, column: 29, scope: !663)
!668 = !DILocation(line: 113, column: 41, scope: !663)
!669 = !DILocation(line: 114, column: 15, scope: !663)
!670 = !DILocation(line: 114, column: 27, scope: !663)
!671 = !DILocation(line: 114, column: 39, scope: !663)
!672 = !DILocation(line: 115, column: 16, scope: !663)
!673 = !DILocation(line: 115, column: 28, scope: !663)
!674 = !DILocation(line: 115, column: 40, scope: !663)
!675 = !DILocation(line: 116, column: 15, scope: !663)
!676 = !DILocation(line: 116, column: 27, scope: !663)
!677 = !DILocation(line: 116, column: 39, scope: !663)
!678 = !DILocation(line: 117, column: 15, scope: !663)
!679 = !DILocation(line: 117, column: 27, scope: !663)
!680 = !DILocation(line: 117, column: 39, scope: !663)
!681 = !DILocation(line: 118, column: 15, scope: !663)
!682 = !DILocation(line: 118, column: 27, scope: !663)
!683 = !DILocation(line: 118, column: 39, scope: !663)
!684 = !DILocation(line: 119, column: 15, scope: !663)
!685 = !DILocation(line: 119, column: 27, scope: !663)
!686 = !DILocation(line: 119, column: 39, scope: !663)
!687 = !DILocation(line: 120, column: 15, scope: !663)
!688 = !DILocation(line: 120, column: 27, scope: !663)
!689 = !DILocation(line: 120, column: 40, scope: !663)
!690 = !DILocation(line: 121, column: 15, scope: !663)
!691 = !DILocation(line: 121, column: 27, scope: !663)
!692 = !DILocation(line: 121, column: 39, scope: !663)
!693 = !DILocation(line: 122, column: 15, scope: !663)
!694 = !DILocation(line: 122, column: 27, scope: !663)
!695 = !DILocation(line: 122, column: 39, scope: !663)
!696 = !DILocation(line: 123, column: 15, scope: !663)
!697 = !DILocation(line: 123, column: 27, scope: !663)
!698 = distinct !DISubprogram(name: "Core::Char::is_print", linkageName: "_$SN@sn.Core.Char&8is_printCv17607SaA1T4charFnE", scope: !608, file: !608, line: 102, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!699 = !DILocalVariable(name: "c", arg: 1, scope: !698, file: !1, line: 102, type: !10)
!700 = !DILocation(line: 102, column: 8, scope: !698)
!701 = !DILocation(line: 103, column: 26, scope: !698)
!702 = !DILocation(line: 103, column: 15, scope: !698)
!703 = distinct !DISubprogram(name: "Core::Char::is_control", linkageName: "_$SN@sn.Core.Char&10is_controlCv17604SaA1T4charFnE", scope: !608, file: !608, line: 92, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!704 = !DILocalVariable(name: "c", arg: 1, scope: !703, file: !1, line: 92, type: !10)
!705 = !DILocation(line: 92, column: 8, scope: !703)
!706 = !DILocation(line: 93, column: 18, scope: !703)
!707 = !DILocation(line: 93, column: 29, scope: !703)
!708 = distinct !DISubprogram(name: "Core::Char::is_alpha_num", linkageName: "_$SN@sn.Core.Char&12is_alpha_numCv17601SaA1T4charFnE", scope: !608, file: !608, line: 82, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!709 = !DILocalVariable(name: "c", arg: 1, scope: !708, file: !1, line: 82, type: !10)
!710 = !DILocation(line: 82, column: 8, scope: !708)
!711 = !DILocation(line: 83, column: 23, scope: !708)
!712 = !DILocation(line: 83, column: 14, scope: !708)
!713 = !DILocation(line: 83, column: 38, scope: !708)
!714 = !DILocation(line: 83, column: 29, scope: !708)
!715 = distinct !DISubprogram(name: "Core::Char::is_alpha", linkageName: "_$SN@sn.Core.Char&8is_alphaCv17598SaA1T4charFnE", scope: !608, file: !608, line: 72, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!716 = !DILocalVariable(name: "c", arg: 1, scope: !715, file: !1, line: 72, type: !10)
!717 = !DILocation(line: 72, column: 8, scope: !715)
!718 = !DILocation(line: 73, column: 23, scope: !715)
!719 = !DILocation(line: 73, column: 14, scope: !715)
!720 = !DILocation(line: 73, column: 38, scope: !715)
!721 = !DILocation(line: 73, column: 29, scope: !715)
!722 = distinct !DISubprogram(name: "Core::Char::is_oct", linkageName: "_$SN@sn.Core.Char&6is_octCv17595SaA1T4charFnE", scope: !608, file: !608, line: 62, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!723 = !DILocalVariable(name: "c", arg: 1, scope: !722, file: !1, line: 62, type: !10)
!724 = !DILocation(line: 62, column: 8, scope: !722)
!725 = !DILocation(line: 63, column: 19, scope: !722)
!726 = !DILocation(line: 63, column: 31, scope: !722)
!727 = distinct !DISubprogram(name: "Core::Char::is_hex", linkageName: "_$SN@sn.Core.Char&6is_hexCv17592SaA1T4charFnE", scope: !608, file: !608, line: 50, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!728 = !DILocalVariable(name: "c", arg: 1, scope: !727, file: !1, line: 50, type: !10)
!729 = !DILocation(line: 50, column: 8, scope: !727)
!730 = !DILocation(line: 51, column: 21, scope: !727)
!731 = !DILocation(line: 51, column: 12, scope: !727)
!732 = !DILocation(line: 51, column: 33, scope: !727)
!733 = !DILocation(line: 51, column: 45, scope: !727)
!734 = !DILocation(line: 52, column: 16, scope: !727)
!735 = !DILocation(line: 52, column: 28, scope: !727)
!736 = distinct !DISubprogram(name: "Core::Char::is_digit", linkageName: "_$SN@sn.Core.Char&8is_digitCv17589SaA1T4charFnE", scope: !608, file: !608, line: 40, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!737 = !DILocalVariable(name: "c", arg: 1, scope: !736, file: !1, line: 40, type: !10)
!738 = !DILocation(line: 40, column: 8, scope: !736)
!739 = !DILocation(line: 41, column: 19, scope: !736)
!740 = !DILocation(line: 41, column: 31, scope: !736)
!741 = distinct !DISubprogram(name: "Core::Char::is_lower", linkageName: "_$SN@sn.Core.Char&8is_lowerCv17586SaA1T4charFnE", scope: !608, file: !608, line: 30, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!742 = !DILocalVariable(name: "c", arg: 1, scope: !741, file: !1, line: 30, type: !10)
!743 = !DILocation(line: 30, column: 8, scope: !741)
!744 = !DILocation(line: 31, column: 19, scope: !741)
!745 = !DILocation(line: 31, column: 31, scope: !741)
!746 = distinct !DISubprogram(name: "Core::Char::is_upper", linkageName: "_$SN@sn.Core.Char&8is_upperCv17583SaA1T4charFnE", scope: !608, file: !608, line: 20, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!747 = !DILocalVariable(name: "c", arg: 1, scope: !746, file: !1, line: 20, type: !10)
!748 = !DILocation(line: 20, column: 8, scope: !746)
!749 = !DILocation(line: 21, column: 19, scope: !746)
!750 = !DILocation(line: 21, column: 31, scope: !746)
!751 = distinct !DISubprogram(name: "Core::Char::is_space", linkageName: "_$SN@sn.Core.Char&8is_spaceCv17580SaA1T4charFnE", scope: !608, file: !608, line: 8, type: !609, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!752 = !DILocalVariable(name: "c", arg: 1, scope: !751, file: !1, line: 8, type: !10)
!753 = !DILocation(line: 8, column: 8, scope: !751)
!754 = !DILocation(line: 9, column: 17, scope: !751)
!755 = !DILocation(line: 9, column: 30, scope: !751)
!756 = !DILocation(line: 10, column: 17, scope: !751)
!757 = !DILocation(line: 10, column: 30, scope: !751)
!758 = distinct !DISubprogram(name: "pkg::cls::test::TypeInsideClassTest::constructor", linkageName: "_$SN&19TypeInsideClassTestCv17666ClsE&4#NwCCv17670SaA1_$SN&19TypeInsideClassTestCv17666ClsE.rFnE", scope: !759, file: !759, line: 68, type: !760, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!759 = !DIFile(filename: "cls.sn", directory: "/home/mauro/work/snowball/tests")
!760 = !DISubroutineType(types: !761)
!761 = !{null, !762}
!762 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !763, size: 64)
!763 = !DICompositeType(tag: DW_TAG_structure_type, name: "pkg::cls::test::TypeInsideClassTest", scope: !759, file: !759, line: 65, elements: !13)
!764 = !DILocalVariable(name: "self", arg: 1, scope: !758, file: !1, line: 68, type: !762)
!765 = !DILocation(line: 68, column: 5, scope: !758)
!766 = distinct !DISubprogram(name: "pkg::cls::test::VirtualTest::test", linkageName: "_$SN&11VirtualTestCv17647ClsE&4testCv17656SaA1_$SN&11VirtualTestCv17647ClsE.rFnE", scope: !759, file: !759, line: 49, type: !767, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!767 = !DISubroutineType(types: !768)
!768 = !{!11, !769}
!769 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !770, size: 64)
!770 = !DICompositeType(tag: DW_TAG_structure_type, name: "pkg::cls::test::VirtualTest", scope: !759, file: !759, line: 46, elements: !13)
!771 = !DILocalVariable(name: "self", arg: 1, scope: !766, file: !1, line: 49, type: !769)
!772 = !DILocation(line: 49, column: 13, scope: !766)
!773 = !DILocation(line: 50, column: 14, scope: !766)
!774 = distinct !DISubprogram(name: "pkg::cls::test::VirtualTest::constructor", linkageName: "_$SN&11VirtualTestCv17647ClsE&4#NwCCv17651SaA1_$SN&11VirtualTestCv17647ClsE.rFnE", scope: !759, file: !759, line: 48, type: !775, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!775 = !DISubroutineType(types: !776)
!776 = !{null, !769}
!777 = !DILocalVariable(name: "self", arg: 1, scope: !774, file: !1, line: 48, type: !769)
!778 = !DILocation(line: 48, column: 5, scope: !774)
!779 = distinct !DISubprogram(name: "pkg::cls::test::ValueAccessTest::constructor", linkageName: "_$SN&15ValueAccessTestCv17633ClsE&4#NwCCv17636SaA1_$SN&15ValueAccessTestCv17633ClsE.rFnE", scope: !759, file: !759, line: 21, type: !780, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!780 = !DISubroutineType(types: !781)
!781 = !{null, !782}
!782 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !783, size: 64)
!783 = !DICompositeType(tag: DW_TAG_structure_type, name: "pkg::cls::test::ValueAccessTest", scope: !759, file: !759, line: 18, elements: !13)
!784 = !DILocalVariable(name: "self", arg: 1, scope: !779, file: !1, line: 21, type: !782)
!785 = !DILocation(line: 21, column: 5, scope: !779)
!786 = !DILocation(line: 20, column: 22, scope: !779)
!787 = distinct !DISubprogram(name: "pkg::cls::test::Test::constructor", linkageName: "_$SN&4TestCv17619ClsE&4#NwCCv17622SaA1_$SN&4TestCv17619ClsE.rFnE", scope: !759, file: !759, line: 5, type: !788, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!788 = !DISubroutineType(types: !789)
!789 = !{null, !790}
!790 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !791, size: 64)
!791 = !DICompositeType(tag: DW_TAG_structure_type, name: "pkg::cls::test::Test", scope: !759, file: !759, line: 3, elements: !13)
!792 = !DILocalVariable(name: "self", arg: 1, scope: !787, file: !1, line: 5, type: !790)
!793 = !DILocation(line: 5, column: 5, scope: !787)
!794 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !795, file: !795, line: 27, type: !223, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!795 = !DIFile(filename: "System.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!796 = !DILocalVariable(name: "msg", arg: 1, scope: !794, file: !1, line: 27, type: !111)
!797 = !DILocation(line: 27, column: 15, scope: !794)
!798 = !DILocation(line: 28, column: 20, scope: !794)
!799 = !DILocation(line: 28, column: 14, scope: !794)
!800 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE", scope: !795, file: !795, line: 16, type: !801, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!801 = !DISubroutineType(types: !802)
!802 = !{!11, !111, !9}
!803 = !DILocalVariable(name: "msg", arg: 1, scope: !800, file: !1, line: 16, type: !111)
!804 = !DILocation(line: 16, column: 15, scope: !800)
!805 = !DILocalVariable(name: "end", arg: 2, scope: !800, file: !1, line: 16, type: !9)
!806 = !DILocalVariable(name: "m", scope: !800, file: !1, line: 17, type: !9)
!807 = !DILocation(line: 17, column: 9, scope: !800)
!808 = !DILocation(line: 17, column: 26, scope: !800)
!809 = !DILocation(line: 17, column: 13, scope: !800)
!810 = !DILocation(line: 18, column: 33, scope: !800)
!811 = !DILocation(line: 18, column: 36, scope: !800)
!812 = !DILocation(line: 18, column: 12, scope: !800)
!813 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv17684SaFnE", scope: !795, file: !795, line: 38, type: !814, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!814 = !DISubroutineType(types: !815)
!815 = !{null}
!816 = !DILocation(line: 38, column: 27, scope: !813)
!817 = distinct !DISubprogram(name: "Core::System::exit", linkageName: "_$SN@sn.Core.System&4exitCv17681SaA1T3i32FnE", scope: !795, file: !795, line: 9, type: !818, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!818 = !DISubroutineType(types: !819)
!819 = !{null, !11}
!820 = !DILocalVariable(name: "exitCode", arg: 1, scope: !817, file: !1, line: 9, type: !11)
!821 = !DILocation(line: 9, column: 15, scope: !817)
!822 = !DILocation(line: 9, column: 52, scope: !817)
!823 = !DILocation(line: 9, column: 41, scope: !817)
!824 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 19, type: !82, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!825 = !DILocalVariable(name: "a", scope: !824, file: !1, line: 20, type: !111)
!826 = !DILocation(line: 20, column: 13, scope: !824)
!827 = !DILocation(line: 20, column: 21, scope: !824)
!828 = !DILocation(line: 21, column: 5, scope: !824)
!829 = !DILocation(line: 22, column: 5, scope: !824)
!830 = !DILocation(line: 23, column: 5, scope: !824)
!831 = !DILocation(line: 24, column: 21, scope: !824)
!832 = !DILocation(line: 24, column: 5, scope: !824)
; ModuleID = 'snowball compiled project'
source_filename = "tests/main.sn"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE" = type { ptr }
%"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE" = type { ptr, ptr }
%"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE" = type { ptr }
%"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" = type { ptr, i32, i32, i32 }
%"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" = type { i1, i32 }
%"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE" = type { ptr, i32, i32, i32, ptr }
%"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE" = type { ptr, i32 }
%"class._$SN&4IterCv17019ClsGStA1T4charClsE" = type { i1, i8 }
%"class._$SN&8IterableCv17018ClsGStA1T4charClsE" = type { ptr, i32 }
%"class._$SN&9ExceptionCv17046ClsE" = type { ptr }

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE" = global %"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE" { ptr @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE" }
@"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE" = global %"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE" { ptr @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", ptr @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE" }
@.str.2 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.3 = private unnamed_addr constant [21 x i8] c"Index out of bounds.\00", align 1
@.str.4 = private unnamed_addr constant [25 x i8] c"Invalid iterator access!\00", align 1
@.str.5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"%i\00", align 1
@.str.20 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.21 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE" = global %"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE" { ptr @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE" }

; Function Attrs: noinline
declare i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64)) #0

; Function Attrs: alwaysinline
define internal ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i32 %2) #1 personality ptr @sn.eh.personality !dbg !5 {
entry:
  %arg.bytes = alloca i32, align 4
  store i32 %0, ptr %arg.bytes, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.bytes, metadata !13, metadata !DIExpression()), !dbg !14
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !15, metadata !DIExpression()), !dbg !14
  %arg.value = alloca i32, align 4
  store i32 %2, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !16, metadata !DIExpression()), !dbg !14
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !17, metadata !DIExpression()), !dbg !18
  br label %body

body:                                             ; preds = %entry
  %3 = load i32, ptr %arg.bytes, align 4, !dbg !19
  %4 = call ptr @malloc(i32 %3), !dbg !20
  store ptr %4, ptr %var.buffer, align 8, !dbg !20
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !21
  %6 = load i32, ptr %arg.bytes, align 4, !dbg !22
  %7 = load ptr, ptr %arg.format, align 8, !dbg !23
  %8 = load i32, ptr %arg.value, align 4, !dbg !24
  %9 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr noundef nonnull align 8 dereferenceable(64) %5, i32 %6, ptr noundef nonnull align 8 dereferenceable(64) %7, i32 %8), !dbg !25
  %10 = load ptr, ptr %var.buffer, align 8, !dbg !26
  ret ptr %10, !dbg !26
}

; Function Attrs: nocallback nofree noinline nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

; Function Attrs: noinline
declare ptr @malloc(i32) #0

; Function Attrs: noinline
declare i32 @snprintf(ptr noundef nonnull align 8 dereferenceable(64), i32, ptr noundef nonnull align 8 dereferenceable(64), ...) #0

; Function Attrs: noinline
declare i32 @sn.eh.personality(i32, i32, i64, ptr, ptr) #0

; Function Attrs: noinline
declare void @memcpy(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64), i32) #0

; Function Attrs: noinline
declare void @memcpy.1(ptr noundef nonnull align 8 dereferenceable(64), ptr noundef nonnull align 8 dereferenceable(64), i32) #0

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE"() #1 personality ptr @sn.eh.personality !dbg !27 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !30
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE"() #1 personality ptr @sn.eh.personality !dbg !31 {
entry:
  br label %body

body:                                             ; preds = %entry
  ret i32 0, !dbg !32
}

; Function Attrs: noinline
declare i32 @printf(ptr noundef nonnull align 8 dereferenceable(64), ...) #0

; Function Attrs: noinline
declare ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64), i32) #0

; Function Attrs: noinline
declare void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64), i32, ptr) #0

; Function Attrs: noinline
declare ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64), i32) #0

; Function Attrs: noinline
declare ptr @sn.ua.alloc(i32) #0

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !33 {
entry:
  %arg.buffer = alloca ptr, align 8
  store ptr %0, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !42, metadata !DIExpression()), !dbg !43
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.buffer, align 8, !dbg !43
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !43
  %3 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !44
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %2, align 8, !dbg !44
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !44
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !44
}

; Function Attrs: noinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !45 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !46, metadata !DIExpression()), !dbg !47
  %var.result = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.result, metadata !48, metadata !DIExpression()), !dbg !50
  %"var.$iter" = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter", metadata !51, metadata !DIExpression()), !dbg !53
  %"var.$iter_value" = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %"var.$iter_value", metadata !54, metadata !DIExpression()), !dbg !53
  %var.i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.i, metadata !56, metadata !DIExpression()), !dbg !53
  br label %body

body:                                             ; preds = %entry
  %1 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !57
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 0, !dbg !57
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !57
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str), !dbg !57
  %3 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, align 8, !dbg !57
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %var.result, align 8, !dbg !57
  %4 = load ptr, ptr %arg.self, align 8, !dbg !47
  %5 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 3, !dbg !47
  %6 = load i32, ptr %5, align 4, !dbg !47
  %7 = alloca %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", align 8, !dbg !53
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 0, !dbg !53
  store ptr @"vtable._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %8, align 8, !dbg !53
  call void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %7, i32 0, i32 %6), !dbg !53
  %9 = load %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, align 8, !dbg !53
  store %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE" %9, ptr %"var.$iter", align 8, !dbg !53
  %10 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !53
  %11 = load ptr, ptr %"var.$iter", align 8, !dbg !53
  %12 = getelementptr inbounds ptr, ptr %11, i32 1, !dbg !53
  %13 = load ptr, ptr %12, align 8, !dbg !53
  %14 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %13(ptr %"var.$iter"), !dbg !53
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %14, ptr %10, align 4, !dbg !53
  %15 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %10, align 4, !dbg !53
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %15, ptr %"var.$iter_value", align 4, !dbg !53
  br label %16, !dbg !53

16:                                               ; preds = %45, %body
  %17 = call i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #5, !dbg !53
  br i1 %17, label %18, label %35, !dbg !53

18:                                               ; preds = %16
  %19 = call i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %"var.$iter_value") #5, !dbg !53
  store i32 %19, ptr %var.i, align 4, !dbg !53
  %20 = load ptr, ptr %arg.self, align 8, !dbg !47
  %21 = load i32, ptr %var.i, align 4, !dbg !58
  %22 = call i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %21), !dbg !59
  %23 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !59
  %24 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE"(i32 %22) #5, !dbg !60
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %24, ptr %23, align 8, !dbg !60
  %25 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %23, align 8, !dbg !60
  %26 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !60
  %27 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.result, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %25) #5, !dbg !61
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %27, ptr %26, align 8, !dbg !61
  %28 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %26, align 8, !dbg !61
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %28, ptr %var.result, align 8, !dbg !61
  %29 = load i32, ptr %var.i, align 4, !dbg !53
  %30 = load ptr, ptr %arg.self, align 8, !dbg !47
  %31 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %30, i32 0, i32 3, !dbg !47
  %32 = load i32, ptr %31, align 4, !dbg !47
  %33 = sub i32 %32, 1, !dbg !62
  %34 = icmp ne i32 %29, %33, !dbg !62
  br i1 %34, label %37, label %44, !dbg !62

35:                                               ; preds = %16
  %36 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %var.result, align 8, !dbg !63
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %36, !dbg !63

37:                                               ; preds = %18
  %38 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !64
  %39 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %38, i32 0, i32 0, !dbg !64
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %39, align 8, !dbg !64
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %38, ptr noundef nonnull align 8 dereferenceable(64) @.str.2), !dbg !64
  %40 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %38, align 8, !dbg !64
  %41 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !64
  %42 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %var.result, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %40) #5, !dbg !65
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %42, ptr %41, align 8, !dbg !65
  %43 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %41, align 8, !dbg !65
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %43, ptr %var.result, align 8, !dbg !65
  br label %45, !dbg !65

44:                                               ; preds = %18
  br label %45, !dbg !65

45:                                               ; preds = %44, %37
  %46 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !53
  %47 = load ptr, ptr %"var.$iter", align 8, !dbg !53
  %48 = getelementptr inbounds ptr, ptr %47, i32 1, !dbg !53
  %49 = load ptr, ptr %48, align 8, !dbg !53
  %50 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %49(ptr %"var.$iter"), !dbg !53
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %50, ptr %46, align 4, !dbg !53
  %.load = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %46, align 4, !dbg !53
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %.load, ptr %"var.$iter_value", align 4, !dbg !53
  br label %16, !dbg !53
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1) #1 personality ptr @sn.eh.personality !dbg !66 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !70, metadata !DIExpression()), !dbg !71
  %arg.other = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !72, metadata !DIExpression()), !dbg !71
  %var.len1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len1, metadata !73, metadata !DIExpression()), !dbg !74
  %var.len2 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.len2, metadata !75, metadata !DIExpression()), !dbg !76
  %var.sum = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %var.sum, metadata !77, metadata !DIExpression()), !dbg !78
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !79, metadata !DIExpression()), !dbg !80
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !71
  %3 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, i32 0, i32 3, !dbg !71
  %4 = load i32, ptr %3, align 4, !dbg !71
  store i32 %4, ptr %var.len1, align 4, !dbg !71
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 3, !dbg !71
  %6 = load i32, ptr %5, align 4, !dbg !71
  store i32 %6, ptr %var.len2, align 4, !dbg !71
  %7 = load i32, ptr %var.len1, align 4, !dbg !74
  %8 = load i32, ptr %var.len2, align 4, !dbg !81
  %9 = add i32 %7, %8, !dbg !81
  store i32 %9, ptr %var.sum, align 4, !dbg !81
  %10 = load i32, ptr %var.sum, align 4, !dbg !82
  %11 = call ptr @malloc(i32 %10), !dbg !83
  store ptr %11, ptr %var.buffer, align 8, !dbg !83
  %12 = load ptr, ptr %var.buffer, align 8, !dbg !84
  %13 = load ptr, ptr %arg.self, align 8, !dbg !71
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %13, i32 0, i32 4, !dbg !71
  %15 = load ptr, ptr %14, align 8, !dbg !71
  %16 = load i32, ptr %var.len1, align 4, !dbg !85
  call void @memcpy.1(ptr noundef nonnull align 8 dereferenceable(64) %12, ptr noundef nonnull align 8 dereferenceable(64) %15, i32 %16), !dbg !86
  %17 = load ptr, ptr %var.buffer, align 8, !dbg !80
  %18 = load i32, ptr %var.len1, align 4, !dbg !87
  %19 = call ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18) #5, !dbg !88
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %arg.other, i32 0, i32 4, !dbg !71
  %21 = load ptr, ptr %20, align 8, !dbg !71
  %22 = load i32, ptr %var.len2, align 4, !dbg !89
  call void @memcpy(ptr noundef nonnull align 8 dereferenceable(64) %19, ptr noundef nonnull align 8 dereferenceable(64) %21, i32 %22), !dbg !90
  %23 = load ptr, ptr %var.buffer, align 8, !dbg !91
  %24 = load i32, ptr %var.sum, align 4, !dbg !92
  %25 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !93
  %26 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %25, i32 0, i32 0, !dbg !93
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %26, align 8, !dbg !93
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %25, ptr noundef nonnull align 8 dereferenceable(64) %23, i32 %24), !dbg !93
  %27 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %25, align 8, !dbg !93
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %27, !dbg !93
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE"(i32 %0) #1 personality ptr @sn.eh.personality !dbg !94 {
entry:
  %arg.buffer = alloca i32, align 4
  store i32 %0, ptr %arg.buffer, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !97, metadata !DIExpression()), !dbg !98
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.buffer, align 4, !dbg !98
  %2 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !98
  %3 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %arg.buffer) #5, !dbg !99
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %3, ptr %2, align 8, !dbg !99
  %4 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %2, align 8, !dbg !99
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, !dbg !99
}

; Function Attrs: noinline
define internal i32 @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !100 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !103, metadata !DIExpression()), !dbg !104
  %arg.index = alloca i32, align 4
  store i32 %1, ptr %arg.index, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.index, metadata !105, metadata !DIExpression()), !dbg !104
  br label %body

body:                                             ; preds = %entry
  %2 = load i32, ptr %arg.index, align 4, !dbg !104
  %3 = icmp slt i32 %2, 0, !dbg !106
  %4 = load i32, ptr %arg.index, align 4, !dbg !104
  %5 = load ptr, ptr %arg.self, align 8, !dbg !104
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 3, !dbg !104
  %7 = load i32, ptr %6, align 4, !dbg !104
  %8 = icmp sge i32 %4, %7, !dbg !104
  %9 = or i1 %3, %8, !dbg !104
  br i1 %9, label %10, label %13, !dbg !104

10:                                               ; preds = %body
  %11 = call ptr @sn.alloca(i32 8), !dbg !107
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, ptr noundef nonnull align 8 dereferenceable(64) @.str.3), !dbg !107
  %12 = call ptr @sn.eh.create(ptr %11, i32 1000), !dbg !107
  call void @sn.eh.throw(ptr %12), !dbg !107
  br label %14, !dbg !107

13:                                               ; preds = %body
  br label %14, !dbg !107

14:                                               ; preds = %13, %10
  %15 = load ptr, ptr %arg.self, align 8, !dbg !104
  %16 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %15, i32 0, i32 4, !dbg !104
  %17 = load ptr, ptr %16, align 8, !dbg !104
  %18 = load i32, ptr %arg.index, align 4, !dbg !108
  %19 = call ptr @sn.ua.get(ptr noundef nonnull align 8 dereferenceable(64) %17, i32 %18), !dbg !109
  %20 = ptrtoint ptr %19 to i32, !dbg !109
  ret i32 %20, !dbg !109
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !110 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !113, metadata !DIExpression()), !dbg !114
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !115, metadata !DIExpression()), !dbg !114
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !114
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 3, !dbg !114
  %4 = load i32, ptr %3, align 4, !dbg !114
  %5 = add i32 %4, 1, !dbg !116
  %6 = load ptr, ptr %arg.self, align 8, !dbg !114
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 2, !dbg !114
  %8 = load i32, ptr %7, align 4, !dbg !114
  %9 = icmp sge i32 %5, %8, !dbg !114
  br i1 %9, label %10, label %16, !dbg !114

10:                                               ; preds = %body
  %11 = load ptr, ptr %arg.self, align 8, !dbg !114
  %12 = load ptr, ptr %arg.self, align 8, !dbg !114
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !114
  %14 = load i32, ptr %13, align 4, !dbg !114
  %15 = add i32 %14, 10, !dbg !117
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %15), !dbg !118
  br label %17, !dbg !118

16:                                               ; preds = %body
  br label %17, !dbg !118

17:                                               ; preds = %16, %10
  %18 = load ptr, ptr %arg.self, align 8, !dbg !114
  %19 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 4, !dbg !114
  %20 = load ptr, ptr %19, align 8, !dbg !114
  %21 = load ptr, ptr %arg.self, align 8, !dbg !114
  %22 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 3, !dbg !114
  %23 = load i32, ptr %22, align 4, !dbg !114
  %24 = load i32, ptr %arg.value, align 4, !dbg !119
  %25 = inttoptr i32 %24 to ptr, !dbg !119
  call void @sn.ua.set(ptr noundef nonnull align 8 dereferenceable(64) %20, i32 %23, ptr %25), !dbg !120
  %26 = load ptr, ptr %arg.self, align 8, !dbg !114
  %27 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %26, i32 0, i32 3, !dbg !114
  %28 = load i32, ptr %27, align 4, !dbg !114
  %29 = load ptr, ptr %arg.self, align 8, !dbg !114
  %30 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %29, i32 0, i32 3, !dbg !114
  %31 = load i32, ptr %30, align 4, !dbg !114
  %32 = add i32 %31, 1, !dbg !121
  store i32 %32, ptr %27, align 4, !dbg !121
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !122 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !123, metadata !DIExpression()), !dbg !124
  %arg.capacity = alloca i32, align 4
  store i32 %1, ptr %arg.capacity, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.capacity, metadata !125, metadata !DIExpression()), !dbg !124
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !124
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 2, !dbg !124
  %4 = load i32, ptr %3, align 4, !dbg !124
  %5 = load i32, ptr %arg.capacity, align 4, !dbg !126
  store i32 %5, ptr %3, align 4, !dbg !126
  %6 = load ptr, ptr %arg.self, align 8, !dbg !124
  %7 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %6, i32 0, i32 4, !dbg !124
  %8 = load ptr, ptr %7, align 8, !dbg !124
  %9 = load ptr, ptr %arg.self, align 8, !dbg !124
  %10 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 4, !dbg !124
  %11 = load ptr, ptr %10, align 8, !dbg !124
  %12 = load ptr, ptr %arg.self, align 8, !dbg !124
  %13 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %12, i32 0, i32 2, !dbg !124
  %14 = load i32, ptr %13, align 4, !dbg !124
  %15 = call ptr @sn.ua.resize(ptr noundef nonnull align 8 dereferenceable(64) %11, i32 %14), !dbg !127
  store ptr %15, ptr %7, align 8, !dbg !127
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !128 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !131, metadata !DIExpression()), !dbg !132
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !132
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1), !dbg !132
  %2 = load ptr, ptr %arg.self, align 8, !dbg !132
  %3 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 1, !dbg !132
  %4 = load i32, ptr %3, align 4, !dbg !132
  store i32 0, ptr %3, align 4, !dbg !133
  %5 = load ptr, ptr %arg.self, align 8, !dbg !132
  %6 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 2, !dbg !132
  %7 = load i32, ptr %6, align 4, !dbg !132
  store i32 10, ptr %6, align 4, !dbg !134
  %8 = load ptr, ptr %arg.self, align 8, !dbg !132
  %9 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %8, i32 0, i32 3, !dbg !132
  %10 = load i32, ptr %9, align 4, !dbg !132
  store i32 0, ptr %9, align 4, !dbg !135
  %11 = load ptr, ptr %arg.self, align 8, !dbg !132
  %12 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %11, i32 0, i32 4, !dbg !132
  %13 = load ptr, ptr %12, align 8, !dbg !132
  %14 = load ptr, ptr %arg.self, align 8, !dbg !132
  %15 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 2, !dbg !132
  %16 = load i32, ptr %15, align 4, !dbg !132
  %17 = call ptr @sn.ua.alloc(i32 %16) #6, !dbg !136
  store ptr %17, ptr %12, align 8, !dbg !136
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE"(i32 %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #1 personality ptr @sn.eh.personality !dbg !137 {
entry:
  %arg.num = alloca i32, align 4
  store i32 %0, ptr %arg.num, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.num, metadata !140, metadata !DIExpression()), !dbg !141
  %arg.format = alloca ptr, align 8
  store ptr %1, ptr %arg.format, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.format, metadata !142, metadata !DIExpression()), !dbg !141
  %var.buffer = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.buffer, metadata !143, metadata !DIExpression()), !dbg !144
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.format, align 8, !dbg !145
  %3 = load i32, ptr %arg.num, align 4, !dbg !146
  %4 = call ptr @"_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE"(i32 10, ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %3) #5, !dbg !147
  store ptr %4, ptr %var.buffer, align 8, !dbg !147
  %5 = load ptr, ptr %var.buffer, align 8, !dbg !148
  %6 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !149
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 0, !dbg !149
  store ptr @"vtable._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, align 8, !dbg !149
  call void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) %5), !dbg !149
  %8 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, align 8, !dbg !149
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %8, !dbg !149
}

; Function Attrs: noinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !150 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !155, metadata !DIExpression()), !dbg !156
  %var.iter = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8
  call void @llvm.dbg.declare(metadata ptr %var.iter, metadata !157, metadata !DIExpression()), !dbg !159
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !156
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !156
  %3 = load i32, ptr %2, align 4, !dbg !156
  %4 = load ptr, ptr %arg.self, align 8, !dbg !156
  %5 = call i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %4) #5, !dbg !160
  %6 = icmp sgt i32 %3, %5, !dbg !160
  br i1 %6, label %7, label %11, !dbg !160

7:                                                ; preds = %body
  %8 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !161
  %9 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE"() #5, !dbg !161
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %9, ptr %8, align 4, !dbg !161
  %10 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %8, align 4, !dbg !161
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %10, !dbg !161

11:                                               ; preds = %body
  br label %12, !dbg !161

12:                                               ; preds = %11
  %13 = load ptr, ptr %arg.self, align 8, !dbg !156
  %14 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 1, !dbg !156
  %15 = load i32, ptr %14, align 4, !dbg !156
  %16 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !156
  %17 = call %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE"(i32 %15) #5, !dbg !162
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %17, ptr %16, align 4, !dbg !162
  %18 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %16, align 4, !dbg !162
  store %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %18, ptr %var.iter, align 4, !dbg !162
  %19 = load ptr, ptr %arg.self, align 8, !dbg !156
  %20 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %19, i32 0, i32 1, !dbg !156
  %21 = load i32, ptr %20, align 4, !dbg !156
  %22 = load ptr, ptr %arg.self, align 8, !dbg !156
  %23 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %22, i32 0, i32 1, !dbg !156
  %24 = load i32, ptr %23, align 4, !dbg !156
  %25 = add i32 %24, 1, !dbg !163
  store i32 %25, ptr %20, align 4, !dbg !163
  %26 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %var.iter, align 4, !dbg !164
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %26, !dbg !164
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !165 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !168, metadata !DIExpression()), !dbg !169
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !169
  %2 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 3, !dbg !169
  %3 = load i32, ptr %2, align 4, !dbg !169
  ret i32 %3, !dbg !169
}

; Function Attrs: noinline
define internal void @"_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1, i32 %2) #0 personality ptr @sn.eh.personality !dbg !170 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !173, metadata !DIExpression()), !dbg !174
  %arg.start = alloca i32, align 4
  store i32 %1, ptr %arg.start, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.start, metadata !175, metadata !DIExpression()), !dbg !174
  %arg.end = alloca i32, align 4
  store i32 %2, ptr %arg.end, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !176, metadata !DIExpression()), !dbg !174
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !174
  call void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !174
  %4 = load ptr, ptr %arg.self, align 8, !dbg !174
  %5 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !174
  %6 = load i32, ptr %5, align 4, !dbg !174
  store i32 0, ptr %5, align 4, !dbg !177
  %7 = load ptr, ptr %arg.self, align 8, !dbg !174
  %8 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %7, i32 0, i32 2, !dbg !174
  %9 = load i32, ptr %8, align 4, !dbg !174
  store i32 0, ptr %8, align 4, !dbg !178
  %10 = load ptr, ptr %arg.self, align 8, !dbg !174
  %11 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 2, !dbg !174
  %12 = load i32, ptr %11, align 4, !dbg !174
  %13 = load i32, ptr %arg.start, align 4, !dbg !179
  store i32 %13, ptr %11, align 4, !dbg !179
  %14 = load ptr, ptr %arg.self, align 8, !dbg !174
  %15 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %14, i32 0, i32 3, !dbg !174
  %16 = load i32, ptr %15, align 4, !dbg !174
  %17 = load i32, ptr %arg.end, align 4, !dbg !180
  store i32 %17, ptr %15, align 4, !dbg !180
  %18 = load ptr, ptr %arg.self, align 8, !dbg !174
  %19 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %18, i32 0, i32 1, !dbg !174
  %20 = load i32, ptr %19, align 4, !dbg !174
  %21 = load ptr, ptr %arg.self, align 8, !dbg !174
  %22 = getelementptr inbounds %"class._$SN&5RangeCv17186ClsGStA1T3i32ClsE", ptr %21, i32 0, i32 2, !dbg !174
  %23 = load i32, ptr %22, align 4, !dbg !174
  store i32 %23, ptr %19, align 4, !dbg !174
  ret void
}

; Function Attrs: noinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !181 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !185, metadata !DIExpression()), !dbg !186
  br label %body

body:                                             ; preds = %entry
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" zeroinitializer
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !187 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !190, metadata !DIExpression()), !dbg !191
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !191
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17187ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 1, !dbg !191
  %3 = load i32, ptr %2, align 4, !dbg !191
  store i32 0, ptr %2, align 4, !dbg !192
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE"(i32 %0) #1 personality ptr @sn.eh.personality !dbg !193 {
entry:
  %arg.val = alloca i32, align 4
  store i32 %0, ptr %arg.val, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.val, metadata !196, metadata !DIExpression()), !dbg !197
  br label %body

body:                                             ; preds = %entry
  %1 = load i32, ptr %arg.val, align 4, !dbg !198
  %2 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !199
  call void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 %1), !dbg !199
  %3 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %2, align 4, !dbg !199
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %3, !dbg !199
}

; Function Attrs: alwaysinline
define internal %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE"() #1 personality ptr @sn.eh.personality !dbg !200 {
entry:
  br label %body

body:                                             ; preds = %entry
  %0 = alloca %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", align 8, !dbg !203
  call void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !203
  %1 = load %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %0, align 4, !dbg !203
  ret %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE" %1, !dbg !203
}

; Function Attrs: alwaysinline
define internal i1 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !204 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !209, metadata !DIExpression()), !dbg !210
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !210
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !210
  %3 = load i1, ptr %2, align 1, !dbg !210
  ret i1 %3, !dbg !210
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !211 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !214, metadata !DIExpression()), !dbg !215
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !215
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !215
  %3 = load i1, ptr %2, align 1, !dbg !215
  %4 = icmp eq i1 %3, false, !dbg !215
  br i1 %4, label %5, label %8, !dbg !215

5:                                                ; preds = %body
  %6 = call ptr @sn.alloca(i32 8), !dbg !216
  call void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %6, ptr noundef nonnull align 8 dereferenceable(64) @.str.4), !dbg !216
  %7 = call ptr @sn.eh.create(ptr %6, i32 1000), !dbg !216
  call void @sn.eh.throw(ptr %7), !dbg !216
  br label %9, !dbg !216

8:                                                ; preds = %body
  br label %9, !dbg !216

9:                                                ; preds = %8, %5
  %10 = load ptr, ptr %arg.self, align 8, !dbg !215
  %11 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %10, i32 0, i32 1, !dbg !215
  %12 = load i32, ptr %11, align 4, !dbg !215
  ret i32 %12, !dbg !215
}

; Function Attrs: noinline
define internal void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, i32 %1) #0 personality ptr @sn.eh.personality !dbg !217 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !220, metadata !DIExpression()), !dbg !221
  %arg.value = alloca i32, align 4
  store i32 %1, ptr %arg.value, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.value, metadata !222, metadata !DIExpression()), !dbg !221
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !221
  %3 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %2, i32 0, i32 0, !dbg !221
  %4 = load i1, ptr %3, align 1, !dbg !221
  store i1 false, ptr %3, align 1, !dbg !223
  %5 = load ptr, ptr %arg.self, align 8, !dbg !221
  %6 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %5, i32 0, i32 1, !dbg !221
  %7 = load i32, ptr %6, align 4, !dbg !221
  %8 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE"() #5, !dbg !224
  store i32 %8, ptr %6, align 4, !dbg !224
  %9 = load ptr, ptr %arg.self, align 8, !dbg !221
  %10 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %9, i32 0, i32 1, !dbg !221
  %11 = load i32, ptr %10, align 4, !dbg !221
  %12 = load i32, ptr %arg.value, align 4, !dbg !225
  store i32 %12, ptr %10, align 4, !dbg !225
  %13 = load ptr, ptr %arg.self, align 8, !dbg !221
  %14 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %13, i32 0, i32 0, !dbg !221
  %15 = load i1, ptr %14, align 1, !dbg !221
  store i1 true, ptr %14, align 1, !dbg !226
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !227 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !230, metadata !DIExpression()), !dbg !231
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !231
  %2 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %1, i32 0, i32 0, !dbg !231
  %3 = load i1, ptr %2, align 1, !dbg !231
  store i1 false, ptr %2, align 1, !dbg !232
  %4 = load ptr, ptr %arg.self, align 8, !dbg !231
  %5 = getelementptr inbounds %"class._$SN&4IterCv17188ClsGStA1T3i32ClsE", ptr %4, i32 0, i32 1, !dbg !231
  %6 = load i32, ptr %5, align 4, !dbg !231
  %7 = call i32 @"_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE"() #5, !dbg !233
  store i32 %7, ptr %5, align 4, !dbg !233
  ret void
}

; Function Attrs: alwaysinline
define internal ptr @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !234 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !237, metadata !DIExpression()), !dbg !238
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !238
  %2 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %1, i32 0, i32 4, !dbg !238
  %3 = load ptr, ptr %2, align 8, !dbg !238
  ret ptr %3, !dbg !238
}

; Function Attrs: noinline
define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1, i32 %2) #0 personality ptr @sn.eh.personality !dbg !239 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !242, metadata !DIExpression()), !dbg !243
  %arg.other = alloca ptr, align 8
  store ptr %1, ptr %arg.other, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.other, metadata !244, metadata !DIExpression()), !dbg !243
  %arg.length = alloca i32, align 4
  store i32 %2, ptr %arg.length, align 4
  call void @llvm.dbg.declare(metadata ptr %arg.length, metadata !245, metadata !DIExpression()), !dbg !243
  br label %body

body:                                             ; preds = %entry
  %3 = load ptr, ptr %arg.self, align 8, !dbg !243
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3), !dbg !243
  %4 = load ptr, ptr %arg.self, align 8, !dbg !243
  %5 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %4, i32 0, i32 1, !dbg !243
  %6 = load i32, ptr %5, align 4, !dbg !243
  store i32 0, ptr %5, align 4, !dbg !246
  %7 = load ptr, ptr %arg.self, align 8, !dbg !243
  %8 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %7, i32 0, i32 2, !dbg !243
  %9 = load i32, ptr %8, align 4, !dbg !243
  store i32 10, ptr %8, align 4, !dbg !247
  %10 = load ptr, ptr %arg.self, align 8, !dbg !243
  %11 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %10, i32 0, i32 3, !dbg !243
  %12 = load i32, ptr %11, align 4, !dbg !243
  store i32 0, ptr %11, align 4, !dbg !248
  %13 = load ptr, ptr %arg.self, align 8, !dbg !243
  %14 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %13, i32 0, i32 4, !dbg !243
  %15 = load ptr, ptr %14, align 8, !dbg !243
  store ptr @.str.5, ptr %14, align 8, !dbg !249
  %16 = load ptr, ptr %arg.self, align 8, !dbg !243
  %17 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %16, i32 0, i32 4, !dbg !243
  %18 = load ptr, ptr %17, align 8, !dbg !243
  %19 = load ptr, ptr %arg.other, align 8, !dbg !250
  store ptr %19, ptr %17, align 8, !dbg !250
  %20 = load ptr, ptr %arg.self, align 8, !dbg !243
  %21 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %20, i32 0, i32 3, !dbg !243
  %22 = load i32, ptr %21, align 4, !dbg !243
  %23 = load i32, ptr %arg.length, align 4, !dbg !251
  store i32 %23, ptr %21, align 4, !dbg !251
  %24 = load ptr, ptr %arg.self, align 8, !dbg !243
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !243
  %26 = load i32, ptr %25, align 4, !dbg !243
  %27 = load i32, ptr %arg.length, align 4, !dbg !243
  %28 = add i32 %27, 10, !dbg !252
  store i32 %28, ptr %25, align 4, !dbg !252
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !253 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !256, metadata !DIExpression()), !dbg !257
  %arg.buffer = alloca ptr, align 8
  store ptr %1, ptr %arg.buffer, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.buffer, metadata !258, metadata !DIExpression()), !dbg !257
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !257
  call void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2), !dbg !257
  %3 = load ptr, ptr %arg.self, align 8, !dbg !257
  %4 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, i32 0, i32 1, !dbg !257
  %5 = load i32, ptr %4, align 4, !dbg !257
  store i32 0, ptr %4, align 4, !dbg !259
  %6 = load ptr, ptr %arg.self, align 8, !dbg !257
  %7 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %6, i32 0, i32 2, !dbg !257
  %8 = load i32, ptr %7, align 4, !dbg !257
  store i32 10, ptr %7, align 4, !dbg !260
  %9 = load ptr, ptr %arg.self, align 8, !dbg !257
  %10 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %9, i32 0, i32 3, !dbg !257
  %11 = load i32, ptr %10, align 4, !dbg !257
  store i32 0, ptr %10, align 4, !dbg !261
  %12 = load ptr, ptr %arg.self, align 8, !dbg !257
  %13 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %12, i32 0, i32 4, !dbg !257
  %14 = load ptr, ptr %13, align 8, !dbg !257
  store ptr @.str.7, ptr %13, align 8, !dbg !262
  %15 = load ptr, ptr %arg.self, align 8, !dbg !257
  %16 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %15, i32 0, i32 4, !dbg !257
  %17 = load ptr, ptr %16, align 8, !dbg !257
  %18 = load ptr, ptr %arg.buffer, align 8, !dbg !263
  store ptr %18, ptr %16, align 8, !dbg !263
  %19 = load ptr, ptr %arg.self, align 8, !dbg !257
  %20 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %19, i32 0, i32 3, !dbg !257
  %21 = load i32, ptr %20, align 4, !dbg !257
  %22 = load ptr, ptr %arg.buffer, align 8, !dbg !264
  %23 = call i32 @strlen(ptr noundef nonnull align 8 dereferenceable(64) %22), !dbg !265
  store i32 %23, ptr %20, align 4, !dbg !265
  %24 = load ptr, ptr %arg.self, align 8, !dbg !257
  %25 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %24, i32 0, i32 2, !dbg !257
  %26 = load i32, ptr %25, align 4, !dbg !257
  %27 = load ptr, ptr %arg.self, align 8, !dbg !257
  %28 = getelementptr inbounds %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %27, i32 0, i32 3, !dbg !257
  %29 = load i32, ptr %28, align 4, !dbg !257
  %30 = add i32 %29, 10, !dbg !266
  store i32 %30, ptr %25, align 4, !dbg !266
  ret void
}

; Function Attrs: noinline
define internal %"class._$SN&4IterCv17019ClsGStA1T4charClsE" @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !267 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !272, metadata !DIExpression()), !dbg !273
  br label %body

body:                                             ; preds = %entry
  ret %"class._$SN&4IterCv17019ClsGStA1T4charClsE" zeroinitializer
}

; Function Attrs: noinline
define internal void @"_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #0 personality ptr @sn.eh.personality !dbg !274 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !277, metadata !DIExpression()), !dbg !278
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !278
  %2 = getelementptr inbounds %"class._$SN&8IterableCv17018ClsGStA1T4charClsE", ptr %1, i32 0, i32 1, !dbg !278
  %3 = load i32, ptr %2, align 4, !dbg !278
  store i32 0, ptr %2, align 4, !dbg !279
  ret void
}

; Function Attrs: noinline
define internal void @"_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #0 personality ptr @sn.eh.personality !dbg !280 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !285, metadata !DIExpression()), !dbg !286
  %arg.m = alloca ptr, align 8
  store ptr %1, ptr %arg.m, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.m, metadata !287, metadata !DIExpression()), !dbg !286
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.self, align 8, !dbg !286
  %3 = getelementptr inbounds %"class._$SN&9ExceptionCv17046ClsE", ptr %2, i32 0, i32 0, !dbg !286
  %4 = load ptr, ptr %3, align 8, !dbg !286
  %5 = load ptr, ptr %arg.m, align 8, !dbg !288
  store ptr %5, ptr %3, align 8, !dbg !288
  ret void
}

; Function Attrs: alwaysinline
define internal %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !289 {
entry:
  %arg.self = alloca ptr, align 8
  store ptr %0, ptr %arg.self, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.self, metadata !293, metadata !DIExpression()), !dbg !294
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.self, align 8, !dbg !295
  %2 = load i32, ptr %1, align 4, !dbg !295
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !296
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE"(i32 %2, ptr noundef nonnull align 8 dereferenceable(64) @.str.11) #5, !dbg !297
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !297
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !297
  ret %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %5, !dbg !297
}

; Function Attrs: noinline
declare noalias noundef nonnull ptr @sn.alloca(i32) #0

; Function Attrs: noinline nounwind
declare noalias noundef nonnull ptr @sn.eh.create(ptr, i32) #3

; Function Attrs: noinline
declare void @sn.eh.throw(ptr) #0

; Function Attrs: noinline
define private ptr @"_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE"(ptr %self, i32 %other) #0 !dbg !298 {
entry:
  %0 = getelementptr i8, ptr %self, i32 %other
  ret ptr %0
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0) #1 personality ptr @sn.eh.personality !dbg !301 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !305, metadata !DIExpression()), !dbg !306
  br label %body

body:                                             ; preds = %entry
  %1 = load ptr, ptr %arg.msg, align 8, !dbg !307
  %2 = call i32 @"_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %1, ptr noundef nonnull align 8 dereferenceable(64) @.str.20) #5, !dbg !308
  ret i32 %2, !dbg !308
}

; Function Attrs: alwaysinline
define internal i32 @"_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0, ptr noundef nonnull align 8 dereferenceable(64) %1) #1 personality ptr @sn.eh.personality !dbg !309 {
entry:
  %arg.msg = alloca ptr, align 8
  store ptr %0, ptr %arg.msg, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.msg, metadata !312, metadata !DIExpression()), !dbg !313
  %arg.end = alloca ptr, align 8
  store ptr %1, ptr %arg.end, align 8
  call void @llvm.dbg.declare(metadata ptr %arg.end, metadata !314, metadata !DIExpression()), !dbg !313
  %var.m = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.m, metadata !315, metadata !DIExpression()), !dbg !316
  br label %body

body:                                             ; preds = %entry
  %2 = load ptr, ptr %arg.msg, align 8, !dbg !317
  %3 = alloca %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", align 8, !dbg !317
  %4 = call %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %2) #5, !dbg !318
  store %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE" %4, ptr %3, align 8, !dbg !318
  %5 = load %"class._$SN&10StringViewCv17017ClsGStA1T4charClsE", ptr %3, align 8, !dbg !318
  %6 = call ptr @"_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %3) #5, !dbg !318
  store ptr %6, ptr %var.m, align 8, !dbg !318
  %7 = load ptr, ptr %var.m, align 8, !dbg !319
  %8 = load ptr, ptr %arg.end, align 8, !dbg !320
  %9 = call i32 (ptr, ...) @printf(ptr noundef nonnull align 8 dereferenceable(64) @.str.21, ptr %7, ptr %8), !dbg !321
  ret i32 %9, !dbg !321
}

; Function Attrs: noinline
define i32 @main() #0 personality ptr @sn.eh.personality !dbg !322 {
entry:
  call void @sn.runtime.initialize()
  %var.a = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %var.a, metadata !323, metadata !DIExpression()), !dbg !324
  br label %body

body:                                             ; preds = %entry
  %0 = call ptr @sn.alloca(i32 32), !dbg !325
  %1 = getelementptr inbounds %"class._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %0, i32 0, i32 0, !dbg !325
  store ptr @"vtable._$SN&6VectorCv17687ClsGStA1T3i32ClsE", ptr %1, align 8, !dbg !325
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %0), !dbg !325
  store ptr %0, ptr %var.a, align 8, !dbg !325
  %2 = load ptr, ptr %var.a, align 8, !dbg !324
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %2, i32 1), !dbg !326
  %3 = load ptr, ptr %var.a, align 8, !dbg !324
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %3, i32 2), !dbg !327
  %4 = load ptr, ptr %var.a, align 8, !dbg !324
  call void @"_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE"(ptr noundef nonnull align 8 dereferenceable(64) %4, i32 3), !dbg !328
  %5 = load ptr, ptr %var.a, align 8, !dbg !329
  %6 = call i32 @"_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE"(ptr noundef nonnull align 8 dereferenceable(64) %5) #5, !dbg !330
  ret i32 0
}

; Function Attrs: alwaysinline nounwind
declare void @sn.runtime.initialize() #4

attributes #0 = { noinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #1 = { alwaysinline "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
attributes #2 = { nocallback nofree noinline nosync nounwind speculatable willreturn memory(none) "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-jump-tables"="false" }
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
!5 = distinct !DISubprogram(name: "Core::CLib::__internal::alloca_and_snprintf", linkageName: "_$SN@sn.Core.CLib.__internal&19alloca_and_snprintfCv17480SaA1T3i32A2T4char.rA3T3i32FnE", scope: !6, file: !6, line: 193, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!6 = !DIFile(filename: "CLib.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !11, !9, !11}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed)
!11 = !DIBasicType(name: "i32", size: 32, encoding: DW_ATE_signed)
!12 = !{}
!13 = !DILocalVariable(name: "bytes", arg: 1, scope: !5, file: !1, line: 193, type: !11)
!14 = !DILocation(line: 193, column: 15, scope: !5)
!15 = !DILocalVariable(name: "format", arg: 2, scope: !5, file: !1, line: 193, type: !9)
!16 = !DILocalVariable(name: "value", arg: 3, scope: !5, file: !1, line: 193, type: !11)
!17 = !DILocalVariable(name: "buffer", scope: !5, file: !1, line: 196, type: !9)
!18 = !DILocation(line: 196, column: 9, scope: !5)
!19 = !DILocation(line: 196, column: 25, scope: !5)
!20 = !DILocation(line: 196, column: 18, scope: !5)
!21 = !DILocation(line: 197, column: 14, scope: !5)
!22 = !DILocation(line: 197, column: 22, scope: !5)
!23 = !DILocation(line: 197, column: 29, scope: !5)
!24 = !DILocation(line: 197, column: 37, scope: !5)
!25 = !DILocation(line: 197, column: 5, scope: !5)
!26 = !DILocation(line: 198, column: 12, scope: !5)
!27 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17208SaFnE", scope: !6, file: !6, line: 123, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!28 = !DISubroutineType(types: !29)
!29 = !{!11}
!30 = !DILocation(line: 124, column: 12, scope: !27)
!31 = distinct !DISubprogram(name: "Core::CLib::null_ptr", linkageName: "_$SN@sn.Core.CLib&8null_ptrCv17200SaFnE", scope: !6, file: !6, line: 123, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!32 = !DILocation(line: 124, column: 12, scope: !31)
!33 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17786SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 644, type: !35, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!34 = !DIFile(filename: "_$core.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !39}
!37 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::StringView<char>", scope: !34, file: !34, line: 529, baseType: !38, elements: !12)
!38 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<char>", scope: !34, file: !34, line: 253, elements: !12)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64)
!40 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Vector<i32>", scope: !34, file: !34, line: 415, baseType: !41, elements: !12)
!41 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iterable<i32>", scope: !34, file: !34, line: 253, elements: !12)
!42 = !DILocalVariable(name: "buffer", arg: 1, scope: !33, file: !1, line: 644, type: !39)
!43 = !DILocation(line: 644, column: 15, scope: !33)
!44 = !DILocation(line: 645, column: 33, scope: !33)
!45 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::to_string", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&9to_stringCv17789SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 496, type: !35, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!46 = !DILocalVariable(name: "self", arg: 1, scope: !45, file: !1, line: 496, type: !39)
!47 = !DILocation(line: 496, column: 8, scope: !45)
!48 = !DILocalVariable(name: "result", scope: !45, file: !1, line: 497, type: !49)
!49 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::StringView<char>", scope: !34, file: !34, line: 529, baseType: !38, elements: !12)
!50 = !DILocation(line: 497, column: 15, scope: !45)
!51 = !DILocalVariable(name: "$iter", scope: !45, file: !1, line: 498, type: !52)
!52 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Range<i32>", scope: !34, file: !34, line: 342, baseType: !41, elements: !12)
!53 = !DILocation(line: 498, column: 17, scope: !45)
!54 = !DILocalVariable(name: "$iter_value", scope: !45, file: !1, line: 498, type: !55)
!55 = !DICompositeType(tag: DW_TAG_structure_type, name: "mut Core::_$core::Core::Iter<i32>", scope: !34, file: !34, line: 285, elements: !12)
!56 = !DILocalVariable(name: "i", scope: !45, file: !1, line: 498, type: !11)
!57 = !DILocation(line: 497, column: 28, scope: !45)
!58 = !DILocation(line: 499, column: 48, scope: !45)
!59 = !DILocation(line: 499, column: 40, scope: !45)
!60 = !DILocation(line: 499, column: 27, scope: !45)
!61 = !DILocation(line: 499, column: 25, scope: !45)
!62 = !DILocation(line: 500, column: 31, scope: !45)
!63 = !DILocation(line: 504, column: 14, scope: !45)
!64 = !DILocation(line: 501, column: 33, scope: !45)
!65 = !DILocation(line: 501, column: 27, scope: !45)
!66 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::operator +", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE", scope: !34, file: !34, line: 599, type: !67, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!67 = !DISubroutineType(types: !68)
!68 = !{!37, !69, !37}
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64)
!70 = !DILocalVariable(name: "self", arg: 1, scope: !66, file: !1, line: 599, type: !69)
!71 = !DILocation(line: 599, column: 14, scope: !66)
!72 = !DILocalVariable(name: "other", arg: 2, scope: !66, file: !1, line: 599, type: !37)
!73 = !DILocalVariable(name: "len1", scope: !66, file: !1, line: 601, type: !11)
!74 = !DILocation(line: 601, column: 11, scope: !66)
!75 = !DILocalVariable(name: "len2", scope: !66, file: !1, line: 602, type: !11)
!76 = !DILocation(line: 602, column: 11, scope: !66)
!77 = !DILocalVariable(name: "sum", scope: !66, file: !1, line: 603, type: !11)
!78 = !DILocation(line: 603, column: 11, scope: !66)
!79 = !DILocalVariable(name: "buffer", scope: !66, file: !1, line: 604, type: !9)
!80 = !DILocation(line: 604, column: 11, scope: !66)
!81 = !DILocation(line: 603, column: 24, scope: !66)
!82 = !DILocation(line: 604, column: 33, scope: !66)
!83 = !DILocation(line: 604, column: 20, scope: !66)
!84 = !DILocation(line: 605, column: 20, scope: !66)
!85 = !DILocation(line: 605, column: 41, scope: !66)
!86 = !DILocation(line: 605, column: 7, scope: !66)
!87 = !DILocation(line: 606, column: 29, scope: !66)
!88 = !DILocation(line: 606, column: 27, scope: !66)
!89 = !DILocation(line: 606, column: 49, scope: !66)
!90 = !DILocation(line: 606, column: 7, scope: !66)
!91 = !DILocation(line: 607, column: 40, scope: !66)
!92 = !DILocation(line: 607, column: 48, scope: !66)
!93 = !DILocation(line: 607, column: 18, scope: !66)
!94 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::from", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4fromCv17805SaA1T3i32FnE", scope: !34, file: !34, line: 644, type: !95, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!95 = !DISubroutineType(types: !96)
!96 = !{!37, !11}
!97 = !DILocalVariable(name: "buffer", arg: 1, scope: !94, file: !1, line: 644, type: !11)
!98 = !DILocation(line: 644, column: 15, scope: !94)
!99 = !DILocation(line: 645, column: 33, scope: !94)
!100 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::at", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&2atCv17729SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !34, file: !34, line: 454, type: !101, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!101 = !DISubroutineType(types: !102)
!102 = !{!11, !39, !11}
!103 = !DILocalVariable(name: "self", arg: 1, scope: !100, file: !1, line: 454, type: !39)
!104 = !DILocation(line: 454, column: 8, scope: !100)
!105 = !DILocalVariable(name: "index", arg: 2, scope: !100, file: !1, line: 454, type: !11)
!106 = !DILocation(line: 456, column: 18, scope: !100)
!107 = !DILocation(line: 458, column: 19, scope: !100)
!108 = !DILocation(line: 460, column: 40, scope: !100)
!109 = !DILocation(line: 460, column: 14, scope: !100)
!110 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::push", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4pushCv17705SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !34, file: !34, line: 427, type: !111, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!111 = !DISubroutineType(types: !112)
!112 = !{null, !39, !11}
!113 = !DILocalVariable(name: "self", arg: 1, scope: !110, file: !1, line: 427, type: !39)
!114 = !DILocation(line: 427, column: 8, scope: !110)
!115 = !DILocalVariable(name: "value", arg: 2, scope: !110, file: !1, line: 427, type: !11)
!116 = !DILocation(line: 429, column: 24, scope: !110)
!117 = !DILocation(line: 431, column: 37, scope: !110)
!118 = !DILocation(line: 431, column: 9, scope: !110)
!119 = !DILocation(line: 433, column: 46, scope: !110)
!120 = !DILocation(line: 433, column: 7, scope: !110)
!121 = !DILocation(line: 434, column: 35, scope: !110)
!122 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::resize", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&6resizeCv17710SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !34, file: !34, line: 444, type: !111, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!123 = !DILocalVariable(name: "self", arg: 1, scope: !122, file: !1, line: 444, type: !39)
!124 = !DILocation(line: 444, column: 8, scope: !122)
!125 = !DILocalVariable(name: "capacity", arg: 2, scope: !122, file: !1, line: 444, type: !11)
!126 = !DILocation(line: 446, column: 23, scope: !122)
!127 = !DILocation(line: 447, column: 21, scope: !122)
!128 = distinct !DISubprogram(name: "Core::_$core::Core::Vector<i32>::constructor", linkageName: "_$SN&6VectorCv17687ClsGStA1T3i32ClsE&4#NwCCv17699SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 421, type: !129, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!129 = !DISubroutineType(types: !130)
!130 = !{null, !39}
!131 = !DILocalVariable(name: "self", arg: 1, scope: !128, file: !1, line: 421, type: !39)
!132 = !DILocation(line: 421, column: 5, scope: !128)
!133 = !DILocation(line: 255, column: 31, scope: !128)
!134 = !DILocation(line: 509, column: 29, scope: !128)
!135 = !DILocation(line: 511, column: 27, scope: !128)
!136 = !DILocation(line: 422, column: 14, scope: !128)
!137 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::fromNumber", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&10fromNumberCv17472SaA1T3i32A2T4char.rFnE", scope: !34, file: !34, line: 631, type: !138, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!138 = !DISubroutineType(types: !139)
!139 = !{!37, !11, !9}
!140 = !DILocalVariable(name: "num", arg: 1, scope: !137, file: !1, line: 631, type: !11)
!141 = !DILocation(line: 631, column: 15, scope: !137)
!142 = !DILocalVariable(name: "format", arg: 2, scope: !137, file: !1, line: 631, type: !9)
!143 = !DILocalVariable(name: "buffer", scope: !137, file: !1, line: 634, type: !9)
!144 = !DILocation(line: 634, column: 11, scope: !137)
!145 = !DILocation(line: 635, column: 51, scope: !137)
!146 = !DILocation(line: 635, column: 59, scope: !137)
!147 = !DILocation(line: 635, column: 9, scope: !137)
!148 = !DILocation(line: 636, column: 40, scope: !137)
!149 = !DILocation(line: 636, column: 18, scope: !137)
!150 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::next", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4nextCv17295SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 381, type: !151, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!151 = !DISubroutineType(types: !152)
!152 = !{!55, !153}
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64)
!154 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Range<i32>", scope: !34, file: !34, line: 342, baseType: !41, elements: !12)
!155 = !DILocalVariable(name: "self", arg: 1, scope: !150, file: !1, line: 381, type: !153)
!156 = !DILocation(line: 381, column: 13, scope: !150)
!157 = !DILocalVariable(name: "iter", scope: !150, file: !1, line: 387, type: !158)
!158 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<i32>", scope: !34, file: !34, line: 285, elements: !12)
!159 = !DILocation(line: 387, column: 11, scope: !150)
!160 = !DILocation(line: 383, column: 28, scope: !150)
!161 = !DILocation(line: 385, column: 16, scope: !150)
!162 = !DILocation(line: 387, column: 18, scope: !150)
!163 = !DILocation(line: 388, column: 43, scope: !150)
!164 = !DILocation(line: 389, column: 14, scope: !150)
!165 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::end", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&3endCv17291SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 375, type: !166, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!166 = !DISubroutineType(types: !167)
!167 = !{!11, !153}
!168 = !DILocalVariable(name: "self", arg: 1, scope: !165, file: !1, line: 375, type: !153)
!169 = !DILocation(line: 375, column: 8, scope: !165)
!170 = distinct !DISubprogram(name: "Core::_$core::Core::Range<i32>::constructor", linkageName: "_$SN&5RangeCv17186ClsGStA1T3i32ClsE&4#NwCCv17265SaA1_$SN&5RangeCv17186ClsGStA1T3i32ClsE.rA2T3i32A3T3i32FnE", scope: !34, file: !34, line: 349, type: !171, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!171 = !DISubroutineType(types: !172)
!172 = !{null, !153, !11, !11}
!173 = !DILocalVariable(name: "self", arg: 1, scope: !170, file: !1, line: 349, type: !153)
!174 = !DILocation(line: 349, column: 5, scope: !170)
!175 = !DILocalVariable(name: "start", arg: 2, scope: !170, file: !1, line: 349, type: !11)
!176 = !DILocalVariable(name: "end", arg: 3, scope: !170, file: !1, line: 349, type: !11)
!177 = !DILocation(line: 255, column: 31, scope: !170)
!178 = !DILocation(line: 398, column: 32, scope: !170)
!179 = !DILocation(line: 350, column: 23, scope: !170)
!180 = !DILocation(line: 350, column: 36, scope: !170)
!181 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::next", linkageName: "_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4nextCv17243SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 268, type: !182, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!182 = !DISubroutineType(types: !183)
!183 = !{!158, !184}
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64)
!185 = !DILocalVariable(name: "self", arg: 1, scope: !181, file: !1, line: 268, type: !184)
!186 = !DILocation(line: 268, column: 13, scope: !181)
!187 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<i32>::constructor", linkageName: "_$SN&8IterableCv17187ClsGStA1T3i32ClsE&4#NwCCv17238SaA1_$SN&8IterableCv17187ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 263, type: !188, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!188 = !DISubroutineType(types: !189)
!189 = !{null, !184}
!190 = !DILocalVariable(name: "self", arg: 1, scope: !187, file: !1, line: 263, type: !184)
!191 = !DILocation(line: 263, column: 5, scope: !187)
!192 = !DILocation(line: 255, column: 31, scope: !187)
!193 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::valid", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&5validCv17223SaA1T3i32FnE", scope: !34, file: !34, line: 331, type: !194, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!194 = !DISubroutineType(types: !195)
!195 = !{!158, !11}
!196 = !DILocalVariable(name: "val", arg: 1, scope: !193, file: !1, line: 331, type: !11)
!197 = !DILocation(line: 331, column: 15, scope: !193)
!198 = !DILocation(line: 332, column: 40, scope: !193)
!199 = !DILocation(line: 332, column: 20, scope: !193)
!200 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::invalid", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&7invalidCv17221SaFnE", scope: !34, file: !34, line: 325, type: !201, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!201 = !DISubroutineType(types: !202)
!202 = !{!158}
!203 = !DILocation(line: 326, column: 20, scope: !200)
!204 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::is_valid", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&8is_validCv17217SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 318, type: !205, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!205 = !DISubroutineType(types: !206)
!206 = !{!207, !208}
!207 = !DIBasicType(name: "bool", size: 8, encoding: DW_ATE_signed)
!208 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64)
!209 = !DILocalVariable(name: "self", arg: 1, scope: !204, file: !1, line: 318, type: !208)
!210 = !DILocation(line: 318, column: 8, scope: !204)
!211 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::value", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&5valueCv17210SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 306, type: !212, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!212 = !DISubroutineType(types: !213)
!213 = !{!11, !208}
!214 = !DILocalVariable(name: "self", arg: 1, scope: !211, file: !1, line: 306, type: !208)
!215 = !DILocation(line: 306, column: 8, scope: !211)
!216 = !DILocation(line: 310, column: 19, scope: !211)
!217 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17202SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rA2T3i32FnE", scope: !34, file: !34, line: 300, type: !218, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!218 = !DISubroutineType(types: !219)
!219 = !{null, !208, !11}
!220 = !DILocalVariable(name: "self", arg: 1, scope: !217, file: !1, line: 300, type: !208)
!221 = !DILocation(line: 300, column: 5, scope: !217)
!222 = !DILocalVariable(name: "value", arg: 2, scope: !217, file: !1, line: 300, type: !11)
!223 = !DILocation(line: 287, column: 24, scope: !217)
!224 = !DILocation(line: 289, column: 33, scope: !217)
!225 = !DILocation(line: 300, column: 41, scope: !217)
!226 = !DILocation(line: 301, column: 14, scope: !217)
!227 = distinct !DISubprogram(name: "Core::_$core::Core::Iter<i32>::constructor", linkageName: "_$SN&4IterCv17188ClsGStA1T3i32ClsE&4#NwCCv17196SaA1_$SN&4IterCv17188ClsGStA1T3i32ClsE.rFnE", scope: !34, file: !34, line: 295, type: !228, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!228 = !DISubroutineType(types: !229)
!229 = !{null, !208}
!230 = !DILocalVariable(name: "self", arg: 1, scope: !227, file: !1, line: 295, type: !208)
!231 = !DILocation(line: 295, column: 5, scope: !227)
!232 = !DILocation(line: 287, column: 24, scope: !227)
!233 = !DILocation(line: 289, column: 33, scope: !227)
!234 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::c_str", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&5c_strCv17176SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rFnE", scope: !34, file: !34, line: 569, type: !235, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!235 = !DISubroutineType(types: !236)
!236 = !{!9, !69}
!237 = !DILocalVariable(name: "self", arg: 1, scope: !234, file: !1, line: 569, type: !69)
!238 = !DILocation(line: 569, column: 8, scope: !234)
!239 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17161SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rA3T3i32FnE", scope: !34, file: !34, line: 558, type: !240, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!240 = !DISubroutineType(types: !241)
!241 = !{null, !69, !9, !11}
!242 = !DILocalVariable(name: "self", arg: 1, scope: !239, file: !1, line: 558, type: !69)
!243 = !DILocation(line: 558, column: 5, scope: !239)
!244 = !DILocalVariable(name: "other", arg: 2, scope: !239, file: !1, line: 558, type: !9)
!245 = !DILocalVariable(name: "length", arg: 3, scope: !239, file: !1, line: 558, type: !11)
!246 = !DILocation(line: 255, column: 31, scope: !239)
!247 = !DILocation(line: 617, column: 29, scope: !239)
!248 = !DILocation(line: 619, column: 27, scope: !239)
!249 = !DILocation(line: 621, column: 30, scope: !239)
!250 = !DILocation(line: 559, column: 23, scope: !239)
!251 = !DILocation(line: 559, column: 38, scope: !239)
!252 = !DILocation(line: 560, column: 25, scope: !239)
!253 = distinct !DISubprogram(name: "Core::_$core::Core::StringView<char>::constructor", linkageName: "_$SN&10StringViewCv17017ClsGStA1T4charClsE&4#NwCCv17141SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2T4char.rFnE", scope: !34, file: !34, line: 543, type: !254, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!254 = !DISubroutineType(types: !255)
!255 = !{null, !69, !9}
!256 = !DILocalVariable(name: "self", arg: 1, scope: !253, file: !1, line: 543, type: !69)
!257 = !DILocation(line: 543, column: 5, scope: !253)
!258 = !DILocalVariable(name: "buffer", arg: 2, scope: !253, file: !1, line: 543, type: !9)
!259 = !DILocation(line: 255, column: 31, scope: !253)
!260 = !DILocation(line: 617, column: 29, scope: !253)
!261 = !DILocation(line: 619, column: 27, scope: !253)
!262 = !DILocation(line: 621, column: 30, scope: !253)
!263 = !DILocation(line: 544, column: 23, scope: !253)
!264 = !DILocation(line: 544, column: 62, scope: !253)
!265 = !DILocation(line: 544, column: 39, scope: !253)
!266 = !DILocation(line: 545, column: 39, scope: !253)
!267 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::next", linkageName: "_$SN&8IterableCv17018ClsGStA1T4charClsE&4nextCv17106SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE", scope: !34, file: !34, line: 268, type: !268, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!268 = !DISubroutineType(types: !269)
!269 = !{!270, !271}
!270 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Iter<char>", scope: !34, file: !34, line: 285, elements: !12)
!271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64)
!272 = !DILocalVariable(name: "self", arg: 1, scope: !267, file: !1, line: 268, type: !271)
!273 = !DILocation(line: 268, column: 13, scope: !267)
!274 = distinct !DISubprogram(name: "Core::_$core::Core::Iterable<char>::constructor", linkageName: "_$SN&8IterableCv17018ClsGStA1T4charClsE&4#NwCCv17101SaA1_$SN&8IterableCv17018ClsGStA1T4charClsE.rFnE", scope: !34, file: !34, line: 263, type: !275, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!275 = !DISubroutineType(types: !276)
!276 = !{null, !271}
!277 = !DILocalVariable(name: "self", arg: 1, scope: !274, file: !1, line: 263, type: !271)
!278 = !DILocation(line: 263, column: 5, scope: !274)
!279 = !DILocation(line: 255, column: 31, scope: !274)
!280 = distinct !DISubprogram(name: "Core::_$core::Core::Exception::constructor", linkageName: "_$SN&9ExceptionCv17046ClsE&4#NwCCv17051SaA1_$SN&9ExceptionCv17046ClsE.rA2T4char.rFnE", scope: !34, file: !34, line: 216, type: !281, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!281 = !DISubroutineType(types: !282)
!282 = !{null, !283, !9}
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !284, size: 64)
!284 = !DICompositeType(tag: DW_TAG_structure_type, name: "Core::_$core::Core::Exception", scope: !34, file: !34, line: 210, elements: !12)
!285 = !DILocalVariable(name: "self", arg: 1, scope: !280, file: !1, line: 216, type: !283)
!286 = !DILocation(line: 216, column: 5, scope: !280)
!287 = !DILocalVariable(name: "m", arg: 2, scope: !280, file: !1, line: 216, type: !9)
!288 = !DILocation(line: 216, column: 31, scope: !280)
!289 = distinct !DISubprogram(name: "i32::to_string", linkageName: "_$SNT3i32&9to_stringCv17462SaA1T3i32.rFnE", scope: !34, file: !34, line: 63, type: !290, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!290 = !DISubroutineType(types: !291)
!291 = !{!37, !292}
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!293 = !DILocalVariable(name: "self", arg: 1, scope: !289, file: !1, line: 63, type: !292)
!294 = !DILocation(line: 63, column: 8, scope: !289)
!295 = !DILocation(line: 64, column: 36, scope: !289)
!296 = !DILocation(line: 64, column: 42, scope: !289)
!297 = !DILocation(line: 64, column: 16, scope: !289)
!298 = distinct !DISubprogram(name: "char::operator +", linkageName: "_$SNT4char&3#PlCv17369SaA1T4char.rA2T3i32FnE", scope: !34, file: !34, line: 19, type: !299, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!299 = !DISubroutineType(types: !300)
!300 = !{!9, !9, !11}
!301 = distinct !DISubprogram(name: "Core::System::println", linkageName: "_$SN@sn.Core.System&7printlnCv17775SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rFnE", scope: !302, file: !302, line: 27, type: !303, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!302 = !DIFile(filename: "System.sn", directory: "/home/mauro/work/snowball/bin/Debug/../../stdlib")
!303 = !DISubroutineType(types: !304)
!304 = !{!11, !39}
!305 = !DILocalVariable(name: "msg", arg: 1, scope: !301, file: !1, line: 27, type: !39)
!306 = !DILocation(line: 27, column: 15, scope: !301)
!307 = !DILocation(line: 28, column: 20, scope: !301)
!308 = !DILocation(line: 28, column: 14, scope: !301)
!309 = distinct !DISubprogram(name: "Core::System::print", linkageName: "_$SN@sn.Core.System&5printCv17779SaA1_$SN&6VectorCv17687ClsGStA1T3i32ClsE.rA2T4char.rFnE", scope: !302, file: !302, line: 16, type: !310, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!310 = !DISubroutineType(types: !311)
!311 = !{!11, !39, !9}
!312 = !DILocalVariable(name: "msg", arg: 1, scope: !309, file: !1, line: 16, type: !39)
!313 = !DILocation(line: 16, column: 15, scope: !309)
!314 = !DILocalVariable(name: "end", arg: 2, scope: !309, file: !1, line: 16, type: !9)
!315 = !DILocalVariable(name: "m", scope: !309, file: !1, line: 17, type: !9)
!316 = !DILocation(line: 17, column: 9, scope: !309)
!317 = !DILocation(line: 17, column: 26, scope: !309)
!318 = !DILocation(line: 17, column: 13, scope: !309)
!319 = !DILocation(line: 18, column: 33, scope: !309)
!320 = !DILocation(line: 18, column: 36, scope: !309)
!321 = !DILocation(line: 18, column: 12, scope: !309)
!322 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 19, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !12)
!323 = !DILocalVariable(name: "a", scope: !322, file: !1, line: 20, type: !39)
!324 = !DILocation(line: 20, column: 13, scope: !322)
!325 = !DILocation(line: 20, column: 21, scope: !322)
!326 = !DILocation(line: 21, column: 5, scope: !322)
!327 = !DILocation(line: 22, column: 5, scope: !322)
!328 = !DILocation(line: 23, column: 5, scope: !322)
!329 = !DILocation(line: 24, column: 21, scope: !322)
!330 = !DILocation(line: 24, column: 5, scope: !322)
/usr/bin/ld: /home/mauro/work/snowball/.sn/bin/out.o.so: in function `_$SN&10StringViewCv17017ClsGStA1T4charClsE&3#PlCv17809SaA1_$SN&10StringViewCv17017ClsGStA1T4charClsE.rA2_$SN&10StringViewCv17017ClsGStA1T4charClsEFnE':
/home/mauro/work/snowball/bin/Debug/../../stdlib/_$core.sn:605: undefined reference to `memcpy.1'
[1;31merror[0m: ([1;31mLinker Error[0m) [1mLinking with /usr/bin/ld failed with code 256[0m
