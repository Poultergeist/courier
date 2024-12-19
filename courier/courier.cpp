#include "DatabaseModel.h"
#include "ConsoleView.h"
#include "Controller.h"

int main() {
    const std::string connection_string = "host=localhost port=5432 dbname=courier_service user=postgres password=dsaqwe0112554";
    DatabaseModel model(connection_string);
    ConsoleView view;
    Controller controller(model, view);

    controller.run();

    return 0;
}