#pragma once
#include "Handle.h"
#include "Device.h"
#include "Enums.h"
#include "Structs.h"
#include "Buffer.h"
#include "ImageView.h"
#include "Sampler.h"

namespace vg
{
    class DescriptorSet
    {
    public:
        DescriptorSet();
        DescriptorSet(DescriptorSetHandle handle, DescriptorPoolHandle pool);
        DescriptorSet(DescriptorSet&& other) noexcept;
        DescriptorSet(const DescriptorSet& other) = delete;
        ~DescriptorSet();

        DescriptorSet& operator=(DescriptorSet&& other) noexcept;
        DescriptorSet& operator=(const DescriptorSet& other) = delete;
        operator const DescriptorSetHandle& () const;

        void AttachBuffer(DescriptorType descriptorType, const Buffer& buffer, int offset, int range, int binding, int arrayElement);
        void AttachImage(DescriptorType descriptorType, ImageLayout layout, const ImageView& imageView, const Sampler& sampler, int binding, int arrayElement);

    private:
        DescriptorSetHandle m_handle;
        DescriptorPoolHandle m_pool;
    };
}