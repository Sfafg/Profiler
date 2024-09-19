#pragma once
#include "Handle.h"
#include "Structs.h"
#include "Shader.h"
#include <vector>
#include <optional>

namespace vg
{
    class GraphicsPipeline
    {

    public:
        GraphicsPipeline(
            const std::vector<std::vector<DescriptorSetLayoutBinding>>& setLayoutBindings,
            const std::vector<PushConstantRange>& pushConstantRanges,
            const std::vector<Shader*>& shaders,
            const VertexLayout& vertexInput,
            const InputAssembly& inputAssembly,
            const Tesselation& tesselation,
            const ViewportState& viewportState,
            const Rasterizer& rasterizer,
            const Multisampling& multisampling,
            const DepthStencil& depthStencil,
            const ColorBlending& colorBlending,
            const std::vector<DynamicState>& dynamicState,
            uint32_t childrenCount = 0
        );

        GraphicsPipeline(
            uint32_t parentIndex,
            const std::optional<std::vector<std::vector<DescriptorSetLayoutBinding>>>& setLayoutBindings = std::nullopt,
            const std::optional<std::vector<PushConstantRange>>& pushConstantRanges = std::nullopt,
            const std::optional<std::vector<Shader*>>& shaders = std::nullopt,
            const std::optional<VertexLayout>& vertexInput = std::nullopt,
            const std::optional<InputAssembly>& inputAssembly = std::nullopt,
            const std::optional<Tesselation>& tesselation = std::nullopt,
            const std::optional<ViewportState>& viewportState = std::nullopt,
            const std::optional<Rasterizer>& rasterizer = std::nullopt,
            const std::optional<Multisampling>& multisampling = std::nullopt,
            const std::optional<DepthStencil>& depthStencil = std::nullopt,
            const std::optional<ColorBlending>& colorBlending = std::nullopt,
            const std::optional<std::vector<DynamicState>>& dynamicState = std::nullopt,
            uint32_t childrenCount = 0
        );

        GraphicsPipeline(
            GraphicsPipeline* parent,
            const std::optional<std::vector<std::vector<DescriptorSetLayoutBinding>>>& setLayoutBindings = std::nullopt,
            const std::optional<std::vector<PushConstantRange>>& pushConstantRanges = std::nullopt,
            const std::optional<std::vector<Shader*>>& shaders = std::nullopt,
            const std::optional<VertexLayout>& vertexInput = std::nullopt,
            const std::optional<InputAssembly>& inputAssembly = std::nullopt,
            const std::optional<Tesselation>& tesselation = std::nullopt,
            const std::optional<ViewportState>& viewportState = std::nullopt,
            const std::optional<Rasterizer>& rasterizer = std::nullopt,
            const std::optional<Multisampling>& multisampling = std::nullopt,
            const std::optional<DepthStencil>& depthStencil = std::nullopt,
            const std::optional<ColorBlending>& colorBlending = std::nullopt,
            const std::optional<std::vector<DynamicState>>& dynamicState = std::nullopt,
            uint32_t childrenCount = 0
        );

        GraphicsPipeline();
        GraphicsPipeline(GraphicsPipeline&& other) noexcept;
        GraphicsPipeline(const GraphicsPipeline& other) = delete;
        ~GraphicsPipeline();

        GraphicsPipeline& operator=(GraphicsPipeline&& other) noexcept;
        GraphicsPipeline& operator=(const GraphicsPipeline& other) = delete;

        operator const GraphicsPipelineHandle& () const;

    private:
        struct CreateInfo
        {
            uint32_t inheritanceCount;
            std::optional<std::vector<std::vector<DescriptorSetLayoutBinding>>> setLayoutBindings;
            std::optional<std::vector<PushConstantRange>> pushConstantRanges;
            std::optional<std::vector<Shader*>> shaders;
            std::optional<VertexLayout> vertexInput;
            std::optional<InputAssembly> inputAssembly;
            std::optional<Tesselation> tesselation;
            std::optional<ViewportState> viewportState;
            std::optional<Rasterizer> rasterizer;
            std::optional<Multisampling> multisampling;
            std::optional<DepthStencil> depthStencil;
            std::optional<ColorBlending> colorBlending;
            std::optional<std::vector<DynamicState>> dynamicState;
            int parentIndex;
            GraphicsPipeline* parent;

            CreateInfo(
                uint32_t inheritanceCount,
                const std::optional<std::vector<std::vector<DescriptorSetLayoutBinding>>>& setLayoutBindings,
                const std::optional<std::vector<PushConstantRange>>& pushConstantRanges,
                const std::optional<std::vector<Shader*>>& shaders, std::optional<VertexLayout> vertexInput,
                const std::optional<InputAssembly>& inputAssembly, std::optional<Tesselation> tesselation,
                const std::optional<ViewportState>& viewportState, std::optional<Rasterizer> rasterizer,
                const std::optional<Multisampling>& multisampling, std::optional<DepthStencil> depthStencil,
                const std::optional<ColorBlending>& colorBlending, std::optional<std::vector<DynamicState>> dynamicState,
                int parentIndex, GraphicsPipeline* parent
            ) :
                inheritanceCount(inheritanceCount), setLayoutBindings(setLayoutBindings),
                pushConstantRanges(pushConstantRanges), shaders(shaders), vertexInput(vertexInput),
                inputAssembly(inputAssembly), tesselation(tesselation),
                viewportState(viewportState), rasterizer(rasterizer),
                multisampling(multisampling), depthStencil(depthStencil),
                colorBlending(colorBlending), dynamicState(dynamicState),
                parentIndex(parentIndex), parent(parent)
            {}

            const std::vector<PushConstantRange>* GetPushConstantRanges(const GraphicsPipeline* parent) const;
            const std::vector<std::vector<DescriptorSetLayoutBinding>>* GetSetLayoutBindings(const GraphicsPipeline* parent) const;
            const std::vector<Shader*>* GetShaders(const GraphicsPipeline* parent) const;
            const VertexLayout* GetVertexInput(const GraphicsPipeline* parent) const;
            const InputAssembly* GetInputAssembly(const GraphicsPipeline* parent) const;
            const Tesselation* GetTesselation(const GraphicsPipeline* parent) const;
            const ViewportState* GetViewportState(const GraphicsPipeline* parent) const;
            const Rasterizer* GetRasterizer(const GraphicsPipeline* parent) const;
            const Multisampling* GetMultisampling(const GraphicsPipeline* parent) const;
            const DepthStencil* GetDepthStencil(const GraphicsPipeline* parent) const;
            const ColorBlending* GetColorBlending(const GraphicsPipeline* parent) const;
            const std::vector<DynamicState>* GetDynamicState(const GraphicsPipeline* parent) const;
            GraphicsPipelineHandle GetParentHandle(const GraphicsPipeline* parent) const;
            void DecrementParentInheritance();
            void UpdateParentInheritance();
        };

    private:
        GraphicsPipelineHandle m_handle;
        CreateInfo* m_createInfo;
        friend class RenderPass;
    };
}