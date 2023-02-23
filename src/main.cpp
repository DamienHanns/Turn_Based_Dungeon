#include <iostream>
#include "Engine.h"

int main() {
    Engine engine;
    engine.setup();

    engine.loop();

    std::cout << "MAIN loop terminated" << std::endl;

    return 0;
}
