#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include <string>
#include <vector>

class DatabaseModel {
private:
    std::string connection_str;
public:
    void executeQuery(const std::string& query);
    DatabaseModel(const std::string& conn_str);
    void insertCourier(const int& courier_id, const std::string& type, const std::string& name);
    void viewTable(const std::string& table_name);
    void deleteRow(const std::string& table_name, const std::string& condition);
    void updateRow(const std::string& table_name, const std::string& set_clause, const std::string& condition);
    void generateData(const std::string& table_name, int count);
    std::vector<std::vector<std::string>> executeAndFetch(const std::string& query);
};

#endif