
#include <stdio.h>
#include <cassert>

#include "common.h"

#ifndef TEST_CHECK
#define TEST_CHECK(value) (value)
#endif

#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED   "\033[1;31m"
#define COLOR_GRAY  "\033[1;30m"
#define COLOR_BLUE  "\033[1;34m"
#define COLOR_RESET "\033[0m"

#define PREFIX ":: "

extern "C" {
void snowball_test(bool(*test)(), const char* name, 
  unsigned int count, unsigned int max_count, unsigned int* succ_count)
  __asm__(SNOWBALL_TEST_EXPORT) SNOWBALL_RT_VISIBILITY;   
void snowball_test_pre_run(unsigned int max_count) 
  __asm__(SNOWBALL_TEST_PRE_RUN) SNOWBALL_RT_VISIBILITY;
void snowball_test_post_run(unsigned int succ_count, unsigned int max_count) 
  __asm__(SNOWBALL_TEST_POST_RUN) SNOWBALL_RT_VISIBILITY;
}

namespace snowball {

bool test_success(bool(*test)()) {
  return TEST_CHECK(test());
}

void print_header(const char* name, unsigned int count, 
    unsigned int max_count) {
  printf("%s" PREFIX "%s%s[ %u/%u ] %s%s ... ", 
    COLOR_GRAY, COLOR_RESET, COLOR_GRAY, count + 1, max_count, name, COLOR_RESET);
}

void print_success() {
  printf("%sok!%s\n", COLOR_GREEN, COLOR_RESET);
}

void print_failure() {
  printf("%sfail%s\n", COLOR_RED, COLOR_RESET);
}

void post_test(bool success, const char* name, unsigned int count, 
    unsigned int max_count) {
  if (success) {
    print_success();
    return;
  }
  print_failure();
}

void run_test(bool(*test)(), const char* name = nullptr, 
  unsigned int count = 0, unsigned int max_count = 0, 
  unsigned int* succ_count = nullptr) {
  assert(test && "Test function must not be null");
  assert(name && "Test name must not be null");
  print_header(name, count, max_count);
  bool success = test_success(test);
  post_test(success, name, count, max_count);
  if (success && succ_count) {
    *succ_count += 1;
  }
}

void tests_pre_run(unsigned int max_count) {
  printf("\n%s" PREFIX "%sRunning %s%u%s tests. Good Luck!\n", 
    COLOR_GRAY, COLOR_RESET, COLOR_BLUE, max_count, COLOR_RESET);
  printf("%s" PREFIX "%s\n", COLOR_GRAY, COLOR_RESET);
}

void tests_post_run(unsigned int succ_count, unsigned int max_count) {
  printf("%s" PREFIX "%s\n", COLOR_GRAY, COLOR_RESET);
  printf("%s" PREFIX "%s%s%u%s out of %u tests passed.\n", 
    COLOR_GRAY, COLOR_RESET, COLOR_GREEN, succ_count, COLOR_RESET, max_count);
}

} // namespace snowball

void snowball_test(bool(*test)(), const char* name, 
  unsigned int count, unsigned int max_count, unsigned int* succ_count) {
  snowball::run_test(test, name, count, max_count, succ_count);
}

void snowball_test_pre_run(unsigned int max_count) {
  snowball::tests_pre_run(max_count);
}

void snowball_test_post_run(unsigned int succ_count, unsigned int max_count) {
  snowball::tests_post_run(succ_count, max_count);
}
