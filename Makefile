CC ?= gcc
AR ?= ar
CFLAGS ?= -std=c23 -O2 -Wall -Wextra -Wpedantic

LIB = libplaincds.a

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

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJECTS)
	$(AR) rcs $@ $^

%.o: %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(LIB)
