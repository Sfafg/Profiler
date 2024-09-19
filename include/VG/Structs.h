#pragma once
#include <cstring>
#include <cstdint>
#include "Enums.h"
#include "Flags.h"
#include "Queue.h"

#ifdef VULKAN_HPP
#define VULKAN_NATIVE_CAST_OPERATOR(nativeName)\
operator const vk::nativeName& () const { return *reinterpret_cast<const vk::nativeName*>(this); }\
operator const vk::nativeName& () { return *reinterpret_cast<vk::nativeName*>(this); }
#else
#define VULKAN_NATIVE_CAST_OPERATOR(nativeName)
#endif

namespace vg
{
    struct DeviceLimits
    {
        uint32_t maxImageDimension1D;
        uint32_t maxImageDimension2D;
        uint32_t maxImageDimension3D;
        uint32_t maxImageDimensionCube;
        uint32_t maxImageArrayLayers;
        uint32_t maxTexelBufferElements;
        uint32_t maxUniformBufferRange;
        uint32_t maxStorageBufferRange;
        uint32_t maxPushConstantsSize;
        uint32_t maxMemoryAllocationCount;
        uint32_t maxSamplerAllocationCount;
        uint64_t bufferImageGranularity;
        uint64_t sparseAddressSpaceSize;
        uint32_t maxBoundDescriptorSets;
        uint32_t maxPerStageDescriptorSamplers;
        uint32_t maxPerStageDescriptorUniformBuffers;
        uint32_t maxPerStageDescriptorStorageBuffers;
        uint32_t maxPerStageDescriptorSampledImages;
        uint32_t maxPerStageDescriptorStorageImages;
        uint32_t maxPerStageDescriptorInputAttachments;
        uint32_t maxPerStageResources;
        uint32_t maxDescriptorSetSamplers;
        uint32_t maxDescriptorSetUniformBuffers;
        uint32_t maxDescriptorSetUniformBuffersDynamic;
        uint32_t maxDescriptorSetStorageBuffers;
        uint32_t maxDescriptorSetStorageBuffersDynamic;
        uint32_t maxDescriptorSetSampledImages;
        uint32_t maxDescriptorSetStorageImages;
        uint32_t maxDescriptorSetInputAttachments;
        uint32_t maxVertexInputAttributes;
        uint32_t maxVertexInputBindings;
        uint32_t maxVertexInputAttributeOffset;
        uint32_t maxVertexInputBindingStride;
        uint32_t maxVertexOutputComponents;
        uint32_t maxTessellationGenerationLevel;
        uint32_t maxTessellationPatchSize;
        uint32_t maxTessellationControlPerVertexInputComponents;
        uint32_t maxTessellationControlPerVertexOutputComponents;
        uint32_t maxTessellationControlPerPatchOutputComponents;
        uint32_t maxTessellationControlTotalOutputComponents;
        uint32_t maxTessellationEvaluationInputComponents;
        uint32_t maxTessellationEvaluationOutputComponents;
        uint32_t maxGeometryShaderInvocations;
        uint32_t maxGeometryInputComponents;
        uint32_t maxGeometryOutputComponents;
        uint32_t maxGeometryOutputVertices;
        uint32_t maxGeometryTotalOutputComponents;
        uint32_t maxFragmentInputComponents;
        uint32_t maxFragmentOutputAttachments;
        uint32_t maxFragmentDualSrcAttachments;
        uint32_t maxFragmentCombinedOutputResources;
        uint32_t maxComputeSharedMemorySize;
        uint32_t maxComputeWorkGroupCount[3];
        uint32_t maxComputeWorkGroupInvocations;
        uint32_t maxComputeWorkGroupSize[3];
        uint32_t subPixelPrecisionBits;
        uint32_t subTexelPrecisionBits;
        uint32_t mipmapPrecisionBits;
        uint32_t maxDrawIndexedIndexValue;
        uint32_t maxDrawIndirectCount;
        float maxSamplerLodBias;
        float maxSamplerAnisotropy;
        uint32_t maxViewports;
        uint32_t maxViewportDimensions[2];
        float viewportBoundsRange[2];
        uint32_t viewportSubPixelBits;
        size_t minMemoryMapAlignment;
        uint64_t minTexelBufferOffsetAlignment;
        uint64_t minUniformBufferOffsetAlignment;
        uint64_t minStorageBufferOffsetAlignment;
        int32_t minTexelOffset;
        uint32_t maxTexelOffset;
        int32_t minTexelGatherOffset;
        uint32_t maxTexelGatherOffset;
        float minInterpolationOffset;
        float maxInterpolationOffset;
        uint32_t subPixelInterpolationOffsetBits;
        uint32_t maxFramebufferWidth;
        uint32_t maxFramebufferHeight;
        uint32_t maxFramebufferLayers;
        uint32_t framebufferColorSampleCounts;
        uint32_t framebufferDepthSampleCounts;
        uint32_t framebufferStencilSampleCounts;
        uint32_t framebufferNoAttachmentsSampleCounts;
        uint32_t maxColorAttachments;
        uint32_t sampledImageColorSampleCounts;
        uint32_t sampledImageIntegerSampleCounts;
        uint32_t sampledImageDepthSampleCounts;
        uint32_t sampledImageStencilSampleCounts;
        uint32_t storageImageSampleCounts;
        uint32_t maxSampleMaskWords;
        uint32_t timestampComputeAndGraphics;
        float timestampPeriod;
        uint32_t maxClipDistances;
        uint32_t maxCullDistances;
        uint32_t maxCombinedClipAndCullDistances;
        uint32_t discreteQueuePriorities;
        float pointSizeRange[2];
        float lineWidthRange[2];
        float pointSizeGranularity;
        float lineWidthGranularity;
        uint32_t strictLines;
        uint32_t standardSampleLocations;
        uint64_t optimalBufferCopyOffsetAlignment;
        uint64_t optimalBufferCopyRowPitchAlignment;
        uint64_t nonCoherentAtomSize;


        VULKAN_NATIVE_CAST_OPERATOR(PhysicalDeviceLimits);
    };

    struct DeviceSparseProperties
    {
        uint32_t residencyStandard2DBlockShape;
        uint32_t residencyStandard2DMultisampleBlockShape;
        uint32_t residencyStandard3DBlockShape;
        uint32_t residencyAlignedMipSize;
        uint32_t residencyNonResidentStrict;


        VULKAN_NATIVE_CAST_OPERATOR(PhysicalDeviceSparseProperties);
    };

    struct DeviceProperties
    {
        uint32_t apiVersion;
        uint32_t driverVersion;
        uint32_t vendorID;
        uint32_t deviceID;
        DeviceType deviceType;
        char deviceName[256];
        uint8_t pipelineCacheUUID[16];
        DeviceLimits limits;
        DeviceSparseProperties sparseProperties;


        VULKAN_NATIVE_CAST_OPERATOR(PhysicalDeviceProperties);
    };

    struct DeviceFeatures
    {
        uint32_t robustBufferAccess;
        uint32_t fullDrawIndexUint32;
        uint32_t imageCubeArray;
        uint32_t independentBlend;
        uint32_t geometryShader;
        uint32_t tessellationShader;
        uint32_t sampleRateShading;
        uint32_t dualSrcBlend;
        uint32_t logicOp;
        uint32_t multiDrawIndirect;
        uint32_t drawIndirectFirstInstance;
        uint32_t depthClamp;
        uint32_t depthBiasClamp;
        uint32_t fillModeNonSolid;
        uint32_t depthBounds;
        uint32_t wideLines;
        uint32_t largePoints;
        uint32_t alphaToOne;
        uint32_t multiViewport;
        uint32_t samplerAnisotropy;
        uint32_t textureCompressionETC2;
        uint32_t textureCompressionASTC_LDR;
        uint32_t textureCompressionBC;
        uint32_t occlusionQueryPrecise;
        uint32_t pipelineStatisticsQuery;
        uint32_t vertexPipelineStoresAndAtomics;
        uint32_t fragmentStoresAndAtomics;
        uint32_t shaderTessellationAndGeometryPointSize;
        uint32_t shaderImageGatherExtended;
        uint32_t shaderStorageImageExtendedFormats;
        uint32_t shaderStorageImageMultisample;
        uint32_t shaderStorageImageReadWithoutFormat;
        uint32_t shaderStorageImageWriteWithoutFormat;
        uint32_t shaderUniformBufferArrayDynamicIndexing;
        uint32_t shaderSampledImageArrayDynamicIndexing;
        uint32_t shaderStorageBufferArrayDynamicIndexing;
        uint32_t shaderStorageImageArrayDynamicIndexing;
        uint32_t shaderClipDistance;
        uint32_t shaderCullDistance;
        uint32_t shaderFloat64;
        uint32_t shaderInt64;
        uint32_t shaderInt16;
        uint32_t shaderResourceResidency;
        uint32_t shaderResourceMinLod;
        uint32_t sparseBinding;
        uint32_t sparseResidencyBuffer;
        uint32_t sparseResidencyImage2D;
        uint32_t sparseResidencyImage3D;
        uint32_t sparseResidency2Samples;
        uint32_t sparseResidency4Samples;
        uint32_t sparseResidency8Samples;
        uint32_t sparseResidency16Samples;
        uint32_t sparseResidencyAliased;
        uint32_t variableMultisampleRate;
        uint32_t inheritedQueries;

        DeviceFeatures()
            :
            robustBufferAccess(false),
            fullDrawIndexUint32(false),
            imageCubeArray(false),
            independentBlend(false),
            geometryShader(false),
            tessellationShader(false),
            sampleRateShading(false),
            dualSrcBlend(false),
            logicOp(false),
            multiDrawIndirect(false),
            drawIndirectFirstInstance(false),
            depthClamp(false),
            depthBiasClamp(false),
            fillModeNonSolid(false),
            depthBounds(false),
            wideLines(false),
            largePoints(false),
            alphaToOne(false),
            multiViewport(false),
            samplerAnisotropy(false),
            textureCompressionETC2(false),
            textureCompressionASTC_LDR(false),
            textureCompressionBC(false),
            occlusionQueryPrecise(false),
            pipelineStatisticsQuery(false),
            vertexPipelineStoresAndAtomics(false),
            fragmentStoresAndAtomics(false),
            shaderTessellationAndGeometryPointSize(false),
            shaderImageGatherExtended(false),
            shaderStorageImageExtendedFormats(false),
            shaderStorageImageMultisample(false),
            shaderStorageImageReadWithoutFormat(false),
            shaderStorageImageWriteWithoutFormat(false),
            shaderUniformBufferArrayDynamicIndexing(false),
            shaderSampledImageArrayDynamicIndexing(false),
            shaderStorageBufferArrayDynamicIndexing(false),
            shaderStorageImageArrayDynamicIndexing(false),
            shaderClipDistance(false),
            shaderCullDistance(false),
            shaderFloat64(false),
            shaderInt64(false),
            shaderInt16(false),
            shaderResourceResidency(false),
            shaderResourceMinLod(false),
            sparseBinding(false),
            sparseResidencyBuffer(false),
            sparseResidencyImage2D(false),
            sparseResidencyImage3D(false),
            sparseResidency2Samples(false),
            sparseResidency4Samples(false),
            sparseResidency8Samples(false),
            sparseResidency16Samples(false),
            sparseResidencyAliased(false),
            variableMultisampleRate(false),
            inheritedQueries(false)
        {}
        DeviceFeatures(Flags<Feature> features)
            :
            robustBufferAccess(features.IsSet(Feature::RobustBufferAccess)),
            fullDrawIndexUint32(features.IsSet(Feature::FullDrawIndexUint32)),
            imageCubeArray(features.IsSet(Feature::ImageCubeArray)),
            independentBlend(features.IsSet(Feature::IndependentBlend)),
            geometryShader(features.IsSet(Feature::GeometryShader)),
            tessellationShader(features.IsSet(Feature::TessellationShader)),
            sampleRateShading(features.IsSet(Feature::SampleRateShading)),
            dualSrcBlend(features.IsSet(Feature::DualSrcBlend)),
            logicOp(features.IsSet(Feature::LogicOp)),
            multiDrawIndirect(features.IsSet(Feature::MultiDrawIndirect)),
            drawIndirectFirstInstance(features.IsSet(Feature::DrawIndirectFirstInstance)),
            depthClamp(features.IsSet(Feature::DepthClamp)),
            depthBiasClamp(features.IsSet(Feature::DepthBiasClamp)),
            fillModeNonSolid(features.IsSet(Feature::FillModeNonSolid)),
            depthBounds(features.IsSet(Feature::DepthBounds)),
            wideLines(features.IsSet(Feature::WideLines)),
            largePoints(features.IsSet(Feature::LargePoints)),
            alphaToOne(features.IsSet(Feature::AlphaToOne)),
            multiViewport(features.IsSet(Feature::MultiViewport)),
            samplerAnisotropy(features.IsSet(Feature::SamplerAnisotropy)),
            textureCompressionETC2(features.IsSet(Feature::TextureCompressionETC2)),
            textureCompressionASTC_LDR(features.IsSet(Feature::TextureCompressionASTC_LDR)),
            textureCompressionBC(features.IsSet(Feature::TextureCompressionBC)),
            occlusionQueryPrecise(features.IsSet(Feature::OcclusionQueryPrecise)),
            pipelineStatisticsQuery(features.IsSet(Feature::PipelineStatisticsQuery)),
            vertexPipelineStoresAndAtomics(features.IsSet(Feature::VertexPipelineStoresAndAtomics)),
            fragmentStoresAndAtomics(features.IsSet(Feature::FragmentStoresAndAtomics)),
            shaderTessellationAndGeometryPointSize(features.IsSet(Feature::ShaderTessellationAndGeometryPointSize)),
            shaderImageGatherExtended(features.IsSet(Feature::ShaderImageGatherExtended)),
            shaderStorageImageExtendedFormats(features.IsSet(Feature::ShaderStorageImageExtendedFormats)),
            shaderStorageImageMultisample(features.IsSet(Feature::ShaderStorageImageMultisample)),
            shaderStorageImageReadWithoutFormat(features.IsSet(Feature::ShaderStorageImageReadWithoutFormat)),
            shaderStorageImageWriteWithoutFormat(features.IsSet(Feature::ShaderStorageImageWriteWithoutFormat)),
            shaderUniformBufferArrayDynamicIndexing(features.IsSet(Feature::ShaderUniformBufferArrayDynamicIndexing)),
            shaderSampledImageArrayDynamicIndexing(features.IsSet(Feature::ShaderSampledImageArrayDynamicIndexing)),
            shaderStorageBufferArrayDynamicIndexing(features.IsSet(Feature::ShaderStorageBufferArrayDynamicIndexing)),
            shaderStorageImageArrayDynamicIndexing(features.IsSet(Feature::ShaderStorageImageArrayDynamicIndexing)),
            shaderClipDistance(features.IsSet(Feature::ShaderClipDistance)),
            shaderCullDistance(features.IsSet(Feature::ShaderCullDistance)),
            shaderFloat64(features.IsSet(Feature::ShaderFloat64)),
            shaderInt64(features.IsSet(Feature::ShaderInt64)),
            shaderInt16(features.IsSet(Feature::ShaderInt16)),
            shaderResourceResidency(features.IsSet(Feature::ShaderResourceResidency)),
            shaderResourceMinLod(features.IsSet(Feature::ShaderResourceMinLod)),
            sparseBinding(features.IsSet(Feature::SparseBinding)),
            sparseResidencyBuffer(features.IsSet(Feature::SparseResidencyBuffer)),
            sparseResidencyImage2D(features.IsSet(Feature::SparseResidencyImage2D)),
            sparseResidencyImage3D(features.IsSet(Feature::SparseResidencyImage3D)),
            sparseResidency2Samples(features.IsSet(Feature::SparseResidency2Samples)),
            sparseResidency4Samples(features.IsSet(Feature::SparseResidency4Samples)),
            sparseResidency8Samples(features.IsSet(Feature::SparseResidency8Samples)),
            sparseResidency16Samples(features.IsSet(Feature::SparseResidency16Samples)),
            sparseResidencyAliased(features.IsSet(Feature::SparseResidencyAliased)),
            variableMultisampleRate(features.IsSet(Feature::VariableMultisampleRate)),
            inheritedQueries(features.IsSet(Feature::InheritedQueries))
        {}

        DeviceFeatures& operator&=(const DeviceFeatures& rhs)
        {
            robustBufferAccess &= rhs.robustBufferAccess;
            fullDrawIndexUint32 &= rhs.fullDrawIndexUint32;
            imageCubeArray &= rhs.imageCubeArray;
            independentBlend &= rhs.independentBlend;
            geometryShader &= rhs.geometryShader;
            tessellationShader &= rhs.tessellationShader;
            sampleRateShading &= rhs.sampleRateShading;
            dualSrcBlend &= rhs.dualSrcBlend;
            logicOp &= rhs.logicOp;
            multiDrawIndirect &= rhs.multiDrawIndirect;
            drawIndirectFirstInstance &= rhs.drawIndirectFirstInstance;
            depthClamp &= rhs.depthClamp;
            depthBiasClamp &= rhs.depthBiasClamp;
            fillModeNonSolid &= rhs.fillModeNonSolid;
            depthBounds &= rhs.depthBounds;
            wideLines &= rhs.wideLines;
            largePoints &= rhs.largePoints;
            alphaToOne &= rhs.alphaToOne;
            multiViewport &= rhs.multiViewport;
            samplerAnisotropy &= rhs.samplerAnisotropy;
            textureCompressionETC2 &= rhs.textureCompressionETC2;
            textureCompressionASTC_LDR &= rhs.textureCompressionASTC_LDR;
            textureCompressionBC &= rhs.textureCompressionBC;
            occlusionQueryPrecise &= rhs.occlusionQueryPrecise;
            pipelineStatisticsQuery &= rhs.pipelineStatisticsQuery;
            vertexPipelineStoresAndAtomics &= rhs.vertexPipelineStoresAndAtomics;
            fragmentStoresAndAtomics &= rhs.fragmentStoresAndAtomics;
            shaderTessellationAndGeometryPointSize &= rhs.shaderTessellationAndGeometryPointSize;
            shaderImageGatherExtended &= rhs.shaderImageGatherExtended;
            shaderStorageImageExtendedFormats &= rhs.shaderStorageImageExtendedFormats;
            shaderStorageImageMultisample &= rhs.shaderStorageImageMultisample;
            shaderStorageImageReadWithoutFormat &= rhs.shaderStorageImageReadWithoutFormat;
            shaderStorageImageWriteWithoutFormat &= rhs.shaderStorageImageWriteWithoutFormat;
            shaderUniformBufferArrayDynamicIndexing &= rhs.shaderUniformBufferArrayDynamicIndexing;
            shaderSampledImageArrayDynamicIndexing &= rhs.shaderSampledImageArrayDynamicIndexing;
            shaderStorageBufferArrayDynamicIndexing &= rhs.shaderStorageBufferArrayDynamicIndexing;
            shaderStorageImageArrayDynamicIndexing &= rhs.shaderStorageImageArrayDynamicIndexing;
            shaderClipDistance &= rhs.shaderClipDistance;
            shaderCullDistance &= rhs.shaderCullDistance;
            shaderFloat64 &= rhs.shaderFloat64;
            shaderInt64 &= rhs.shaderInt64;
            shaderInt16 &= rhs.shaderInt16;
            shaderResourceResidency &= rhs.shaderResourceResidency;
            shaderResourceMinLod &= rhs.shaderResourceMinLod;
            sparseBinding &= rhs.sparseBinding;
            sparseResidencyBuffer &= rhs.sparseResidencyBuffer;
            sparseResidencyImage2D &= rhs.sparseResidencyImage2D;
            sparseResidencyImage3D &= rhs.sparseResidencyImage3D;
            sparseResidency2Samples &= rhs.sparseResidency2Samples;
            sparseResidency4Samples &= rhs.sparseResidency4Samples;
            sparseResidency8Samples &= rhs.sparseResidency8Samples;
            sparseResidency16Samples &= rhs.sparseResidency16Samples;
            sparseResidencyAliased &= rhs.sparseResidencyAliased;
            variableMultisampleRate &= rhs.variableMultisampleRate;
            inheritedQueries &= rhs.inheritedQueries;

            return *this;
        }

        DeviceFeatures operator&(const DeviceFeatures& rhs) const
        {
            DeviceFeatures features(*this);
            return features.operator&=(rhs);
        }

        bool operator==(const DeviceFeatures& rhs) const
        {
            return
                robustBufferAccess == rhs.robustBufferAccess &&
                fullDrawIndexUint32 == rhs.fullDrawIndexUint32 &&
                imageCubeArray == rhs.imageCubeArray &&
                independentBlend == rhs.independentBlend &&
                geometryShader == rhs.geometryShader &&
                tessellationShader == rhs.tessellationShader &&
                sampleRateShading == rhs.sampleRateShading &&
                dualSrcBlend == rhs.dualSrcBlend &&
                logicOp == rhs.logicOp &&
                multiDrawIndirect == rhs.multiDrawIndirect &&
                drawIndirectFirstInstance == rhs.drawIndirectFirstInstance &&
                depthClamp == rhs.depthClamp &&
                depthBiasClamp == rhs.depthBiasClamp &&
                fillModeNonSolid == rhs.fillModeNonSolid &&
                depthBounds == rhs.depthBounds &&
                wideLines == rhs.wideLines &&
                largePoints == rhs.largePoints &&
                alphaToOne == rhs.alphaToOne &&
                multiViewport == rhs.multiViewport &&
                samplerAnisotropy == rhs.samplerAnisotropy &&
                textureCompressionETC2 == rhs.textureCompressionETC2 &&
                textureCompressionASTC_LDR == rhs.textureCompressionASTC_LDR &&
                textureCompressionBC == rhs.textureCompressionBC &&
                occlusionQueryPrecise == rhs.occlusionQueryPrecise &&
                pipelineStatisticsQuery == rhs.pipelineStatisticsQuery &&
                vertexPipelineStoresAndAtomics == rhs.vertexPipelineStoresAndAtomics &&
                fragmentStoresAndAtomics == rhs.fragmentStoresAndAtomics &&
                shaderTessellationAndGeometryPointSize == rhs.shaderTessellationAndGeometryPointSize &&
                shaderImageGatherExtended == rhs.shaderImageGatherExtended &&
                shaderStorageImageExtendedFormats == rhs.shaderStorageImageExtendedFormats &&
                shaderStorageImageMultisample == rhs.shaderStorageImageMultisample &&
                shaderStorageImageReadWithoutFormat == rhs.shaderStorageImageReadWithoutFormat &&
                shaderStorageImageWriteWithoutFormat == rhs.shaderStorageImageWriteWithoutFormat &&
                shaderUniformBufferArrayDynamicIndexing == rhs.shaderUniformBufferArrayDynamicIndexing &&
                shaderSampledImageArrayDynamicIndexing == rhs.shaderSampledImageArrayDynamicIndexing &&
                shaderStorageBufferArrayDynamicIndexing == rhs.shaderStorageBufferArrayDynamicIndexing &&
                shaderStorageImageArrayDynamicIndexing == rhs.shaderStorageImageArrayDynamicIndexing &&
                shaderClipDistance == rhs.shaderClipDistance &&
                shaderCullDistance == rhs.shaderCullDistance &&
                shaderFloat64 == rhs.shaderFloat64 &&
                shaderInt64 == rhs.shaderInt64 &&
                shaderInt16 == rhs.shaderInt16 &&
                shaderResourceResidency == rhs.shaderResourceResidency &&
                shaderResourceMinLod == rhs.shaderResourceMinLod &&
                sparseBinding == rhs.sparseBinding &&
                sparseResidencyBuffer == rhs.sparseResidencyBuffer &&
                sparseResidencyImage2D == rhs.sparseResidencyImage2D &&
                sparseResidencyImage3D == rhs.sparseResidencyImage3D &&
                sparseResidency2Samples == rhs.sparseResidency2Samples &&
                sparseResidency4Samples == rhs.sparseResidency4Samples &&
                sparseResidency8Samples == rhs.sparseResidency8Samples &&
                sparseResidency16Samples == rhs.sparseResidency16Samples &&
                sparseResidencyAliased == rhs.sparseResidencyAliased &&
                variableMultisampleRate == rhs.variableMultisampleRate &&
                inheritedQueries == rhs.inheritedQueries;
        }

        VULKAN_NATIVE_CAST_OPERATOR(PhysicalDeviceFeatures);
    };

    struct SurfaceFormat
    {
        Format format;
        ColorSpace colorSpace;

        SurfaceFormat() :format(Format::Undefined), colorSpace(ColorSpace::SRGBNL) {}
        SurfaceFormat(Format format, ColorSpace colorSpace) : format(format), colorSpace(colorSpace) {}
    };

    struct FormatProperties
    {
        Flags<FormatFeature> linearTilingFeatures;
        Flags<FormatFeature> optimalTilingFeatures;
        Flags<FormatFeature> bufferFeatures;


        VULKAN_NATIVE_CAST_OPERATOR(FormatProperties);
    };

    struct ColorBlend
    {
        uint32_t blendEnable;
        BlendFactor srcColorBlendFactor;
        BlendFactor dstColorBlendFactor;
        BlendOp colorBlendOp;
        BlendFactor srcAlphaBlendFactor;
        BlendFactor dstAlphaBlendFactor;
        BlendOp alphaBlendOp;
        Flags<ColorComponent> colorWriteMask;

        ColorBlend() :
            blendEnable(false),
            srcColorBlendFactor(BlendFactor::Zero),
            dstColorBlendFactor(BlendFactor::Zero),
            colorBlendOp(BlendOp::Add),
            srcAlphaBlendFactor(BlendFactor::Zero),
            dstAlphaBlendFactor(BlendFactor::Zero),
            alphaBlendOp(BlendOp::Add),
            colorWriteMask(ColorComponent::RGBA)
        {}

        ColorBlend(
            BlendFactor srcColorBlendFactor,
            BlendFactor dstColorBlendFactor,
            BlendOp colorBlendOp,
            BlendFactor srcAlphaBlendFactor,
            BlendFactor dstAlphaBlendFactor,
            BlendOp alphaBlendOp,
            Flags<ColorComponent> colorWriteMask
        ) :
            blendEnable(true),
            srcColorBlendFactor(srcColorBlendFactor),
            dstColorBlendFactor(dstColorBlendFactor),
            colorBlendOp(colorBlendOp),
            srcAlphaBlendFactor(srcAlphaBlendFactor),
            dstAlphaBlendFactor(dstAlphaBlendFactor),
            alphaBlendOp(alphaBlendOp),
            colorWriteMask(colorWriteMask)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(PipelineColorBlendAttachmentState);
    };

    struct SubpassDependency
    {
        uint32_t srcSubpass;
        uint32_t dstSubpass;
        Flags<PipelineStage> srcStageMask;
        Flags<PipelineStage> dstStageMask;
        Flags<Access> srcAccessMask;
        Flags<Access> dstAccessMask;
        Flags<Dependency> dependencyFlags;

        SubpassDependency() {}

        SubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, Flags<Dependency> dependencyFlags) :
            srcSubpass(srcSubpass), dstSubpass(dstSubpass), srcStageMask(srcStageMask), dstStageMask(dstStageMask), srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), dependencyFlags(dependencyFlags)
        {}

        VULKAN_NATIVE_CAST_OPERATOR(SubpassDependency);
    };

    struct Attachment
    {
    private:
        uint32_t flags = 0;

    public:
        Format format;
        unsigned int samples;
        LoadOp loadOp;
        StoreOp storeOp;
        LoadOp stencilLoadOp;
        StoreOp stencilStoreOp;
        ImageLayout initialLayout;
        ImageLayout finalLayout;

        Attachment()
            :format(Format::Undefined),
            samples(1),
            loadOp(LoadOp::DontCare),
            storeOp(StoreOp::DontCare),
            stencilLoadOp(LoadOp::DontCare),
            stencilStoreOp(StoreOp::DontCare),
            initialLayout(ImageLayout::Undefined),
            finalLayout(ImageLayout::Undefined)
        {}

        Attachment(
            Format format,
            ImageLayout finalLayout,
            ImageLayout initialLayout = ImageLayout::Undefined,
            LoadOp loadOp = LoadOp::Clear,
            StoreOp storeOp = StoreOp::Store,
            LoadOp stencilLoadOp = LoadOp::DontCare,
            StoreOp stencilStoreOp = StoreOp::DontCare,
            unsigned int samples = 1) :
            format(format), samples(samples), loadOp(loadOp), storeOp(storeOp), stencilLoadOp(stencilLoadOp), stencilStoreOp(stencilStoreOp), initialLayout(initialLayout), finalLayout(finalLayout)
        {}

        Attachment(
            Format format,
            unsigned int samples,
            ImageLayout finalLayout,
            ImageLayout initialLayout = ImageLayout::Undefined,
            LoadOp loadOp = LoadOp::Clear,
            StoreOp storeOp = StoreOp::Store,
            LoadOp stencilLoadOp = LoadOp::DontCare,
            StoreOp stencilStoreOp = StoreOp::DontCare) :
            format(format), samples(samples), loadOp(loadOp), storeOp(storeOp), stencilLoadOp(stencilLoadOp), stencilStoreOp(stencilStoreOp), initialLayout(initialLayout), finalLayout(finalLayout)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(AttachmentDescription);
    };

    struct AttachmentReference
    {
        unsigned int index;
        ImageLayout layout;
        AttachmentReference(unsigned int index = 0, ImageLayout layout = ImageLayout::Undefined)
            :index(index), layout(layout)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(AttachmentReference);
    };

    struct Viewport
    {
        float x;
        float y;
        float width;
        float height;
        float minDepth;
        float maxDepth;
        Viewport() : Viewport(0, 0) {}
        Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1) :x(x), y(y), width(width), height(height), minDepth(minDepth), maxDepth(maxDepth) {}


        VULKAN_NATIVE_CAST_OPERATOR(Viewport);
    };
    struct Scissor
    {
        int x;
        int y;
        int width;
        int height;
        Scissor() :Scissor(0, 0) {}
        Scissor(float width, float height, int x = 0, int y = 0) :x(x), y(y), width(width), height(height) {}


        VULKAN_NATIVE_CAST_OPERATOR(Rect2D);
    };

    struct VertexBinding
    {
        uint32_t binding;
        uint32_t stride;
        InputRate inputRate;

        VertexBinding(int binding = 0, int stride = 0, InputRate inputRate = InputRate::Vertex) :binding(binding), stride(stride), inputRate(inputRate) {}


        VULKAN_NATIVE_CAST_OPERATOR(VertexInputBindingDescription);
    };

    struct VertexAttribute
    {
        uint32_t location;
        uint32_t binding;
        Format format;
        uint32_t offset;

        VertexAttribute(uint32_t location = 0, uint32_t binding = 0, Format format = Format::Undefined, uint32_t offset = 0) :location(location), binding(binding), format(format), offset(offset) {}


        VULKAN_NATIVE_CAST_OPERATOR(VertexInputAttributeDescription);
    };

    struct VertexLayout
    {
    private:
        const uint32_t reserved_1 = 19;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        uint32_t vertexDescriptionCount = 0;
        const VertexBinding* vertexDescritpions = nullptr;
        uint32_t vertexAttributesCount = 0;
        const VertexAttribute* vertexAttributes = nullptr;

        VertexLayout() {}

        VertexLayout(const std::vector<VertexBinding>& vertexDescriptions, const std::vector<VertexAttribute>& vertexAttributes)
            : vertexDescriptionCount(vertexDescriptions.size()), vertexDescritpions(new VertexBinding[vertexDescriptionCount]), vertexAttributesCount(vertexAttributes.size()), vertexAttributes(new VertexAttribute[vertexAttributesCount])
        {
            memcpy((void*) this->vertexDescritpions, &vertexDescriptions[0], sizeof(VertexBinding) * vertexDescriptionCount);
            memcpy((void*) this->vertexAttributes, &vertexAttributes[0], sizeof(VertexAttribute) * vertexAttributesCount);
        }

        VertexLayout(VertexLayout&& rhs) noexcept
            :VertexLayout()
        {
            *this = std::move(rhs);
        }
        VertexLayout& operator=(VertexLayout&& rhs)
        {
            if (&rhs == this) return *this;
            std::swap(vertexDescriptionCount, rhs.vertexDescriptionCount);
            std::swap(vertexDescritpions, rhs.vertexDescritpions);
            std::swap(vertexAttributesCount, rhs.vertexAttributesCount);
            std::swap(vertexAttributes, rhs.vertexAttributes);
            return *this;
        }

        VertexLayout(const VertexLayout& rhs)
        {
            vertexDescriptionCount = rhs.vertexDescriptionCount;
            vertexDescritpions = new VertexBinding[vertexDescriptionCount];
            memcpy((void*) vertexDescritpions, rhs.vertexDescritpions, sizeof(VertexBinding) * vertexDescriptionCount);

            vertexAttributesCount = rhs.vertexAttributesCount;
            vertexAttributes = new VertexAttribute[vertexAttributesCount];
            memcpy((void*) vertexAttributes, rhs.vertexAttributes, sizeof(VertexAttribute) * vertexAttributesCount);
        }
        VertexLayout& operator=(const VertexLayout& rhs)
        {
            if (&rhs == this)return *this;
            vertexDescriptionCount = rhs.vertexDescriptionCount;
            vertexDescritpions = new VertexBinding[vertexDescriptionCount];
            memcpy((void*) vertexDescritpions, rhs.vertexDescritpions, sizeof(VertexBinding) * vertexDescriptionCount);
            vertexAttributesCount = rhs.vertexAttributesCount;
            vertexAttributes = new VertexAttribute[vertexAttributesCount];
            memcpy((void*) vertexAttributes, rhs.vertexAttributes, sizeof(VertexAttribute) * vertexAttributesCount);
            return *this;
        }
        ~VertexLayout()
        {
            delete[] vertexDescritpions;
            delete[] vertexAttributes;
        }


        VULKAN_NATIVE_CAST_OPERATOR(PipelineVertexInputStateCreateInfo);
    };
    struct InputAssembly
    {
    private:
        const uint32_t reserved_1 = 20;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        Primitive primitive = Primitive::Points;
        uint32_t primitiveRestart = 0;

        InputAssembly() {}

        InputAssembly(Primitive primitive, bool primitiveRestart = false) :primitive(primitive), primitiveRestart(primitiveRestart) {}


        VULKAN_NATIVE_CAST_OPERATOR(PipelineInputAssemblyStateCreateInfo);
    };
    struct Tesselation
    {
    private:
        const uint32_t reserved_1 = 21;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
        int reserved_4 = 0;

    public:

        VULKAN_NATIVE_CAST_OPERATOR(PipelineTessellationStateCreateInfo);
    };
    struct ViewportState
    {
    private:
        const uint32_t reserved_1 = 22;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        uint32_t viewportCount = 0;
        Viewport* viewports = nullptr;
        uint32_t scissorCount = 0;
        Scissor* scissors = nullptr;

        ViewportState() :viewportCount(0), viewports(nullptr), scissorCount(0), scissors(nullptr) {}

        ViewportState(Viewport viewport, Scissor scissor) :viewportCount(1), viewports(new Viewport(viewport)), scissorCount(1), scissors(new Scissor(scissor)) {}

        ViewportState(const std::vector<Viewport>& viewports, const std::vector<Scissor>& scissors) :viewportCount(viewports.size()), viewports(new Viewport[viewportCount]), scissorCount(scissors.size()), scissors(new Scissor[scissorCount])
        {
            memcpy((void*) this->viewports, &viewports[0], sizeof(Viewport) * viewportCount);
            memcpy((void*) this->scissors, &scissors[0], sizeof(Scissor) * scissorCount);
        }

        ViewportState(ViewportState&& rhs)
            :ViewportState()
        {
            *this = std::move(rhs);
        }

        ViewportState& operator=(ViewportState&& rhs)
        {
            if (&rhs == this) return *this;
            std::swap(viewportCount, rhs.viewportCount);
            std::swap(viewports, rhs.viewports);
            std::swap(scissorCount, rhs.scissorCount);
            std::swap(scissors, rhs.scissors);
            return *this;
        }

        ViewportState(const ViewportState& rhs)
        {
            viewportCount = rhs.viewportCount;
            viewports = new Viewport[viewportCount];
            memcpy((void*) viewports, rhs.viewports, sizeof(Viewport) * viewportCount);
            scissorCount = rhs.scissorCount;
            scissors = new Scissor[scissorCount];
            memcpy((void*) scissors, rhs.scissors, sizeof(Scissor) * scissorCount);
        }
        ViewportState& operator=(const ViewportState& rhs)
        {
            if (&rhs == this)return *this;
            viewportCount = rhs.viewportCount;
            viewports = new Viewport[viewportCount];
            memcpy((void*) viewports, rhs.viewports, sizeof(Viewport) * viewportCount);
            scissorCount = rhs.scissorCount;
            scissors = new Scissor[scissorCount];
            memcpy((void*) scissors, rhs.scissors, sizeof(Scissor) * scissorCount);
            return *this;
        }
        ~ViewportState()
        {
            delete[] viewports;
            delete[] scissors;
        }


        VULKAN_NATIVE_CAST_OPERATOR(PipelineViewportStateCreateInfo);
    };
    struct alignas(float) DepthBias
    {
        uint32_t enable = 0;
        float constantFactor = 0;
        float clamp = 0;
        float slopeFactor = 0;

        DepthBias(bool enable = false, float constantFactor = 0, float clamp = 0, float slopeFactor = 0) :enable(enable), constantFactor(constantFactor), clamp(clamp), slopeFactor(slopeFactor) {}
    };
    struct Rasterizer
    {
    private:
        const uint32_t reserved_1 = 23;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        uint32_t depthClamp = 0;
        uint32_t discard = 0;
        PolygonMode polygonMode = PolygonMode::Fill;
        CullMode cullMode = CullMode::None;
        FrontFace  frontFace = FrontFace::CounterClockwise;
        DepthBias depthBias;
        float lineWidth = 1.0f;

        Rasterizer()
            :discard(true)
        {}

        Rasterizer(bool depthClamp, PolygonMode polygonMode, CullMode cullMode = CullMode::Back, FrontFace frontFace = FrontFace::CounterClockwise, DepthBias depthBias = DepthBias(), float lineWidth = 1.0f)
            :discard(false), depthClamp(depthClamp), polygonMode(polygonMode), cullMode(cullMode), frontFace(frontFace), depthBias(depthBias), lineWidth(lineWidth)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(PipelineRasterizationStateCreateInfo);
    };
    struct Multisampling
    {
    private:
        const uint32_t reserved_1 = 24;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        uint32_t rasterizationSamples = 1;
        uint32_t sampleShadingEnable = 0;
        float minSampleShading = 0;
        const void* sampleMask = nullptr;
        uint32_t alphaToCoverageEnable = 0;
        uint32_t alphaToOneEnable = 0;

        Multisampling() {}

        Multisampling(uint32_t samples, bool enableSampleShading = false, float minSampleShading = 0, void* sampleMask = nullptr, bool enableAlphaToCoverage = false, bool enableAlphaToOne = false) :
            rasterizationSamples(samples), sampleShadingEnable(enableSampleShading),
            minSampleShading(minSampleShading), sampleMask(sampleMask),
            alphaToCoverageEnable(enableAlphaToCoverage), alphaToOneEnable(enableAlphaToOne)
        {}

        VULKAN_NATIVE_CAST_OPERATOR(PipelineMultisampleStateCreateInfo);
    };

    struct StencilOpState
    {
        StencilOp failOp = StencilOp::Keep;
        StencilOp passOp = StencilOp::Replace;
        StencilOp depthFailOp = StencilOp::Replace;
        CompareOp compareOp = CompareOp::Equal;
        uint32_t compareMask = ~0;
        uint32_t writeMask = ~0;
        uint32_t reference = 0;

        StencilOpState() {}

        StencilOpState(StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp, uint32_t compareMask, uint32_t writeMask, uint32_t reference)
            : failOp(failOp), passOp(passOp), depthFailOp(depthFailOp), compareOp(compareOp), compareMask(compareMask), writeMask(writeMask), reference(reference)
        {}
    };

    struct DepthStencil
    {
    private:
        const uint32_t reserved_1 = 25;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
    public:
        uint32_t depthTestEnable = 0;
        uint32_t depthWriteEnable = 0;
        CompareOp depthCompareOp = CompareOp::Never;
        uint32_t depthBoundsTestEnable = 0;
        uint32_t stencilTestEnable = 0;
        StencilOpState front = {};
        StencilOpState back = {};
        float minDepthBounds = 0;
        float maxDepthBounds = 0;

    public:
        DepthStencil() {}
        DepthStencil(bool enableDepthTest, bool enableDepthWrite, CompareOp depthCompareOp) :depthTestEnable(enableDepthTest), depthWriteEnable(enableDepthWrite), depthCompareOp(depthCompareOp) {}
        DepthStencil(bool enableDepthTest, bool enableDepthWrite, CompareOp depthCompareOp, bool enabledepthBoundsTest, float minDepthBounds, float maxDepthBounds) :depthTestEnable(enableDepthTest), depthWriteEnable(enableDepthWrite), depthCompareOp(depthCompareOp), depthBoundsTestEnable(enabledepthBoundsTest), minDepthBounds(minDepthBounds), maxDepthBounds(maxDepthBounds) {}
        DepthStencil(bool enableDepthTest, bool enableDepthWrite, CompareOp depthCompareOp, StencilOpState front, StencilOpState back, bool enabledepthBoundsTest, float minDepthBounds, float maxDepthBounds) :depthTestEnable(enableDepthTest), depthWriteEnable(enableDepthWrite), depthCompareOp(depthCompareOp), depthBoundsTestEnable(enabledepthBoundsTest), stencilTestEnable(true), front(front), back(back), minDepthBounds(minDepthBounds), maxDepthBounds(maxDepthBounds) {}


        VULKAN_NATIVE_CAST_OPERATOR(PipelineDepthStencilStateCreateInfo);
    };
    struct ColorBlending
    {
    private:
        const uint32_t reserved_1 = 26;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        uint32_t enableLogicOp;
        LogicOp logicOp;
        uint32_t attachmentCount;
        ColorBlend* attachments = nullptr;
        float blendConsts[4];

        ColorBlending()
            :enableLogicOp(0), logicOp(LogicOp::Clear), blendConsts{ 0,0,0,0 }, attachmentCount(0), attachments(nullptr)
        {}

        ColorBlending(bool enableLogicOp, LogicOp logicOp, const float(&blendConstants)[4], const std::vector<ColorBlend>& colorBlending = {})
            :enableLogicOp(enableLogicOp), logicOp(logicOp), blendConsts{ blendConstants[0],blendConstants[1],blendConstants[2],blendConstants[3] }, attachmentCount(colorBlending.size()), attachments(new ColorBlend[attachmentCount])
        {
            memcpy((void*) this->attachments, &colorBlending[0], sizeof(ColorBlend) * attachmentCount);
        }

        ColorBlending(ColorBlending&& rhs)
            :ColorBlending()
        {}

        ColorBlending& operator=(ColorBlending&& rhs)
        {
            if (&rhs == this) return *this;
            std::swap(enableLogicOp, rhs.enableLogicOp);
            std::swap(logicOp, rhs.logicOp);
            std::swap(attachmentCount, rhs.attachmentCount);
            std::swap(attachments, rhs.attachments);
            std::swap(blendConsts, rhs.blendConsts);
            return *this;
        }

        ColorBlending(const ColorBlending& rhs)
        {
            enableLogicOp = rhs.enableLogicOp;
            logicOp = rhs.logicOp;
            memcpy(blendConsts, rhs.blendConsts, sizeof(float) * 4);
            attachmentCount = rhs.attachmentCount;
            attachments = new ColorBlend[attachmentCount];
            memcpy((void*) attachments, rhs.attachments, sizeof(ColorBlend) * attachmentCount);
        }
        ColorBlending& operator=(const ColorBlending& rhs)
        {
            if (&rhs == this)return *this;
            enableLogicOp = rhs.enableLogicOp;
            logicOp = rhs.logicOp;
            memcpy(blendConsts, rhs.blendConsts, sizeof(float) * 4);
            attachmentCount = rhs.attachmentCount;
            attachments = new ColorBlend[attachmentCount];
            memcpy((void*) attachments, rhs.attachments, sizeof(ColorBlend) * attachmentCount);
            return *this;
        }
        ~ColorBlending()
        {
            delete[] attachments;
        }


        VULKAN_NATIVE_CAST_OPERATOR(PipelineColorBlendStateCreateInfo);
    };

    struct DescriptorSetLayoutBinding
    {
    public:
        uint32_t binding;
        DescriptorType descriptorType;
        uint32_t descriptorCount;
        Flags<ShaderStage> stageFlags;
        const void* pImmutableSamplers = nullptr;

        DescriptorSetLayoutBinding()
            :binding(0), descriptorType(DescriptorType::UniformBuffer), stageFlags()
        {}

        DescriptorSetLayoutBinding(uint32_t binding, DescriptorType descriptorType, uint32_t descriptorCount, Flags<ShaderStage> stageFlags) :binding(binding), descriptorType(descriptorType), descriptorCount(descriptorCount), stageFlags(stageFlags)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(DescriptorSetLayoutBinding);

    };

    struct ImageSubresourceLayers
    {
        Flags<ImageAspect> aspectMask;
        uint32_t mipLevel;
        uint32_t baseArrayLayer;
        uint32_t layerCount;

        ImageSubresourceLayers() :aspectMask(), mipLevel(0), baseArrayLayer(0), layerCount(0) {}

        ImageSubresourceLayers(Flags<ImageAspect> aspectMask, uint32_t mipLevel = 0, uint32_t baseArrayLayer = 0, uint32_t layerCount = 1)
            :aspectMask(aspectMask), mipLevel(mipLevel), baseArrayLayer(baseArrayLayer), layerCount(layerCount)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(ImageSubresourceLayers);
    };

    struct BufferCopyRegion
    {
        uint64_t srcOffset;
        uint64_t dstOffset;
        uint64_t size;

        BufferCopyRegion() :srcOffset(0), dstOffset(0), size(0) {}

        BufferCopyRegion(uint64_t size, uint64_t srcOffset = 0, uint64_t dstOffset = 0) :srcOffset(srcOffset), dstOffset(dstOffset), size(size) {}


        VULKAN_NATIVE_CAST_OPERATOR(BufferCopy);
    };

    template<typename T = uint32_t>
    struct Point2D
    {
        T x, y;
        Point2D() :x(0), y(0) {}
        template<typename OT>
        Point2D(OT scalar) : x(scalar), y(scalar) {}
        template<typename OT>
        Point2D(OT x, OT y) : x(x), y(y) {}


        VULKAN_NATIVE_CAST_OPERATOR(Offset2D);
    };

    template<typename T = uint32_t>
    struct Point3D
    {
        T x, y, z;
        Point3D() :x(0), y(0), z(0) {}
        template<typename OT>
        Point3D(OT scalar) : x(scalar), y(scalar), z(scalar) {}
        template<typename OT>
        Point3D(OT x, OT y, OT z) : x(x), y(y), z(z) {}


        VULKAN_NATIVE_CAST_OPERATOR(Offset3D);
    };
    union ClearValue;
    union ClearColor
    {
        float float32[4];
        int32_t int32[4];
        uint32_t Uint32[4];

        /// @brief Create a clear structure for color attachments or images. Make sure that the type matches the format of the image.
        /// @param r Red
        /// @param g Green 
        /// @param b Blue
        /// @param a Alpha
        ClearColor(float r = 0, float g = 0, float b = 0, float a = 1) :float32{ r,g,b,a } {}

        /// @brief Create a clear structure for color attachments or images. Make sure that the type matches the format of the image.
        /// @param r Red
        /// @param g Green 
        /// @param b Blue
        /// @param a Alpha
        ClearColor(int32_t r, int32_t g, int32_t b, int32_t a) : int32{ r,g,b,a } {}

        /// @brief Create a clear structure for color attachments or images. Make sure that the type matches the format of the image.
        /// @param r Red
        /// @param g Green 
        /// @param b Blue
        /// @param a Alpha
        ClearColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a) :Uint32{ r,g,b,a } {}
        operator ClearValue();
    };
    struct ClearDepthStencil
    {
        float depthClearValue;
        uint32_t stencilClearValue;

        ClearDepthStencil() :depthClearValue(0), stencilClearValue(0) {}


        /// @brief Create a clear structure for depth and/or stencil attachments or images.
        /// @param depthClearValue Depth Clear Value
        /// @param stencilClearValue Stencil Clear Value 
        ClearDepthStencil(float depthClearValue, uint32_t stencilClearValue) :depthClearValue(depthClearValue), stencilClearValue(stencilClearValue) {}

        operator ClearValue();
    };
    union ClearValue
    {
        ClearColor color;
        ClearDepthStencil depthStencil;

        ClearValue() {}
        explicit ClearValue(ClearColor color) :color(color) {}
        explicit ClearValue(ClearDepthStencil depthStencil) : depthStencil(depthStencil) {}

        VULKAN_NATIVE_CAST_OPERATOR(ClearColorValue);
    };

    inline ClearColor::operator vg::ClearValue() { return *(ClearValue*) this; }

    inline ClearDepthStencil::operator vg::ClearValue() { return *(ClearValue*) this; }

    struct ImageCopy
    {
        ImageSubresourceLayers srcSubresource;
        Point3D<uint32_t> srcOffset;
        ImageSubresourceLayers dstSubresource;
        Point3D<uint32_t> dstOffset;
        Point3D<uint32_t> extent;

        ImageCopy()
        {}

        ImageCopy(
            ImageSubresourceLayers srcSubresource,
            uint32_t srcOffset,
            ImageSubresourceLayers dstSubresource,
            uint32_t dstOffset,
            uint32_t extent)
            :srcSubresource(srcSubresource),
            srcOffset{ srcOffset, 0U, 0U },
            dstSubresource(dstSubresource),
            dstOffset{ dstOffset, 0U, 0U },
            extent{ extent, 1U, 1U }
        {}

        ImageCopy(
            ImageSubresourceLayers srcSubresource,
            Point2D<uint32_t> srcOffset,
            ImageSubresourceLayers dstSubresource,
            Point2D<uint32_t> dstOffset,
            Point2D<uint32_t> extent)
            :srcSubresource(srcSubresource),
            srcOffset{ srcOffset.x,srcOffset.y, 0U },
            dstSubresource(dstSubresource),
            dstOffset{ dstOffset.x,dstOffset.y, 0U },
            extent{ extent.x, extent.y, 1U }
        {}

        ImageCopy(
            ImageSubresourceLayers srcSubresource,
            Point3D<uint32_t> srcOffset,
            ImageSubresourceLayers dstSubresource,
            Point3D<uint32_t> dstOffset,
            Point3D<uint32_t> extent)
            :srcSubresource(srcSubresource),
            srcOffset(srcOffset),
            dstSubresource(dstSubresource),
            dstOffset(dstOffset),
            extent(extent)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(ImageCopy);
    };

    struct ImageBlit
    {
        ImageSubresourceLayers srcSubresource;
        Point3D<int32_t> srcOffsets[2];
        ImageSubresourceLayers dstSubresource;
        Point3D<int32_t> dstOffsets[2];

        ImageBlit() :srcOffsets{ Point3D<int32_t>(), Point3D<int32_t>() }, dstOffsets{ Point3D<int32_t>(),Point3D<int32_t>() } {}

        ImageBlit(
            ImageSubresourceLayers srcSubresource,
            const int32_t(&srcOffsets)[2],
            ImageSubresourceLayers dstSubresource,
            const int32_t(&dstOffsets)[2]
        ) :
            srcSubresource(srcSubresource),
            srcOffsets{ {srcOffsets[0], 0, 0},{srcOffsets[1], 0, 0} },
            dstSubresource(dstSubresource),
            dstOffsets{ {dstOffsets[0], 0, 0},{dstOffsets[1], 0, 0} }
        {}

        ImageBlit(
            ImageSubresourceLayers srcSubresource,
            const Point2D<int32_t>(&srcOffsets)[2],
            ImageSubresourceLayers dstSubresource,
            const Point2D<int32_t>(&dstOffsets)[2]
        ) :
            srcSubresource(srcSubresource),
            srcOffsets{ {srcOffsets[0].x,srcOffsets[0].y,0},{srcOffsets[1].x,srcOffsets[1].y,0} },
            dstSubresource(dstSubresource),
            dstOffsets{ {dstOffsets[0].x,dstOffsets[0].y,0},{dstOffsets[1].x,dstOffsets[1].y,0} }
        {}

        ImageBlit(
            ImageSubresourceLayers srcSubresource,
            const Point3D<int32_t>(&srcOffsets)[2],
            ImageSubresourceLayers dstSubresource,
            const Point3D<int32_t>(&dstOffsets)[2]
        ) :
            srcSubresource(srcSubresource),
            srcOffsets{ srcOffsets[0],srcOffsets[1] },
            dstSubresource(dstSubresource),
            dstOffsets{ dstOffsets[0],dstOffsets[1] }
        {}

        VULKAN_NATIVE_CAST_OPERATOR(ImageBlit);
    };

    struct BufferImageCopy
    {
        uint64_t bufferOffset;
        uint32_t bufferRowLength;
        uint32_t bufferImageHeight;
        ImageSubresourceLayers imageSubresource;
        Point3D<uint32_t> imageOffset;
        Point3D<uint32_t> imageExtend;

        BufferImageCopy() :bufferOffset(0), bufferRowLength(0), bufferImageHeight(0)
        {}

        BufferImageCopy(uint64_t bufferOffset, uint32_t bufferRowLength, uint32_t bufferImageHeight, ImageSubresourceLayers imageSubresource, uint32_t imageExtend, uint32_t imageOffset = 0U)
            :bufferOffset(bufferOffset), bufferRowLength(bufferRowLength), bufferImageHeight(bufferImageHeight), imageSubresource(imageSubresource), imageOffset{ imageOffset,0U, 0U }, imageExtend{ imageExtend,1U, 1U }
        {}

        BufferImageCopy(uint64_t bufferOffset, ImageSubresourceLayers imageSubresource, uint32_t imageExtend, uint32_t imageOffset = 0U)
            :bufferOffset(bufferOffset), bufferRowLength(0), bufferImageHeight(0), imageSubresource(imageSubresource), imageOffset{ imageOffset,0U, 0U }, imageExtend{ imageExtend,1U, 1U }
        {}

        BufferImageCopy(uint64_t bufferOffset, uint32_t bufferRowLength, uint32_t bufferImageHeight, ImageSubresourceLayers imageSubresource, Point2D<uint32_t> imageExtend, Point2D<uint32_t> imageOffset = Point2D<uint32_t>())
            :bufferOffset(bufferOffset), bufferRowLength(bufferRowLength), bufferImageHeight(bufferImageHeight), imageSubresource(imageSubresource), imageOffset{ imageOffset.x,imageOffset.y, 0U }, imageExtend{ imageExtend.x, imageExtend.y, 1U }
        {}

        BufferImageCopy(uint64_t bufferOffset, ImageSubresourceLayers imageSubresource, Point2D<uint32_t> imageExtend, Point2D<uint32_t> imageOffset = Point2D<uint32_t>())
            :bufferOffset(bufferOffset), bufferRowLength(0), bufferImageHeight(0), imageSubresource(imageSubresource), imageOffset{ imageOffset.x,imageOffset.y, 0U }, imageExtend{ imageExtend.x, imageExtend.y, 1U }
        {}

        BufferImageCopy(uint64_t bufferOffset, uint32_t bufferRowLength, uint32_t bufferImageHeight, ImageSubresourceLayers imageSubresource, Point3D<uint32_t> imageExtend, Point3D<uint32_t> imageOffset = Point3D<uint32_t>())
            :bufferOffset(bufferOffset), bufferRowLength(bufferRowLength), bufferImageHeight(bufferImageHeight), imageSubresource(imageSubresource), imageOffset(imageOffset), imageExtend(imageExtend)
        {}

        BufferImageCopy(uint64_t bufferOffset, ImageSubresourceLayers imageSubresource, Point3D<uint32_t> imageExtend, Point3D<uint32_t> imageOffset = Point3D<uint32_t>())
            :bufferOffset(bufferOffset), bufferRowLength(0), bufferImageHeight(0), imageSubresource(imageSubresource), imageOffset(imageOffset), imageExtend(imageExtend)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(BufferImageCopy);
    };

    struct DescriptorPoolSize
    {
        DescriptorType descriptorType;
        uint32_t descriptorCount;

        DescriptorPoolSize() :descriptorType(DescriptorType::UniformBuffer), descriptorCount(0) {}

        DescriptorPoolSize(DescriptorType descriptorType, uint32_t descriptorCount) :descriptorType(descriptorType), descriptorCount(descriptorCount) {}


        VULKAN_NATIVE_CAST_OPERATOR(DescriptorPoolSize);
    };

    struct ImageSubresource
    {
        ImageAspect aspectMask;
        uint32_t baseMipLevel;
        uint32_t levelCount;
        uint32_t baseArrayLayer;
        uint32_t layerCount;

        ImageSubresource()
            : aspectMask(ImageAspect::None), baseMipLevel(0), levelCount(0), baseArrayLayer(0), layerCount(0)
        {}

        ImageSubresource(ImageAspect aspectMask, uint32_t baseMipLevel = 0, uint32_t levelCount = 1, uint32_t baseArrayLayer = 0, uint32_t layerCount = 1)
            : aspectMask(aspectMask), baseMipLevel(baseMipLevel), levelCount(levelCount), baseArrayLayer(baseArrayLayer), layerCount(layerCount)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(ImageSubresourceRange);
    };

    struct BufferMemoryBarrier
    {
    private:
        uint32_t sType = 44;
        void* pNext = nullptr;

    public:
        Flags<Access> srcAccessMask;
        Flags<Access> dstAccessMask;
        uint32_t srcQueueFamilyIndex;
        uint32_t dstQueueFamilyIndex;
        BufferHandle buffer;
        uint64_t offset;
        uint64_t size;

        BufferMemoryBarrier()
            :srcQueueFamilyIndex(0), dstQueueFamilyIndex(0), offset(0), size(0)
        {}

        BufferMemoryBarrier(Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, const Queue& srcQueue, const Queue& dstQueue, BufferHandle buffer, uint64_t offset, uint64_t size)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), srcQueueFamilyIndex(srcQueue.GetIndex()), dstQueueFamilyIndex(dstQueue.GetIndex()), buffer(buffer), offset(offset), size(size)
        {}
        BufferMemoryBarrier(Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, const Queue& dstQueue, BufferHandle buffer, uint64_t offset, uint64_t size)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), srcQueueFamilyIndex(~0U), dstQueueFamilyIndex(dstQueue.GetIndex()), buffer(buffer), offset(offset), size(size)
        {}
        BufferMemoryBarrier(Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, BufferHandle buffer, uint64_t offset, uint64_t size)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), srcQueueFamilyIndex(~0U), dstQueueFamilyIndex(~0U), buffer(buffer), offset(offset), size(size)
        {}


        VULKAN_NATIVE_CAST_OPERATOR(BufferMemoryBarrier);
    };

    struct ImageMemoryBarrier
    {
    private:
        uint32_t sType = 45;
        void* pNext = nullptr;

    public:
        Flags<Access> srcAccessMask;
        Flags<Access> dstAccessMask;
        ImageLayout oldLayout;
        ImageLayout newLayout;
        uint32_t srcQueueFamilyIndex;
        uint32_t dstQueueFamilyIndex;
        ImageHandle image;
        ImageSubresource subresourceRange;

        ImageMemoryBarrier()
            :oldLayout(ImageLayout::Undefined), newLayout(ImageLayout::Undefined), srcQueueFamilyIndex(0), dstQueueFamilyIndex(0)
        {}

        ImageMemoryBarrier(ImageHandle image, ImageLayout oldLayout, ImageLayout newLayout, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, const Queue& srcQueue, const Queue& dstQueue, ImageSubresource subresourceRange)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), oldLayout(oldLayout), newLayout(newLayout), srcQueueFamilyIndex(srcQueue.GetIndex()), dstQueueFamilyIndex(dstQueue.GetIndex()), image(image), subresourceRange(subresourceRange)
        {}
        ImageMemoryBarrier(ImageHandle image, ImageLayout oldLayout, ImageLayout newLayout, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, const Queue& dstQueue, ImageSubresource subresourceRange)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), oldLayout(oldLayout), newLayout(newLayout), srcQueueFamilyIndex(~0U), dstQueueFamilyIndex(dstQueue.GetIndex()), image(image), subresourceRange(subresourceRange)
        {}
        ImageMemoryBarrier(ImageHandle image, ImageLayout oldLayout, ImageLayout newLayout, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, ImageSubresource subresourceRange)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), oldLayout(oldLayout), newLayout(newLayout), srcQueueFamilyIndex(~0U), dstQueueFamilyIndex(~0U), image(image), subresourceRange(subresourceRange)
        {}
        ImageMemoryBarrier(ImageHandle image, ImageLayout newLayout, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, const Queue& srcQueue, const Queue& dstQueue, ImageSubresource subresourceRange)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), oldLayout(ImageLayout::Undefined), newLayout(newLayout), srcQueueFamilyIndex(srcQueue.GetIndex()), dstQueueFamilyIndex(dstQueue.GetIndex()), image(image), subresourceRange(subresourceRange)
        {}
        ImageMemoryBarrier(ImageHandle image, ImageLayout newLayout, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, const Queue& dstQueue, ImageSubresource subresourceRange)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), oldLayout(ImageLayout::Undefined), newLayout(newLayout), srcQueueFamilyIndex(~0U), dstQueueFamilyIndex(dstQueue.GetIndex()), image(image), subresourceRange(subresourceRange)
        {}
        ImageMemoryBarrier(ImageHandle image, ImageLayout newLayout, Flags<Access> srcAccessMask, Flags<Access> dstAccessMask, ImageSubresource subresourceRange)
            :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask), oldLayout(ImageLayout::Undefined), newLayout(newLayout), srcQueueFamilyIndex(~0U), dstQueueFamilyIndex(~0U), image(image), subresourceRange(subresourceRange)
        {}



        VULKAN_NATIVE_CAST_OPERATOR(ImageMemoryBarrier);
    };

    struct MemoryBarrier
    {
    private:
        uint32_t sType = 46;
        void* pNext = nullptr;

    public:
        Flags<Access> srcAccessMask;
        Flags<Access> dstAccessMask;

        MemoryBarrier() {}
        MemoryBarrier(Flags<Access> srcAccessMask, Flags<Access> dstAccessMask) :srcAccessMask(srcAccessMask), dstAccessMask(dstAccessMask) {}


        VULKAN_NATIVE_CAST_OPERATOR(MemoryBarrier);
    };

    struct SubmitInfo
    {
    private:
        uint32_t sType = 4;
        void* pNext = nullptr;

    public:
        uint32_t waitSemaphoreCount;
        SemaphoreHandle* waitSemaphores;
        Flags<PipelineStage>* waitDstStageMask;
        uint32_t cmdBufferCount;
        CmdBufferHandle* cmdBuffers;
        uint32_t signalSemaphoreCount;
        SemaphoreHandle* signalSemaphores;

        SubmitInfo(const std::vector<std::tuple<Flags<PipelineStage>, SemaphoreHandle>>& waitStages = {}, const std::vector<SemaphoreHandle>& signalSemaphores = {}, const std::vector<CmdBufferHandle>& cmdBuffers = {}) :
            waitSemaphoreCount(waitStages.size()), waitSemaphores(new SemaphoreHandle[waitStages.size()]), waitDstStageMask(new Flags<PipelineStage>[waitStages.size()]),
            cmdBufferCount(cmdBuffers.size()), cmdBuffers(new CmdBufferHandle[cmdBuffers.size()]), signalSemaphoreCount(signalSemaphores.size()), signalSemaphores(new SemaphoreHandle[signalSemaphores.size()])
        {
            for (int i = 0; i < waitStages.size(); i++)
            {
                this->waitSemaphores[i] = std::get<1>(waitStages[i]);
                this->waitDstStageMask[i] = std::get<0>(waitStages[i]);
            }
            memcpy((void*) this->cmdBuffers, &cmdBuffers[0], sizeof(CmdBufferHandle) * cmdBufferCount);
            memcpy((void*) this->signalSemaphores, &signalSemaphores[0], sizeof(SemaphoreHandle) * signalSemaphoreCount);
        }

        SubmitInfo(SubmitInfo&& rhs) noexcept
            :SubmitInfo()
        {
            *this = std::move(rhs);
        }

        SubmitInfo& operator=(SubmitInfo&& rhs)
        {
            if (&rhs == this) return *this;
            std::swap(waitSemaphoreCount, rhs.waitSemaphoreCount);
            std::swap(waitSemaphores, rhs.waitSemaphores);
            std::swap(waitDstStageMask, rhs.waitDstStageMask);
            std::swap(cmdBufferCount, rhs.cmdBufferCount);
            std::swap(cmdBuffers, rhs.cmdBuffers);
            std::swap(signalSemaphoreCount, rhs.signalSemaphoreCount);
            std::swap(signalSemaphores, rhs.signalSemaphores);
            return *this;
        }

        SubmitInfo(const SubmitInfo& rhs)
        {
            waitSemaphoreCount = rhs.waitSemaphoreCount;
            cmdBufferCount = rhs.cmdBufferCount;
            signalSemaphoreCount = rhs.signalSemaphoreCount;

            waitSemaphores = new SemaphoreHandle[waitSemaphoreCount];
            waitDstStageMask = new Flags<PipelineStage>[waitSemaphoreCount];
            cmdBuffers = new CmdBufferHandle[waitSemaphoreCount];
            signalSemaphores = new SemaphoreHandle[waitSemaphoreCount];
            memcpy((void*) waitSemaphores, rhs.waitSemaphores, sizeof(SemaphoreHandle) * waitSemaphoreCount);
            memcpy((void*) waitDstStageMask, rhs.waitDstStageMask, sizeof(Flags<PipelineStage>) * waitSemaphoreCount);
            memcpy((void*) cmdBuffers, rhs.cmdBuffers, sizeof(CmdBufferHandle) * cmdBufferCount);
            memcpy((void*) signalSemaphores, rhs.signalSemaphores, sizeof(SemaphoreHandle) * signalSemaphoreCount);
        }
        SubmitInfo& operator=(const SubmitInfo& rhs)
        {
            if (&rhs == this)return *this;

            waitSemaphoreCount = rhs.waitSemaphoreCount;
            cmdBufferCount = rhs.cmdBufferCount;
            signalSemaphoreCount = rhs.signalSemaphoreCount;

            waitSemaphores = new SemaphoreHandle[waitSemaphoreCount];
            waitDstStageMask = new Flags<PipelineStage>[waitSemaphoreCount];
            cmdBuffers = new CmdBufferHandle[waitSemaphoreCount];
            signalSemaphores = new SemaphoreHandle[waitSemaphoreCount];
            memcpy((void*) waitSemaphores, rhs.waitSemaphores, sizeof(SemaphoreHandle) * waitSemaphoreCount);
            memcpy((void*) waitDstStageMask, rhs.waitDstStageMask, sizeof(Flags<PipelineStage>) * waitSemaphoreCount);
            memcpy((void*) cmdBuffers, rhs.cmdBuffers, sizeof(CmdBufferHandle) * cmdBufferCount);
            memcpy((void*) signalSemaphores, rhs.signalSemaphores, sizeof(SemaphoreHandle) * signalSemaphoreCount);

            return *this;
        }

        ~SubmitInfo()
        {
            delete[] waitSemaphores;
            delete[] waitDstStageMask;
            delete[] cmdBuffers;
            delete[] signalSemaphores;
        }


        VULKAN_NATIVE_CAST_OPERATOR(SubmitInfo);
    };

    struct PushConstantRange
    {
        Flags<ShaderStage> stageFlags;
        uint32_t offset;
        uint32_t size;

        PushConstantRange(Flags<ShaderStage> stageFlags = {}, uint32_t offset = 0, uint32_t size = 0) :stageFlags(stageFlags), offset(offset), size(size) {}


        VULKAN_NATIVE_CAST_OPERATOR(PushConstantRange);
    };
}