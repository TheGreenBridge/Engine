//------------------------------------------------------------------------------
// File Name: Random.cpp
// Description: Implementation of the random generator
//
// Author: Sommerauer Christian
// Created: 17.08.2018
// Changed: 17.08.2018
//------------------------------------------------------------------------------
//


#include "Random.h"


namespace engine{

	Random::Random() : ranDev(), mt(ranDev())
	{
	
	}

	U32 Random::generateInt(U32 max) 
	{
		std::uniform_int_distribution<U32> intDist(0, max);
		return intDist(mt);
	}

	F32 Random::generateF32(F32 max) 
	{
		std::uniform_real_distribution<F32> realDist(0, max);
		return realDist(mt);
	}
}
