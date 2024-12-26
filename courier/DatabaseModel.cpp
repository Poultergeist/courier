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

string DatabaseModel::join(const vector<string>& vec, const string& delimiter, const bool& quotes) {
    ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        const string& item = vec[i];

        // Add quotes for strings if needed, otherwise just append the item
        if (quotes && item.find_first_of("0123456789") == string::npos) {
            oss << "'" << item << "'";
        }
        else {
            oss << item;
        }

        // Only add delimiter if it's not the last element
        if (i < vec.size() - 1) {
            oss << delimiter;
        }
    }
    return oss.str();
}

void DatabaseModel::insert(const string table, const vector<string>& columns, const std::vector<string> values) {
    string query = "INSERT INTO " + table + " (" + join(columns, ", ", false) + ") VALUES (" + join(values, ", ", true) + ");";
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

        // Отримуємо список колонок таблиці
        std::string getColumnsQuery =
            "SELECT column_name FROM information_schema.columns WHERE table_name = '" + table_name + "' ORDER BY ordinal_position;";
        result columnsResult = txn.exec(getColumnsQuery);

        if (columnsResult.empty()) {
            std::cerr << "Table " << table_name << " does not exist or has no columns." << std::endl;
            return;
        }

        std::vector<std::string> columns;
        for (const auto& row : columnsResult) {
            columns.push_back(row["column_name"].c_str());
        }

        // Генеруємо дані для кожної колонки
        std::ostringstream query;
        query << "INSERT INTO " << table_name << " (" << join(columns, ", ", false) << ") VALUES ";

        // Знаходимо максимальний ID для ідентифікаторної колонки
        int max_id = 0;
        if (std::find(columns.begin(), columns.end(), "courier_id") != columns.end() ||
            std::find(columns.begin(), columns.end(), "package_id") != columns.end() ||
            std::find(columns.begin(), columns.end(), "sender_id") != columns.end() ||
            std::find(columns.begin(), columns.end(), "receiver_id") != columns.end() ||
            std::find(columns.begin(), columns.end(), "vehicle_id") != columns.end()) {

            std::string idColumn = columns[0]; // Передбачається, що перший стовпець — це ID
            std::string getMaxIdQuery = "SELECT COALESCE(MAX(" + idColumn + "), 0) FROM " + table_name + ";";
            result maxIdResult = txn.exec(getMaxIdQuery);
            max_id = maxIdResult[0][0].as<int>();
        }

        // Створюємо рядки даних
        for (int i = 0; i < count; ++i) {
            query << "(";
            for (size_t j = 0; j < columns.size(); ++j) {
                const std::string& column = columns[j];
                if (column.find("id") != std::string::npos) {
                    query << max_id + i + 1;
                }
                else if (column.find("name") != std::string::npos) {
                    query << "'Name_" << max_id + i + 1 << "'";
                }
                else if (column.find("type") != std::string::npos) {
                    query << "'Type_" << max_id + i + 1 << "'";
                }
                else if (column.find("money") != std::string::npos) {
                    query << 1000 + (i * 10);
                }
                else if (column.find("weight") != std::string::npos) {
                    query << 50 + i * 5;
                }
                else if (column.find("price") != std::string::npos) {
                    query << 200 + i * 20;
                }
                else if (column.find("speed") != std::string::npos) {
                    query << 60 + i * 2;
                }
                else if (column.find("capacity") != std::string::npos) {
                    query << 500 + i * 50;
                }
                else if (column.find("address") != std::string::npos) {
                    query << "'Address_" << max_id + i + 1 << "'";
                }
                else {
                    query << "NULL";
                }

                if (j < columns.size() - 1) {
                    query << ", ";
                }
            }
            query << ")";
            if (i < count - 1) {
                query << ", ";
            }
        }
        query << ";";

        // Виконання запиту
        txn.exec(query.str());
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
