# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -std=c11 -I./include
LDFLAGS = -lm

# Директории
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = .

# Имя исполняемого файла
TARGET = $(BIN_DIR)/cmdcalc

# Исходные файлы
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/calc.c

# Объектные файлы
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/calc.o

# Заголовочные файлы
HEADERS = $(INC_DIR)/calc.h

# Правила
.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/calc.o: $(SRC_DIR)/calc.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Зависимости (автоматическая генерация)
-include $(OBJS:.o=.d)

# Правило для генерации файлов зависимостей
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@