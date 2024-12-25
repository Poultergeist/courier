#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include <string>
#include <vector>

class DatabaseModel {
private:
    std::string connection_str;
public:
    std::string join(const std::vector<std::string>& vec, const std::string& delimiter, const bool& quotes);
    void executeQuery(const std::string& query);
    DatabaseModel(const std::string& conn_str);

    void insert(const std::string table, const std::vector<std::string>& columns, const std::vector<std::string> values);

    void viewTable(const std::string& table_name);
    void deleteRow(const std::string& table_name, const std::string& condition);
    void updateRow(const std::string& table_name, const std::string& set_clause, const std::string& condition);
    void generateData(const std::string& table_name, int count);
    std::vector<std::vector<std::string>> executeAndFetch(const std::string& query);
};

#endif