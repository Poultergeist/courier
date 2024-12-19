#include "DatabaseModel.h"
#include <iostream>
#include <pqxx/pqxx>
using namespace std;
using namespace pqxx;

DatabaseModel::DatabaseModel(const std::string& conn_str) : connection_str(conn_str) {}

void DatabaseModel::executeQuery(const std::string& query) {
    try {
        connection conn(connection_str);
        work txn(conn);
        txn.exec(query);
        txn.commit();
    }
    catch (const sql_error& e) {
        cerr << "SQL error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void DatabaseModel::insertCourier(const int& courier_id, const std::string& type, const std::string& name) {
    string query = "INSERT INTO courier (courier_id, type, name) VALUES ('" + to_string(courier_id) + "', '" + type + "', '" + name + "');";
    executeQuery(query);
}

void DatabaseModel::viewTable(const std::string& table_name) {
    try {
        connection conn(connection_str);
        work txn(conn);
        result res = txn.exec("SELECT * FROM " + table_name);

        // Заголовок таблиці
        std::cout << "\nTable: " << table_name << "\n";
        std::cout << std::string(50, '-') << "\n";

        // Вивід назв стовпців
        for (int i = 0; i < res.columns(); ++i) {
            std::cout << std::setw(15) << std::left << res.column_name(i) << "|";
        }
        std::cout << "\n" << std::string(50, '-') << "\n";

        // Вивід рядків
        for (const auto& row : res) {
            for (const auto& field : row) {
                std::cout << std::setw(15) << std::left << field.c_str() << "|";
            }
            std::cout << "\n";
        }

        std::cout << std::string(50, '-') << "\n";
    }
    catch (const sql_error& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void DatabaseModel::deleteRow(const std::string& table_name, const std::string& condition) {
    string query = "DELETE FROM " + table_name + " WHERE " + condition + ";";
    executeQuery(query);
}

void DatabaseModel::updateRow(const std::string& table_name, const std::string& set_clause, const std::string& condition) {
    string query = "UPDATE " + table_name + " SET " + set_clause + " WHERE " + condition + ";";
    executeQuery(query);
}

void DatabaseModel::generateData(const std::string& table_name, int count) {
    try {
        connection conn(connection_str);
        work txn(conn);

        // Знаходимо максимальний ID у таблиці
        std::string getMaxIdQuery = "SELECT COALESCE(MAX(courier_id), 0) FROM " + table_name + ";";
        result res = txn.exec(getMaxIdQuery);
        int max_id = res[0][0].as<int>();

        // Генерація даних із наступного ID
        std::string query =
            "INSERT INTO " + table_name + " (courier_id, type, name) "
            "SELECT generate_series(" + std::to_string(max_id + 1) + ", " +
            std::to_string(max_id + count) + "), "
            "'Type ' || generate_series(" + std::to_string(max_id + 1) + ", " +
            std::to_string(max_id + count) + "), "
            "'Name ' || generate_series(" + std::to_string(max_id + 1) + ", " +
            std::to_string(max_id + count) + ");";

        txn.exec(query);
        txn.commit();

        std::cout << "Successfully generated " << count << " records in the table: " << table_name << std::endl;
    }
    catch (const sql_error& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error during data generation: " << e.what() << std::endl;
    }
}

std::vector<std::vector<std::string>> DatabaseModel::executeAndFetch(const std::string& query) {
    try {
        connection conn(connection_str);
        work txn(conn);
        result res = txn.exec(query);

        std::vector<std::vector<std::string>> rows;

        // Додаємо заголовки стовпців
        std::vector<std::string> headers;
        for (int i = 0; i < res.columns(); ++i) {
            headers.push_back(res.column_name(i));
        }
        rows.push_back(headers);

        // Додаємо рядки
        for (const auto& row : res) {
            std::vector<std::string> fields;
            for (const auto& field : row) {
                fields.push_back(field.c_str());
            }
            rows.push_back(fields);
        }

        return rows;
    }
    catch (const std::exception& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        return {};
    }
}
