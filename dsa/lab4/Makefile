# Компилятор и флаги
CC = gcc
# -Iinclude указывает компилятору искать заголовочные файлы в папке include
CFLAGS = -Wall -Wextra -Iinclude
LDLIBS = -lm

# Директории проекта
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Целевой исполняемый файл
TARGET = program

# Автоматический поиск исходников и заголовков
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
HEADERS = $(wildcard $(INCDIR)/*.h)

# Сборка по умолчанию
all: $(TARGET)

# Линковка объектных файлов в исполняемый файл
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Компиляция каждого .c файла в .o с зависимостью от заголовков
# Порядок выполнения (| $(OBJDIR)) гарантирует, что директория obj существует
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директории для объектных файлов
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Очистка промежуточных файлов, исполняемого файла и результатов
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Запуск всех экспериментов
run: $(TARGET)
	./$(TARGET) all > results.dat

# Запуск отдельных экспериментов
run_exp1: $(TARGET)
	./$(TARGET) exp1 > exp1.dat

run_exp5: $(TARGET)
	./$(TARGET) exp5 > exp5.dat

run_exp6: $(TARGET)
	./$(TARGET) exp6 > exp6.dat
	
.PHONY: all clean run run_exp1 run_exp5 run_exp6