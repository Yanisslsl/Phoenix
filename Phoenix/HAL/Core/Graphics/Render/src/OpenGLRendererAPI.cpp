#include "../include/OpenGLRendererAPI.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>

#include "Core/Graphics/OpenGLImpl/include/OpenGLBuffer.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLShader.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLTexture2D.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLVertexArray.h"


namespace Phoenix
{
    class Shader;

    void OpenGLRendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::SetClearColor(const ColorRGBA color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        vertexArray->Bind();
        auto d = vertexArray->GetIndexBuffer()->GetCount();
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
    {
        glDrawArrays(GL_LINES, 0, vertexCount);
    }

    void OpenGLRendererAPI::SetLineWidth(float width)
    {
        glLineWidth(width);
    }

    Ref<VertexBuffer> OpenGLRendererAPI::CreateVertexBuffer(std::vector<float> vertices)
    {
        return OpenGLVertexBuffer::Create(vertices);
    }

    Ref<IndexBuffer> OpenGLRendererAPI::CreateIndexBuffer(std::vector<uint32_t> indices)
    {
        return OpenGLIndexBuffer::Create(indices);
    }

    Ref<VertexArray> OpenGLRendererAPI::CreateVertexArray()
    {
        return OpenGLVertexArray::Create();
    }

    Ref<Shader> OpenGLRendererAPI::CreateShader(std::string name, const char* vertexShader, const char* fragmentShader)
    {
        return CreateRef<OpenGLShader>(name, vertexShader, fragmentShader);
    }

    Ref<Shader> OpenGLRendererAPI::CreateShader(std::string name)
    {
        return CreateRef<OpenGLShader>(name);
    }

    Ref<Texture2D> OpenGLRendererAPI::CreateTexture2D(std::string texturePath)
    {
        return CreateRef<OpenGLTexture2D>(texturePath);
    }

    

}
