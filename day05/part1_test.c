#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part1.c"

#define MAKE_STRING_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    size_t input_length = strlen(input); \
    int64_t result = is_nice_string(input, input_length); \
    munit_assert_int64(result, ==, expected); \
    return MUNIT_OK; \
}

MAKE_STRING_TEST_FUNC(test_string_01, "ugknbfddgicrmopn", 1);
MAKE_STRING_TEST_FUNC(test_string_02, "aaa", 1);
MAKE_STRING_TEST_FUNC(test_string_03, "jchzalrnumimnmhp", 0);
MAKE_STRING_TEST_FUNC(test_string_04, "haegwjzuvuyypxyu", 0);
MAKE_STRING_TEST_FUNC(test_string_05, "dvszwmarrgswjxmb", 0);

MunitResult test_input(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input;
    size_t input_length = read_file_to_string("input.txt", &input); \
    munit_assert_size(input_length, >, 0); \
    int64_t result = solve(input, input_length); \
    free(input); \
    munit_assert_int64(result, ==, 255); \
    return MUNIT_OK; \
}

MunitTest tests[] = {
    { "/test-string-01", test_string_01, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-string-02", test_string_02, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-string-03", test_string_03, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-string-04", test_string_04, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-string-05", test_string_05, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-input", test_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  .prefix = "/day05/part1",
  .tests = tests,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
