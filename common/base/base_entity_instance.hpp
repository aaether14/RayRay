#ifndef BASE_ENTITY_INSTANCE_HPP
#define BASE_ENTITY_INSTANCE_HPP





#include <stdafx.h>







/**
Interface for entity instance
*/
class AEntityInstance
{


public:






    /**
    Cleaning routine
    */
    inline void Clean(){adatas.clear();}

    /**
    Every instance should have a way to affect scene
    */
    virtual void Enable(AModule * manager) = 0;





    //Data management


    /**
    Add data to entity instance
    */
    inline void AddAData(std::string name, AData * adata)
    {
        adatas.insert(std::pair<std::string, boost::shared_ptr<AData> >(name, boost::shared_ptr<AData>(adata)));
    }
    /**
    Get data from entity instance
    */
    inline AData * GetAData(std::string name){ return adatas[name].get(); }
    /**
    Get adatas map pointer
    */
    inline std::map<std::string, boost::shared_ptr<AData> > *GetADatasMapPointer(){ return &adatas; }






    /**
    Get entity name
    */
    inline std::string GetEntityName(){ return entity_name; }
    /**
    Set entity name
    */
    inline void SetEntityName(std::string name){ entity_name = name; }




private:



    std::map<std::string, boost::shared_ptr<AData> > adatas;
    std::string entity_name;




protected:




};



#endif
