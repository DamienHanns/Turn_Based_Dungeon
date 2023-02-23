//
// Created by Damien Hanns on 11/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_TRANSFORMCOMPONENT_H
#define TURN_BASED_DUNGEON_V02_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec2 _position;
    glm::vec2 _scale;
    float _rotation;

    TransformComponent(glm::vec2 position = glm::vec2 (0,0), glm::vec2 scale = glm::vec2 (1,1), float rotation = 0.0f) :
    _position(position), _scale(scale), _rotation(rotation){};
};


#endif //TURN_BASED_DUNGEON_V02_TRANSFORMCOMPONENT_H
