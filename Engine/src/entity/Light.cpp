#include "Light.h"
namespace engine {	namespace graphics {
	Light::Light() : m_Position(Vec3(0.0,0.0,0.0)), m_Color(Vec3(1.0,1.0,1.0))
	{
	}
	Light::Light(const Vec3 &position, const Vec3 &color) :
		m_Position(position), m_Color(color)
	{
	}	

}}


