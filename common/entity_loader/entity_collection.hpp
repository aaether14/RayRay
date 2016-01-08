#ifndef ENTITY_COLLECTION_HPP
#define ENTITY_COLLECTION_HPP




#include <stdafx.h>
#define OBJECT_FOLDER "data/objects/"





/**
Stores entity information
*/
class EntityCollection : public AModule
{


    std::map<std::string, boost::shared_ptr<Entity> > entity_map;



    /**
    Function for adding components to entity
    */
    void CreateComponentInstance(boost::filesystem::directory_iterator iterator, AComponent * new_component, std::string class_name, Entity * new_entity);
    /**
    Based on the files in path you provide ScenInfo adds specific components to the given entity
    */
    void AddComponentsToEntity(std::string path, Entity * new_entity);
    /**
    Adds entity to the entity map
    */
    void AddEntity(Entity* new_entity);




public:




    /**
    Load entities
    */
    void Init();
    /**
    Release entities
    */
    void Clean();
    /**
    Match interface
    */
    inline void Enable() {}




    /**
    Get entity with provided key
    */
    inline Entity* GetEntity(std::string name){ return entity_map[name].get(); }
    /**
    Get entity with provided index
    */
    inline Entity* GetEntity(GLuint counter){ std::map<std::string, boost::shared_ptr<Entity> >::iterator it(entity_map.begin()); std::advance(it, counter); return it->second.get(); }
    /**
    Get number of entities in map
    */
    inline GLuint GetNumberOfEntities(){ return entity_map.size(); }
    /**
    Clear entity map
    */
    inline void ClearEntities(){ entity_map.clear(); }
    /**
    See if entity with 'name' exists
    */
    inline GLboolean EntityExists(std::string name){return entity_map.count(name);}








};







#endif
