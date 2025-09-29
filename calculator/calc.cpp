#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

// Функция для вывода справки
void printHelp(const char* progName) {
    std::cerr << "\n";
    std::cerr << "Мультипликативный калькулятор: поддерживает умножение и деление.\n";
    std::cerr << "\n";
    std::cerr << "Операции:\n";
    std::cerr << "  multiply    — умножить все операнды\n";
    std::cerr << "  divide      — разделить первый операнд на все остальные последовательно\n";
    std::cerr << "\n";
    std::cerr << "Ограничения:\n";
    std::cerr << "  - Количество операндов: от 2 до 4\n";
    std::cerr << "  - Операнды могут быть целыми или дробными числами\n";
    std::cerr << "\n";
    std::cerr << "Примеры:\n";
    std::cerr << "  " << progName << " -o multiply 2 3 4\n";
    std::cerr << "  " << progName << " --operation divide 100 2 5\n";
}


bool isValidNumber(const std::string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') {
        if (s.size() == 1) return false;
        start = 1;
    }
    bool hasDot = false;
    for (size_t i = start; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
}


double stringToDouble(const std::string& s) {
    try {
        size_t pos;
        double val = std::stod(s, &pos);
        if (pos != s.size()) {
            throw std::invalid_argument("лишние символы");
        }
        return val;
    } catch (...) {
        throw std::invalid_argument("некорректное число: " + s);
    }
}

int main(int argc, char* argv[]) {
    
    if (argc == 1) {
        printHelp(argv[0]);
        return 1;
    }

    std::string operation;
    std::vector<double> operands;
    bool operationSet = false;


    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-o" || arg == "--operation") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: не указано имя операции после " << arg << "\n";
                return 1;
            }
            operation = argv[++i];
            operationSet = true;
        } else if (arg[0] == '-' && arg.size() > 1) {
            
            std::cerr << "Ошибка: неизвестный параметр '" << arg << "'\n";
            printHelp(argv[0]);
            return 1;
        } else {
            // Считаем, что это операнд
            if (!isValidNumber(arg)) {
                std::cerr << "Ошибка: '" << arg << "' не является допустимым числом\n";
                return 1;
            }
            operands.push_back(stringToDouble(arg));
        }
    }

    // Проверка: указана ли операция
    if (!operationSet) {
        std::cerr << "Ошибка: не указана операция (-o или --operation)\n";
        printHelp(argv[0]);
        return 1;
    }

    // Проверка поддерживаемых операций
    if (operation != "multiply" && operation != "divide") {
        std::cerr << "Ошибка: неизвестная операция '" << operation << "'\n";
        std::cerr << "Поддерживаемые операции: multiply, divide\n";
        return 1;
    }

    // Проверка количества операндов
    if (operands.size() < 2 || operands.size() > 4) {
        std::cerr << "Ошибка: количество операндов должно быть от 2 до 4 (указано: " << operands.size() << ")\n";
        return 1;
    }

    // Выполнение операции
    double result = 0.0;
    try {
        if (operation == "multiply") {
            result = 1.0;
            for (double num : operands) {
                result *= num;
            }
        } else if (operation == "divide") {
            result = operands[0];
            for (size_t i = 1; i < operands.size(); ++i) {
                if (operands[i] == 0.0) {
                    std::cerr << "Ошибка: деление на ноль\n";
                    return 1;
                }
                result /= operands[i];
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка вычисления: " << e.what() << "\n";
        return 1;
    }

    // Вывод результата: если целое — без точки
    if (result == static_cast<long long>(result)) {
        std::cout << static_cast<long long>(result) << "\n";
    } else {
        std::cout << result << "\n";
    }

    return 0;
}
