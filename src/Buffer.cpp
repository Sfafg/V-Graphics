#include <vulkan/vulkan.hpp>
#include "Buffer.h"
#include "MemoryManager.h"

namespace vg
{
    Buffer::Buffer() : m_handle(nullptr), m_offset(0), m_size(0), m_memory(0) {}
    Buffer::Buffer(uint64_t byteSize, Flags<BufferUsage> usage, SharingMode sharing) : m_memory(nullptr), m_size(byteSize), m_offset(0)
    {
        m_handle = ((DeviceHandle) *currentDevice).createBuffer({ {}, byteSize, (vk::BufferUsageFlagBits) (int) usage, (vk::SharingMode) sharing });
    }
    Buffer::Buffer(Buffer&& other) noexcept
    {
        std::swap(m_handle, other.m_handle);

        std::swap(m_size, other.m_size);
        std::swap(m_offset, other.m_offset);
        std::swap(m_memory, other.m_memory);
    }
    Buffer::~Buffer()
    {
        if (!m_handle) return;
        ((DeviceHandle) *currentDevice).destroyBuffer(m_handle);
        if (m_memory) m_memory->Dereferance();
    }

    Buffer& Buffer::operator=(Buffer&& other) noexcept
    {
        if (this == &other) return *this;
        std::swap(m_handle, other.m_handle);

        std::swap(m_size, other.m_size);
        std::swap(m_offset, other.m_offset);
        std::swap(m_memory, other.m_memory);
        return *this;
    }
    Buffer::operator const BufferHandle& () const
    {
        return m_handle;
    }

    uint64_t Buffer::GetSize() const
    {
        return m_size;
    }

    uint64_t Buffer::GetOffset() const
    {
        return m_offset;
    }
    MemoryBlock* Buffer::GetMemory() const
    {
        return m_memory;
    }

    char* Buffer::MapMemory()
    {
        return GetMemory()->GetMappedMemory() + m_offset;
    }

    void Buffer::UnmapMemory()
    {
        GetMemory()->UnmapMemory();
    }
}