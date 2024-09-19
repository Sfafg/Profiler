#pragma once
#include "Handle.h"
#include "GraphicsPipeline.h"
#include "Span.h"
#include <vector>
#include <optional>
#include <memory>

namespace vg
{
    /**
     *@brief Subpass used in Renderpass
     *
     */
    struct Subpass
    {
        GraphicsPipeline graphicsPipeline;
        std::vector<AttachmentReference> inputAttachments;
        std::vector<AttachmentReference> colorAttachments;
        std::vector<AttachmentReference> resolveAttachments;
        std::optional<AttachmentReference> depthStencilAttachment;
        std::vector<uint32_t> preserveAttachments;

        /**
         *@brief Construct a new Subpass object
         *
         * @param graphicsPipeline Graphics pipeline
         * @param inputAttachments Array of input attachments
         * @param colorAttachments Array of color attachments must be same size as Resolve and DepthStencil atachments if are not null
         * @param resolveAttachments Array of resolve attachments must be same size as Color and DepthStencil atachments if are not null
         * @param depthStencilAttachment depth stencil attachment or null
         * @param preserveAttachments Array of preserve attachments that are not used by subpass but must be preserved
         */
        Subpass(
            GraphicsPipeline&& graphicsPipeline,
            const std::vector<AttachmentReference>& inputAttachments = {},
            const std::vector<AttachmentReference>& colorAttachments = {},
            const std::vector<AttachmentReference>& resolveAttachments = {},
            const std::optional<AttachmentReference>& depthStencilAttachment = std::nullopt,
            const std::vector<uint32_t>& preserveAttachments = {}
        );

        Subpass(
            GraphicsPipeline&& graphicsPipeline,
            std::vector<AttachmentReference>&& inputAttachments = {},
            std::vector<AttachmentReference>&& colorAttachments = {},
            std::vector<AttachmentReference>&& resolveAttachments = {},
            const std::optional<AttachmentReference>& depthStencilAttachment = std::nullopt,
            std::vector<uint32_t>&& preserveAttachments = {}
        );

        Subpass();
        Subpass(Subpass&& other) noexcept;
        Subpass(const Subpass& other) = delete;

        Subpass& operator=(Subpass&& other) noexcept;
        Subpass& operator=(const Subpass& other) = delete;
    };
}
