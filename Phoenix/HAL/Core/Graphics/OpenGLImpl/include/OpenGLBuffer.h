#pragma once
#include "Core/Graphics/DataObjects/include/Buffer.h"

namespace Phoenix
{
    /** \class OpenGLVertexBuffer
    *  \brief A class that represents a vertex buffer in OpenGL.
    */
    class OpenGLVertexBuffer: public VertexBuffer
    {
    public:
        OpenGLVertexBuffer() = default;

        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(std::vector<float> vertices);

        virtual ~OpenGLVertexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(const void* data, uint32_t size) override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    /** \class OpenGLIndexBuffer
    *  \brief A class that represents an index buffer in OpenGL.
    */
    class OpenGLIndexBuffer: public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(std::vector<uint32_t> indices);
        virtual ~OpenGLIndexBuffer();
        virtual void Bind() const;
        virtual void Unbind() const;
        virtual uint32_t GetCount() const { return m_Count; }
    private:
        uint32_t m_RendererID;
        size_t m_Count;
    };
}
