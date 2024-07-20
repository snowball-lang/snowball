includes("@builtin/check")

set_project("Snowball")
set_version("1.0.0")

set_languages("c++latest")

-- Config and template files
set_configdir("$(buildir)/config")
set_configvar("SN_VERSION", "$(version)")
add_configfiles("templates/config.h.in")

add_requires("llvm 18.x", {
    alias = "llvm-18", debug = true, 
    system = false, kind = "library", 
    configs = {
        lld = true,
        polly = true,

        mlir = false,
        flang = false,
        clang = false,
        lldb = false,
        compiler_rt = false,
        libcxx = false,
        libcxxabi = false,
        libunwind = false,
        openmp = false,
        libclc = false,
        libomptarget = false,
        clang_tools_extra = false,
        bolt = false,
        openmp = false,
    }
})

set_toolchains("clang@llvm-18")

set_license("MIT")

add_rules("mode.debug", "mode.release")

-- Setup for debug symbols and optimization
if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
else
    set_symbols("hidden")
    set_optimize("fastest")
    set_strip("all")
    set_policy("build.optimization.lto", true)
end

-- Function to add platform-specific flags
function add_platform_specific_flags()
    if is_plat("windows") then
        add_cxxflags("/EHsc")
    else
        -- Add flags for e.g. linux here
    end
end

target("snowball")
    add_packages("llvm-18", {public = true})

    set_kind("binary")
    add_files("src/**.cpp")
    add_files("src/**.cppm", { install = true })
    add_platform_specific_flags()
    add_includedirs("src")
    set_policy("build.c++.modules", true)
    set_policy("build.c++.clang.fallbackscanner", true)
    set_policy("build.c++.modules.std", true)
    add_rules("plugin.compile_commands.autoupdate")

    configvar_check_ctypes("SN_HAS_WCHAR", "wchar_t")

    configvar_check_cincludes("SN_HAS_STRING_H", "string.h")
    configvar_check_cincludes("SN_HAS_STDIO_H", "stdio.h")

    check_csnippets("SN_HAS_INT_4", "return (sizeof(int) == 4)? 0: -1;", {tryrun = true})
    check_csnippets("SN_INT_SIZE",'printf("%d", sizeof(int)); return 0;', {output = true, number = true})
    configvar_check_csnippets("SN_HAS_LONG_8", "return (sizeof(long) == 8)? 0: -1;", {tryrun = true})
    configvar_check_csnippets("SN_PTR_SIZE",'printf("%d", sizeof(void*)); return 0;', {output = true, number = true})

    configvar_check_features("SN_HAS_CONSTEXPR", "cxx_constexpr")

    set_runtimes("c++_shared")
target_end()
