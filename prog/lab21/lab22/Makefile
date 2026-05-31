CC = gcc
CFLAGS = -Wall -Wextra
TARGET = program
SRCS = main.c bitrgbled.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
run:
	./program

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean