#pragma once

#ifdef VULKAN_HPP
#define HANDLE(name, nativeName)\
class name : public vk::nativeName\
{\
public:\
    name() :vk::nativeName(nullptr) {}\
    name(const vk::nativeName& o) : vk::nativeName(o) {}\
    name(vk::nativeName&& o) : vk::nativeName(o) {}\
    name& operator=(void*& rhs) { ((vk::nativeName*)this)->operator=((Vk##nativeName)rhs); return *this; }\
    name& operator=(const vk::nativeName& rhs) { ((vk::nativeName*)this)->operator=(rhs); return *this; }\
    bool operator==(const vk::nativeName& rhs) const { return ((vk::nativeName*)this)->operator==(rhs); }\
    bool operator==(const void* rhs) const { return ((vk::nativeName*)this)->operator==((Vk##nativeName)rhs); }\
};
#else
#define HANDLE(name, nativeName)\
class name\
{\
    void* m_handle;\
public:\
    name() :m_handle(nullptr) {}\
    name& operator=(void*& rhs) { m_handle = rhs; return *this; }\
    bool operator==(const void* rhs) const { return  m_handle == rhs; }\
    bool operator==(name rhs) const { return  m_handle == rhs; }\
};
#endif


namespace vg
{
    HANDLE(InstanceHandle, Instance);
    HANDLE(DebugMessengerHandle, DebugUtilsMessengerEXT);
    HANDLE(DeviceHandle, Device);
    HANDLE(PhysicalDeviceHandle, PhysicalDevice);
    HANDLE(QueueHandle, Queue);
    HANDLE(SurfaceHandle, SurfaceKHR);
    HANDLE(SwapchainHandle, SwapchainKHR);
    HANDLE(ImageHandle, Image);
    HANDLE(ImageViewHandle, ImageView);
    HANDLE(ShaderHandle, ShaderModule);
    HANDLE(PipelineCacheHandle, PipelineCache);
    HANDLE(GraphicsPipelineHandle, Pipeline);
    HANDLE(ComputePipelineHandle, Pipeline);
    HANDLE(PipelineLayoutHandle, PipelineLayout);
    HANDLE(RenderPassHandle, RenderPass);
    HANDLE(FramebufferHandle, Framebuffer);
    HANDLE(SemaphoreHandle, Semaphore);
    HANDLE(FenceHandle, Fence);
    HANDLE(CmdPoolHandle, CommandPool);
    HANDLE(CmdBufferHandle, CommandBuffer);
    HANDLE(BufferHandle, Buffer);
    HANDLE(DeviceMemoryHandle, DeviceMemory);
    HANDLE(DescriptorSetLayoutHandle, DescriptorSetLayout);
    HANDLE(DescriptorPoolHandle, DescriptorPool);
    HANDLE(DescriptorSetHandle, DescriptorSet);
    HANDLE(SamplerHandle, Sampler);
}
#undef HANDLE