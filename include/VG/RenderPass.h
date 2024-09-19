#pragma once
#include "Handle.h"
#include "Subpass.h"
#include "PipelineLayout.h"
#include "PipelineCache.h"
#include "Span.h"

namespace vg
{
    /**
     *@brief Specifies render process
     * Configures whole render process by defining attachments, subpasses, fixed function parameters, shaders
     */
    class RenderPass
    {
    public:
        /**
         *@brief Construct a new Render Pass object
         *
         * @param attachments Array of Attachments e.g. color, depth
         * @param subpasses Array of Subpasses used for multi pass rendering e.g. Differed Rendering
         * @param dependencies Dependencies
         */
        RenderPass(Span<const Attachment> attachments, std::span<Subpass> subpasses, Span<const SubpassDependency> dependencies = {}, PipelineCacheHandle cache = PipelineCacheHandle());
        RenderPass(Span<const Attachment> attachments, std::initializer_list<Subpass> subpasses, Span<const SubpassDependency> dependencies = {}, PipelineCacheHandle cache = PipelineCacheHandle());

        RenderPass();
        RenderPass(RenderPass&& other) noexcept;
        RenderPass(const RenderPass& other) = delete;
        ~RenderPass();

        RenderPass& operator=(RenderPass&& other) noexcept;
        RenderPass& operator=(const RenderPass& other) = delete;
        operator const RenderPassHandle& () const;

        Span<const PipelineLayout> GetPipelineLayouts() const;
        Span<GraphicsPipelineHandle> GetPipelines();
        Span<const GraphicsPipelineHandle> GetPipelines() const;

    private:
        RenderPassHandle m_handle;

        std::vector<GraphicsPipelineHandle> m_graphicsPipelines;
        std::vector<PipelineLayout> m_pipelineLayouts;
    };
}