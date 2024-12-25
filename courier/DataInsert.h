#ifndef DATAINSERT_H
#define DATAINSERT_H

#include "ConsoleView.h"

class DataInsert {
private:
    ConsoleView view;
    void handleInsertCourier();
    void handleInsertPackage();
    void handleInsertReceiver();
    void handleInsertSender();
    void handleInsertVehicle();
public:
    DataInsert(const ConsoleView& view);
    std::string table;

};

#endif