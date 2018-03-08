#pragma once

#include "skeleton.h"
#include "AnimationSample.h"

#include <common/Types.h>

namespace engine {	namespace animation {

		struct AnimationClip {
			Skeleton *m_pSkeleton;
			F32 m_framesPerSeconds;
			F32 m_duration;
			I32 m_frameCount;
			AnimationSample *m_aSample;
			bool m_isLooping;
		};

}}