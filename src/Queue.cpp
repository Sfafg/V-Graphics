#include <vulkan/vulkan.hpp>
#include "Queue.h"
#include "Structs.h"
#include "Synchronization.h"

namespace vg
{
    Queue::Queue(Flags<QueueType> type, float priority) :m_handle(nullptr), m_type(type), m_priority(priority), m_index(0) {}

    Queue::Queue() :m_handle(nullptr), m_type(0), m_priority(0), m_index(0) {}

    Queue::Queue(Queue&& other) noexcept
    {
        std::swap(m_handle, other.m_handle);
        std::swap(m_commandPool, other.m_commandPool);
        std::swap(m_transientCommandPool, other.m_transientCommandPool);
        std::swap(m_type, other.m_type);
        std::swap(m_priority, other.m_priority);
        std::swap(m_index, other.m_index);
    }

    Queue::~Queue()
    {
        if (m_handle == nullptr || !(bool) m_type)
            return;

        ((DeviceHandle) *currentDevice).destroyCommandPool(m_commandPool);
        ((DeviceHandle) *currentDevice).destroyCommandPool(m_transientCommandPool);

        m_handle = nullptr;
    }

    Queue& Queue::operator=(Queue&& other) noexcept
    {
        if (&other == this) return *this;
        std::swap(m_handle, other.m_handle);
        std::swap(m_commandPool, other.m_commandPool);
        std::swap(m_transientCommandPool, other.m_transientCommandPool);
        std::swap(m_type, other.m_type);
        std::swap(m_priority, other.m_priority);
        std::swap(m_index, other.m_index);

        return *this;
    }

    Queue::operator const QueueHandle& () const
    {
        return m_handle;
    }

    Flags<QueueType> Queue::GetType() const
    {
        return m_type;
    }

    unsigned int Queue::GetIndex() const
    {
        return m_index;
    }

    CmdPoolHandle Queue::GetCmdPool(bool transient) const
    {
        if (transient)
            return m_transientCommandPool;
        return m_commandPool;
    }

    Result Queue::Present(const std::vector<SemaphoreHandle>& waitSemaphores, const std::vector<SwapchainHandle>& swapchains, const std::vector<uint32_t>& imageIndices)
    {
        vk::PresentInfoKHR info(*(std::vector<vk::Semaphore>*) & waitSemaphores, *(std::vector<vk::SwapchainKHR>*) & swapchains, imageIndices);
        return (Result) vkQueuePresentKHR(m_handle, (VkPresentInfoKHR*) &info);
    }

    void Queue::Submit(const std::vector<SubmitInfo>& submits, const Fence& fence)
    {
        m_handle.submit(*(std::vector<vk::SubmitInfo>*) & submits, fence);
    }

    Fence Queue::Submit(const std::vector<class SubmitInfo>& submits)
    {
        Fence fence;
        Submit(submits, fence);

        return fence;
    }

}