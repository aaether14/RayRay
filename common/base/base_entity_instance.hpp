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
	Every instance should have a way to affect scene
	*/
	virtual void Enable(AModule * manager) = 0;



	/**
	Get vector of child nodes
	*/
	inline AEntityInstance* GetChildNode(GLuint i){ return child_nodes[i].get(); }
	/**
	Get number of childs
	*/
	inline GLuint GetNumberOfChilds(){ return child_nodes.size(); }
	/**
	Add child node
	*/
	inline void AddChildNode(AEntityInstance* new_child){ child_nodes.push_back(boost::shared_ptr<AEntityInstance>(new_child)); }




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
	Get first adress of datas map
	*/
	inline std::map<std::string, boost::shared_ptr<AData> >::iterator GetFirstAdata(){ return adatas.begin(); }
	/**
	Get last adress of datas map
	*/
	inline std::map<std::string, boost::shared_ptr<AData> >::iterator GetLastAdata(){ return adatas.end(); }







	/**
	Get entity name
	*/
	inline std::string GetEntityName(){ return entity_name; }
	/**
	Set entity name
	*/
	inline void SetEntityName(std::string name){ entity_name = name; }



private:



	std::vector<boost::shared_ptr<AEntityInstance> > child_nodes;
	std::map<std::string, boost::shared_ptr<AData> > adatas;


	std::string entity_name;




protected:




};



#endif