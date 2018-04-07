#pragma once

#include <math/mat4.h>
#include <common\types.h>
#include <string>

#define SHADER_FOLDER "res/shader/"

namespace engine { namespace graphics{


	struct ShaderSource
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Shader
	{
	private:
		

		U32 m_ShaderID;

		ShaderSource parseFile(const char* path);
		ShaderSource parseFile(const char* vertexPath, const char* fragmentPath);

		U32 load(ShaderSource source);
		
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		Shader(const char* shaderPath);
		Shader() {}
		~Shader();

		void enable() const;
		void disable() const;

		void setUniformMat4(const char *name, const mat4 &matrix) const;
		void setUniform3f(const char *name, const Vec3 &value) const;
		void setUniformMat4Array(const char *name, const F32 *matrix) const;
		void setUniform1f(const char *name, F32 value) const;
		void setUniform1i(const char *name, I32 value) const;
		void setUniformTexture(const char *name, I32 slot ,I32 texture) const;
	};

}}