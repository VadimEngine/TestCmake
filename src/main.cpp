// standard lib
#include <filesystem>
// project
#include "App.h"
#include "Logger.h"

int main() {
    LOG_IV("Starting Application from %s", std::filesystem::current_path().string().c_str());
    App theApp;
    theApp.setScene(new menu_scene::MenuScene(theApp));
    theApp.run();
    return 0;
}