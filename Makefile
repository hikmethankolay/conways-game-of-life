# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -g

# Executable name with OS-specific extension
TARGET = conways_game_of_life$(EXE)

# Source files
SRCS = main.c # Add all your source files here

# Object files
OBJS = $(SRCS:.c=.o)

# Detect OS
ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM = del /Q
    RUN = $(TARGET)
    SHELL := cmd.exe
else
    EXE =
    RM = rm -f
    RUN = ./$(TARGET)
endif

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	$(RM) $(TARGET) $(OBJS)

# Run the program with OS-specific command
run: $(TARGET)
	$(RUN)

.PHONY: all clean run
