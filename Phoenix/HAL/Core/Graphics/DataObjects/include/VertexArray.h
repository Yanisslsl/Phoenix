// VertexArray.h

#pragma once
#include "Buffer.h"


namespace Phoenix
{
    /** @brief VertexArray class, should be extended in platform specific code */
    class PHOENIX_API VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        /**
         * \brief Bind the vertex array
         */
        virtual void Bind() const = 0;

        /**
         * \brief Unbind the vertex array
         */
        virtual void Unbind() const = 0;

        /**
         * \brief Add a vertex buffer to the vertex array
         * \param vertexBuffer Vertex buffer
         */
        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

        /**
         * \brief Set the index buffer of the vertex array
         * \param indexBuffer Index buffer
         */
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        /**
         * \brief Get the vertex buffers of the vertex array
         * \return std::vector<Ref<VertexBuffer>> Vertex buffers
         */
        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

        /**
         * \brief Get the index buffer of the vertex array
         * \return Ref<IndexBuffer> Index buffer
         */
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        /**
         * \brief Create a vertex array. Call the platform specific Create function.
         * \return Ref<VertexArray> Vertex array
         */
        static Ref<VertexArray> Create();
    };
}
