#include <string.h>

#include "common/file.h"
#include "munit/munit.h"
#include "part1.c"

#define MAKE_MD5_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    MD5State result; \
    char buffer[BYTES_PER_CHUNK] = { 0 }; \
    memcpy(buffer, input, strlen(input)); \
    md5_hash(buffer, strlen(input), &result); \
    munit_assert_uint32(result.a, ==, expected.a); \
    munit_assert_uint32(result.b, ==, expected.b); \
    munit_assert_uint32(result.c, ==, expected.c); \
    munit_assert_uint32(result.d, ==, expected.d); \
    return MUNIT_OK; \
}

MAKE_MD5_TEST_FUNC(test_md5_empty, "", ((MD5State){ 0xd98c1dd4, 0x04b2008f, 0x980980e9, 0x7e42f8ec }));
MAKE_MD5_TEST_FUNC(test_md5_a, "a", ((MD5State){ 0xb975c10c, 0xa8b6f1c0, 0xe299c331, 0x61267769 }));
MAKE_MD5_TEST_FUNC(test_md5_qbf, "The quick brown fox jumps over the lazy dog", ((MD5State){ 0x9d7d109e, 0x82b62b37, 0x351dd86b, 0xd619a442 }));


#define MAKE_MD5_TEST_A_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    MD5State result; \
    char buffer[BYTES_PER_CHUNK] = { 0 }; \
    memcpy(buffer, input, strlen(input)); \
    md5_hash(buffer, strlen(input), &result); \
    munit_assert_uint32(result.a, ==, expected); \
    return MUNIT_OK; \
}

MAKE_MD5_TEST_A_FUNC(test_md5_a_1, "abcdef609043", 0xdb010000);
MAKE_MD5_TEST_A_FUNC(test_md5_a_2, "pqrstuv1048970", 0x13060000);

#define MAKE_TEST_FUNC(name, input, expected) \
MunitResult name(const MunitParameter _params[], void* _user_data_or_fixture) { \
    int64_t result = solve(input, strlen(input)); \
    munit_assert_int64(result, ==, expected); \
    return MUNIT_OK; \
}

MAKE_TEST_FUNC(test_solve_1, "abcdef", 609043);
MAKE_TEST_FUNC(test_solve_2, "pqrstuv", 1048970);

MunitResult test_input(const MunitParameter _params[], void* _user_data_or_fixture) { \
    char* input;
    size_t input_length = read_file_to_string("input.txt", &input); \
    munit_assert_size(input_length, >, 0); \
    int64_t result = solve(input, input_length); \
    free(input); \
    munit_assert_int64(result, ==, 254575); \
    return MUNIT_OK; \
}

MunitTest tests[] = {
    { "/test-md5-empty", test_md5_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-md5-a", test_md5_a, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-md5-qbf", test_md5_qbf, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-md5-a-1", test_md5_a_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-md5-a-2", test_md5_a_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-solve-1", test_solve_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-solve-2", test_solve_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-input", test_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  .prefix = "/day04/part1",
  .tests = tests,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
