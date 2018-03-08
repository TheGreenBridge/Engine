#pragma once

#include "Joint.h"

namespace engine {	namespace animation {
	struct Skeleton {
		// 
		unsigned int m_jointCount;
		Joint *m_aJoint; // 
	};
}}