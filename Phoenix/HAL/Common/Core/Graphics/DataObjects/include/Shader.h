// Shader.h

#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "../../../Core/Base/Base.h"
#include "../../Render/include/RendererAPI.h"


namespace Phoenix
{
    class PHOENIX_API Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat2(const std::string& name, const Maths::Vec2& value) = 0;
        virtual void SetFloat3(const std::string& name, const Maths::Vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const Maths::Vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const Maths::Matrix4& value) = 0;

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& filepath);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary
    {
    public :
        void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
        void Add(const std::shared_ptr<Shader>& shader);
        std::shared_ptr<Shader> Load(const std::string& filepath);
        std::shared_ptr<Shader> Load(const std::string& name, const std::string& filepath);

        std::shared_ptr<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    };
}
