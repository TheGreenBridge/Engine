#pragma once

#include <math/mat4.h>
#include <common\types.h>

namespace engine { namespace graphics{
	class Shader
	{
	private:
		U32 m_ShaderID;
		U32 load();
		const char* m_VertPath;
		const char* m_FragPath;
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void enable() const;
		void disable() const;

		void setUniformMat4(const char* name, const mat4 &matrix) const;
		void setUniform3f(const char* name, const Vec3 &value) const;
		void setUniformMat4Array(const char*name, const F32 *matrix) const;
	};

}}