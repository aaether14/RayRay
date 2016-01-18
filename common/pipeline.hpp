#ifndef PIPELINE
#define PIPELINE





#include <stdafx.h>






class Pipeline : public AModule
{




public:




	/**
	Initialize data
	*/
	AVoid Init();


	/**
	Enable pipeline
	*/
	AVoid Enable();
	/**
	Clean data
	*/
	AVoid Clean();


};

#endif