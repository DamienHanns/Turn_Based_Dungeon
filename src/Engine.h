//
// Created by Damien Hanns on 05/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_ENGINE_H
#define TURN_BASED_DUNGEON_V02_ENGINE_H

#include <SDL2/SDL.h>
#include "Settings.h"
#include "Time.h"

class Engine {
private:
    bool _bIsRunning = false;

    Settings* _settings = new Settings;
    const int TIME_BETWEEN_FRAMES = 1000 / _settings -> frameRateCap;
    int _nextFrameTime = -1.0f;

    Time time;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    struct testObject{
        float posX = 20.0f;
        float posY = 20.0f;

        SDL_Rect testObjectRect {20, 20, 20, 20};
    } _testObject;


    void processInput();
    void update();
    void render();
    void destroy();

public:
    void setup();
    void loop();
};


#endif //TURN_BASED_DUNGEON_V02_ENGINE_H
