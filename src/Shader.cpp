#include <vulkan/vulkan.hpp>
#include "Shader.h"
#include <fstream>
#include <iostream>
#include <math.h>

namespace vg
{
    Shader::Shader(const Device& device, ShaderStage stage, const char* path) : m_device(device), m_stage(stage)
    {
        std::ifstream file(path, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            std::cout << "Failed to open shader file at path: " << path << '\n';
        }

        unsigned int fileSize = file.tellg();
        std::vector<char> code(fileSize);
        file.seekg(0);
        file.read(code.data(), fileSize);
        file.close();

        m_handle = m_device.createShaderModule({ {}, code.size(), (const uint32_t*) code.data() });
    }

    Shader::Shader() : m_handle(nullptr), m_device(nullptr), m_stage(ShaderStage::Vertex) {}

    Shader::Shader(Shader&& other) noexcept
    {
        std::swap(m_handle, other.m_handle);
        std::swap(m_device, other.m_device);
        other.m_handle = nullptr;
        other.m_device = nullptr;
    }

    Shader::~Shader()
    {
        if (m_handle == nullptr) return;
        m_device.destroyShaderModule(m_handle);
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if (&other == this) return *this;
        std::swap(m_handle, other.m_handle);
        std::swap(m_device, other.m_device);

        return *this;
    }

    ShaderStage Shader::GetStage() const
    {
        return m_stage;
    }

    Shader::operator const ShaderHandle& () const
    {
        return m_handle;
    }


#ifdef VULKAN_HPP
    Shader::operator vk::PipelineShaderStageCreateInfo() const
    {
        return vk::PipelineShaderStageCreateInfo({}, (vk::ShaderStageFlagBits) GetStage(), (vg::ShaderHandle) m_handle, "main");
    }
#endif
}