COMMON_DEPS := ../common/run.c
TEST_DEPS := ../common/file.c ../munit/munit.c

part%: part%.c $(COMMON_DEPS)
	gcc -o $@ $^ -I .. $(COMMON_DEPS) -Wall -Wextra -Werror -g

run_part%: part%
	./$<

part%_test: part%_test.c part%.c $(COMMON_DEPS) $(TEST_DEPS)
	gcc -o $@ $< $(COMMON_DEPS) $(TEST_DEPS) -DTESTING -I .. -Wextra -Werror -g
test_part%: part%_test
	./$<

test: test_part1 test_part2

.PHONY: run_part% test_part% test
