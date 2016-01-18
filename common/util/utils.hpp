#ifndef UTILS_HPP
#define UTILS_HPP




#include <stdafx.h>





/**


Just a class to provide quads for WTT


*/
class Quad
{


	AUInt m_VAO, m_VBO;



public:



	/**
	Calls Init()
	*/
	inline Quad(){ this->Init(); }
	/**
	Initializes data
	*/
	AVoid Init();


	/**
	Calls Clean()
	*/
	inline ~Quad(){ this->Clean(); }
	/**
	Cleans data
	*/
	AVoid Clean();


	/**
	Renders quad
	*/
	AVoid Render();


};



#endif