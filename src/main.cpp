#include "App.h"
#include "Logger.h"

int main() {
    LOG_IV("Starting Application");
    App theApp;
    theApp.run();
    return 0;
}