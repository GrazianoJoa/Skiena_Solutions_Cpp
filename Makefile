# Compilador y flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g

# Archivos fuente
SRC = src/data_structures/stack.c \
	  src/data_structures/linked_list.c

# Archivos de tests
TESTS = tests/test.c \
        tests/data_structures/stack_test.c \
		tests/data_structures/linked_list_test.c

# Archivo ejecutable
TARGET = run_tests

# Regla principal
all: $(TARGET)

# Compilación de todos los archivos
$(TARGET): $(SRC) $(TESTS)
	$(CC) $(CFLAGS) $(SRC) $(TESTS) -o $(TARGET)

# Limpiar archivos compilados
clean:
	rm -f $(TARGET)

