CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = prog
OBJS = matrix2d.o main.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

matrix2d.o: matrix2d.c matrix2d.h
	$(CC) $(CFLAGS) -c matrix2d.c -o matrix2d.o

main.o: main.c matrix2d.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJS) $(TARGET) result.txt

run: $(TARGET)
	./$(TARGET)

save: $(TARGET)
	./$(TARGET) > result.txt

.PHONY: clean run save