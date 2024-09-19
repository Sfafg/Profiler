#pragma once
#include "Handle.h"
#include "Flags.h"
#include "Enums.h"
#include "Structs.h"
#include "Image.h"

namespace vg
{
    class ImageView
    {
    public:
        ImageView(const Image& image, ImageSubresource subresourceRange);
        ImageView(const Image& image, ImageViewType type, Format format, ImageSubresource subresourceRange);

        ImageView();
        ImageView(ImageView&& other) noexcept;
        ImageView(const ImageView& other) = delete;
        ~ImageView();

        ImageView& operator=(ImageView&& other) noexcept;
        ImageView& operator=(const ImageView& other) = delete;
        operator const ImageViewHandle& () const;

    private:
        ImageViewHandle m_handle;
    };
}