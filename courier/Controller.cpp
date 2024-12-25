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
            handleInsert();
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

void Controller::handleInsert() {
    string table = view.getUserInputString("Enter table you want to insert data to: ");
    bool validTable = false;

    if (table == "courier") {
        validTable = true;
        handleInsertCourier();
    }

    if (table == "package") {
        validTable = true;
        handleInsertPackage();
    }

    if (table == "receiver") {
        validTable = true;
        handleInsertReceiver();
    }

    if (table == "sender") {
        validTable = true;
        handleInsertSender();
    }

    if (table == "vehicle") {
        validTable = true;
        handleInsertVehiÒle();
    }

    if (!validTable) {
        view.displayMessage("Invalid table name.");
    }
}

void Controller::handleInsertCourier() {
    string table = "courier";
    vector<string> columns = {"courier_id", "type", "name", "vachile_id"};
    vector<string> values;
    int courier_id = view.getUserInputInt("Enter Courier ID (or !stop! to cancel): ");
    if (courier_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(courier_id));

    string type = view.getUserInputString("Enter Courier Type (or !stop! to cancel): ");
    if (type == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(type);

    string name = view.getUserInputString("Enter Courier Name (or !stop! to cancel): ");
    if (name == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(name);

    int vachile_id = view.getUserInputInt("Enter vachile id:");
    if (vachile_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(vachile_id));

    model.insert(table, columns, values);
    view.displayMessage("Courier inserted successfully.");
}

void Controller::handleInsertPackage() {
    string table = "package";
    vector<string> columns = { "package_id", "weight", "price", "sender_id", "receiver_id", "courier_id" };
    vector<string> values;

    int package_id = view.getUserInputInt("Enter Package ID (or !stop! to cancel): ");
    if (package_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(package_id));

    int weight = view.getUserInputInt("Enter Package Weight: ");
    if (weight == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(weight));

    int price = view.getUserInputInt("Enter Package Price: ");
    if (price == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(price));

    int sender_id = view.getUserInputInt("Enter Sender ID: ");
    if (sender_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(sender_id));

    int receiver_id = view.getUserInputInt("Enter Receiver ID: ");
    if (receiver_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(receiver_id));

    int courier_id = view.getUserInputInt("Enter Courier ID: ");
    if (courier_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(courier_id));

    model.insert(table, columns, values);
    view.displayMessage("Package inserted successfully.");
}

void Controller::handleInsertReceiver() {
    string table = "receiver";
    vector<string> columns = { "receiver_id", "money", "address", "name" };
    vector<string> values;

    int receiver_id = view.getUserInputInt("Enter Receiver ID (or !stop! to cancel): ");
    if (receiver_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(receiver_id));

    int money = view.getUserInputInt("Enter Receiver Money: ");
    if (money == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(money));

    string address = view.getUserInputString("Enter Receiver Address: ");
    if (address == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(address);

    string name = view.getUserInputString("Enter Receiver Name: ");
    if (name == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(name);

    model.insert(table, columns, values);
    view.displayMessage("Receiver inserted successfully.");
}

void Controller::handleInsertSender() {
    string table = "sender";
    vector<string> columns = { "sender_id", "money", "address", "name" };
    vector<string> values;

    int sender_id = view.getUserInputInt("Enter Sender ID (or !stop! to cancel): ");
    if (sender_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(sender_id));

    int money = view.getUserInputInt("Enter Sender Money: ");
    if (money == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(money));

    string address = view.getUserInputString("Enter Sender Address: ");
    if (address == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(address);

    string name = view.getUserInputString("Enter Sender Name: ");
    if (name == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(name);

    model.insert(table, columns, values);
    view.displayMessage("Sender inserted successfully.");
}

void Controller::handleInsertVehiÒle() {
    string table = "vehicle";
    vector<string> columns = { "vehicle_id", "name", "type", "speed", "capacity" };
    vector<string> values;

    int vehicle_id = view.getUserInputInt("Enter Vehicle ID (or !stop! to cancel): ");
    if (vehicle_id == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(vehicle_id));

    string name = view.getUserInputString("Enter Vehicle Name: ");
    if (name == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(name);

    string type = view.getUserInputString("Enter Vehicle Type: ");
    if (type == "!stop!") {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(type);

    int speed = view.getUserInputInt("Enter Vehicle Speed: ");
    if (speed == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(speed));

    int capacity = view.getUserInputInt("Enter Vehicle Capacity: ");
    if (capacity == -1) {
        view.displayMessage("Operation cancelled. Returning to main menu.");
        return;
    }
    values.push_back(to_string(capacity));

    model.insert(table, columns, values);
    view.displayMessage("Vehicle inserted successfully.");
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
    auto results = model.executeAndFetch(query); // œÓ‚ÂÚ‡∫ÏÓ ÂÁÛÎ¸Ú‡Ú Á‡ÔËÚÛ
    auto end = std::chrono::high_resolution_clock::now();

    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    view.displayExecutionTime(duration);

    if (!results.empty()) {
        view.displayTable(results); // ¬Ë‚Ó‰ËÏÓ ÂÁÛÎ¸Ú‡ÚË Û ‚Ë„Îˇ‰≥ Ú‡·ÎËˆ≥
    }
    else {
        view.displayMessage("No data found or query returned no rows.");
    }
}
