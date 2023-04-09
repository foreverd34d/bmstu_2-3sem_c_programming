# Dirs
SRC  		:= ./src
INC  		:= ./inc
OUT  		:= ./out
UNIT  		:= ./unit_tests
COVERAGE 	:= $(OUT)/coverage

# Files
OBJS		:= $(OUT)/list.o $(OUT)/numbers_io.o
UNIT_OBJS	:= $(OUT)/check_list.o $(OUT)/check_numbers_io.o

# Compiler vars
CC 	 	 	 	:= gcc
CFLAGS 	 	 	:= -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla
CPPFLAGS 	 	:= -I$(INC)/ -MMD -D_GNU_SOURCE
LDFLAGS 	 	:=
CHECK_CFLAGS 	:= $(shell pkg-config --cflags check)
CHECK_LDFLAGS 	:= $(shell pkg-config --libs check)


.PHONY: release debug coverage sanitized unit func clean test_debug

release: CFLAGS += -O2
release: app.exe

coverage: CC 	 	:= clang
coverage: CFLAGS 	+= -fprofile-arcs -ftest-coverage
coverage: LDFLAGS 	+= -fprofile-arcs -ftest-coverage
coverage: func
	gcov $(OUT)/*.c
	lcov -c -d $(OUT) -o $(OUT)/cov.info && genhtml $(OUT)/cov.info -o $(COVERAGE)

debug: CFLAGS 	+= -DDEBUG=1 -g3
debug: app.exe

asan: CFLAGS  	+= -fsanitize=address -fsanitize=undefined
asan: LDFLAGS 	+= -fsanitize=address -fsanitize=undefined
asan: debug

unit: unit_tests.exe
	@./unit_tests.exe

unit_asan: CFLAGS  	+= -fsanitize=address -fsanitize=undefined -g3
unit_asan: LDFLAGS 	+= -fsanitize=address -fsanitize=undefined -g3
unit_asan: unit_tests.exe
	@CK_FORK=no ./unit_tests.exe

func: app.exe
	@./func_tests/scripts/func_tests.sh

clean:
	$(RM) -r $(COVERAGE)
	$(RM) *.exe $(OUT)/*


app.exe: $(OBJS) $(OUT)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

unit_tests.exe: $(UNIT_OBJS) $(OBJS) $(OUT)/check_main.o
	$(CC) $(LDFLAGS) $(CHECK_LDFLAGS) $^ -o $@

$(OUT)/%.o: $(UNIT)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CHECK_CFLAGS) -c $< -o $@

$(OUT)/%.o: $(SRC)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(wildcard $(OUT)/*.d)
