#ifndef ENTITY_HPP
#define ENTITY_HPP




#include <stdafx.h>



/**


Entity implmentation
Stores components


*/
class Entity : public ACollection
{



	std::map<std::string, boost::shared_ptr<AComponent> > components;




public:




	/**
	Render if components have required info
	*/
	void Render(AModule * manager, AEntityInstance * entity_instance);



	/**
	Add a component to the entity
	*/
	inline void AddComponent(std::string name, AComponent *comp)
	{ 
		components.insert(std::pair<std::string, boost::shared_ptr<AComponent> >(name, boost::shared_ptr<AComponent>(comp)));
	}
	/**
	Get component by key
	*/
	inline AComponent*GetComponent(std::string name){ return components[name].get(); }
	/**
	Get number of components
	*/
	inline GLuint GetComponentsSize(){ return components.size(); }



    /**
    See if component with 'name' exists
    */
    inline bool InCollection(std::string name){return components.count(name) > 0;}




	/**
	Calls Clean()
	*/
	inline ~Entity(){ Clean(); }
	/**
	Cleans data
	*/
	void Clean();


};






#endif
