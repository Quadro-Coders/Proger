CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -I./include -I./src
LIBS = -lm

SRCDIR = src
OBJDIR = obj
TARGET = main
TEST_BIN = test_prac5

SRCS = $(SRCDIR)/main.c $(SRCDIR)/contstruct.c $(SRCDIR)/matrix2d.c $(SRCDIR)/bitrgbled.c $(SRCDIR)/fiostruct.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Для тестов исключаем main.o, чтобы не было конфликта двух main()
TEST_OBJS = $(filter-out $(OBJDIR)/main.o, $(OBJS))

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#  ЗАПУСК UNIT-ТЕСТОВ 
test: $(OBJDIR) $(SRCDIR)/test_prac5.c $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(SRCDIR)/test_prac5.c $(TEST_OBJS) $(LIBS)
	@echo "Запуск Unit-тестов..."
	@./$(TEST_BIN)
	@echo ""

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_BIN) *.bin *.txt *.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run