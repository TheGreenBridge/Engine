//------------------------------------------------------------------------------
// GLCommon.h
//
// OPEN GL implementation of a shader
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Shader.h>
#include <renderapi\opengl\GLCommon.h>
#include <utils\Log.h>
#include <vector>
#include <utils\fileutils.h>

namespace engine { namespace graphics{

	//--------------------------------------------------------------------------
	Shader::Shader(const char* vertexPath, const char* fragmentPath) : 
		m_VertPath(vertexPath), m_FragPath(fragmentPath) 
	{	
		m_ShaderID = load(parseFile(vertexPath, fragmentPath));
	}

	//--------------------------------------------------------------------------
	Shader::Shader(const char* shaderPath) 
	{
		m_ShaderID = load(parseFile(shaderPath));
	}

	//--------------------------------------------------------------------------
	Shader::~Shader() 
	{
		LOG_ERROR("Deleted Shader");
		GLCall(glDeleteProgram(m_ShaderID));
	}
	
	//--------------------------------------------------------------------------
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

	//--------------------------------------------------------------------------
	ShaderSource Shader::parseFile(const char* vertexPath, const char* fragmentPath)
	{
		ShaderSource source;
		source.vertexShader = FileUtils::read_file(vertexPath);
		source.fragmentShader = FileUtils::read_file(fragmentPath);
		return source;
	}

	//--------------------------------------------------------------------------
	U32 Shader::load(ShaderSource source) 
	{
		U32 program = GLCall(glCreateProgram());
		U32 vertex = GLCall(glCreateShader(GL_VERTEX_SHADER));
		U32 fragment = GLCall(glCreateShader(GL_FRAGMENT_SHADER));

		//std::string vertSourceString = FileUtils::read_file(m_VertPath);
		//std::string fragSourceString = FileUtils::read_file(m_FragPath);

		const char *vertSource = source.vertexShader.c_str();
		const char *fragSource = source.fragmentShader.c_str();

		// Vertex Shader
		GLCall(glShaderSource(vertex, 1, &vertSource, NULL));
		GLCall(glCompileShader(vertex));

		int result;
		GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
		if (result == false) {
			int length;
			GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));
			LOG("Length: ", length);
			std::vector<GLchar> error(length);
			GLCall(glGetShaderInfoLog(vertex, length, &length, error.data()));
			LOG("Failed to compile Vertex Shader. ");
			LOG(&error[0]);
			GLCall(glDeleteShader(vertex));
			HALT();
			return 0;
		}

		// Fragment Shader
		GLCall(glShaderSource(fragment, 1, &fragSource, NULL));
		GLCall(glCompileShader(fragment));

		GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
		if (result == false) {
			int length;
			GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));
			std::vector<GLchar> error(length);
			GLCall(glGetShaderInfoLog(fragment, length, &length, error.data()));
			LOG("Failed to compile Fragment Shader. ");
			LOG(&error[0]);
			GLCall(glDeleteShader(fragment));
			HALT();
			return 0;
		}

		// Erstellen des Shader Programms
		GLCall(glAttachShader(program, vertex));
		GLCall(glAttachShader(program, fragment));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		// Die Shader werden nicht mehr gebraucht
		GLCall(glDeleteShader(vertex));
		GLCall(glDeleteShader(fragment));

		return program;
	}

	//--------------------------------------------------------------------------
	void Shader::enable() const {
		GLCall(glUseProgram(m_ShaderID));
	}

	//--------------------------------------------------------------------------
	void Shader::disable() const {
		GLCall(glUseProgram(0));
	}

	//--------------------------------------------------------------------------
	void Shader::setUniform3f(const char* name, const Vec3 &value) const 
	{
		GLint location = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (location == -1) { LOG("Could not find Uniform 3f with name", name); return; }
		GLCall(glUniform3f(location, value.x, value.y, value.z));
	}

	//--------------------------------------------------------------------------
	void Shader::setUniformMat4(const char *name, const mat4 &matrix) const 
	{
		GLint location = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (location == -1) { LOG("Could not find Uniform mat4fv with name", name); return; }
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements));
	}

	//--------------------------------------------------------------------------
	void Shader::setUniformMat4Array(const char *name, const F32 *matrix) const 
	{
		GLint location = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (location == -1) { LOG("Could not find Uniform mat4fva with name", name); return; }
		GLCall(glUniformMatrix4fv(location, 30, GL_FALSE, matrix));
	}

	//--------------------------------------------------------------------------
	void Shader::setUniform1f(const char * name, F32 value) const
	{
		GLint location = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (location == -1) { LOG("Could not find Uniform 1f with name", name); return; }
		GLCall(glUniform1f(location, value));		
	}

	//--------------------------------------------------------------------------
	void Shader::setUniform1i(const char * name, I32 value) const
	{
		GLint location = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (location == -1) { LOG("Could not find Uniform 1i with name", name); return; }
		GLCall(glUniform1i(location, value));
	}

	//--------------------------------------------------------------------------
	void Shader::setUniformTexture(const char * name, I32 slot, 
		I32 texture) const
	{
		GLint location = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (location == -1) 
		{ 
			std::string errortext = "Could not find Uniform Texture with name" + std::string(name);
			LOG_ERROR(errortext.c_str()); 
			return; 
		}

		GLCall(glUniform1i(location, slot));
		switch (slot) 
		{
			case 0: GLCall(glActiveTexture(GL_TEXTURE0)); break;
			case 1: GLCall(glActiveTexture(GL_TEXTURE1)); break;
			case 2: GLCall(glActiveTexture(GL_TEXTURE2)); break;
			case 3: GLCall(glActiveTexture(GL_TEXTURE3)); break;
			case 4: GLCall(glActiveTexture(GL_TEXTURE4)); break;
			case 5: GLCall(glActiveTexture(GL_TEXTURE5)); break;
			default: LOG_ERROR("Slot not supported");
		}
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));
	}

	void Shader::setUniformBlockIndex(const char * name, U32 slot)
	{
		U32 index =  GLCall(glGetUniformBlockIndex(m_ShaderID, name));
		GLCall(glUniformBlockBinding(m_ShaderID, index, slot));
	}

	//--------------------------------------------------------------------------
	/*void Shader::setUniformBuffer(const UniformBuffer& buffer, 
		const char* name) 
	{
		U32 block_index = glGetUniformBlockIndex(m_ShaderID, name);

		glBindBufferBase(GL_UNIFORM_BUFFER, m_UniformIndex, buffer.getHandle());
		glUniformBlockBinding(m_ShaderID, block_index, m_UniformIndex);

		m_UniformIndex++;
	}*/
}}