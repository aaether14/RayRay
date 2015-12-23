#ifndef PIPELINE
#define PIPELINE





#include <stdafx.h>






class Pipeline : public AModule
{




public:




	/**
	Initialize data
	*/
	void Init();


	/**
	Enable pipeline
	*/
	void Enable();
	/**
	Clean data
	*/
	void Clean();


};

#endif