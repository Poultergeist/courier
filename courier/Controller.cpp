#include "Controller.h"
#include <chrono>
using namespace std;
using namespace chrono;

Controller::Controller(const DatabaseModel& model, const ConsoleView& view) : model(model), view(view) {}

void Controller::run() {
    bool running = true;
    while (running) {
        view.displayMenu();
        int choice = view.getUserInputInt("Enter your choice: ");

        switch (choice) {
        case 1:
            handleInsertCourier();
            break;
        case 2:
            handleViewTable();
            break;
        case 3:
            handleDeleteRow();
            break;
        case 4:
            handleEditData();
            break;
        case 5:
            handleGenerateData();
            break;
        case 6:
            handleSearchData();
            break;
        case 7:
            running = false;
            break;
        default:
            view.displayMessage("Invalid option, please try again.");
        }
    }
}

void Controller::handleInsertCourier() {
    int courier_id = view.getUserInputInt("Enter Courier ID (or !stop! to cancel): ");
    if (courier_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }

    std::string type = view.getUserInputString("Enter Courier Type (or !stop! to cancel): ");
    if (type == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }

    std::string name = view.getUserInputString("Enter Courier Name (or !stop! to cancel): ");
    if (name == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }

    model.insertCourier(courier_id, type, name);
    view.displayMessage("Courier inserted successfully.");
}

void Controller::handleViewTable() {
    string table_name = view.getUserInputString("Enter table name to view: ");
    model.viewTable(table_name);
}

void Controller::handleDeleteRow() {
    string table_name = view.getUserInputString("Enter table name to delete from: ");
    string condition = view.getUserInputString("Enter condition for deletion (e.g., id=1): ");
    model.deleteRow(table_name, condition);
}

void Controller::handleEditData() {
    string table_name = view.getUserInputString("Enter table name to edit: ");
    string set_clause = view.getUserInputString("Enter SET clause (e.g., column='value'): ");
    string condition = view.getUserInputString("Enter condition (e.g., id=1): ");
    model.updateRow(table_name, set_clause, condition);
}

void Controller::handleGenerateData() {
    string table_name = view.getUserInputString("Enter table name to generate data for: ");
    int count = view.getUserInputInt("Enter number of records to generate: ");
    model.generateData(table_name, count);
}

void Controller::handleSearchData() {
    std::string query = view.getUserInputString("Enter your custom search query: ");

    auto start = std::chrono::high_resolution_clock::now();
    auto results = model.executeAndFetch(query); // Повертаємо результат запиту
    auto end = std::chrono::high_resolution_clock::now();

    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    view.displayExecutionTime(duration);

    if (!results.empty()) {
        view.displayTable(results); // Виводимо результати у вигляді таблиці
    }
    else {
        view.displayMessage("No data found or query returned no rows.");
    }
}
