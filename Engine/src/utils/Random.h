//------------------------------------------------------------------------------
// File Name: Random.h
// Description: Generates random numbers
//
// Author: Sommerauer Christian
// Created: 17.08.2018
// Changed: 17.08.2018
//------------------------------------------------------------------------------
//


#pragma once

#include <common\types.h>
#include <random>

namespace engine {

	class Random
	{
	public:

		Random();
		F32 generateF32(F32 max = std::numeric_limits<F32>::max());
		U32 generateInt(U32 max = std::numeric_limits<U32>::max());

	private:
		std::random_device ranDev;
		std::mt19937 mt;
	
	};
}
