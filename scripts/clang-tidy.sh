
cc_files=$(find src/ -name "*.cc")

run_clang_tidy() {
  clang-tidy $@ --fix --fix-errors -p $(pwd)/compile_commands.json --quiet
}

# First the source files
run_clang_tidy "$cc_files"

