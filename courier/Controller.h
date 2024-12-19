#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "DatabaseModel.h"
#include "ConsoleView.h"

class Controller {
private:
    DatabaseModel model;
    ConsoleView view;
    void handleInsertCourier();
    void handleViewTable();
    void handleDeleteRow();
    void handleEditData();
    void handleGenerateData();
    void handleSearchData();
public:
    Controller(const DatabaseModel& model, const ConsoleView& view);
    void run();
};

#endif