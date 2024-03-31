#pragma once
#include <string>

#include "Core/Graphics/DataObjects/include/Shader.h"
#include "glm/glm.hpp"

#include "glad/glad.h"


namespace Phoenix
{
    /** \class OpenGLShader
    *  \brief A class that represents a shader in OpenGL.
    */
    class OpenGLShader: public Shader
    {
    public:

        OpenGLShader(const std::string& name);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

        virtual ~OpenGLShader() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
        

        virtual const std::string& GetName() const override { return m_Name; }

        /**
         * \brief Upload the uniform int value of the shader
         * \param name Name of the uniform 
         * \param value Value of the uniform
         */
        void UploadUniformInt(const std::string& name, int value);

        /** 
         * \brief Upload the uniform int array value of the shader
         * \param name Name of the uniform
         * \param values Array of values
         * \param count Count of the array
         */
        void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

        /**
         * \brief Upload the uniform float value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        void UploadUniformFloat(const std::string& name, float value);

        /**
         * \brief Upload the uniform float2 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);

        /**
         * \brief Upload the uniform float3 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);

        /**
         * \brief Upload the uniform float4 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        /**
         * \brief Upload the uniform mat3 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

        /**
         * \brief Upload the uniform mat4 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        /**
         * \brief Read the file
         * \param filepath Path of the file
         * \return std::string
         */
        std::string ReadFile(const std::string& filepath);

        /** 
         * \brief Compile the shader
         * \param src Source code of the shader
         * \param shader_type Type of the shader
         * \return int
         */
        int CompileShader(const char* src, const GLenum shader_type);
     
         /**
         * \brief Create the program
         * \param vertex_shader Vertex shader
         * \param fragment_shader Fragment shader
         * \return uint32_t
         */
        int CreateProgram(const GLuint vertex_shader, const GLuint fragment_shader);
        std::string m_Name;
        uint32_t m_RendererID;
        std::string m_FilePath;
    };
}
