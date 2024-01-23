#include <vulkan/vulkan.hpp>
#include "Fence.h"

namespace vg
{
    Fence::Fence(const Device& device, bool createSignalled) : m_device(device)
    {
        m_handle = m_device.createFence({ createSignalled ? vk::FenceCreateFlagBits::eSignaled : (vk::FenceCreateFlagBits) 0U });
    }

    Fence::Fence() : m_handle(nullptr), m_device(nullptr) {}

    Fence::Fence(Fence&& other) noexcept
    {
        std::swap(m_handle, other.m_handle);
        std::swap(m_device, other.m_device);
    }

    Fence::~Fence()
    {
        if (m_handle == nullptr) return;
        m_device.destroyFence(m_handle);
    }

    Fence& Fence::operator=(Fence&& other) noexcept
    {
        if (this == &other) return *this;
        std::swap(m_handle, other.m_handle);
        std::swap(m_device, other.m_device);

        return *this;
    }

    Fence::operator const FenceHandle& () const
    {
        return m_handle;
    }

    void WaitForFences(const Device& device, const std::vector<FenceHandle>& fences, bool awaitAll, uint64_t timeout)
    {
        auto result = device.m_handle.waitForFences(*(std::vector<vk::Fence>*) & fences, awaitAll, timeout);
    }

    void ResetFences(const Device& device, const std::vector<FenceHandle>& fences)
    {
        device.m_handle.resetFences(*(std::vector<vk::Fence>*) & fences);
    }
}