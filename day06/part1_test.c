#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part1.c"

#define MAKE_PARSE_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    Instruction inst; \
    size_t input_length = strlen(input); \
    parse_instruction(input, input_length, &inst); \
    munit_assert_uint32(inst.action, ==, expected.action); \
    munit_assert_uint32(inst.bounds.x0, ==, expected.bounds.x0); \
    munit_assert_uint32(inst.bounds.y0, ==, expected.bounds.y0); \
    munit_assert_uint32(inst.bounds.x1, ==, expected.bounds.x1); \
    munit_assert_uint32(inst.bounds.y1, ==, expected.bounds.y1); \
    return MUNIT_OK; \
}

MAKE_PARSE_TEST_FUNC(test_parse_01, "turn on 0,0 through 999,999", ((Instruction){ TurnOn, { 0, 0, 999, 999 } }));
MAKE_PARSE_TEST_FUNC(test_parse_02, "toggle 0,0 through 999,0", ((Instruction){ Toggle, { 0, 0, 999, 0 } }));
MAKE_PARSE_TEST_FUNC(test_parse_03, "turn off 499,499 through 500,500", ((Instruction){ TurnOff, { 499, 499, 500, 500 } }));

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
    { "/test-parse-01", test_parse_01, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-parse-02", test_parse_02, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-parse-03", test_parse_03, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
