#pragma once
#include <vector>
#include "Device.h"
#include "Surface.h"
#include "Enums.h"
#include "Synchronization.h"

namespace vg
{
    /**
     *@brief Array of images used for rendering
     * Depending on present mode will switch between rendering and presenting different images to minimize lattency and tearing
     */
    class Swapchain
    {
    public:
        /**
         *@brief Construct a new Swapchain object
         *
         * @param surface Surface
         * @param device Device
         * @param imageCount Count of images used if available
         * @param width Width used if available
         * @param height Heihgt used if available
         * @param usage Usage
         * @param presentMode Present mode used if available
         * @param alpha Alpha usage
         * @param oldSwapchain Optional old swapchain handle used when recreating swapchain when resizing window. Do not destroy old handle until it's presenting is done
         */
        Swapchain(const Surface& surface, const Device& device, unsigned int imageCount, unsigned int width, unsigned int height, Usage usage = Usage::ColorAttachment, PresentMode presentMode = PresentMode::Fifo, CompositeAlpha alpha = CompositeAlpha::Opaque, SwapchainHandle oldSwapchain = SwapchainHandle());

        Swapchain();
        Swapchain(Swapchain&& other) noexcept;
        Swapchain(const Swapchain& other) = delete;
        ~Swapchain();

        Swapchain& operator=(Swapchain&& other) noexcept;
        Swapchain& operator=(const Swapchain& other) = delete;

        operator const SwapchainHandle& () const;

        /**
         *@brief Get the Width object
         *
         * @return unsigned int
         */
        unsigned int GetWidth() const;
        /**
         *@brief Get the Height object
         *
         * @return unsigned int
         */
        unsigned int GetHeight() const;
        /**
         * @brief Get the Image Views object
         *
         * @return const std::vector<ImageViewHandle>&
         */
        const std::vector<ImageViewHandle>& GetImageViews() const;
        /**
         *@brief Get the Next Image Index object
         *
         * @param timeout
         * @param semaphore
         * @param fence
         * @return uint32_t
         */
        uint32_t GetNextImageIndex(uint64_t timeout, const Semaphore& semaphore, const  Fence& fence);

    private:
        SwapchainHandle m_handle;
        DeviceHandle m_device;
        std::vector<ImageHandle> m_images;
        std::vector<ImageViewHandle> m_imageViews;

        unsigned int m_width, m_height;
    };
}