#include <graphics\api\Shader.h>
#include <renderapi\opengl\GLCommon.h>
#include <utils\Log.h>
#include <vector>
#include <utils\fileutils.h>

namespace engine { namespace graphics{

	Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_VertPath(vertexPath), m_FragPath(fragmentPath) {	
		m_ShaderID = load(parseFile(vertexPath, fragmentPath));
		//LOG("Shader ID", m_ShaderID);
	}

	Shader::Shader(const char* shaderPath) {
		m_ShaderID = load(parseFile(shaderPath));
		//LOG("Shader ID", m_ShaderID);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}
	

	ShaderSource Shader::parseFile(const char* path)
	{
		std::string rawData = FileUtils::read_file(path);
		std::string vertexDelimiter = "#VERTEX_SHADER";
		std::string fragmentDelimiter = "#FRAGMENT_SHADER";

		U32 vertexStart = rawData.find(vertexDelimiter) + vertexDelimiter.length();
		U32 fragmentStart = rawData.find(fragmentDelimiter);
		U32 vertexLength = fragmentStart - vertexStart;
		fragmentStart += fragmentDelimiter.length();
		U32 fragmentLength = rawData.length() - fragmentStart;

		ShaderSource source;
		source.vertexShader = rawData.substr(vertexStart, vertexLength);
		source.fragmentShader = rawData.substr(fragmentStart, fragmentLength);


		return source;
	}

	ShaderSource Shader::parseFile(const char* vertexPath, const char* fragmentPath)
	{
		ShaderSource source;
		source.vertexShader = FileUtils::read_file(vertexPath);
		source.fragmentShader = FileUtils::read_file(fragmentPath);
		return source;
	}

	U32 Shader::load(ShaderSource source) {
		U32 program = glCreateProgram();
		U32 vertex = glCreateShader(GL_VERTEX_SHADER);
		U32 fragment = glCreateShader(GL_FRAGMENT_SHADER);

		//std::string vertSourceString = FileUtils::read_file(m_VertPath);
		//std::string fragSourceString = FileUtils::read_file(m_FragPath);

		const char *vertSource = source.vertexShader.c_str();
		const char *fragSource = source.fragmentShader.c_str();

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
			HALT();
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
			HALT();
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
		if (location == -1) { LOG("Could not find Uniform 3f with name", name); return; }
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::setUniformMat4(const char *name, const mat4 &matrix) const {
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform mat4fv with name", name); return; }
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements);
	}

	void Shader::setUniformMat4Array(const char *name, const F32 *matrix) const {
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform mat4fva with name", name); return; }
		glUniformMatrix4fv(location, 30, GL_FALSE, matrix);
	}

	void Shader::setUniform1f(const char * name, F32 value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform 1f with name", name); return; }
		glUniform1f(location, value);
		
	}

	void Shader::setUniform1i(const char * name, I32 value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform 1i with name", name); return; }
		glUniform1i(location, value);
	}

	void Shader::setUniformTexture(const char * name, I32 slot, I32 texture) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) { LOG("Could not find Uniform Texture with name", name); return; }
		glUniform1i(location, slot);
		switch (slot) 
		{
			case 0: glActiveTexture(GL_TEXTURE0); break;
			case 1: glActiveTexture(GL_TEXTURE1); break;
			case 2: glActiveTexture(GL_TEXTURE2); break;
			case 3: glActiveTexture(GL_TEXTURE3); break;
			case 4: glActiveTexture(GL_TEXTURE4); break;
			case 5: glActiveTexture(GL_TEXTURE5); break;
			default: LOG_ERROR("Slot not supported");
		}
		glBindTexture(GL_TEXTURE_2D, texture);
	}

}}