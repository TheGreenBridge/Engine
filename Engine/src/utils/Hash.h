//------------------------------------------------------------------------------
// Hash.h
//
// Class to generates hashes
//
// Author: Sommerauer Christian
// Created: 08.08.18
// Changed: 08.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>
#include <string>

namespace engine {

	class Hash
	{
	private:

	public:
		static U32 toHash(std::string name);
	};
}