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
#include <string>
#include "base/Macros.h"

namespace cc {

class ISchedulable {
public:
    std::string id;
    std::string uuid;
    virtual ~ISchedulable() {}
};

enum Priority : uint32_t {
    Low       = 0,
    Medium    = 100,
    High      = 200,
    SCHEDULER = (1 << 31),
};

class CC_DLL System : public ISchedulable {
private:
    /* data */
public:
    System(/* args */);
    ~System();

    inline std::string getId() { return _id; }
    inline std::string setId(std::string s) { _id = s; }

    inline uint32_t getPriority() { return _priority; }
    inline uint32_t setPriority(uint32_t i) { _priority = i; }

    inline bool getExecuteInEditMode() { return _executeInEditMode; }
    inline bool setExecuteInEditMode(bool b) { _executeInEditMode = b; }

    /**
     * @en Sorting between different systems.
     * @zh 不同系统间排序。
     * @param a System a
     * @param b System b
     */
    static int16_t sortByPriority(System* a, System* b);

    /**
     * @en Init the system, will be invoked by [[Director]] when registered, should be implemented if needed.
     * @zh 系统初始化函数，会在注册时被 [[Director]] 调用，如果需要的话应该由子类实现
     */
    bool init() {}

    /**
     * @en Update function of the system, it will be invoked between all components update phase and late update phase.
     * @zh 系统的帧更新函数，它会在所有组件的 update 和 lateUpdate 之间被调用
     * @param dt Delta time after the last frame
     */
    void update(uint32_t& dt) {}

    /**
     * @en Post update function of the system, it will be invoked after all components late update phase and before the rendering process.
     * @zh 系统的帧后处理函数，它会在所有组件的 lateUpdate 之后以及渲染之前被调用
     * @param dt Delta time after the last frame
     */
    void postUpdate(uint32_t& dt) {}

    //Hard to define encapsulation
protected:
    std::string _id;
    uint32_t    _priority;
    bool        _executeInEditMode;
};

} // namespace cc