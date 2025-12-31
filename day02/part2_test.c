#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part2.c"

#define MAKE_RIBBON_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    Box box = parse_box(input); \
    int64_t result = ribbon_needed(box); \
    munit_assert_int64(result, ==, expected); \
    return MUNIT_OK; \
}

MAKE_RIBBON_TEST_FUNC(test_ribbon_01, "2x3x4", 34);
MAKE_RIBBON_TEST_FUNC(test_ribbon_02, "1x1x10", 14);

MunitResult test_input(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input;
    size_t input_length = read_file_to_string("input.txt", &input); \
    munit_assert_size(input_length, >, 0); \
    int64_t result = solve(input, input_length); \
    free(input); \
    munit_assert_int64(result, ==, 3783758); \
    return MUNIT_OK; \
}

MunitTest tests[] = {
    { "/test-01", test_ribbon_01, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-02", test_ribbon_02, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-input", test_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  .prefix = "/day02/part2",
  .tests = tests,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}