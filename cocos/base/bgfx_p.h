/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma once

#include "bx/platform.h"

#ifndef BGFX_CONFIG_DEBUG
#    define BGFX_CONFIG_DEBUG 0
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG || BX_COMPILER_CLANG_ANALYZER
#    define BX_TRACE _BX_TRACE
#    define BX_WARN  _BX_WARN
#    define BX_CHECK _BX_CHECK
#    define BX_CONFIG_ALLOCATOR_DEBUG 1
#endif // BGFX_CONFIG_DEBUG

#include "bgfx.h"
#include "config.h"

#include <inttypes.h>

#if BGFX_CONFIG_DEBUG
#    define BGFX_API_FUNC(_func) BX_NO_INLINE _func
#else
#    define BGFX_API_FUNC(_func) _func
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_MULTITHREADED
#    define BGFX_MUTEX_SCOPE(_mutex) bx::MutexScope BX_CONCATENATE(mutexScope, __LINE__)(_mutex)
#else
#    define BGFX_MUTEX_SCOPE(_mutex) BX_NOOP()
#endif // BGFX_CONFIG_MULTITHREADED

#if BGFX_CONFIG_PROFILER
#    define BGFX_PROFILER_SCOPE(_name, _abgr) ProfilerScope BX_CONCATENATE(profilerScope, __LINE__)(_name, _abgr, __FILE__, uint16_t(__LINE__) )
#    define BGFX_PROFILER_BEGIN(_name, _abgr) g_callback->profilerBeginLiteral(_name, _abgr, __FILE__, uint16_t(__LINE__) )
#    define BGFX_PROFILER_END() g_callback->profilerEnd()
#    define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) BX_NOOP()
#else
#    define BGFX_PROFILER_SCOPE(_name, _abgr) BX_NOOP()
#    define BGFX_PROFILER_BEGIN(_name, _abgr) BX_NOOP()
#    define BGFX_PROFILER_END() BX_NOOP()
#    define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) BX_NOOP()
#endif // BGFX_PROFILER_SCOPE
