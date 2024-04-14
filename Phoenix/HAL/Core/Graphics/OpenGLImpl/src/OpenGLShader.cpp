#include "../include/OpenGLShader.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Log/include/Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Application/include/Application.h"
#include "Utils/FileSystem.h"
#include "Utils/Timer.h"

namespace Phoenix
{
	std::string ShaderDirectory = FileSystem::GetAssetsPath() + "shaders\\";

	OpenGLShader::OpenGLShader(const std::string& name)
	: m_FilePath(ShaderDirectory)
	{
		std::string vertShader = ReadFile(ShaderDirectory + "vertex.vert");
		if(vertShader == "")
		{
			return;
		}
		std::string fragShader = ReadFile(ShaderDirectory + "fragment.frag");
		if(fragShader == "")
		{
			return;
		}
    	const GLuint vertexShader = CompileShader(vertShader.c_str(), GL_VERTEX_SHADER);
    	const GLuint fragmentShader = CompileShader(fragShader.c_str(), GL_FRAGMENT_SHADER);
    	m_RendererID = CreateProgram(vertexShader, fragmentShader);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::string vertShader = ReadFile(ShaderDirectory + "vertex.vert");
		if(vertShader == "")
		{
			return;
		}
		std::string fragShader = ReadFile(ShaderDirectory + "fragment.frag");
		if(fragShader == "")
		{
			return;
		}
    	const GLuint vertexShader = CompileShader(vertexSrc.c_str(), GL_VERTEX_SHADER);
    	const GLuint fragmentShader = CompileShader(fragmentSrc.c_str(), GL_FRAGMENT_SHADER);
    	m_RendererID = CreateProgram(vertexShader, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::ifstream file(filepath);
    	if(!file.is_open())
		{
    		PX_ERROR("Could not open shader file!");
    		Application::Get().SetErrorCode(ErrorCode::LOADING_ASSET_ERROR);
    		return "";
		}
    	std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    	return result;
	}
	
	int OpenGLShader::CompileShader(const char* src, const GLenum shader_type)
    {
    	const int shader = glCreateShader(shader_type);
		glShaderSource(shader, 1, &src, nullptr);	
    	glCompileShader(shader);
    	int sucess;
    	glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);
    	if(!sucess)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			PX_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{0}", infoLog);
		}

    	return shader;
    }

	int OpenGLShader::CreateProgram(const GLuint vertex_shader, const GLuint fragment_shader)
	{
    		const GLuint shader_program = glCreateProgram();
    		glAttachShader(shader_program, vertex_shader);
    		glAttachShader(shader_program, fragment_shader);
    		glLinkProgram(shader_program);

    		GLint success;
    		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    		if (!success) {

    			GLsizei length;
    			glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
    			auto* log = new GLchar(length + 1);

    			glGetProgramInfoLog(shader_program, length, &length, log);
    			PX_ERROR("Error linking shader program: {0}", log);

    			delete[] log;
    			log = nullptr;

    			return 0;
    		}

    		glDeleteShader(vertex_shader);
    		glDeleteShader(fragment_shader);

    		return shader_program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
