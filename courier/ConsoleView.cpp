#include "ConsoleView.h"
#include <iostream>
#include <iomanip>
using namespace std;

void ConsoleView::displayMenu() {
    std::cout << "\nMenu Options:\n";
    std::cout << "1. Insert into table\n";
    std::cout << "2. View Table\n";
    std::cout << "3. Delete Row\n";
    std::cout << "4. Edit Data\n";
    std::cout << "5. Generate Data\n";
    std::cout << "6. Search Data\n";
    std::cout << "7. Exit\n";
    std::cout << "\n(Note: Type '!stop!' during any operation to cancel and return to main menu.)\n";
}


void ConsoleView::displayMessage(const std::string& message) {
    cout << message << endl;
}

int ConsoleView::getUserInputInt(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;

    if (input == "!stop!") return -1; // Код для зупинки
    try {
        return std::stoi(input);
    }
    catch (...) {
        displayMessage("Invalid input. Please enter a valid number.");
        return getUserInputInt(prompt); // Повторення вводу
    }
}


std::string ConsoleView::getUserInputString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    if (std::cin.peek() == '\n') std::cin.ignore(); // Пропустити новий рядок, якщо є
    std::getline(std::cin, input);
    return input;
}

void ConsoleView::displayExecutionTime(double time_ms) {
    cout << fixed << setprecision(2);
    cout << "Execution time: " << time_ms << " ms\n";
}

void ConsoleView::displayTable(const std::vector<std::vector<std::string>>& table) {
    if (table.empty()) {
        displayMessage("No data to display.");
        return;
    }

    // Вивід заголовків
    for (const auto& header : table[0]) {
        std::cout << std::setw(15) << std::left << header << "|";
    }
    std::cout << "\n" << std::string(50, '-') << "\n";

    // Вивід рядків
    for (size_t i = 1; i < table.size(); ++i) {
        for (const auto& field : table[i]) {
            std::cout << std::setw(15) << std::left << field << "|";
        }
        std::cout << "\n";
    }
    std::cout << std::string(50, '-') << "\n";
}
