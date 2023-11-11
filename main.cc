#include <iostream>
#include "controllers/AuthController.h"
#include <drogon/drogon.h>

using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

void registerDefaultRoute() {
    // Register root route
    app().registerHandler(
        "/",
        [](
    const HttpRequestPtr&req, function<void(
        const HttpResponsePtr&)>&&callback) {
            Json::Value response;
            response["status"] = "up";
            HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response);
            callback(resp);
        });
}

void dropTables() {
}

void runServer() {
    // Set log level
    app().setLogLevel(trantor::Logger::kTrace);

    // Load config file
    try {
        app().loadConfigFile("../config.json");
    }
    catch (const exception&e) {
        cerr << "Exception caught: "
                << typeid(e).name() << " - " << e.what() << endl;
    }

    // Register routes
    registerDefaultRoute();

    // Run server
    LOG_INFO << "Server running on 127.0.0.1:3000";
    app().run();
}

int main(int argc, char* argv[]) {
    // Generate config file from .env
    // generateConfigFile();

    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        // cerr << "Usage: "
        //         "--action=run-server|create-tables|drop-tables"
        //      << endl;
        runServer();
        return 0;
    }

    // Parse the command-line argument
    string action = argv[1];

    // Extract the action from the argument
    size_t equalsPos = action.find('=');
    if (equalsPos == string::npos || equalsPos == action.length() - 1) {
        cerr << "Invalid argument format" << endl;
        return 1;
    }

    string key = action.substr(0, equalsPos);
    string value = action.substr(equalsPos + 1);

    // Check the action and perform the corresponding operation
    if (key == "--action") {
        if (value == "run-server") {
            runServer();
        }
        else {
            cerr << "Invalid action" << endl;
            return 1;
        }
    }
    else {
        cerr << "Invalid argument" << endl;
        return 1;
    }

    return 0;
}
