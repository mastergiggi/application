/*
 * Copyright (c) 2023-2024 Stefan Giggenbach (https://github.com/mastergiggi)
 * SPDX-License-Identifier: Apache-2.0
 */

#include <memory>

#include <zephyr/kernel.h>
#include <osal/os-thread.hpp>

#include "pimpl-impl.hpp"

class OS::Thread::impl
{
private:
    static void threadEntry(void* param)
    {
        __ASSERT(param != nullptr, "Invalid thread object!");
        OS::Thread::impl* me = static_cast<OS::Thread::impl*>(param);
        me->threadFunction();
    }

public:
    impl() = default;

    impl(OS::Thread::Function function, const OS::Thread::Config& config, const bool autostart)
        : threadFunction(function)
    {
#ifdef CONFIG_USERSPACE
        int flags = K_USER;
#else
        int flags = 0;
#endif

        const k_timeout_t delay = autostart ? K_NO_WAIT : K_FOREVER;
        
        threadStack = k_thread_stack_alloc(config.stackSize, flags);
        __ASSERT(threadStack != nullptr, "Thread stack allocation failed!");
        threadId = k_thread_create(&thread, threadStack, config.stackSize,
			                        (k_thread_entry_t) threadEntry,
			                        (void*) this, NULL, NULL, K_PRIO_COOP(config.prio), 0, delay);
    }

    ~impl()
    {
        abort();
        k_thread_stack_free(threadStack);
    }

    void abort()
    {
        k_thread_abort(threadId);
    }

    void join()
    {
        k_thread_join(&thread, K_FOREVER);
        
    }

    void suspend()
    {
        k_thread_suspend(threadId);
    }

    void resume()
    {
        k_thread_resume(threadId);
    }
    
private:
    struct k_thread thread;
    k_thread_stack_t* threadStack;
    k_tid_t threadId;
    OS::Thread::Function threadFunction;
};

OS::Thread::Thread(OS::Thread::Function function, const OS::Thread::Config& config, const bool autostart)
    : handle(function, config, autostart)
{
}

OS::Thread::~Thread()
{
}

void OS::Thread::abort()
{
    handle->abort();
}

void OS::Thread::join()
{
    handle->join();
}

void OS::Thread::suspend()
{
    handle->suspend();
}

void OS::Thread::resume()
{
    handle->resume();
}

void OS::Thread::sleep(const Timeout timeout)
{
    k_sleep(K_SECONDS(timeout));
}

void OS::Thread::msleep(const Timeout timeout)
{
    k_sleep(K_MSEC(timeout));
}

void OS::Thread::usleep(const Timeout timeout)
{
    k_sleep(K_USEC(timeout));
}

void OS::Thread::yield()
{
    k_yield();
}
