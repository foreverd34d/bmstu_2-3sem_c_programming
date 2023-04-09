# Dirs
SRC  		:= ./src
INC  		:= ./inc
OUT  		:= ./out
TARGET		:= ./towers

# Files
OBJS 	 	:= $(OUT)/towers.o

# Compiler vars
CC 	 	 	 	:= gcc
CFLAGS 	 	 	:= -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla
CPPFLAGS 	 	:= -I./inc/ -MMD
LDFLAGS 	 	:=


$(TARGET): $(OBJS) $(OUT)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

$(OUT)/%.o: $(SRC)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d) $(OUT)/main.d


.PHONY: release debug clean

release: CFLAGS += -O2
release: app.exe

debug: CFLAGS 	+= -DDEBUG=1 -g3
debug: app.exe

clean:
	$(RM) $(TARGET) $(OUT)/*
