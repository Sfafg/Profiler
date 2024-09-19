#pragma once
#include "Handle.h"
#include "Device.h"
#include "Enums.h"
namespace vg
{
    /**
     *@brief Custom code run on GPU
     *
     */
    class Shader
    {
    public:
        /**
         *@brief Construct a new Shader object
         *
         * @param ((DeviceHandle)currentDevice).Device
         * @param shaderStage Shader stage
         * @param path path to source file in GLSL
         */
        Shader(ShaderStage shaderStage, const char* path);

        Shader();
        Shader(Shader&& other) noexcept;
        Shader(const Shader& other) = delete;
        ~Shader();

        Shader& operator=(Shader&& other) noexcept;
        Shader& operator=(const Shader& other) = delete;

        operator const ShaderHandle& () const;
        /**
         *@brief Get the Stage object
         *
         * @return ShaderStage
         */
        ShaderStage GetStage() const;

#ifdef VULKAN_HPP
        operator vk::PipelineShaderStageCreateInfo() const;
#endif

    private:
        ShaderHandle m_handle;
        ShaderStage m_stage;
    };
}