#pragma once
#include "Handle.h"
#include <stdint.h>
#include <vector>

namespace vg
{
    class PipelineCache
    {
    public:
        PipelineCache(const void* initialData, uint32_t initialDataSize = 0, bool isExternallySynchronized = false);

        template<typename T>
        PipelineCache(const std::vector<T>& initialData, bool isExternallySynchronized = false) :
            PipelineCache(initialData.data(), initialData.size() * sizeof(T), isExternallySynchronized)
        {}

        PipelineCache();
        PipelineCache(PipelineCache&& other) noexcept;
        PipelineCache(const PipelineCache& other) = delete;
        ~PipelineCache();

        PipelineCache& operator=(PipelineCache&& other) noexcept;
        PipelineCache& operator=(const PipelineCache& other) = delete;
        operator const PipelineCacheHandle& () const;

        void* GetData(uint32_t* dataSize) const;

        template <typename T = char>
        std::vector<T> GetData() const
        {
            std::vector<T> vec;
            uint32_t size;

            T* data = (T*) GetData(&size);
            size = size / (float) sizeof(T) > size / sizeof(T) ? size / sizeof(T) + 1 : size / sizeof(T);
            vec.assign(data, data + size);

            delete[] data;
            return vec;

        }
        void MergeCaches(const std::vector<PipelineCacheHandle>& caches);

    private:
        PipelineCacheHandle m_handle;
    };
}