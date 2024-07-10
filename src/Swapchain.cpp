#include <vulkan/vulkan.hpp>
#include "Swapchain.h"
namespace vg
{
    struct SwapChainSupportDetails
    {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::set<vk::PresentModeKHR> presentModes;

        SwapChainSupportDetails(vk::PhysicalDevice device, vk::SurfaceKHR surface)
        {
            capabilities = device.getSurfaceCapabilitiesKHR(surface);
            for (const auto& presentMode : device.getSurfacePresentModesKHR(surface)) presentModes.insert(presentMode);
        }
    };

    Swapchain::Swapchain(const Surface& surface, unsigned int imageCount, unsigned int width, unsigned int height, Flags<Usage> usage, PresentMode presentMode, CompositeAlpha alpha, SwapchainHandle oldSwapchain)
    {
        // Get the sharing mode, needed if queues are in different families.
        vk::SharingMode sharingMode = vk::SharingMode::eExclusive;
        std::vector<unsigned int> indices;
        if (currentDevice.graphicsQueue.GetIndex() != currentDevice.presentQueue.GetIndex())
        {
            indices.assign({ currentDevice.graphicsQueue.GetIndex(), currentDevice.presentQueue.GetIndex() });
            sharingMode = vk::SharingMode::eConcurrent;
        }

        // Check if parameters for Swapchain creation are valid and change them if not.
        SwapChainSupportDetails supportDetails((PhysicalDeviceHandle) currentDevice, surface);
        imageCount = std::clamp(imageCount, supportDetails.capabilities.minImageCount, supportDetails.capabilities.maxImageCount);

        if (supportDetails.capabilities.currentExtent.width != UINT_MAX)
        {
            m_width = supportDetails.capabilities.currentExtent.width;
            m_height = supportDetails.capabilities.currentExtent.height;
        }
        else
        {
            vk::Extent2D min = supportDetails.capabilities.minImageExtent;
            vk::Extent2D max = supportDetails.capabilities.maxImageExtent;
            m_width = std::clamp(width, min.width, max.width);
            m_height = std::clamp(height, min.height, max.height);
        }

        if (!supportDetails.presentModes.contains((vk::PresentModeKHR) presentMode))
        {
            presentMode = PresentMode::Fifo;
        }

        // Create Swapchain and get its Images and ImageViews.
        vk::SwapchainCreateInfoKHR createInfo(
            {}, surface, imageCount, (vk::Format) surface.GetFormat(), (vk::ColorSpaceKHR) surface.GetColorSpace(), { m_width, m_height }, 1, (vk::ImageUsageFlagBits) (Flags<Usage>::TMask) usage,
            sharingMode, indices, supportDetails.capabilities.currentTransform, (vk::CompositeAlphaFlagBitsKHR) alpha, (vk::PresentModeKHR) presentMode, 1,
            oldSwapchain
        );

        m_handle = ((DeviceHandle) currentDevice).createSwapchainKHR(createInfo);
        for (const auto& image : ((DeviceHandle) currentDevice).getSwapchainImagesKHR(m_handle))
            m_images.push_back(image);

        m_imageViews.resize(m_images.size());
        for (unsigned int i = 0; i < m_images.size(); i++)
        {
            vk::ComponentMapping componentMapping;
            vk::ImageSubresourceRange subresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);
            vk::ImageViewCreateInfo createInfo({}, m_images[i], vk::ImageViewType::e2D, (vk::Format) surface.GetFormat(), componentMapping, subresourceRange);

            m_imageViews[i] = ((DeviceHandle) currentDevice).createImageView(createInfo);
        }
    }

    Swapchain::Swapchain() : m_handle(nullptr) {}

    Swapchain::Swapchain(Swapchain&& other) noexcept
    {
        std::swap(m_handle, other.m_handle);

        std::swap(m_images, other.m_images);
        std::swap(m_imageViews, other.m_imageViews);
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
    }

    Swapchain::~Swapchain()
    {
        if (m_handle == nullptr) return;
        for (auto& imageView : m_imageViews)
        {
            ((DeviceHandle) currentDevice).destroyImageView(imageView);
        }
        ((DeviceHandle) currentDevice).destroySwapchainKHR(m_handle);
        m_handle = nullptr;
    }

    Swapchain& Swapchain::operator=(Swapchain&& other) noexcept
    {
        if (&other == this) return *this;
        std::swap(m_handle, other.m_handle);

        std::swap(m_images, other.m_images);
        std::swap(m_imageViews, other.m_imageViews);
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);

        return *this;
    }

    Swapchain::operator const SwapchainHandle& () const
    {
        return m_handle;
    }

    unsigned int Swapchain::GetWidth() const
    {
        return m_width;
    }

    unsigned int Swapchain::GetHeight() const
    {
        return m_height;
    }

    const std::vector<ImageViewHandle>& Swapchain::GetImageViews() const
    {
        return m_imageViews;
    }

    uint32_t Swapchain::GetNextImageIndex(const Semaphore& semaphore, const  Fence& fence, uint64_t timeout)
    {
        uint32_t index;
        auto result = ((DeviceHandle) currentDevice).acquireNextImageKHR(vk::SwapchainKHR((SwapchainHandle) m_handle), timeout, (SemaphoreHandle) semaphore, (FenceHandle) fence, &index);

        return index;
    }

    std::vector<Framebuffer> Swapchain::CreateFramebuffers(RenderPassHandle renderPass, const std::vector<ImageViewHandle>& additionalImageAttachments, int layers) const
    {
        std::vector<Framebuffer> frameBuffers(GetImageViews().size());
        for (size_t i = 0; i < GetImageViews().size(); i++)
        {
            std::vector<ImageViewHandle> imageViews = additionalImageAttachments;
            imageViews.insert(imageViews.begin(), GetImageViews()[i]);
            frameBuffers[i] = Framebuffer(renderPass, imageViews, GetWidth(), GetHeight(), 1);

        }

        return frameBuffers;
    }

}