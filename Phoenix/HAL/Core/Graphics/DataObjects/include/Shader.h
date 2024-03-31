#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Base/Base.h"
#include "glm/glm.hpp"


namespace Phoenix
{
    /** \class Shader
     *  \brief Shader class that represent a shader in the game.
     */
    class PHOENIX_API Shader
    {
    public:
        virtual ~Shader() = default;

        /**
         * \brief Bind the shader
         */
        virtual void Bind() const = 0;

        /**
         * \brief Unbind the shader
         */
        virtual void Unbind() const = 0;

        /**
         * \brief Set the uniform int value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        virtual void SetInt(const std::string& name, int value) = 0;

        /**
         * \brief Set the uniform int array value of the shader
         * \param name Name of the uniform
         * \param values Array of values
         * \param count Count of the array
         */
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

        /**
         * \brief Set the uniform float value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        virtual void SetFloat(const std::string& name, float value) = 0;

        /**
         * \brief Set the uniform float2 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;

        /**
         * \brief Set the uniform float3 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;

        /**
         * \brief Set the uniform float4 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

        /**
         * \brief Set the uniform mat3 value of the shader
         * \param name Name of the uniform
         * \param value Value of the uniform
         */
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        /**
         * \brief Get the name of the shader
         * \return std::string Name of the shader
         */
        virtual const std::string& GetName() const = 0;

        /**
         * \brief Create a shader with a filepath. Call the platform specific Create function.
         * \param filepath Filepath of the shader
         * \return Ref<Shader> Shader
         */
        static Ref<Shader> Create(const std::string& filepath);

        /**
         * \brief Create a shader with a name, vertex source and fragment source. Call the platform specific Create function.
         * \param name Name of the shader
         * \param vertexSrc Vertex source of the shader
         * \param fragmentSrc Fragment source of the shader
         * \return Ref<Shader> Shader
         */
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    /** \class ShaderLibrary
     *  \brief ShaderLibrary class that represent a library of shaders in the game. Used to manage shaders in the game.
     */
    class ShaderLibrary
    {
    public:
        ShaderLibrary() = default;


        /**
        * \brief Add a shader to the library
        * \param name Name of the shader
        * \param shader Shader to add
        */
        void Add(const std::string& name, const std::shared_ptr<Shader>& shader);

        /**
         * \brief Add a shader to the library
         * \param shader Shader to add
         */
        void Add(const std::shared_ptr<Shader>& shader);

        /**
         * \brief Load a shader from a filepath
         * \param filepath shader filepath to load
         * \return Shader
         */
        std::shared_ptr<Shader> Load(const std::string& filepath);

        /**
         * \brief Load a shader from a name and filepath
         * \param name 
         * \param filepath 
         * \return Shader
         */
        std::shared_ptr<Shader> Load(const std::string& name, const std::string& filepath);

        /**
         * \brief Get a shader from the library
         * \param name name of the shader
         * \return Shader
         */
        std::shared_ptr<Shader> Get(const std::string& name);

        /**
         * \brief Check if a shader exists in the library
         * \param name name of the shader
         * \return whether the shader exists
         */
        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    };
}
