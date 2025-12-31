#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part1.c"

#define MAKE_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    int64_t result = solve(input, strlen(input)); \
    munit_assert_int64(result, ==, expected); \
    return MUNIT_OK; \
}

MAKE_TEST_FUNC(test_solve_01, "(())", 0);
MAKE_TEST_FUNC(test_solve_02, "()()", 0);
MAKE_TEST_FUNC(test_solve_03, "(((", 3);
MAKE_TEST_FUNC(test_solve_04, "(()(()(", 3);
MAKE_TEST_FUNC(test_solve_05, "))(((((", 3);
MAKE_TEST_FUNC(test_solve_06, "())", -1);
MAKE_TEST_FUNC(test_solve_07, "))(", -1);
MAKE_TEST_FUNC(test_solve_08, ")))", -3);
MAKE_TEST_FUNC(test_solve_09, ")())())", -3);

MunitResult test_input(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input;
    size_t input_length = read_file_to_string("input.txt", &input); \
    munit_assert_size(input_length, >, 0); \
    int64_t result = solve(input, input_length); \
    free(input); \
    munit_assert_int64(result, ==, 74); \
    return MUNIT_OK; \
}

MunitTest tests[] = {
    { "/test-01", test_solve_01, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-02", test_solve_02, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-03", test_solve_03, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-04", test_solve_04, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-05", test_solve_05, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-06", test_solve_06, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-07", test_solve_07, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-08", test_solve_08, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-09", test_solve_09, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-input", test_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  .prefix = "/day01/part1",
  .tests = tests,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}