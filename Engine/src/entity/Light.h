#pragma once

#include "../math/vec3.h"

namespace engine {	namespace graphics {

	class Light {
	private:
		Vec3 m_Position;
		Vec3 m_Color;
	public:
		Light(const Vec3 &position, const Vec3 &color);
		const Vec3 &getPosition()const { return m_Position; }
		void setPosition(const Vec3 &position) { m_Position = position; }
		void translate(const Vec3 &translation) { m_Position += translation; }
	
		void setColor(const Vec3 &color) { m_Color = color; }
		Vec3 getColor() const { return m_Color; }
	};

}}