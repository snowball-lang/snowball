
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

#define COLOR_BOLD_BLK  "\033[1;30m"

#define COLOR_GRN_BG "\e[0;102m"
#define COLOR_RED_BG "\e[0;101m"

#define CLEAR_LINE "\33[2K\r"
#define GO_UP      "\033[A"

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

static bool test_success(bool(*test)()) {
  return TEST_CHECK(test());
}

static void print_test_results(unsigned int succ_count, unsigned int max_count, 
    unsigned int curr_count) {
  printf(CLEAR_LINE "Results: %s%u%s out of %s%u%s tests passed.", 
    COLOR_GREEN, succ_count, COLOR_RESET, COLOR_BLUE, max_count, COLOR_RESET);
  if (succ_count < curr_count) {
    printf(" But %s%u%s tests failed.", COLOR_RED, curr_count - succ_count, COLOR_RESET);
  }
  printf("\n");
  if (curr_count < max_count) {
    // Convert them into percentages
    curr_count = (curr_count * 20) / max_count;
    max_count = 20;
    printf("       [" COLOR_GREEN);
    for (unsigned int i = 0; i < curr_count; i++)
      printf("█");
    printf(COLOR_RESET);
    for (unsigned int i = 0; i < max_count - curr_count; i++)
      printf("▁");
    printf("]\n");
  }
  fflush(stdout);
}

static void clear_test_results(unsigned int max_count, unsigned int curr_count, bool with_header = false) {
  if (curr_count < max_count) {
    printf(CLEAR_LINE);
  }
  if (with_header) {
    printf(GO_UP CLEAR_LINE);
    printf(GO_UP CLEAR_LINE);
  }
  printf(GO_UP CLEAR_LINE);
  printf(GO_UP CLEAR_LINE);
  fflush(stdout);
}

static void print_test_header(const char* name, unsigned int count, 
    unsigned int max_count, int success) {
  printf("[");
  switch (success) {
    case -1:
      printf(COLOR_BOLD_BLK " RUN  ");
      break;
    case 0:
      printf(COLOR_RED_BG " ERR  ");
      break;
    case 1:
      printf(COLOR_GRN_BG " NICE ");
      break;
  }
  printf(COLOR_RESET "] %s%s%s (%u/%u)\n", COLOR_GRAY, name, COLOR_RESET, 
    count, max_count);
  fflush(stdout);
}

static void run_test(bool(*test)(), const char* name = nullptr, 
  unsigned int count = 0, unsigned int max_count = 0, 
  unsigned int* succ_count = nullptr) {
  assert(test && "Test function must not be null");
  assert(name && "Test name must not be null");
  clear_test_results(max_count, count);
  print_test_header(name, count, max_count, -1);
  printf("\n");
  print_test_results(*succ_count, max_count, count);
  bool success = test_success(test);
  clear_test_results(max_count, count, true);
  print_test_header(name, count, max_count, success);
  print_test_results(*succ_count, max_count, count);
  if (success && succ_count) {
    *succ_count += 1;
  }
}

static void tests_pre_run(unsigned int max_count) {
  printf("\nRunning %s%u%s tests. Good Luck!\n", 
    COLOR_BLUE, max_count, COLOR_RESET);
  printf("\n");
  print_test_results(0, max_count, 0);
}     

static void tests_post_run(unsigned int succ_count, unsigned int max_count) {
  clear_test_results(max_count, max_count);
  printf("\n");
  printf("All tests are done!\n");
  print_test_results(succ_count, max_count, max_count);
  printf("\n");
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
