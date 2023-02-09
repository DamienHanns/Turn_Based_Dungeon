//
// Created by Damien Hanns on 05/02/2023.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Engine.h"
#include "Time.h"

//Create basic elements for Engine and Game.
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
            nullptr,
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
                                   _settings -> _bEnableVSync ?
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC : SDL_RENDERER_ACCELERATED
                                   );
    if (!_renderer){
        std::cerr << "renderer creation FAILED" << std::endl;
        return;
    }

    _bIsRunning = true;
}

//if basic setup done, run game loop.
//game FPS capped - additional sleep/delay functions not implemented.
void Engine::loop() {
    if (!_bIsRunning) {
        std::cerr << " engine NOT SETUP to loop" << std::endl;
        return;
    }

    while(_bIsRunning)
    {
        if  (Time::getTimeRaw() <= _nextFrameTime) { continue;}

        time.updateTime();
        _nextFrameTime = Time::getTimeRaw() + TIME_BETWEEN_FRAMES;

        processInput();
        update();
        render();
    }

    destroy();
}


//easy exit functionality
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

//testing functions and APIs.
//a lot of this to be moved into systems and components later

void Engine::update() {
    _testObject.posX += 10 * Time::getDelta();

    _testObject.testObjectRect.x = (int)_testObject.posX;
}

void Engine::render() {
    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &_testObject.testObjectRect);

    SDL_RenderPresent(_renderer);
}

void Engine::destroy() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}


