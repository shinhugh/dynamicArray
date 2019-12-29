# Compiler
CC = gcc
# Compiler flags
CFLAGS = -I .
# Global dependencies
DEPS = dynamicArray.h
# Object files to make
OBJ = dynamicArray.o
# Libraries to make
LIB = libdynamicArray.a

all: libdynamicArray.a

# Make object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Make static library string_parser
libdynamicArray.a: $(OBJ)
	ar rcs $@ $^
	rm -f $^

.PHONY: clean

# Remove all but source code
clean:
	rm -f $(OBJ) $(LIB)
