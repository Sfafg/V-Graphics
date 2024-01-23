#pragma once
#include <cstdint>
#include "Enums.h"
namespace vg
{
    struct Limits
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
    };
    struct Viewport
    {
        float x;
        float y;
        float width;
        float height;
        float minDepth;
        float maxDepth;
        Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1) :x(x), y(y), width(width), height(height), minDepth(minDepth), maxDepth(maxDepth) {}

#ifdef VULKAN_HPP
        operator const vk::Viewport& () const { return *reinterpret_cast<const vk::Viewport*>(this); }
        operator const vk::Viewport& () { return *reinterpret_cast<vk::Viewport*>(this); }
#endif
    };
    struct Scissor
    {
        int x;
        int y;
        int width;
        int height;
        Scissor(float width, float height, int x = 0, int y = 0) :x(x), y(y), width(width), height(height) {}

#ifdef VULKAN_HPP
        operator const vk::Rect2D& () const { return *reinterpret_cast<const vk::Rect2D*>(this); }
        operator const vk::Rect2D& () { return *reinterpret_cast<vk::Rect2D*>(this); }
#endif
    };
    struct VertexLayout
    {
    private:
        const uint32_t reserved_1 = 19;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
        uint32_t reserved_4 = 0;
        const void* reserved_5 = nullptr;
        uint32_t reserved_6 = 0;
        const void* reserved_7 = nullptr;
    public:

#ifdef VULKAN_HPP
        operator const vk::PipelineVertexInputStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineVertexInputStateCreateInfo*>(this); }
        operator const vk::PipelineVertexInputStateCreateInfo& () { return *reinterpret_cast<vk::PipelineVertexInputStateCreateInfo*>(this); }
#endif
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
        InputAssembly(Primitive primitive = Primitive::Triangles, bool primitiveRestart = false) :primitive(primitive), primitiveRestart(primitiveRestart) {}

#ifdef VULKAN_HPP
        operator const vk::PipelineInputAssemblyStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineInputAssemblyStateCreateInfo*>(this); }
        operator const vk::PipelineInputAssemblyStateCreateInfo& () { return *reinterpret_cast<vk::PipelineInputAssemblyStateCreateInfo*>(this); }
#endif
    };
    struct Tesselation
    {
    private:
        const uint32_t reserved_1 = 21;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
        int reserved_4 = 0;

    public:
#ifdef VULKAN_HPP
        operator const vk::PipelineTessellationStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineTessellationStateCreateInfo*>(this); }
        operator const vk::PipelineTessellationStateCreateInfo& () { return *reinterpret_cast<vk::PipelineTessellationStateCreateInfo*>(this); }
#endif
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
        ViewportState(Viewport viewport, Scissor scissor) :viewportCount(1), viewports(new Viewport(viewport)), scissorCount(1), scissors(new Scissor(scissor)) {}
        ~ViewportState()
        {
            // if (viewportCount != 0) delete viewports;
            // if (scissorCount != 0) delete scissors;
        }
#ifdef VULKAN_HPP
        operator const vk::PipelineViewportStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineViewportStateCreateInfo*>(this); }
        operator const vk::PipelineViewportStateCreateInfo& () { return *reinterpret_cast<vk::PipelineViewportStateCreateInfo*>(this); }
#endif
    };
    struct DepthBias
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
        float lineWidth = 0;
        Rasterizer(bool enable, bool depthClamp, PolygonMode polygonMode, CullMode cullMode, FrontFace frontFace, DepthBias depthBias, float lineWidth)
            :discard(enable), depthClamp(depthClamp), polygonMode(polygonMode), cullMode(cullMode), frontFace(frontFace), depthBias(depthBias), lineWidth(lineWidth)
        {}

#ifdef VULKAN_HPP
        operator const vk::PipelineRasterizationStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineRasterizationStateCreateInfo*>(this); }
        operator const vk::PipelineRasterizationStateCreateInfo& () { return *reinterpret_cast<vk::PipelineRasterizationStateCreateInfo*>(this); }
#endif
    };
    struct Multisampling
    {
    private:
        const uint32_t reserved_1 = 24;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
        uint32_t rasterizationSamples = 1;
        uint32_t sampleShadingEnable = 0;
        float minSampleShading = 0;
        const void* pSampleMask = nullptr;
        uint32_t alphaToCoverageEnable = 0;
        uint32_t alphaToOneEnable = 0;

    public:
#ifdef VULKAN_HPP
        operator const vk::PipelineMultisampleStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineMultisampleStateCreateInfo*>(this); }
        operator const vk::PipelineMultisampleStateCreateInfo& () { return *reinterpret_cast<vk::PipelineMultisampleStateCreateInfo*>(this); }
#endif
    };
    struct DepthStencil
    {
    private:
        const uint32_t reserved_1 = 25;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
        uint32_t  depthTestEnable = 0;
        uint32_t  depthWriteEnable = 0;
        uint32_t depthCompareOp = 0;
        uint32_t  depthBoundsTestEnable = 0;
        uint32_t  stencilTestEnable = 0;
        uint32_t front = 0;
        uint32_t back = 0;
        float  minDepthBounds = 0;
        float  maxDepthBounds = 0;

    public:
#ifdef VULKAN_HPP
        operator const vk::PipelineDepthStencilStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineDepthStencilStateCreateInfo*>(this); }
        operator const vk::PipelineDepthStencilStateCreateInfo& () { return *reinterpret_cast<vk::PipelineDepthStencilStateCreateInfo*>(this); }
#endif
    };
    struct ColorBlending
    {
    private:
        const uint32_t reserved_1 = 26;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;

    public:
        uint32_t enableLogicOp = 0;
        LogicOp logicOp = LogicOp::Clear;
        uint32_t attachmentCount = 0;
        void* pAttachments = nullptr;
        float blendConsts[4];

        ColorBlending(bool enableLogicOp, LogicOp logicOp, const float(&blendConstants)[4])
            :enableLogicOp(enableLogicOp), logicOp(logicOp), blendConsts{ blendConstants[0],blendConstants[1],blendConstants[2],blendConstants[3] }
        {}

#ifdef VULKAN_HPP
        operator const vk::PipelineColorBlendStateCreateInfo& () const { return *reinterpret_cast<const vk::PipelineColorBlendStateCreateInfo*>(this); }
        operator const vk::PipelineColorBlendStateCreateInfo& () { return *reinterpret_cast<vk::PipelineColorBlendStateCreateInfo*>(this); }
#endif
    };
    struct PipelineLayout
    {
    private:
        const uint32_t reserved_1 = 30;
        const void* reserved_2 = nullptr;
        const uint32_t reserved_3 = 0;
        uint32_t setLayoutCount = 0;
        void* pSetLayouts = nullptr;
        uint32_t pushConstantRangeCount = 0;
        void* pPushConstantRanges = nullptr;

    public:
#ifdef VULKAN_HPP
        operator const vk::PipelineLayoutCreateInfo& () const { return *reinterpret_cast<const vk::PipelineLayoutCreateInfo*>(this); }
        operator const vk::PipelineLayoutCreateInfo& () { return *reinterpret_cast<vk::PipelineLayoutCreateInfo*>(this); }
#endif
    };
}