# Dirs
SRC  		:= ./src
INC  		:= ./inc
OUT  		:= ./out
UNIT  		:= ./unit_tests
COVERAGE 	:= $(OUT)/coverage

# Files
HEADERS 	:= $(INC)/numio.h $(INC)/numsort.h $(INC)/numkey.h
OBJS 	 	:= $(OUT)/numio.o $(OUT)/numsort.o $(OUT)/numkey.o
UNIT_OBJS 	:= $(OUT)/check_numsort.o $(OUT)/check_numkey.o $(OUT)/check_numio.o

# Compiler vars
CC 	 	 	:= gcc
CFLAGS 	 	:= -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla
LDFLAGS 	:=
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)


app.exe: $(OBJS) $(OUT)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

$(OUT)/main.o: $(SRC)/main.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/numio.o: $(SRC)/numio.c $(INC)/numio.h $(INC)/errcodes.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/numsort.o: $(SRC)/numsort.c $(INC)/numsort.h $(INC)/errcodes.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/numkey.o: $(SRC)/numkey.c $(INC)/numkey.h $(INC)/errcodes.h
	$(CC) -c $(CFLAGS) $< -o $@


unit_tests.exe: $(UNIT_OBJS) $(OBJS) $(OUT)/check_main.o
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $^ -o $@

$(OUT)/check_main.o: $(UNIT)/check_main.c $(INC)/check_main.h
	$(CC) -c $(CFLAGS) $(CHECK_FLAGS) $< -o $@

$(OUT)/check_numsort.o: $(UNIT)/check_numsort.c $(INC)/check_main.h $(INC)/numsort.h
	$(CC) -c $(CFLAGS) $(CHECK_FLAGS) $< -o $@

$(OUT)/check_numkey.o: $(UNIT)/check_numkey.c $(INC)/check_main.h $(INC)/numkey.h
	$(CC) -c $(CFLAGS) $(CHECK_FLAGS) $< -o $@

$(OUT)/check_numio.o: $(UNIT)/check_numio.c $(INC)/check_main.h $(INC)/numio.h
	$(CC) -c $(CFLAGS) $(CHECK_FLAGS) $< -o $@


.PHONY: release debug coverage sanitized unit func clean

release: CFLAGS += -O2
release: app.exe

coverage: CC 	 	:= clang
coverage: CFLAGS 	+= -fprofile-arcs -ftest-coverage
coverage: LDFLAGS 	+= -fprofile-arcs -ftest-coverage
coverage: func
	gcov $(OUT)/*.c
	lcov -c -d $(OUT) -o $(OUT)/cov.info && genhtml $(OUT)/cov.info -o $(COVERAGE)

debug: CC 	 	:= clang
debug: CFLAGS 	+= -DDEBUG=1 -glldb -fdebug-macro
debug: app.exe

sanitized: CC 	 	:= clang
sanitized: CFLAGS  	+= -fsanitize=address -fsanitize=undefined
sanitized: LDFLAGS 	+= -fsanitize=address -fsanitize=undefined
sanitized: debug

unit: unit_tests.exe
	./unit_tests.exe

func: app.exe
	./func_tests/scripts/func_tests.sh

clean:
	$(RM) -r $(COVERAGE)
	$(RM) *.exe *.gcno *.gcda *.gcov $(OUT)/*
