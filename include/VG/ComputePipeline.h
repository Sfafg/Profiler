#pragma once
#include "Handle.h"
#include "PipelineLayout.h"
#include "PipelineCache.h"
#include "Shader.h"
#include "Span.h"

namespace vg
{
    class ComputePipeline
    {
    public:
        ComputePipeline(const Shader& shader, Span<const Span<const DescriptorSetLayoutBinding>> setLayoutBindings, Span<const PushConstantRange> pushConstantRanges, PipelineCacheHandle cache = PipelineCacheHandle());

        ComputePipeline();
        ComputePipeline(ComputePipeline&& other) noexcept;
        ComputePipeline(const ComputePipeline& other) = delete;
        ~ComputePipeline();

        ComputePipeline& operator=(ComputePipeline&& other) noexcept;
        ComputePipeline& operator=(const ComputePipeline& other) = delete;
        operator const ComputePipelineHandle& () const;

        const PipelineLayout& GetPipelineLayout() const;

    private:
        ComputePipelineHandle m_handle;
        PipelineLayout m_pipelineLayout;
    };
}