//
// Created by Damien Hanns on 06/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_SETTINGS_H
#define TURN_BASED_DUNGEON_V02_SETTINGS_H

#include <SDL2/SDL.h>


struct Settings{

    int _windowSizeX = 600;
    int _windowSizeY =  600;
    bool _maxResolution = false;

    bool _bFullScreen = false;

    bool _bEnableVSync = false;

    const int frameRateCap = 20;
};


#endif //TURN_BASED_DUNGEON_V02_SETTINGS_H
