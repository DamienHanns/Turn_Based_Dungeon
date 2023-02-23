//
// Created by Damien Hanns on 11/02/2023.
//

#include <string>
#include "ECS.h"
#include "../Log.h"

int IComponent::_nextId = 0;

void System::addEntityToSystem(Entity entity) {
    _entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    _entities.erase(std::remove_if(
            _entities.begin(), _entities.end(),
            [&entity] (Entity other){
                return entity == other;
                }),
            _entities.end());
}

Entity Registry::createEntity() {
    int entityID = _numEntities++;

    const Entity entity(entityID);

    _entitiesToAdd.insert(entity);

    Log::out ("entity created, ID: " + std::to_string(entityID));

    return entity;
}

void Registry::addEntityToSystem(Entity entity) {
    const auto  id = entity.getID();
    const auto& entityCompoentSet = _entityComponentSet[id];

    for(auto& system: systemsMap){
        const auto& systemComponentSet = system.second -> getComponentSet();

        bool bHasMatchingSets = (entityCompoentSet & systemComponentSet) == systemComponentSet;

        if (bHasMatchingSets){
            system.second->addEntityToSystem(entity);
        }

    }


}
