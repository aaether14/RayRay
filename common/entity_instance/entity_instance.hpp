#ifndef ENTITY_INSTANCE_HPP
#define ENTITY_INSTANCE_HPP





#include <stdafx.h>






class EntityInstance : public AEntityInstance
{




public:





	/**
	Match interface and determine how instance affects scene
	*/
	AVoid Enable(AModule * manager);




};





#endif