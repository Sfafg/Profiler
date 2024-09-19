#pragma once
#include "Handle.h"
#include "Enums.h"
#include "Flags.h"
#include "Queue.h"

namespace vg
{
    class CmdPool
    {
    public:
        CmdPool(const Queue& queue, Flags<CmdPoolUsage> usage);

        CmdPool();
        CmdPool(CmdPool&& other) noexcept;
        CmdPool(const CmdPool& other) = delete;
        ~CmdPool();

        CmdPool& operator=(CmdPool&& other) noexcept;
        CmdPool& operator=(const CmdPool& other) = delete;
        operator const CmdPoolHandle& () const;

        const QueueHandle GetQueue() const;

        void Trim();
        void Reset(bool releaseResources);

    private:
        CmdPoolHandle m_handle;
        QueueHandle m_queue;
    };
}