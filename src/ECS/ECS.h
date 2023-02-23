//
// Created by Damien Hanns on 11/02/2023.
//

#ifndef TURN_BASED_DUNGEON_V02_ECS_H
#define TURN_BASED_DUNGEON_V02_ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>


//component set for necessary for Systems to operate on and process.
const unsigned int MAX_COMPONENTS = 16;
typedef std::bitset<MAX_COMPONENTS> ComponentSet;

//allows derived components to have different, and relivent, ID values.
struct IComponent{
protected:
    static int _nextId;
};

//base class for data containers
template <typename T>
class Component : public IComponent{
    static int getId(){
        static auto id = _nextId++;
        return id;
    }
};

//_id will point to a collection of Components.
class Entity {
private:
    int _id;

public:
    Entity(int id) : _id(id){};
    Entity(const Entity& entity) = default;

    int getID() const { return _id;}

    Entity& operator = (const Entity& other) = default;
    bool operator == (const Entity& other) const { return _id == other._id; }
    bool operator != (const Entity& other) const { return _id != other._id; }
    bool operator > (const Entity& other) const { return _id > other._id; }
    bool operator < (const Entity& other) const { return _id < other._id; }
};

//base class for logic systems
//get IDs with components necessary for system and perform logic.
class System {
private:
    ComponentSet _requiredComponentSet;
    std::vector<Entity> _entities;

public :
    System() = default;
    ~System() = default;

    void addEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> getSystemEntities() const { return _entities;};
    const ComponentSet& getComponentSet() const {return _requiredComponentSet;};

    template<typename T> void RequireComponent();
};

//IPool allows for a dataset, point to other datasets of pooled components of varying types.
struct IPool {
    virtual ~IPool() = 0;
};

template <typename T>
class Pool : public IPool{
private:
    std::vector<T> data;

public:
    virtual ~Pool() = default;

    //TODO init pools to a max entity size. Keep max size adjustable.
    // this will greatly reduce resizing.

    Pool(int size = 100){
        data.resize(100);
    }

    bool _bIsEmpty (){ return data.empty(); }

    int getSize(){ return data.size();}

    void resize(int newSize){
        data.resize(newSize);
    }

    void clear(){
        data.clear;
    }

    void add(T object){
        data.push_back(object);
    }

    void set(int index, T object){
        data[index] = object;
    }

    T& get(int index){
        return data[index];
    }

    T& operator [] (unsigned int index){
        return data[index];
    }
};

class Registry {
private :
    //TODO have a max entity number. Let the maximum be flexible - produce warning if original max is exceeded.
    int _numEntities = 0;

    std::vector<IPool*> _componentPools; //=  std::vector<Pool*>(MAX_COMPONENTS);

    //components on a given entity, indexed by entity._id;
    std::vector<ComponentSet> _entityComponentSet;

    std::unordered_map<std::type_index, System*> systemsMap;

    std::set<Entity> _entitiesToAdd;
    std::set<Entity> _entitiesToDeactivate;
    //TODO create a free entity function, so that id can be recycled into something else.

public :
    Registry() = default;

    void update();
    Entity createEntity();

    //component prototypes
    template<typename T, typename ...TArgs> void addComponent(Entity entity, TArgs&& ...args);
    template<typename T> void removeComponent(Entity entity);
    template<typename T> bool hasComponent(Entity entity);

    //system prototypes
    template<typename T, typename ...TArgs> void addSystem(TArgs&& ...args);
    template<typename T> void removeSystem();
    template<typename T> bool bHasSystem() const;
    template<typename T> T& getSystem() const;

    void addEntityToSystem(Entity entity);
};

template<typename T, typename ...TArgs>
void Registry::addSystem(TArgs&& ...args){
    T* newSystem(new System(std::forward<TArgs>(args)... ));
    systemsMap.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
}

template<typename T>
void Registry::removeSystem(){
    auto system = systemsMap.find(std::type_index(typeid(T)));
    systemsMap.erase(system);
}

template<typename T>
bool Registry::bHasSystem() const {
    return systemsMap.find(std::type_index(typeid(T))) != systemsMap.end();
}

template<typename T>
T& Registry::getSystem() const {
    auto system = systemsMap.find(std::type_index(typeid(T)));
    return *(std::static_pointer_cast<T>(system->second));
}


template<typename T>
void System::RequireComponent(){
    const auto componentID = Component<T>::getID();
    _requiredComponentSet.set(componentID);
}

//make sure there is space in IPool and Pool vector then set component.
template<typename T, typename ...TArgs>
void Registry::addComponent(Entity entity, TArgs&& ...args){
    const auto componentID = Component<T>::getId();
    const auto entityID = entity.getID();

    if (componentID >= _componentPools.size()){
        _componentPools.resize(componentID + 1, nullptr);
    }

    if (!_componentPools[componentID]){
        Pool<T>* newComponentPool = new Pool<T>();
        _componentPools[componentID] = newComponentPool;
    }

    Pool<T>* componentPool = _componentPools[componentID];

    if (entityID >= componentPool->getSize()){
        componentPool-> resize(_numEntities);
    }

    T newComponent(std::forward<TArgs>(args)...);

    componentPool ->set(entityID, newComponent);

    _entityComponentSet[entityID].set(componentID);
}

//TODO these functions may require tests to make sure
// components / entityComponentsets exist and can be found.
template<typename T> void Registry::removeComponent(Entity entity){
    const auto componentID = Component<T>::getID();
    const auto entityID = entity.getID();

    _entityComponentSet[entityID].set(componentID, false);
}

template<typename T> bool Registry::hasComponent(Entity entity){
    const auto componentID = Component<T>::getId();
    const auto entityID = entity.getID();

    return _entityComponentSet[entityID].test(componentID);
}

#endif //TURN_BASED_DUNGEON_V02_ECS_H
