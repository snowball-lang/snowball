set_project("Snowball")
set_version("1.0.0")

set_languages("c++latest")

-- Config and template files
set_configdir("$(buildir)/config")
set_configvar("SN_VERSION", "$(version)")
add_configfiles("templates/config.h.in")

set_toolchains("clang", "@muslcc")

set_license("MIT")

add_rules("mode.debug", "mode.release")

-- Set all possible warnings
set_warnings("all", "error")

-- Setup for debug symbols and optimization
if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
else
    set_symbols("hidden")
    set_optimize("fastest")
    set_strip("all")
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
    set_kind("shared")
    add_files("src/*.cppm")
    add_platform_specific_flags()
target_end()

