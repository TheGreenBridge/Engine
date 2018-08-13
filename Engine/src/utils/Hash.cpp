//------------------------------------------------------------------------------
// Hash.cpp
//
// implemenation of the Hash class
//
// Author: Sommerauer Christian
// Created: 08.08.18
// Changed: 08.08.18
//------------------------------------------------------------------------------
//

#include <utils\Hash.h>
#include <functional>

namespace engine {

	U32 engine::Hash::toHash(std::string name)
	{
		return static_cast<U32>(std::hash<std::string>()(name));
	}

}
