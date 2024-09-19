#pragma once
#include "Handle.h"
#include "Flags.h"
#include "Enums.h"
#include "Span.h"

namespace vg
{
    class CmdBuffer;
    class Image
    {
    public:
        Image(
            Span<const uint32_t> extend,
            Format format,
            Flags<ImageUsage> usage,
            uint32_t mipLevels = 1,
            int arrayLevels = 1,
            ImageTiling tiling = ImageTiling::Optimal,
            ImageLayout initialLayout = ImageLayout::Undefined,
            int samples = 1,
            SharingMode sharingMode = SharingMode::Exclusive);

        Image(
            Span<const uint32_t> extend,
            Format format,
            Flags<ImageUsage> usage,
            uint32_t mipLevels,
            int arrayLevels,
            int samples,
            ImageTiling tiling = ImageTiling::Optimal,
            ImageLayout initialLayout = ImageLayout::Undefined,
            SharingMode sharingMode = SharingMode::Exclusive)
            :Image(extend, format, usage, mipLevels, arrayLevels, tiling, initialLayout, samples, sharingMode)
        {}

        Image(
            Span<const uint32_t> extend,
            Span<const Format> formatCandidates,
            Flags<FormatFeature> features,
            Flags<ImageUsage> usage,
            uint32_t mipLevels = 1,
            int arrayLevels = 1,
            ImageTiling tiling = ImageTiling::Optimal,
            ImageLayout initialLayout = ImageLayout::Undefined,
            int samples = 1,
            SharingMode sharingMode = SharingMode::Exclusive);

        Image(
            Span<const uint32_t> extend,
            Span<const Format> formatCandidates,
            Flags<FormatFeature> features,
            Flags<ImageUsage> usage,
            uint32_t mipLevels,
            int arrayLevels,
            int samples,
            ImageTiling tiling = ImageTiling::Optimal,
            ImageLayout initialLayout = ImageLayout::Undefined,
            SharingMode sharingMode = SharingMode::Exclusive)
            :Image(extend, formatCandidates, features, usage, mipLevels, arrayLevels, tiling, initialLayout, samples, sharingMode)
        {}

        Image();
        Image(Image&& other) noexcept;
        Image(const Image& other) = delete;
        ~Image();

        Image& operator=(Image&& other) noexcept;
        Image& operator=(const Image& other) = delete;
        operator const ImageHandle& () const;

        /// @brief Append commands to an CmdBuffer to generate mimpmaps, all images have to be in Layout::TransferDstOptimal, and will end up in Layout::TransferSrcOptmial 
        /// @param cmdBuffer Buffer
        /// @param mipMapCount MipMapCount 
        void AppendMipmapGenerationCommands(CmdBuffer* cmdBuffer, int mipMapCount) const;

        Format GetFormat() const;
        unsigned int GetDimensionCount() const;
        void GetDimensions(uint32_t* width, uint32_t* height, uint32_t* depth) const;
        Span<const uint32_t> GetDimensions() const;
        uint64_t GetSize() const;
        uint64_t GetOffset() const;
        uint32_t GetMipLevels() const;
        class MemoryBlock* GetMemory() const;

        /// @brief Find the supported format from candidates.
        /// @param candidates array of Formats sorted by best to worst
        /// @param tiling ImageTiling needed for the image
        /// @param features Needed features
        /// @return one of the formats that are supported or Format::Undefined
        static Format FindSupportedFormat(Span<const Format> candidates, ImageTiling tiling, Flags<FormatFeature> features);

    private:
        ImageHandle m_handle;
        Format m_format;
        ImageTiling m_tiling;
        uint32_t m_mipLevels;
        unsigned int m_dimensionCount;
        uint32_t m_dimensions[3];
        uint64_t m_offset;
        uint64_t m_size;

        class MemoryBlock* m_memory;

        friend class MemoryBlock;
        friend void Allocate(Span<Image>, Flags<MemoryProperty>);
        friend void Allocate(Span<Image* const>, Flags<MemoryProperty>);
    };
}