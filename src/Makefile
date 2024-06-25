# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Target executable name
TARGET = main

# Source files
SRCS = main.c tokenizer.c history.c

# Object files
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c tokenizer.h history.h
	$(CC) $(CFLAGS) -c main.c

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) -c tokenizer.c

history.o: history.c history.h
	$(CC) $(CFLAGS) -c history.c

clean:
	rm -f $(TARGET) $(OBJS)
