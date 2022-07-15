
project(SNLibs)
set(children
    "system")
foreach(child ${children})
    add_subdirectory(${child})
endforeach()
