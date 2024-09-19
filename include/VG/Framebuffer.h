#pragma once
#include "Handle.h"
#include "Span.h"

namespace vg
{
    /**
     *@brief Framebuffer
     * Indirection of Image data can be used by multiple Renderpasses if their outputs are compatible with first one
     */
    class Framebuffer
    {
    public:
        /**
         *@brief Construct a new Framebuffer object
         *
         * @param ((DeviceHandle)currentDevice).Device
         * @param renderPass Renderpass for determining format
         * @param attachments Array of ImageViews each attachment corresponds to attachments specified during RenderPass creation
         * @param width Width
         * @param height Height
         * @param layers Amount of layers, used for anaglif rendering
         */
        Framebuffer(RenderPassHandle renderPass, Span<const ImageViewHandle> attachments, unsigned int width, unsigned int height, unsigned int layers = 1);

        Framebuffer();
        Framebuffer(Framebuffer&& other) noexcept;
        Framebuffer(const Framebuffer& other) = delete;
        ~Framebuffer();

        Framebuffer& operator=(Framebuffer&& other) noexcept;
        Framebuffer& operator=(const Framebuffer& other) = delete;

        operator const FramebufferHandle& () const;

    private:
        FramebufferHandle m_handle;
    };
}