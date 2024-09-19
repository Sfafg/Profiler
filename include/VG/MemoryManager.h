#pragma once
#include "Buffer.h"
#include "Image.h"
#include "Enums.h"
#include "Flags.h"
#include "Device.h"
#include "Span.h"

namespace vg
{
    extern void Allocate(Span<Buffer* const> buffers, Flags<MemoryProperty> memoryProperty);
    extern void Allocate(Span<Buffer> buffers, Flags<MemoryProperty> memoryProperty);

    extern void Allocate(Span<Image* const> images, Flags<MemoryProperty> memoryProperty);
    extern void Allocate(Span<Image> images, Flags<MemoryProperty> memoryProperty);

    class MemoryBlock
    {
    public:
        MemoryBlock(DeviceMemoryHandle memory, uint64_t totalSize) : m_handle(memory), m_referanceCount(0), m_totalSize(totalSize), m_mappedMemory(nullptr) {}

        operator DeviceMemoryHandle() const;

        void Bind(Buffer* buffer);
        void Bind(Image* buffer);

    private:
        void Dereferance();
        char* GetMappedMemory();
        void UnmapMemory();
        int m_referanceCount;
        DeviceMemoryHandle m_handle;
        uint64_t m_totalSize;
        void* m_mappedMemory;

        friend class vg::Buffer;
        friend class vg::Image;
    };
}