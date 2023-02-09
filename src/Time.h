//
// Created by Damien Hanns on 08/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_TIME_H
#define TURN_BASED_DUNGEON_V02_TIME_H

#include <SDL2/SDL.h>

//much of the class is static for easier functionality
//when creating gameEntities.
class Time {
private:
    float _timeLastTick;

    inline static float _currentRawTime = 0.0f;

    inline static double delta = 0.0f;

    double calculateDelta()  {
        return (_currentRawTime - _timeLastTick) / 1000;
    }

public:
    void updateTime() {
        _timeLastTick = _currentRawTime;

        _currentRawTime = SDL_GetTicks();

        delta = calculateDelta();
    };

    int getTimeLastTick () { return _timeLastTick; }

    inline static float getCurrentTime() { return  SDL_GetTicks() / 1000; }

    inline static float getTimeRaw() {  return SDL_GetTicks(); }

    inline static double getDelta() { return delta; };
};

#endif //TURN_BASED_DUNGEON_V02_TIME_H
