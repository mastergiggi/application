/*
 * Copyright (c) 2023-2024 Stefan Giggenbach (https://github.com/mastergiggi)
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OS_THREAD_HPP
#define OS_THREAD_HPP

#include <cstddef>
#include <functional>
#include <string_view>

#include "os.hpp"
#include "pimpl.hpp"

namespace OS
{

class Thread
{
public:
    using StackSize = OS::Size;
    using Priority = std::uint32_t;

    struct Config
    {
        Name name;
        StackSize stackSize;
        Priority prio;
    };

    using Function = std::function<void()>;

    Thread(Function, const Config&, const bool autostart = true);
    ~Thread();

    void start();
    void suspend();
    void resume();
    void abort();
    void join();

    static void sleep(const Timeout);
    static void msleep(const Timeout);
    static void usleep(const Timeout);

    static void yield();

private:
    class impl;
    pimpl<impl> handle;
};

} // namespace OS

#endif // OS_THREAD_HPP
