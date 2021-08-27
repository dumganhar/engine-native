/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.
 
 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "scene/Camera.h"

namespace cc {
namespace scene {

const std::vector<float> Camera::FSTOPS{1.8F, 2.0F, 2.2F, 2.5F, 2.8F, 3.2F, 3.5F, 4.0F, 4.5F, 5.0F, 5.6F, 6.3F, 7.1F, 8.0F, 9.0F, 10.0F, 11.0F, 13.0F, 14.0F, 16.0F, 18.0F, 20.0F, 22.0F};
const std::vector<float> Camera::SHUTTERS{1.0F, 1.0F / 2.0F, 1.0F / 4.0F, 1.0F / 8.0F, 1.0F / 15.0F, 1.0F / 30.0F, 1.0F / 60.0F, 1.0F / 125.0F,
    1.0F / 250.0F, 1.0F / 500.0F, 1.0F / 1000.0F, 1.0F / 2000.0F, 1.0F / 4000.0F};
const std::vector<float> Camera::ISOS{100.0F, 200.0F, 400.0F, 800.0F};

}
}
