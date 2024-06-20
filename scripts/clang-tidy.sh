
cc_files=$(find src/ -name "*.cc")
header_files=$(find src/ -name "*.h")

run_clang_tidy() {
  clang-tidy $1 --fix --fix-errors -p $(pwd)/compile_commands.json
}

run_clang_on_files() {
  for file in $1; do
    run_clang_tidy $file
  done
}

# First the source files
run_clang_on_files $cc_files

# Then the header files
run_clang_on_files $header_files
