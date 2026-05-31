CC = gcc
CFLAGS = -Wall -Wextra -lm
TARGET = cmdcalc
SRC = main.c calc.c

all: $(TARGET)

$(TARGET): $(SRC) calc.h
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean