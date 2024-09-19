#pragma once
#include "Queue.h"
#include "CmdPool.h"
#include "Structs.h"
#include "RenderPass.h"
#include "GraphicsPipeline.h"
#include "Framebuffer.h"
#include "Synchronization.h"
#include "Buffer.h"
#include "Image.h"

namespace vg
{
    class CmdBuffer;
    namespace cmd
    {
        struct Command {};
        struct BindPipeline : Command
        {
            BindPipeline(GraphicsPipelineHandle pipeline) : pipeline(pipeline), bindPoint(PipelineBindPoint::Graphics) {}
            BindPipeline(ComputePipelineHandle computePipeline) : pipeline(*(GraphicsPipelineHandle*) &computePipeline), bindPoint(PipelineBindPoint::Compute) {}

            GraphicsPipelineHandle pipeline;
            PipelineBindPoint bindPoint;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct BindVertexBuffers : Command
        {
            BindVertexBuffers(const std::vector<Buffer>& buffers, std::vector<uint64_t> offset = {}, uint32_t firstBinding = 0) :buffers(buffers.size()), offset(offset), firstBinding(firstBinding)
            {
                for (int i = 0; i < buffers.size(); i++)
                {
                    this->buffers[i] = buffers[i];
                    if (offset.size() == 0)
                        this->offset.push_back(0);
                }
            }
            BindVertexBuffers(const std::vector<BufferHandle>& buffers, std::vector<uint64_t> offset = {}, uint32_t firstBinding = 0) :buffers(buffers), offset(offset), firstBinding(firstBinding)
            {
                if (offset.size() == 0)
                    for (int i = 0; i < buffers.size(); i++)
                        this->offset.push_back(0);
            }
            BindVertexBuffers(BufferHandle buffers, uint64_t offset, uint32_t firstBinding = 0) :buffers{ buffers }, offset{ offset }, firstBinding(firstBinding) {}

            std::vector<BufferHandle> buffers;
            std::vector<uint64_t> offset;
            uint32_t firstBinding;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct BindIndexBuffer : Command
        {
            BindIndexBuffer(BufferHandle buffer, uint64_t offset, IndexType type) :buffer(buffer), offset(offset), type(type) {}

            BufferHandle buffer;
            uint64_t offset;
            IndexType type;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct BindDescriptorSets : Command
        {
            BindDescriptorSets(PipelineLayoutHandle layout, PipelineBindPoint bindPoint, uint32_t firstSet, std::vector<DescriptorSetHandle> descriptorSets) :layout(layout), bindPoint(bindPoint), firstSet(firstSet), descriptorSets(descriptorSets) {}

            PipelineBindPoint bindPoint;
            PipelineLayoutHandle layout;
            uint32_t firstSet;
            std::vector<DescriptorSetHandle> descriptorSets;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct BeginRenderpass : Command
        {
            BeginRenderpass(const RenderPass& renderpass, const Framebuffer& framebuffer, Point2D<int32_t> offset, Point2D<uint32_t> extend, const std::vector<ClearValue>& clearValues, SubpassContents subpassContents)
                : renderpass(renderpass), framebuffer(framebuffer), offset(offset), extend(extend), clearValues(clearValues), subpassContents(subpassContents)
            {}

            RenderPassHandle renderpass;
            FramebufferHandle framebuffer;
            Point2D<int32_t> offset;
            Point2D<uint32_t> extend;
            std::vector<ClearValue> clearValues;
            SubpassContents subpassContents;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetViewport : Command
        {
            SetViewport(const Viewport& viewport) : viewports{ viewport }, first(0) {}
            SetViewport(const std::vector<Viewport>& vieports, int first = 0) : viewports(vieports), first(first) {}

            uint32_t first;
            std::vector<Viewport> viewports;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetScissor : Command
        {
            SetScissor(const Scissor& scissor) : scissors{ scissor }, first(0) {}
            SetScissor(const std::vector<Scissor>& vieports, int first = 0) : scissors(vieports), first(first) {}

            uint32_t first;
            std::vector<Scissor> scissors;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct Draw : Command
        {
            Draw(int vertexCount, int instanceCount = 1, int firstVertex = 0, int firstInstance = 0)
                :vertexCount(vertexCount), instanceCount(instanceCount), firstVertex(firstVertex), firstInstance(firstInstance)

            {}

            int vertexCount;
            int instanceCount;
            int firstVertex;
            int firstInstance;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct EndRenderpass : Command
        {
            EndRenderpass() {}

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct DrawIndexed : Command
        {
            DrawIndexed(uint32_t indexCount, uint32_t instanceCount = 1, uint32_t firstIndex = 0, uint32_t vertexOffset = 0, uint32_t firstInstance = 0)
                : indexCount(indexCount), instanceCount(instanceCount), firstIndex(firstIndex), vertexOffset(vertexOffset), firstInstance(firstInstance)
            {}

            uint32_t indexCount;
            uint32_t instanceCount;
            uint32_t firstIndex;
            uint32_t vertexOffset;
            uint32_t firstInstance;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct CopyBuffer : Command
        {
            CopyBuffer(Buffer& src, Buffer& dst, const std::vector<BufferCopyRegion>& regions) : src(src), dst(dst), regions(regions) {}

            BufferHandle src;
            BufferHandle dst;
            std::vector<BufferCopyRegion> regions;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct CopyBufferToImage : Command
        {
            CopyBufferToImage(const Buffer& src, const Image& dst, ImageLayout dstImageLayout, std::vector<BufferImageCopy> regions)
                : src(src), dst(dst), dstImageLayout(dstImageLayout), regions(regions)
            {}

            BufferHandle src;
            ImageHandle dst;
            ImageLayout dstImageLayout;
            std::vector<BufferImageCopy> regions;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct PipelineBarier : Command
        {
            PipelineBarier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, Flags<Dependency> dependency, std::vector<MemoryBarrier> memoryBarriers, std::vector<BufferMemoryBarrier> bufferMemoryBarriers = {}, std::vector<ImageMemoryBarrier> imageMemoryBarriers = {})
                :srcStageMask(srcStageMask), dstStageMask(dstStageMask), dependency(dependency), memoryBarriers(memoryBarriers), bufferMemoryBarriers(bufferMemoryBarriers), imageMemoryBarriers(imageMemoryBarriers)
            {}

            PipelineBarier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, Flags<Dependency> dependency, std::vector<BufferMemoryBarrier> bufferMemoryBarriers, std::vector<ImageMemoryBarrier> imageMemoryBarriers = {})
                :srcStageMask(srcStageMask), dstStageMask(dstStageMask), dependency(dependency), bufferMemoryBarriers(bufferMemoryBarriers), imageMemoryBarriers(imageMemoryBarriers)
            {}

            PipelineBarier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, Flags<Dependency> dependency, std::vector<ImageMemoryBarrier> imageMemoryBarriers)
                :srcStageMask(srcStageMask), dstStageMask(dstStageMask), dependency(dependency), imageMemoryBarriers(imageMemoryBarriers)
            {}

            PipelineBarier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, std::vector<MemoryBarrier> memoryBarriers, std::vector<BufferMemoryBarrier> bufferMemoryBarriers = {}, std::vector<ImageMemoryBarrier> imageMemoryBarriers = {})
                :srcStageMask(srcStageMask), dstStageMask(dstStageMask), dependency(Dependency::None), memoryBarriers(memoryBarriers), bufferMemoryBarriers(bufferMemoryBarriers), imageMemoryBarriers(imageMemoryBarriers)
            {}

            PipelineBarier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, std::vector<BufferMemoryBarrier> bufferMemoryBarriers, std::vector<ImageMemoryBarrier> imageMemoryBarriers = {})
                :srcStageMask(srcStageMask), dstStageMask(dstStageMask), dependency(Dependency::None), bufferMemoryBarriers(bufferMemoryBarriers), imageMemoryBarriers(imageMemoryBarriers)
            {}

            PipelineBarier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, std::vector<ImageMemoryBarrier> imageMemoryBarriers)
                :srcStageMask(srcStageMask), dstStageMask(dstStageMask), dependency(Dependency::None), imageMemoryBarriers(imageMemoryBarriers)
            {}

            Flags<PipelineStage> srcStageMask;
            Flags<PipelineStage> dstStageMask;
            Flags<Dependency> dependency;
            std::vector<MemoryBarrier> memoryBarriers;
            std::vector<BufferMemoryBarrier> bufferMemoryBarriers;
            std::vector<ImageMemoryBarrier> imageMemoryBarriers;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct ExecuteCommands : Command
        {
            ExecuteCommands(const std::vector<CmdBufferHandle>& cmdBuffers)
                : cmdBuffers(cmdBuffers)
            {}

            std::vector<CmdBufferHandle> cmdBuffers;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct PushConstants : Command
        {
            PushConstants(PipelineLayoutHandle layout, Flags<ShaderStage> stages, uint32_t offset, uint32_t size, void* values)
                :layout(layout), stages(stages), offset(offset)
            {
                data.assign((char*) values, (char*) values + size);
            }

            template <typename T>
            PushConstants(PipelineLayoutHandle layout, Flags<ShaderStage> stages, uint32_t offset, const std::vector<T>& data)
                : layout(layout), stages(stages), offset(offset)
            {
                this->data.assign((char*) data.data(), (char*) (data.begin() + data.size()));
            }

            template <typename T>
            PushConstants(PipelineLayoutHandle layout, Flags<ShaderStage> stages, uint32_t offset, const T& data)
                : layout(layout), stages(stages), offset(offset)
            {
                this->data.assign((char*) &data, (char*) (&data + 1));
            }

            PipelineLayoutHandle layout;
            Flags<ShaderStage> stages;
            uint32_t offset;
            std::vector<char> data;

        private:
            void operator ()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };

        struct SetLineWidth : Command
        {
            SetLineWidth(float lineWidth) :lineWidth(lineWidth) {}

            float lineWidth;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetDepthBias : Command
        {
            SetDepthBias(DepthBias bias) : bias(bias) {}

            DepthBias bias;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetBlendConstants : Command
        {
            SetBlendConstants(float c1, float c2, float c3, float c4) :blendConstants{ c1,c2,c3,c4 } {}

            const float blendConstants[4];

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetDepthBounds : Command
        {
            SetDepthBounds(float minDepthBounds, float maxDepthBounds) :minDepthBounds(minDepthBounds), maxDepthBounds(maxDepthBounds) {}

            float minDepthBounds;
            float maxDepthBounds;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetStencilCompareMask : Command
        {
            SetStencilCompareMask(Flags<StencilFace> faceMask, uint32_t compareMask) :faceMask(faceMask), compareMask(compareMask) {}

            Flags<StencilFace> faceMask;
            uint32_t compareMask;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetStencilWriteMask : Command
        {
            SetStencilWriteMask(Flags<StencilFace> faceMask, uint32_t writeMask) :faceMask(faceMask), writeMask(writeMask) {}

            Flags<StencilFace> faceMask;
            uint32_t writeMask;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct SetStencilReference : Command
        {
            SetStencilReference(Flags<StencilFace> faceMask, uint32_t reference) :faceMask(faceMask), reference(reference) {}

            Flags<StencilFace> faceMask;
            uint32_t reference;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct DrawIndirect : Command
        {
            DrawIndirect(
                BufferHandle buffer, uint64_t offset, uint32_t drawCount, uint32_t stride)
                :buffer(buffer), offset(offset), drawCount(drawCount), stride(stride)
            {}

            BufferHandle buffer;
            uint64_t offset;
            uint32_t drawCount;
            uint32_t stride;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct DrawIndexedIndirect : Command
        {
            DrawIndexedIndirect(BufferHandle buffer, uint64_t offset, uint32_t drawCount, uint32_t stride)
                :buffer(buffer), offset(offset), drawCount(drawCount), stride(stride)
            {}

            BufferHandle buffer;
            uint64_t offset;
            uint32_t drawCount;
            uint32_t stride;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct Dispatch : Command
        {
            Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
                :groupCountX(groupCountX), groupCountY(groupCountY), groupCountZ(groupCountZ)
            {}

            uint32_t groupCountX;
            uint32_t groupCountY;
            uint32_t groupCountZ;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct DispatchIndirect : Command
        {
            DispatchIndirect(BufferHandle buffer, uint64_t offset)
                :buffer(buffer), offset(offset)
            {}

            BufferHandle buffer;
            uint64_t offset;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct CopyImage : Command
        {
            CopyImage(ImageHandle srcImage, ImageLayout srcImageLayout, ImageHandle dstImage, ImageLayout dstImageLayout, const std::vector<ImageCopy>& regions)
                : srcImage(srcImage), srcImageLayout(srcImageLayout), dstImage(dstImage), dstImageLayout(dstImageLayout), regions(regions)
            {}

            ImageHandle srcImage;
            ImageLayout srcImageLayout;
            ImageHandle dstImage;
            ImageLayout dstImageLayout;
            std::vector<ImageCopy> regions;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct BlitImage : Command
        {
            BlitImage(ImageHandle srcImage, ImageLayout srcImageLayout, ImageHandle dstImage, ImageLayout dstImageLayout, const std::vector<ImageBlit>& regions, Filter filter)
                :srcImage(srcImage), srcImageLayout(srcImageLayout), dstImage(dstImage), dstImageLayout(dstImageLayout), regions(regions), filter(filter)
            {}

            ImageHandle srcImage;
            ImageLayout srcImageLayout;
            ImageHandle dstImage;
            ImageLayout dstImageLayout;
            std::vector<ImageBlit> regions;
            Filter filter;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct CopyImageToBuffer : Command
        {
            CopyImageToBuffer(ImageHandle srcImage, ImageLayout srcImageLayout, BufferHandle dstBuffer, const std::vector<BufferImageCopy>& regions)
                :srcImage(srcImage), srcImageLayout(srcImageLayout), dstBuffer(dstBuffer), regions(regions)
            {}

            ImageHandle srcImage;
            ImageLayout srcImageLayout;
            BufferHandle dstBuffer;

        private:
            std::vector<BufferImageCopy> regions;
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct UpdateBuffer : Command
        {
            UpdateBuffer(BufferHandle dstBuffer, uint64_t dstOffset, uint64_t dataSize, const void* data)
                :dstBuffer(dstBuffer), dstOffset(dstOffset)
            {
                this->data.assign((const char*) data, (const char*) data + dataSize);
            }

            template <typename T>
            UpdateBuffer(BufferHandle dstBuffer, uint64_t dstOffset, const std::vector<T>& data)
                : dstBuffer(dstBuffer), dstOffset(dstOffset)
            {
                this->data.assign((char*) data.data(), (char*) data.data() + data.size() * sizeof(T));
            }

            BufferHandle dstBuffer;
            uint64_t dstOffset;
            std::vector<char> data;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct FillBuffer : Command
        {
            FillBuffer(BufferHandle dstBuffer, uint64_t dstOffset, uint64_t size, uint32_t data)
                :dstBuffer(dstBuffer), dstOffset(dstOffset), size(size), data(data)
            {}

            BufferHandle dstBuffer;
            uint64_t dstOffset;
            uint64_t size;
            uint32_t data;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };
        struct ClearColorImage : Command
        {
            ClearColorImage(ImageHandle image, ImageLayout imageLayout, ClearValue color, const std::vector<ImageSubresource>& ranges)
                :image(image), imageLayout(imageLayout), color(color), ranges(ranges)
            {}

            ImageHandle image;
            ImageLayout imageLayout;
            ClearValue color;
            std::vector<ImageSubresource> ranges;

        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
        };

        // struct ClearDepthStencilImage : Command
        // {
        //     ClearDepthStencilImage() {}
        // private:
        //     ImageHandle image;
        //     ImageLayout imageLayout;
        //     float depthClear;
        //     float stencilClear;
        //     uint32_t rangeCount;
        //     const VkImageSubresourceRange* pRanges;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct ClearAttachments : Command
        // {
        //     ClearAttachments() {}
        // private:
        //     uint32_t attachmentCount;
        //     const VkClearAttachment pAttachments;
        //     uint32_t rectCount;
        //     const VkClearRect* pRects;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct ResolveImage : Command
        // {
        //     ResolveImage() {}
        // private:
        //     ImageHandle srcImage;
        //     ImageLayout srcImageLayout;
        //     ImageHandle dstImage;
        //     ImageLayout dstImageLayout;
        //     uint32_t regionCount;
        //     const VkImageResolve* pRegions;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct SetEvent : Command
        // {
        //     SetEvent() {}
        // private:
        //     VkEvent event;
        //     Flags<PipelineStage> stageMask;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct ResetEvent : Command
        // {
        //     ResetEvent() {}
        // private:
        //     VkEvent event;
        //     Flags<PipelineStage> stageMask;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct WaitEvents : Command
        // {
        //     WaitEvents() {}
        // private:
        //     uint32_t eventCount;
        //     const VkEvent pEvents;
        //     Flags<PipelineStage> srcStageMask;
        //     Flags<PipelineStage> dstStageMask;
        //     uint32_t memoryBarrierCount;
        //     const VkMemoryBarrier pMemoryBarriers;
        //     uint32_t bufferMemoryBarrierCount;
        //     const BufferHandleMemoryBarrier pBufferMemoryBarriers;
        //     uint32_t imageMemoryBarrierCount;
        //     const VkImageMemoryBarrier* pImageMemoryBarriers;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct BeginQuery : Command
        // {
        //     BeginQuery() {}
        // private:
        //     VkQueryPool queryPool;
        //     uint32_t query;
        //     VkQueryControlFlags flags;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct EndQuery : Command
        // {
        //     EndQuery() {}
        // private:
        //     VkQueryPool queryPool;
        //     uint32_t query;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct ResetQueryPool : Command
        // {
        //     ResetQueryPool() {}
        // private:
        //     VkQueryPool queryPool;
        //     uint32_t firstQuery;
        //     uint32_t queryCount;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct WriteTimestamp : Command
        // {
        //     WriteTimestamp() {}
        // private:
        //     VkPipelineStageFlagBits pipelineStage;
        //     VkQueryPool queryPool;
        //     uint32_t query;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        // struct CopyQueryPoolResults : Command
        // {
        //     CopyQueryPoolResults() {}
        // private:
        //     VkQueryPool queryPool;
        //     uint32_t firstQuery;
        //     uint32_t queryCount;
        //     BufferHandle dstBuffer;
        //     uint64_t dstOffset;
        //     uint64_t stride;
        //     VkQueryResultFlags flags;
        //     void operator()(CmdBuffer& commandBuffer) const;
        //     friend CmdBuffer;
        // };
        struct NextSubpass : Command
        {
            NextSubpass(SubpassContents subpassContents) :subpassContents(subpassContents) {}
        private:
            void operator()(CmdBuffer& commandBuffer) const;
            friend CmdBuffer;
            SubpassContents subpassContents;
        };
    }

    template<class T>
    concept Command = std::is_base_of<cmd::Command, T>::value;
    template<class... T>
    concept Commands = (std::is_base_of<cmd::Command, T>::value && ...);
    /**
     *@brief Array of commands
     * Used to send commands to the GPU in one big batch improving performance
     */
    class CmdBuffer
    {
    public:
        /**
         *@brief Construct a new Command Buffer object
         *
         * @param queue Queue object
         */
        CmdBuffer(const Queue& queue, bool isShortLived = true, CmdBufferLevel cmdLevel = CmdBufferLevel::Primary);
        CmdBuffer(const CmdPool& pool, CmdBufferLevel cmdLevel = CmdBufferLevel::Primary);

        static std::vector<CmdBuffer> CreateArray(const Queue& queue, bool areShortLived, CmdBufferLevel cmdLevel, uint32_t count);
        static std::vector<CmdBuffer> CreateArray(const CmdPool& pool, CmdBufferLevel cmdLevel, uint32_t count);

        CmdBuffer();
        CmdBuffer(CmdBuffer&& other) noexcept;
        CmdBuffer(const CmdBuffer& other) = delete;
        ~CmdBuffer();

        CmdBuffer& operator=(CmdBuffer&& other) noexcept;
        CmdBuffer& operator=(const CmdBuffer& other) = delete;
        operator const CmdBufferHandle& () const;

        /**
         *@brief Clear commands
         *
         */
        CmdBuffer& Clear();

        /**
         *@brief Begin appending to the command buffer
         *  Needs to be called before all Appends
         * @param usage how the recorded buffer will be used
         */
        CmdBuffer& Begin(Flags<CmdBufferUsage> usage = { CmdBufferUsage::OneTimeSubmit });

        CmdBuffer& Begin(Flags<CmdBufferUsage> usage,
            RenderPassHandle renderPass, uint32_t subpassIndex, FramebufferHandle framebuffer = FramebufferHandle(), bool occlusionQueryEnable = false, Flags<QueryControl> queryFlags = {}, Flags<PipelineStatistic> pipelineStatistics = {});

        /**
         *@brief Append commands, has to be between \ref CommandBuffer::Begin() and \ref CommandBuffer::End()
         * Appends array commands to the buffer
         * @tparam T class derived from cmd::Command
         * @param commands Array of commands from cmd:: namespace
         */
        template<Commands... T>
        CmdBuffer& Append(const T&... commands) { (..., _Append(std::move(commands))); return *this; }

        /**
         *@brief End appending to command buffer
        * Has to be called before submiting
        */
        CmdBuffer& End();

        /**
         *@brief Submit command buffers and all relevant data
        *
        * @param submits Synchronization info
        * @param fence Fence to be signaled upon all submits finish
        */
        CmdBuffer& Submit(Span<const std::tuple<Flags<PipelineStage>, SemaphoreHandle>> waitStages, Span<const SemaphoreHandle> signalSemaphores, const Fence& fence);
        /**
         *@brief Submit command buffer and all relevant data
         *
         *@param submits Synchronization info
         *@return Fence to be signaled upon all submits finish
         */

        Fence Submit(Span<const std::tuple<Flags<PipelineStage>, SemaphoreHandle>> waitStages = {}, Span<const SemaphoreHandle> signalSemaphores = {})
        {
            Fence fence;
            Submit(waitStages, signalSemaphores, fence);
            return fence;
        }

    private:
        template<Command T>
        void _Append(const T& command) { command(*this); };

    private:
        CmdBufferHandle m_handle;
        CmdPoolHandle m_commandPool;
        QueueHandle m_queue;
    };
}