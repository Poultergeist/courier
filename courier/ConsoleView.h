#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include <string>
#include <vector>

class ConsoleView {
public:
    void displayMenu();
    void displayMessage(const std::string& message);
    int getUserInputInt(const std::string& prompt);
    std::string getUserInputString(const std::string& prompt);
    void displayExecutionTime(double time_ms);
    void displayTable(const std::vector<std::vector<std::string>>& table);
};

#endif