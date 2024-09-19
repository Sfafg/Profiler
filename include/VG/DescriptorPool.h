#pragma once
#include "Handle.h"
#include "Device.h"
#include "Enums.h"
#include "Structs.h"
#include "DescriptorSet.h"
#include "Span.h"

namespace vg
{
    class DescriptorPool
    {
    public:
        DescriptorPool(unsigned int maxSets, Span<const DescriptorPoolSize> sizes);

        DescriptorPool();
        DescriptorPool(DescriptorPool&& other) noexcept;
        DescriptorPool(const DescriptorPool& other) = delete;
        ~DescriptorPool();

        DescriptorPool& operator=(DescriptorPool&& other) noexcept;
        DescriptorPool& operator=(const DescriptorPool& other) = delete;
        operator const DescriptorPoolHandle& () const;

        std::vector<DescriptorSet> Allocate(Span<const DescriptorSetLayoutHandle> setLayouts)
        {
            std::vector<DescriptorSet> set;
            Allocate(setLayouts, &set);
            return set;
        }
        void Allocate(Span<const DescriptorSetLayoutHandle> setLayouts, std::vector<DescriptorSet>* descriptors);
        void Allocate(DescriptorSetLayoutHandle setLayouts, DescriptorSet* descriptors);

    private:
        DescriptorPoolHandle m_handle;

    };
}