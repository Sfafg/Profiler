#pragma once
#include "Handle.h"
#include "Enums.h"

namespace vg
{
    class Sampler
    {
    public:
        Sampler(
            Filter magFilter,
            Filter minFilter = Filter::Nearest,
            SamplerMipmapMode mipmapMode = SamplerMipmapMode::Nearest,
            SamplerAddressMode uAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode vAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode wAddressMode = SamplerAddressMode::Repeat,
            float mipLodBias = 0,
            float minLod = 0,
            float maxLod = 1000,
            BorderColor borderColor = BorderColor::FloatTransparentBlack,
            bool unnormalizedCoordinates = false);

        Sampler(
            float maxAnisotropy,
            Filter magFilter,
            Filter minFilter = Filter::Nearest,
            SamplerMipmapMode mipmapMode = SamplerMipmapMode::Nearest,
            SamplerAddressMode uAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode vAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode wAddressMode = SamplerAddressMode::Repeat,
            float mipLodBias = 0,
            float minLod = 0,
            float maxLod = 1000,
            BorderColor borderColor = BorderColor::FloatTransparentBlack,
            bool unnormalizedCoordinates = false);

        Sampler(
            vg::CompareOp compareOp,
            Filter magFilter,
            Filter minFilter = Filter::Nearest,
            SamplerMipmapMode mipmapMode = SamplerMipmapMode::Nearest,
            SamplerAddressMode uAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode vAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode wAddressMode = SamplerAddressMode::Repeat,
            float mipLodBias = 0,
            float minLod = 0,
            float maxLod = 1000,
            BorderColor borderColor = BorderColor::FloatTransparentBlack,
            bool unnormalizedCoordinates = false);

        Sampler(
            float maxAnisotropy,
            vg::CompareOp compareOp,
            Filter magFilter,
            Filter minFilter = Filter::Nearest,
            SamplerMipmapMode mipmapMode = SamplerMipmapMode::Nearest,
            SamplerAddressMode uAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode vAddressMode = SamplerAddressMode::Repeat,
            SamplerAddressMode wAddressMode = SamplerAddressMode::Repeat,
            float mipLodBias = 0,
            float minLod = 0,
            float maxLod = 1000,
            BorderColor borderColor = BorderColor::FloatTransparentBlack,
            bool unnormalizedCoordinates = false);

        Sampler();
        Sampler(Sampler&& other) noexcept;
        Sampler(const Sampler& other) = delete;
        ~Sampler();

        Sampler& operator=(Sampler&& other) noexcept;
        Sampler& operator=(const Sampler& other) = delete;
        operator const SamplerHandle& () const;

    private:
        SamplerHandle m_handle;
    };
}