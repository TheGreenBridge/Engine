#pragma once

//#include "../../math/mat4.h"
//#include "../../graphics/animation/AnimationHandle.h"
//#include "../../graphics/animation/skinning/RenderableSkin.h"

struct mat4;

namespace engine {
	namespace animation {
		struct RenderableSkin;
		struct AnimationHandle;
	}
}

namespace engine { 	namespace animation {
	struct Animatable {
		mat4 *m_pBones;
		AnimationHandle *m_pHandle;
		RenderableSkin * m_pSkin;
	};
}}