set -ex
cc_files=$(find src/ -name "*.cc")

run_clang_tidy() {
  clang-tidy $1 --fix --fix-errors -p $(pwd)/compile_commands.json
}

# First the source files
run_clang_tidy "$cc_files"

