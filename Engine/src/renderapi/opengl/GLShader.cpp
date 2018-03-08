#include <graphics\api\Shader.h>
#include <renderapi\opengl\GLCommon.h>
#include <utils\Log.h>
#include <vector>
#include <utils\fileutils.h>

namespace engine { namespace graphics{
	Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_VertPath(vertexPath), m_FragPath(fragmentPath) {
		m_ShaderID = load();
		//LOG("Shader ID", m_ShaderID);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	U32 Shader::load() {
		U32 program = glCreateProgram();
		U32 vertex = glCreateShader(GL_VERTEX_SHADER);
		U32 fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = FileUtils::read_file(m_VertPath);
		std::string fragSourceString = FileUtils::read_file(m_FragPath);

		const char *vertSource = vertSourceString.c_str();
		const char *fragSource = fragSourceString.c_str();

		// Vertex Shader
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		int result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == false) {
			int length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			LOG("Length: ", length);
			std::vector<GLchar> error(length);
			glGetShaderInfoLog(vertex, length, &length, error.data());
			LOG("Failed to compile Vertex Shader. ");
			LOG(&error[0]);
			glDeleteShader(vertex);
			return 0;
		}

		// Fragment Shader
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == false) {
			int length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> error(length);
			glGetShaderInfoLog(fragment, length, &length, error.data());
			LOG("Failed to compile Fragment Shader. ");
			LOG(&error[0]);
			glDeleteShader(fragment);
			return 0;
		}

		// Erstellen des Shader Programms
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		glValidateProgram(program);

		// Die Shader werden nicht mehr gebraucht
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::enable() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const {
		glUseProgram(0);
	}


	void Shader::setUniform3f(const char* name, const Vec3 &value) const {
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform with name", name); return; }
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::setUniformMat4(const char *name, const mat4 &matrix) const {
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform with name", name); return; }
		glUniformMatrix4fv(location, GL_FALSE, 1, matrix.elements);
	}

	void Shader::setUniformMat4Array(const char *name, const F32 *matrix) const {
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform with name", name); return; }
		glUniformMatrix4fv(location, 30, GL_FALSE, matrix);
	}

}}