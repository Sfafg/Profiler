#pragma once
#include <cstdint>
#include "Span.h"
#include "Handle.h"
#include "Enums.h"
#include "Flags.h"

namespace vg
{
    class Queue
    {
    public:
        Queue(Flags<QueueType> type, float priority);

        Queue();
        Queue(Queue&& other) noexcept;
        Queue(const Queue& other) = delete;

        Queue& operator=(Queue&& other) noexcept;
        Queue& operator=(const Queue& other) = delete;
        operator const QueueHandle& () const;

        /**
         *@brief Get the type flags of queue
         *
         * @return Flags<QueueType>
         */
        Flags<QueueType> GetType() const;
        /**
         *@brief Get the Index object
         *
         * @return unsigned int
         */
        unsigned int GetIndex() const;
        /**
         *@brief Get the Command Pool object
         *
         * @param transient if true returns handle to the transient command pool, used for short lived CmdBuffers
         * @return CmdPoolHandle
         */
        CmdPoolHandle GetCmdPool(bool transient = false) const;
        /**
         *@brief Present image to the window. Queue Type must be Queue::Present
         *
         * @param waitSemaphores Semaphores to await before presenting
         * @param swapchains array of Swapchains used for rendering
         * @param imageIndices indices of images from Swapchains
         * @return Result
         */
        Result Present(Span<const SemaphoreHandle> waitSemaphores, Span<const SwapchainHandle> swapchains, Span<const uint32_t> imageIndices);

        void Submit(Span<const class SubmitInfo> submits, const class Fence& fence);

        Fence Submit(Span<const class SubmitInfo> submits);

    private:
        QueueHandle m_handle;
        CmdPoolHandle m_commandPool;
        CmdPoolHandle m_transientCommandPool;
        Flags<QueueType> m_type;
        float m_priority;
        unsigned int m_index;

        friend class Device;
    };
}