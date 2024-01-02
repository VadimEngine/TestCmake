#include "App.h"
#include "Logger.h"
#include <iostream>
#include <filesystem>

int main() {
    LOG_IV("Starting Application from %s", std::filesystem::current_path().string().c_str());
    App theApp;
    theApp.run();
    return 0;
}