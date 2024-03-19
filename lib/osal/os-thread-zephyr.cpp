/*
 * Copyright (c) 2023-2024 Stefan Giggenbach (https://github.com/mastergiggi)
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cassert>
#include <memory>

#include <osal/os-thread.hpp>

#include <zephyr/kernel.h>

#include "pimpl-impl.hpp"

class OS::Thread::impl
{
private:
    static void threadCallback(void* param)
    {
        assert(param != nullptr);
        OS::Thread::impl* me = static_cast<OS::Thread::impl*>(param);
        me->_function();
    }

public:
    impl() = default;

    impl(OS::Thread::Function function, const OS::Thread::Config& config, const bool autostart)
        : _function(function)
    {
#ifdef CONFIG_USERSPACE
        int flags = K_USER;
#else
        int flags = 0;
#endif

        const k_timeout_t delay = autostart ? K_NO_WAIT : K_FOREVER;
        
        _threadStack = k_thread_stack_alloc(config.stackSize, flags);
        assert(_threadStack != nullptr);
        _threadId = k_thread_create(&_thread, _threadStack, config.stackSize,
			                        (k_thread_entry_t) threadCallback,
			                        (void*) this, NULL, NULL, K_PRIO_COOP(config.prio), 0, delay);
    }

    ~impl()
    {
        abort();
        k_thread_stack_free(_threadStack);
    }

    void abort()
    {
        k_thread_abort(_threadId);
    }

    void join()
    {
        k_thread_join(&_thread, K_FOREVER);
        
    }

    void suspend()
    {
        k_thread_suspend(_threadId);
    }

    void resume()
    {
        k_thread_resume(_threadId);
    }
    
private:
    struct k_thread _thread;
    k_thread_stack_t* _threadStack;
    k_tid_t _threadId;
    OS::Thread::Function _function;
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
