#pragma once

#include "JointPose.h"

namespace engine {	namespace animation {
	struct AnimationSample {
		JointPose *m_aJointPose;
		float m_timeStamp; // Keyframe
	};
}}
