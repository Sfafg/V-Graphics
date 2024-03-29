#pragma once
#include "Handle.h"
#include "Attachment.h"
#include "Subpass.h"
#include "Device.h"
#include <vector>

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
         * @param device Device
         * @param attachments Array of Attachments e.g. color, depth
         * @param subpasses Array of Subpasses used for multi pass rendering e.g. Differed Rendering
         * @param dependencies Dependencies
         */
        RenderPass(const Device& device, const std::vector<Attachment>& attachments, const std::initializer_list<Subpass>&& subpasses, const std::vector<SubpassDependency>& dependencies);

        RenderPass();
        RenderPass(RenderPass&& other) noexcept;
        RenderPass(const RenderPass& other) = delete;
        ~RenderPass();

        RenderPass& operator=(RenderPass&& other) noexcept;
        RenderPass& operator=(const RenderPass& other) = delete;
        operator const RenderPassHandle& () const;

    public:
        RenderPassHandle m_handle;
        DeviceHandle m_device;
        std::vector<GraphicsPipelineHandle> m_graphicsPipelines;
        std::vector<PipelineLayoutHandle> m_pipelineLayouts;
        std::vector<Attachment> m_attachments;
        std::vector<SubpassDependency> m_dependencies;
    };
}