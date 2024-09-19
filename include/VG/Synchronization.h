#pragma once
#include "Handle.h"
#include "Device.h"
#include <vector>

namespace vg
{
    /**
     *@brief Used to synchronize CPU and GPU
     *
     */
    class Fence
    {
    public:
        /**
         *@brief Construct a new Fence object
         *
         * @param createSignalled If true then fence will start in signalled state
         */
        Fence(bool createSignalled = false);

        Fence(void* ptr);
        Fence(Fence&& other) noexcept;
        Fence(const Fence& other) = delete;
        ~Fence();

        Fence& operator=(Fence&& other) noexcept;
        Fence& operator=(const Fence& other) = delete;
        operator const FenceHandle& () const;

        /**
         *@brief Check if fence is signalled or not
         *
         * @return true fence is signalled
         * @return false fence is not signalled
         */
        bool IsSignaled() const;
        /**
         *@brief Wait for fence to be signalled
         *
         * @param reset If true fence will be reset
         * @param timeout Timeout in nanoseconds
         */
        void Await(bool reset = false, uint64_t timeout = UINT64_MAX);
        /**
         *@brief Reset fence unsignalling it
         */
        void Reset();
        /**
         *@brief Returns only when all fences are signalled
         *
         * @param fences Array of fences
         * @param reset If true all fences will be reset
         * @param timeout Timeout in nanoseconds
         */
        static void AwaitAll(std::span<Fence> fences, bool reset = false, uint64_t timeout = UINT64_MAX);
        static void AwaitAll(Span<Fence* const> fences, bool reset = false, uint64_t timeout = UINT64_MAX);

        /**
         *@brief Returns when at least one fence is signalled
         *
         * @param fences Array of fences
         * @param timeout Timeout in nanoseconds
         */
        static void AwaitAny(std::span<Fence> fences, uint64_t timeout = UINT64_MAX);
        static void AwaitAny(Span<Fence* const> fences, uint64_t timeout = UINT64_MAX);

        /**
         *@brief Reset all fences unsignalling them
         *
         * @param fences Array of Fences
         */
        static void ResetAll(std::span<Fence> fences);
        static void ResetAll(Span<Fence* const> fences);

    private:
        FenceHandle m_handle;

    };

    /**
     *@brief Used to synchronize GPU with GPU processes
     *
     */
    class Semaphore
    {
    public:
        Semaphore();

        Semaphore(void* ptr);
        Semaphore(Semaphore&& other) noexcept;
        Semaphore(const Semaphore& other) = delete;
        ~Semaphore();

        Semaphore& operator=(Semaphore&& other) noexcept;
        Semaphore& operator=(const Semaphore& other) = delete;
        operator const SemaphoreHandle& () const;

    private:
        SemaphoreHandle m_handle;

    };
}