#ifndef INSTANCE_COLLECTION_HPP
#define INSTANCE_COLLECTION_HPP





#include <stdafx.h>






/**
Entity data is stored here
*/
class InstanceCollection : public AStateSaver, public ACollection
{


private:




    std::map<std::string, boost::shared_ptr<EntityInstance> > instance_map;




public:






    /**
    Load data from file
    */
    AVoid Load();
    /**
    Save data to file
    */
    AVoid Save();
    /**
    Reset data
    */
    AVoid Reset();







    /**
    Get how many instances are in scene
    */
    inline AUInt GetNumberOfInstances(){ return instance_map.size(); }
    /**
    Get instance at position 'index'
    */
    inline EntityInstance * GetInstance(std::string name){ return instance_map[name].get(); }
    /**
    Add instance to scene
    */
    inline AVoid AddInstance(std::string name, EntityInstance * new_instance)
    {
        instance_map.insert(std::pair<std::string, boost::shared_ptr<EntityInstance> >(name, boost::shared_ptr<EntityInstance>(new_instance)));
    }
    /**
    Get instance map pointer
    */
    inline std::map<std::string, boost::shared_ptr<EntityInstance> > * GetInstanceMapPointer(){return &instance_map;}
    /**
    Clear instances
    */
    inline AVoid ClearInstances(){ instance_map.clear(); }
    /**
    See if instance with 'name' exists
    */
    inline ABoolean InCollection(std::string name){ return instance_map.count(name) > 0; }







};




#endif
