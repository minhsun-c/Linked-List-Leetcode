CC      := gcc
CFLAGS  := -Wall -Wextra -Iincludes

# Files
SRCS    := $(wildcard src/*.c)
OBJS    := $(patsubst src/%.c,obj/%.o,$(SRCS))
TARGET  := main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm $(TARGET)

run: $(TARGET)
	./$(TARGET)

obj:
    mkdir obj

indent: 
	clang-format -i src/* includes/*

.PHONY: all clean run
