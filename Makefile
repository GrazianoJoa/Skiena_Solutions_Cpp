
CC = gcc
CFLAGS = -Iinclude -Itests -Wall -Wextra -g

SRC = src/data_structures/stack.c \
      src/data_structures/linked_list.c \
      src/data_structures/binary_search_tree.c \
			src/data_structures/hash_map.c \
			src/data_structures/comparator.c \
			src/data_structures/utils.c

TESTS = tests/test.c

OBJ = $(SRC:.c=.o) $(TESTS:.c=.o)

TARGET = run_tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

