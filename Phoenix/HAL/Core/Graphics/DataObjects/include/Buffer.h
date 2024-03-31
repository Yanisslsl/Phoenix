// Buffer.h

#pragma once
#include <cstdint>
#include "../../../Core/Base/Base.h"
#include "../../../Core/Log/include/Log.h"


namespace Phoenix
{
    /**
     * \brief ShaderDataType enum class that contains the different types of data that can be used in a shader.
     */
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    /**
     * \brief ShaderDataTypeSize function that returns the size of a ShaderDataType.
     * \param type ShaderDataType
     * \return uint32_t
     */
    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Bool:     return 1;
            default: break;
        }

        PX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    /**
     * \brief BufferElement struct that contains the name, type, size, offset and normalized of a buffer element.
     *        Used in BufferLayout to each attributes of a buffer.
     */
    struct PHOENIX_API BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        size_t Offset;
        bool Normalized;

        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }

        /**
         * \brief GetComponentCount function that returns the number of components in a ShaderDataType.
         * \return uint32_t
         */
        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Mat3:    return 3;
                case ShaderDataType::Mat4:    return 4;
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::Int2:    return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Bool:    return 1;
                default: break;
            }

            PX_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    /**
     * \brief BufferLayout class that contains the elements and the stride of a buffer.
     *        Used to define the layout of a buffer.
     */
    class PHOENIX_API BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(std::initializer_list<BufferElement> elements)
            : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        /**
         * \brief Get the stride of the buffer.
         * \return uint32_t Stride of the buffer
         */
        uint32_t GetStride() const { return m_Stride; }

        /**
         * \brief Get the elements of the buffer.
         * \return const std::vector<BufferElement>& Elements of the buffer
         */
        const std::vector<BufferElement>& GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        /**
         * \brief CalculateOffsetsAndStride function that calculates the offsets and stride of the buffer by iterating through the BufferElements.
         */
        void CalculateOffsetsAndStride()
        {
            size_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    /**
     * \brief VertexBuffer base class that represents a vertex buffer.
     *         Should be implemented in the platform specific vertex buffer.
     */
    class PHOENIX_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        /**
         * \brief Bind the vertex buffer.
         */
        virtual void Bind() const = 0;

        /**
         * \brief Unbind the vertex buffer.
         */
        virtual void Unbind() const = 0;

        /**
         * \brief Set the data of the vertex buffer.
         * \param data Data to set
         * \param size Size of the data
         */
        virtual void SetData(const void* data, uint32_t size) = 0;


        /**
         * \brief Get the layout of the vertex buffer.
         * \return const BufferLayout& Layout of the vertex buffer
         */
        virtual const BufferLayout& GetLayout() const = 0;

        /**
         * \brief Set the layout of the vertex buffer.
         * \param layout Layout to set
         */
        virtual void SetLayout(const BufferLayout& layout) = 0;


        /**
         * \brief Create a vertex buffer with a size. Call the platform specific Create function.
         * \param size Size of the vertex buffer
         * \return Ref<VertexBuffer> Vertex buffer
         */
        static Ref<VertexBuffer> Create(uint32_t size);

        /**
         * \brief Create a vertex buffer with a vertices. Call the platform specific Create function.
         * \param vertices Vertices of the vertex buffer
         * \return Ref<VertexBuffer> Vertex buffer
         */
        static Ref<VertexBuffer> Create(std::vector<float> vertices);
    };

    /**
     * \brief IndexBuffer base class that represents an index buffer.
     *         Should be implemented in the platform specific index buffer.
     */
    class PHOENIX_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        /**
         * \brief Bind the index buffer.
         */
        virtual void Bind() const = 0;

        /**
         * \brief Unbind the index buffer.
         */
        virtual void Unbind() const = 0;

        /**
         * \brief Get the count of the index buffer.
         * \return uint32_t Count of the index buffer
         */
        virtual uint32_t GetCount() const = 0;

        /**
         * \brief Create an index buffer with indices. Call the platform specific Create function.
         * \param indices Indices of the index buffer
         * \return Ref<IndexBuffer> Index buffer
         */
        static Ref<IndexBuffer> Create(std::vector<uint32_t> indices);
    };
}
