// OpenGLShader.h

#pragma once
#include <string>

#include "../../DataObjects/include/Shader.h"
#include "glad/glad.h"


namespace Phoenix
{
    class OpenGLShader: public Shader
    {
    public:

        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

        virtual ~OpenGLShader() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat2(const std::string& name, const Maths::Vec2& value) override;
        virtual void SetFloat3(const std::string& name, const Maths::Vec3& value) override;
        virtual void SetFloat4(const std::string& name, const Maths::Vec4& value) override;
        virtual void SetMat4(const std::string& name, const Maths::Matrix4& value) override;
        

        virtual const std::string& GetName() const override { return m_Name; }

        void UploadUniformInt(const std::string& name, int value);
        void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const Maths::Vec2& value);
        void UploadUniformFloat3(const std::string& name, const Maths::Vec3& value);
        void UploadUniformFloat4(const std::string& name, const Maths::Vec4& value);

        void UploadUniformMat3(const std::string& name, const Maths::Matrix3& matrix);
        void UploadUniformMat4(const std::string& name, const Maths::Matrix4& matrix);
    private:
        std::string ReadFile(const std::string& filepath);
        // std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        int CompileShader(const char* src, const GLenum shader_type);
        // void CompileOrGetOpenGLBinaries();
        int CreateProgram(const GLuint vertex_shader, const GLuint fragment_shader);
        // void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);


        std::string m_Name;
        uint32_t m_RendererID;
        std::string m_FilePath;

        // std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
        std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;

        std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
    };
}
