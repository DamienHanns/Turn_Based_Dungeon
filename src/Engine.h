//
// Created by Damien Hanns on 05/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_ENGINE_H
#define TURN_BASED_DUNGEON_V02_ENGINE_H

#include <SDL2/SDL.h>
#include "Settings.h"

class Engine {
private:
    bool _bIsRunning = false;

    Settings* _settings = new Settings;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    void processInput();
    void update();
    void render();
    void destroy();

public:
    void setup();
    void run();
};


#endif //TURN_BASED_DUNGEON_V02_ENGINE_H
