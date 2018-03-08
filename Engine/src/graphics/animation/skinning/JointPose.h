#pragma once

#include <math/Quaternion.h>
#include <math/vec3.h>
#include <common/types.h>

namespace engine {	namespace animation {
	struct JointPose {
		// JointPose = 32 Bytes
		Quaternion m_rot; // 4 * 4 Bytes = 16 Bytes
		Vec3 m_trans; // 4 * 3 Bytes = 12 Bytes
		float m_scale; // 4 Bytes
	};
}}

