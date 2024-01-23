#include <vulkan/vulkan.hpp>
#include "RenderPass.h"
#include "Attachment.h"
namespace vg
{
    RenderPass::RenderPass(const Device& device, const std::vector<Attachment>& attachments, const std::initializer_list<Subpass>&& subpasses, const std::vector<SubpassDependency>& dependencies) :
        m_device(device), m_attachments(attachments), m_dependencies(dependencies)
    {
        std::vector<vk::AttachmentDescription> colorAttachments(attachments.size());
        for (unsigned int i = 0; i < attachments.size(); i++)
        {
            colorAttachments[i] = vk::AttachmentDescription({},
                (vk::Format) attachments[i].format,
                (vk::SampleCountFlagBits) attachments[i].samples,
                (vk::AttachmentLoadOp) attachments[i].loadOp,
                (vk::AttachmentStoreOp) attachments[i].storeOp,
                (vk::AttachmentLoadOp) attachments[i].stencilLoadOp,
                (vk::AttachmentStoreOp) attachments[i].stencilStoreOp,
                (vk::ImageLayout) attachments[i].initialLayout,
                (vk::ImageLayout) attachments[i].finalLayout
            );
        }

        std::vector <vk::SubpassDescription> subpassDescriptions(subpasses.size());
        for (unsigned int i = 0; i < subpasses.size(); i++)
        {
            const Subpass& pass = subpasses.begin()[i];
            subpassDescriptions[i] = vk::SubpassDescription({},
                vk::PipelineBindPoint::eGraphics,
                *(std::vector<vk::AttachmentReference>*) & pass.inputAttachments,
                *(std::vector<vk::AttachmentReference>*) & pass.colorAttachments,
                *(std::vector<vk::AttachmentReference>*) & pass.resolveAttachments,
                nullptr,
                *(std::vector<uint32_t>*) & pass.preserveAttachments
            );
        }

        VkSubpassDependency subpassDependency{};
        subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        subpassDependency.dstSubpass = 0;
        subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency.srcAccessMask = 0;
        subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        vk::SubpassDependency dependency(subpassDependency);

        vk::RenderPassCreateInfo renderPassInfo({}, colorAttachments, subpassDescriptions, dependency);
        m_handle = m_device.createRenderPass(renderPassInfo);


        std::vector<vk::GraphicsPipelineCreateInfo> graphicPipelineCreateInfos(subpasses.size());
        std::vector<std::vector<vk::PipelineShaderStageCreateInfo>> stages(subpasses.size());
        std::vector<std::vector<vk::PipelineColorBlendAttachmentState>> colorBlendAttachmentStates(subpasses.size());
        m_pipelineLayouts = std::vector<PipelineLayoutHandle>(subpasses.size());
        for (unsigned int i = 0; i < subpasses.size(); i++)
        {
            const GraphicsPipeline pipeline = subpasses.begin()[i].graphicsPipeline;
            stages[i].resize(pipeline.shaders.size());
            for (int j = 0; j < pipeline.shaders.size(); j++)  stages[i][j] = *pipeline.shaders[j];

            colorBlendAttachmentStates[i].resize(attachments.size());
            for (int j = 0; j < attachments.size(); j++)  colorBlendAttachmentStates[i][j] = (vk::PipelineColorBlendAttachmentState) attachments[j].colorBlending;

            vk::PipelineVertexInputStateCreateInfo* vertexInput = new vk::PipelineVertexInputStateCreateInfo(pipeline.vertexInput);
            vk::PipelineInputAssemblyStateCreateInfo* inputAssembly = new vk::PipelineInputAssemblyStateCreateInfo(pipeline.inputAssembly);
            vk::PipelineTessellationStateCreateInfo* tesselation = new vk::PipelineTessellationStateCreateInfo(pipeline.tesselation);
            vk::PipelineViewportStateCreateInfo* viewportState = new vk::PipelineViewportStateCreateInfo(pipeline.viewportState);
            vk::PipelineRasterizationStateCreateInfo* rasterizer = new vk::PipelineRasterizationStateCreateInfo(pipeline.rasterizer);
            vk::PipelineMultisampleStateCreateInfo* multisampling = new vk::PipelineMultisampleStateCreateInfo(pipeline.multisampling);
            vk::PipelineDepthStencilStateCreateInfo* depthStencil = new vk::PipelineDepthStencilStateCreateInfo(pipeline.depthStencil);
            vk::PipelineColorBlendStateCreateInfo* colorBlending = new vk::PipelineColorBlendStateCreateInfo(pipeline.colorBlending);
            colorBlending->attachmentCount = colorBlendAttachmentStates[i].size();
            colorBlending->pAttachments = colorBlendAttachmentStates[i].data();
            auto states = { vk::DynamicState::eViewport, vk::DynamicState::eScissor };
            vk::PipelineDynamicStateCreateInfo* dynamicState = new vk::PipelineDynamicStateCreateInfo({}, states);

            m_pipelineLayouts[i] = m_device.createPipelineLayout(pipeline.layout);

            graphicPipelineCreateInfos[i] = vk::GraphicsPipelineCreateInfo(
                vk::PipelineCreateFlags(0), stages[i], vertexInput,
                inputAssembly, tesselation, viewportState, rasterizer,
                multisampling, depthStencil, colorBlending, dynamicState,
                m_pipelineLayouts[i], (vk::RenderPass) m_handle, i
            );
        }

        m_graphicsPipelines.resize(graphicPipelineCreateInfos.size());
        VkPipeline* ptr = (VkPipeline*) m_graphicsPipelines.data();
        vkCreateGraphicsPipelines(m_device, nullptr, graphicPipelineCreateInfos.size(), (VkGraphicsPipelineCreateInfo*) graphicPipelineCreateInfos.data(), nullptr, ptr);
        // std::vector<vk::Pipeline> graphicPipelines = m_device.createGraphicsPipelines(nullptr, graphicPipelineCreateInfos).value;
        // m_graphicsPipelines.assign(graphicPipelines.begin(), graphicPipelines.end());
    }

    RenderPass::RenderPass() :m_handle(nullptr), m_device(nullptr) {}

    RenderPass::RenderPass(RenderPass&& other) noexcept
    {
        std::swap(m_handle, other.m_handle);
        std::swap(m_dependencies, other.m_dependencies);
        other.m_handle = nullptr;
        other.m_device = nullptr;
    }

    RenderPass::~RenderPass()
    {
        if (m_handle == nullptr) return;

        for (const auto& pipeline : m_graphicsPipelines) m_device.destroyPipeline(pipeline);
        for (const auto& layout : m_pipelineLayouts) m_device.destroyPipelineLayout(layout);

        m_device.destroyRenderPass(m_handle);
    }

    RenderPass& RenderPass::operator=(RenderPass&& other) noexcept
    {
        if (&other == this) return *this;
        std::swap(m_handle, other.m_handle);
        std::swap(m_dependencies, other.m_dependencies);
        other.m_handle = nullptr;

        return *this;
    }

    RenderPass::operator const RenderPassHandle& () const
    {
        return m_handle;
    }
}