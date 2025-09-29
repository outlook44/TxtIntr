# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Имя исполняемого файла
TARGET = calc

# Исходный файл
SRC = calc.cpp

# Цель по умолчанию
all: $(TARGET)

# Сборка исполняемого файла напрямую (без промежуточных .o при одном файле)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Запуск — просто напоминание, так как аргументы нужны внешние
run:
	@echo "Запустите вручную с нужными аргументами, например:"
	@echo "  ./${TARGET} -o multiply 2 3 4"
	@echo "  ./${TARGET} --operation divide 100 2 5"

# Очистка
clean:
	rm -f $(TARGET)

# Указание фиктивных целей
.PHONY: all clean run
