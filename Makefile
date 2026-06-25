CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic

SOURCES = \
    single-linked-list.c \
    double-linked-list.c \
    stack.c \
    queue.c \
    deque.c \
    dynamic-array.c \
    priority-queue.c \
    hash-map.c \
    binary-search-tree.c

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean test

all: $(OBJECTS)

test: tests/test
	./tests/test

tests/test: tests/test.c $(SOURCES) *.h
	$(CC) $(CFLAGS) tests/test.c $(SOURCES) -o tests/test

clean:
	rm -f $(OBJECTS) tests/test tests/test_sanitize
