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

namespace bgfx {

struct RenderFrame
{
    enum Enum
    {
        NoContext,
        Render,
        Timeout,
        Exiting,

        Count
    };
};

/// Render frame.
///
/// @param _msecs Timeout in milliseconds.
///
/// @returns Current renderer state. See: `bgfx::RenderFrame`.
///
/// @attention `bgfx::renderFrame` is blocking call. It waits for
///   `bgfx::frame` to be called from API thread to process frame.
///   If timeout value is passed call will timeout and return even
///   if `bgfx::frame` is not called.
///
/// @warning This call should be only used on platforms that don't
///   allow creating separate rendering thread. If it is called before
///   to bgfx::init, render thread won't be created by bgfx::init call.
RenderFrame::Enum renderFrame(int32_t _msecs = -1);

} // namespace bgfx {
