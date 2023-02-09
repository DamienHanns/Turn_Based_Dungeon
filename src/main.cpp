#include <iostream>
#include "Engine.h"



int main() {

    Engine engine;
    engine.setup();

    engine.loop();
    std::cout << "Hello, World!  " << std::endl;
    return 0;
}
