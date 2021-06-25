#include<iostream>
#include "konzola.hpp"
#include "gui.hpp"
using namespace std;
int main(int argc, char** argv) {
    Engine* engine = nullptr;
    if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "--konzola") {
            engine = new Konzola();
        }
        else {
            engine = new Gui();
        }
    }
    else {
        engine = new Gui();
    }
    engine->start();
    delete engine;
    return 0;
}