#pragma once

#include <math/mat4.h>

namespace engine {	namespace animation {

	struct Joint {

		const char *m_name;
		int m_iParent; // 4 bytes
		mat4 m_invBindPose; // 64 bytes
		mat4 m_globalTransform; // 64 bytes
	};

}}
