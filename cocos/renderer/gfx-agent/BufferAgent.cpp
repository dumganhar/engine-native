/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "base/CoreStd.h"
#include "base/LinearAllocatorPool.h"
#include "base/threading/MessageQueue.h"

#include "BufferAgent.h"
#include "DeviceAgent.h"

namespace cc {
namespace gfx {

BufferAgent::BufferAgent(Buffer *actor)
: Agent<Buffer>(actor) {
    _typedID = generateObjectID<decltype(this)>();
}

BufferAgent::~BufferAgent() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(),
        BufferDestruct,
        actor, _actor,
        {
            CC_SAFE_DELETE(actor);
        });
}

void BufferAgent::doInit(const BufferInfo &info) {
    ENQUEUE_MESSAGE_2(
        DeviceAgent::getInstance()->getMessageQueue(),
        BufferInit,
        actor, getActor(),
        info, info,
        {
            actor->initialize(info);
        });
}

void BufferAgent::doInit(const BufferViewInfo &info) {
    BufferViewInfo actorInfo = info;
    actorInfo.buffer         = static_cast<BufferAgent *>(info.buffer)->getActor();

    ENQUEUE_MESSAGE_2(
        DeviceAgent::getInstance()->getMessageQueue(),
        BufferViewInit,
        actor, getActor(),
        info, actorInfo,
        {
            actor->initialize(info);
        });
}

void BufferAgent::doResize(uint size, uint /*count*/) {
    ENQUEUE_MESSAGE_2(
        DeviceAgent::getInstance()->getMessageQueue(),
        BufferResize,
        actor, getActor(),
        size, size,
        {
            actor->resize(size);
        });
}

void BufferAgent::doDestroy() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(),
        BufferDestroy,
        actor, getActor(),
        {
            actor->destroy();
        });
}

void BufferAgent::update(const void *buffer, uint size) {
    auto *actorBuffer = DeviceAgent::getInstance()->getMainAllocator()->allocate<uint8_t>(size);
    memcpy(actorBuffer, buffer, size);

    ENQUEUE_MESSAGE_3(
        DeviceAgent::getInstance()->getMessageQueue(),
        BufferUpdate,
        actor, getActor(),
        buffer, actorBuffer,
        size, size,
        {
            actor->update(buffer, size);
        });
}

} // namespace gfx
} // namespace cc