#ifndef ENTITY_COLLECTION_HPP
#define ENTITY_COLLECTION_HPP




#include <stdafx.h>
#define OBJECT_FOLDER "data/objects/"





/**
Stores entity information
*/
class EntityCollection : public AModule, public ACollection
{


    std::map<std::string, boost::shared_ptr<Entity> > entity_map;



    /**
    Function for adding components to entity
    */
    AVoid CreateComponentInstance(boost::filesystem::directory_iterator iterator, AComponent * new_component, std::string class_name, Entity * new_entity);
    /**
    Based on the files in path you provide ScenInfo adds specific components to the given entity
    */
    AVoid AddComponentsToEntity(std::string path, Entity * new_entity);
    /**
    Adds entity to the entity map
    */
    AVoid AddEntity(Entity* new_entity);




public:




    /**
    Load entities
    */
    AVoid Init();
    /**
    Release entities
    */
    AVoid Clean();
    /**
    Match interface
    */
    inline AVoid Enable() {}




    /**
    Get entity with provided key
    */
    inline Entity* GetEntity(std::string name){ return entity_map[name].get(); }
    /**
    Get number of entities in map
    */
    inline AUInt GetNumberOfEntities(){ return entity_map.size(); }
    /**
    Clear entity map
    */
    inline AVoid ClearEntities(){ entity_map.clear(); }
    /**
    See if entity with 'name' exists
    */
    inline ABoolean InCollection(std::string name) {return entity_map.count(name) > 0;}








};







#endif
