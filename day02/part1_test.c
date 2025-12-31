#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part1.c"

#define MAKE_PAPER_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    Box box = parse_box(input); \
    int64_t result = paper_needed(box); \
    munit_assert_int64(result, ==, expected); \
    return MUNIT_OK; \
}

MAKE_PAPER_TEST_FUNC(test_paper_01, "2x3x4", 58);
MAKE_PAPER_TEST_FUNC(test_paper_02, "1x1x10", 43);

MunitResult test_input(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input;
    size_t input_length = read_file_to_string("input.txt", &input); \
    munit_assert_size(input_length, >, 0); \
    int64_t result = solve(input, input_length); \
    free(input); \
    munit_assert_int64(result, ==, 1588178); \
    return MUNIT_OK; \
}

MunitTest tests[] = {
    { "/test-01", test_paper_01, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-02", test_paper_02, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-input", test_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  .prefix = "/day02/part1",
  .tests = tests,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}