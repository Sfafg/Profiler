#pragma once
#include "Instance.h"
#include "Queue.h"
#include "Structs.h"
#include "Span.h"
#include <functional>
#include <string>
#include <set>

namespace vg
{
    /**
     *@brief Represents GPU device
     * Handles both physical and logical device
     */
    class Device
    {
    public:
        /**
         *@brief Construct a new Device object
         *
         * @param queues Queues that are required
         * @param extensions Extensions that are required
         * @param hintedDeviceEnabledFeatures Features to be enabled if available, by default all
         * @param surface Surface when device is used to render to a window
         * @param scoreFunction Function for scroing each device, function should return score or -1 if device is not an option
         */
        Device(
            Span<Queue* const> queues,
            const std::set<std::string>& extensions = {},
            const DeviceFeatures& hintedDeviceEnabledFeatures = {},
            SurfaceHandle surface = {},
            std::function<int(PhysicalDeviceHandle id, Span<Queue* const> supportedQueues, const std::set<std::string>& supportedExtensions, DeviceType type, const DeviceLimits& limits, const DeviceFeatures& features)> scoreFunction = nullptr);
        /**
         *@brief Construct a new Device object
         *
         * @param queues Queues that are required
         * @param extensions Extensions that are required
         * @param hintedDeviceEnabledFeatures Features to be enabled if available, by default none
         * @param scoreFunction Function for scroing each device, function should return score or -1 if device is not an option
         */
        Device(
            Span<Queue* const> queues,
            const std::set<std::string>& extensions = {},
            const DeviceFeatures& hintedDeviceEnabledFeatures = {},
            std::function<int(PhysicalDeviceHandle id, Span<Queue* const> supportedQueues, const std::set<std::string>& supportedExtensions, DeviceType type, const DeviceLimits& limits, const DeviceFeatures& features)> scoreFunction = nullptr)
            :Device::Device(queues, extensions, hintedDeviceEnabledFeatures, {}, scoreFunction) {}

        Device();
        Device(Device&& other) noexcept;

        Device(const Device& other) = delete;
        ~Device();

        Device& operator=(Device&& other) noexcept;
        Device& operator=(const Device& other) = delete;

        operator const DeviceHandle& () const;
        operator const PhysicalDeviceHandle& () const;

        /**
         *@brief Waits until device is idle
         *
         */
        void WaitUntilIdle();

        std::set<std::string> GetExtensions() const;
        DeviceLimits GetLimits() const;
        DeviceProperties GetProperties() const;
        DeviceFeatures GetFeatures() const;
        FormatProperties GetFormatProperties(Format format) const;
        const Queue& GetQueue(uint32_t queueIndex) const;


    private:
        DeviceHandle m_handle;
        PhysicalDeviceHandle m_physicalDevice;
        std::vector<Queue*> m_queues;
    };

    extern Device* currentDevice;

    class ScopedDeviceChange
    {
    public:
        ScopedDeviceChange(Device* newDevice)
        {
            oldDevice = currentDevice;
            currentDevice = newDevice;
        }

        ~ScopedDeviceChange()
        {
            currentDevice = oldDevice;
        }

    private:
        Device* oldDevice;
    };
#define CONCAT_IMPL( x, y ) x##y
#define MACRO_CONCAT( x, y ) CONCAT_IMPL( x, y )
#define SCOPED_DEVICE_CHANGE(newDevice) ScopedDeviceChange MACRO_CONCAT(___DEVICE_CHANGE_OBJECT___, __COUNTER__)(newDevice)
}