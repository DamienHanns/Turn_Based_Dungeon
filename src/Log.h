//
// Created by Damien Hanns on 10/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_LOG_H
#define TURN_BASED_DUNGEON_V02_LOG_H

#include <iostream>
#include <string>
#include "Time.h"

//BUG if the individual static functions called sequentially they might execute twice.
//found by testing this in Engine::loop.
struct Log {
    inline static void out(const std::string& logMessage){
        std::cout << Time::getCurrentTime() << ": "<< logMessage << "\n";
    }

    inline static void err(const std::string& errMessage){
        std::cerr << Time::getCurrentTime() << ": " << errMessage << "\n";
    }
};

#endif //TURN_BASED_DUNGEON_V02_LOG_H
