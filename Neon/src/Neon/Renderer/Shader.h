#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Neon/Core/Base.h"

namespace Neon {
    class Shader {
    public:
        static Ref<Shader> Create(const std::string& name, const std::string& filepath);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexStr,
                                  const std::string& fragmentStr);

        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
        virtual void UploadUniformInt(const std::string& name, int value) = 0;

        virtual const std::string& GetName() const = 0;
    };

    class ShaderLibrary {
    public:
        void Add(const std::string& name, Ref<Shader>& shader);

        Ref<Shader> Load(const std::string& name, const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& vertexStr, const std::string& fragmentStr);

        Ref<Shader>& Get(const std::string& name);
        bool Exists(const std::string& name);

    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}  // namespace Neon
