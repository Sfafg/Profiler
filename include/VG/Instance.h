#pragma once
#include <vector>
#include "Span.h"
#include "Handle.h"

namespace vg
{
    enum class MessageSeverity
    {
        Verbose = 1,
        Info = 16,
        Warning = 256,
        Error = 4096
    };

    /**
     *@brief Vulkan Instance and Error handling
     *
     * Handles instance and will automatically turns on validation layers in debug mode.
     * There should be only one Instance created before any API calls.
     * Make sure to assign static variable of vg::instance.
     *
     */
    class Instance
    {
    public:
        typedef void(*DebugCallback)(MessageSeverity, const char* message);

    public:
        /**
         *@brief Construct a new Instance object
         *
         * @param requiredExtensions list of required extensions
         * @param debugCallback optional callback to custom logging function
         */
        Instance(Span<const char* const> requiredExtensions, DebugCallback debugCallback = nullptr, bool enableValidationLayers = true);

        Instance();
        Instance(Instance&& other) noexcept;
        Instance(const Instance& other) = delete;
        ~Instance();

        Instance& operator= (Instance&& other) noexcept;
        Instance& operator=(const Instance& other) = delete;

        operator const InstanceHandle& () const;

    private:
        InstanceHandle m_handle;
        DebugMessengerHandle m_debugMessenger;
        DebugCallback m_debugCallback;
    };
    extern Instance instance;
}