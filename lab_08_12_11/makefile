# Dirs
SRC  		:= ./src
INC  		:= ./inc
OUT  		:= ./out
UNIT  		:= ./unit_tests
COVERAGE 	:= $(OUT)/coverage

# Files
OBJS 	 	:= $(OUT)/matrix.o $(OUT)/matrix_io.o $(OUT)/matrix_operations.o
UNIT_OBJS 	:= $(OUT)/check_matrix_operations.o $(OUT)/check_matrix.o $(OUT)/check_matrix_io.o

# Compiler vars
CC 	 	 	 	:= gcc
CFLAGS 	 	 	:= -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla
CPPFLAGS 	 	:= -I./inc/ -MMD
LDFLAGS 	 	:=
CHECK_CFLAGS 	:= $(shell pkg-config --cflags check)
CHECK_LDFLAGS 	:= $(shell pkg-config --libs check)


app.exe: $(OBJS) $(OUT)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

unit_tests.exe: $(UNIT_OBJS) $(OBJS) $(OUT)/check_main.o
	$(CC) $(LDFLAGS) $(CHECK_LDFLAGS) $^ -o $@

$(OUT)/%.o: $(UNIT)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CHECK_CFLAGS) -c $< -o $@

$(OUT)/%.o: $(SRC)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d) $(UNIT_OBJS:.o=.d) $(OUT)/main.d $(OUT)/check_main.d


.PHONY: release debug coverage sanitized unit func clean

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
	./unit_tests.exe

func: app.exe
	./func_tests/scripts/func_tests.sh

clean:
	$(RM) -r $(COVERAGE)
	$(RM) *.exe $(OUT)/*
