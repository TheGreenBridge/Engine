#include "../../entity/component/Transform.h"
#include "Animation.h"
#include "Interpolation.h"


//Animation::Animation():
//	m_start(Transform(vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f)), m_end(Transform(vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f))
//{}

namespace engine {	namespace animation {
	Animation::Animation(Transform startV, Transform endV) :
		m_start(startV), m_end(endV)//, m_speed(speed)
	{}

	Animation::~Animation()
	{}

	Vec3 Animation::getPosition(const float deltaTime) const {
		return ani_lerp(m_start.position, m_end.position, deltaTime);
	}

	Quaternion Animation::getRotation(const float deltaTime) const {
		return ani_lerp(m_start.rotation, m_end.rotation, deltaTime);
	}

	float Animation::getScale(const float deltaTime) const {
		return ani_lerp(m_start.scale, m_end.scale, deltaTime);
	}

}}

