CC=gcc
CFLAGS=-Wall -Wextra
SOURCES=bitrgbled_field.c bitrgbled_ops.c main.c
OBJECTS=$(SOURCES:.c=.o)
HEADERS=bitrgbled_field.h bitrgbled_ops.h
TARGET=program

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
