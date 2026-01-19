#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part1.c"

MunitResult test_parse_01(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input = "123 -> x";
    size_t input_length = strlen(input);
    Booklet booklet;
    parse_booklet(input, input_length, &booklet);

    munit_assert_size(booklet.instruction_count, ==, 1);
    munit_assert_size(booklet.wires.length, ==, 1);
    munit_assert_char(booklet.instructions[0].type, ==, UNARY_OP);
    munit_assert_char(booklet.instructions[0].op.unary.gate, ==, SET);
    munit_assert_char(booklet.instructions[0].op.unary.src.type, ==, VALUE);
    munit_assert_uint16(booklet.instructions[0].op.unary.src.val.value, ==, 123);
    munit_assert_char(booklet.instructions[0].op.unary.dst.type, ==, WIRE);
    munit_assert_ptr_equal(booklet.instructions[0].op.unary.dst.val.wire, &booklet.wires.wires[0]);
    munit_assert_string_equal(booklet.wires.wires[0].data, "x");

    destroy_booklet(&booklet);
    return MUNIT_OK;
}
MunitResult test_parse_02(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input = "x AND y -> z";
    size_t input_length = strlen(input);
    Booklet booklet;
    parse_booklet(input, input_length, &booklet);

    munit_assert_size(booklet.instruction_count, ==, 1);
    munit_assert_size(booklet.wires.length, ==, 3);
    munit_assert_char(booklet.instructions[0].type, ==, BINARY_OP);
    munit_assert_char(booklet.instructions[0].op.binary.gate, ==, AND);
    munit_assert_char(booklet.instructions[0].op.binary.src1.type, ==, WIRE);
    munit_assert_char(booklet.instructions[0].op.binary.src2.type, ==, WIRE);
    munit_assert_char(booklet.instructions[0].op.binary.dst.type, ==, WIRE);
    munit_assert_ptr_equal(booklet.instructions[0].op.binary.src1.val.wire, &booklet.wires.wires[0]);
    munit_assert_ptr_equal(booklet.instructions[0].op.binary.src2.val.wire, &booklet.wires.wires[1]);
    munit_assert_ptr_equal(booklet.instructions[0].op.binary.dst.val.wire, &booklet.wires.wires[2]);
    munit_assert_size(booklet.wires.wires[0].length, ==, 1);
    munit_assert_char(booklet.wires.wires[0].data[0], ==, 'x');
    munit_assert_size(booklet.wires.wires[1].length, ==, 1);
    munit_assert_char(booklet.wires.wires[1].data[0], ==, 'y');
    munit_assert_size(booklet.wires.wires[2].length, ==, 1);
    munit_assert_char(booklet.wires.wires[2].data[0], ==, 'z');

    destroy_booklet(&booklet);
    return MUNIT_OK;
}
MunitResult test_parse_03(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input = "p LSHIFT 2 -> q";
    size_t input_length = strlen(input);
    Booklet booklet;
    parse_booklet(input, input_length, &booklet);

    munit_assert_size(booklet.instruction_count, ==, 1);
    munit_assert_size(booklet.wires.length, ==, 2);
    munit_assert_char(booklet.instructions[0].type, ==, BINARY_OP);
    munit_assert_char(booklet.instructions[0].op.binary.gate, ==, LSHIFT);
    munit_assert_char(booklet.instructions[0].op.binary.src1.type, ==, WIRE);
    munit_assert_char(booklet.instructions[0].op.binary.src2.type, ==, VALUE);
    munit_assert_uint16(booklet.instructions[0].op.binary.src2.val.value, ==, 2);
    munit_assert_char(booklet.instructions[0].op.binary.dst.type, ==, WIRE);
    munit_assert_ptr_equal(booklet.instructions[0].op.binary.src1.val.wire, &booklet.wires.wires[0]);
    munit_assert_ptr_equal(booklet.instructions[0].op.binary.dst.val.wire, &booklet.wires.wires[1]);
    munit_assert_size(booklet.wires.wires[0].length, ==, 1);
    munit_assert_char(booklet.wires.wires[0].data[0], ==, 'p');
    munit_assert_size(booklet.wires.wires[1].length, ==, 1);
    munit_assert_char(booklet.wires.wires[1].data[0], ==, 'q');

    destroy_booklet(&booklet);
    return MUNIT_OK;
}
MunitResult test_parse_04(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input = "NOT e -> f";
    size_t input_length = strlen(input);
    Booklet booklet;
    parse_booklet(input, input_length, &booklet);

    munit_assert_size(booklet.instruction_count, ==, 1);
    munit_assert_size(booklet.wires.length, ==, 2);
    munit_assert_char(booklet.instructions[0].type, ==, UNARY_OP);
    munit_assert_char(booklet.instructions[0].op.unary.gate, ==, NOT);
    munit_assert_char(booklet.instructions[0].op.unary.src.type, ==, WIRE);
    munit_assert_char(booklet.instructions[0].op.unary.dst.type, ==, WIRE);
    munit_assert_ptr_equal(booklet.instructions[0].op.unary.src.val.wire, &booklet.wires.wires[0]);
    munit_assert_ptr_equal(booklet.instructions[0].op.unary.dst.val.wire, &booklet.wires.wires[1]);
    munit_assert_size(booklet.wires.wires[0].length, ==, 1);
    munit_assert_char(booklet.wires.wires[0].data[0], ==, 'e');
    munit_assert_size(booklet.wires.wires[1].length, ==, 1);
    munit_assert_char(booklet.wires.wires[1].data[0], ==, 'f');

    destroy_booklet(&booklet);
    return MUNIT_OK;
}

MunitResult test_input(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input;
    size_t input_length = read_file_to_string("input.txt", &input); \
    munit_assert_size(input_length, >, 0); \
    int64_t result = solve(input, input_length); \
    free(input); \
    munit_assert_int64(result, ==, 400410); \
    return MUNIT_OK; \
}

MunitTest tests[] = {
    { "/test-parse-01", test_parse_01, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-parse-02", test_parse_02, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-parse-03", test_parse_03, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-parse-04", test_parse_04, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/test-input", test_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  .prefix = "/day06/part1",
  .tests = tests,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
