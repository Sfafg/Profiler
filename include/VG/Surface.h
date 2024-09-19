#pragma once
#include "Handle.h"
#include "Enums.h"
#include "Device.h"
#include "Span.h"

namespace vg
{
    /**
     *@brief Window surface
     *
     */
    class Surface
    {
    public:
        /**
         *@brief Construct a new Surface object
         *
         * @param ((DeviceHandle)currentDevice).Device
         * @param windowSurfaceHandle Surface handle from windowing library
         * @param candidates Surface Format candidates ranked from best to worse
         */
        Surface(SurfaceHandle windowSurfaceHandle, Span<const SurfaceFormat> candidates);

        Surface(SurfaceHandle windowSurfaceHandle, SurfaceFormat candidate) :Surface(windowSurfaceHandle, Span<const SurfaceFormat>{ candidate }) {}

        Surface();
        Surface(Surface&& other) noexcept;
        Surface(const Surface& other) = delete;
        ~Surface();

        Surface& operator=(Surface&& other) noexcept;
        Surface& operator=(const Surface& other) = delete;
        operator const SurfaceHandle& () const;
        operator SurfaceHandle& ();

        /**
         *@brief Get the Format object
         *
         * @return Format
         */
        Format GetFormat() const;
        /**
         *@brief Get the Color Space object
         *
         * @return ColorSpace
         */
        ColorSpace GetColorSpace() const;

    private:
        SurfaceHandle m_handle;
        Format m_format;
        ColorSpace m_colorSpace;
    };
}