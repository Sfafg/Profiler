#pragma once
#include <vector>
#include "Handle.h"
#include "Structs.h"
#include "Span.h"

namespace vg
{
    class PipelineLayout
    {
    public:
        PipelineLayout();

        PipelineLayout(PipelineLayout&& other) noexcept;
        PipelineLayout(const PipelineLayout& other) = delete;

        PipelineLayout& operator=(PipelineLayout&& other) noexcept;
        PipelineLayout& operator=(const PipelineLayout& other) = delete;
        operator const PipelineLayoutHandle& () const;

        Span<DescriptorSetLayoutHandle> GetDescriptorSets();
        Span<const DescriptorSetLayoutHandle> GetDescriptorSets()const;

    private:
        PipelineLayoutHandle m_handle;
        std::vector<DescriptorSetLayoutHandle> m_descriptorSetLayouts;
        friend class RenderPass;
        friend class ComputePipeline;
    };
};