//
// Created by Damien Hanns on 05/02/2023.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Engine.h"

void Engine::setup() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL Init Failed" << std::endl;
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0,&displayMode);

    int windowW =  _settings->_maxResolution ? displayMode.w : _settings->_windowSizeX;
    int windowH =  _settings->_maxResolution ? displayMode.h : _settings->_windowSizeY;

    //needs SDL_WINDOW_RESIZABLE - NOT SDL_WINDOW_FULLSCREEN - or errors with no display.
    //full screen set after.
    _window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowW, windowH,
            _settings->_bFullScreen ? SDL_WINDOW_RESIZABLE : SDL_WINDOW_BORDERLESS
            );

    if(!_window){
        std::cerr << "window creation FAILED" << std::endl;
        return;
    }

    if (_settings -> _bFullScreen) {SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);}

    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   _settings -> _bEnableVSync ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                   : SDL_RENDERER_ACCELERATED
                                   );
    if (!_renderer){
        std::cerr << "renderer creation FAILED" << std::endl;
        return;
    }

    _bIsRunning = true;
}

void Engine::run() {
    if (!_bIsRunning) {
        std::cerr << " engine NOT SETUP to run" << std::endl;
        return;
    }

    while(_bIsRunning)
    {
        processInput();
        update();
        render();
    }

    destroy();
}

void Engine::processInput() {
    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)){
        switch (inputEvent.type){
            case SDL_QUIT:
                _bIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (inputEvent.key.keysym.sym == SDLK_ESCAPE) {
                    _bIsRunning = false;
                }
                break;
            default:
                break;
        }
    }
}

void Engine::update() {

}

void Engine::render() {
    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_Rect testObject {100, 100, 200, 200};

    SDL_RenderFillRect(_renderer, &testObject);
    SDL_RenderPresent(_renderer);
}

void Engine::destroy() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}


