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

#pragma once

#include "core/Types.h"

#include <any>
#include <functional>

namespace cc {

using TaskCompleteCallback = std::function<void(const Error* /* err */, const std::any& /* data */)>;
using TaskProgressCallback = std::function<void(const std::vector<std::any>&)>;
using TaskErrorCallback = std::function<void(const std::vector<std::any>&)>;

struct ITaskOption {
    TaskCompleteCallback onComplete {nullptr};
    TaskProgressCallback onProgress {nullptr};
    TaskErrorCallback onError {nullptr};
    std::any input;
    std::any progress;
    Record<std::string, std::any> options;
};

/**
 * @en
 * Task is used to run in the pipeline for some effect
 *
 * @zh
 * 任务用于在管线中运行以达成某种效果
 *
 */
class Task final {
public:
    static constexpr uint32_t MAX_DEAD_NUM = 500;

    /**
     * @en
     * Create a new task from pool
     *
     * @zh
     * 从对象池中创建 task
     *
     * @static
     * @method create
     * @param options - Some optional paramters
     * @param options.onComplete - Callback when the task complete, if the pipeline is synchronous, onComplete is unnecessary.
     * @param options.onProgress - Continuously callback when the task is runing, if the pipeline is synchronous, onProgress is unnecessary.
     * @param options.onError - Callback when something goes wrong, if the pipeline is synchronous, onError is unnecessary.
     * @param options.input - Something will be handled with pipeline
     * @param options.progress - Progress information, you may need to assign it manually when multiple pipeline share one progress
     * @param options.options - Custom parameters
     * @returns task
     *
     */
    static Task* create (ITaskOption options);


    /**
     * @en
     * The id of task
     *
     * @zh
     * 任务id
     *
     */
    uint32_t id {0};

    /**
     * @en
     * The callback when task is completed
     *
     * @zh
     * 完成回调
     *
     */
    TaskCompleteCallback onComplete {nullptr};

    /**
     * @en
     * The callback of progression
     *
     * @zh
     * 进度回调
     *
     */
    TaskProgressCallback onProgress {nullptr};

    /**
     * @en
     * The callback when something goes wrong
     *
     * @zh
     * 错误回调
     *
     */
    TaskErrorCallback onError {nullptr};

    /**
     * @en
     * The source of task
     *
     * @zh
     * 任务的源
     *
     */
    std::any source = nullptr;

    /**
     * @en
     * The output of task
     *
     * @zh
     * 任务的输出
     */
    std::any output = nullptr;

    /**
     * @en
     * The input of task
     *
     * @zh
     * 任务的输入
     *
     */
    std::any input = nullptr;

    /**
     * @en
     * The progression of task
     *
     * @zh
     * 任务的进度
     *
     */
    std::any progress = nullptr;

    /**
     * @en
     * Custom options
     *
     * @zh
     * 自定义参数
     *
     */
    Record<std::string, std::any> options;

    /**
     * @en
     * Whether or not this task is completed
     *
     * @zh
     * 此任务是否已经完成
     *
     */
    bool isFinish = true;

    /**
     * @en
     * Create a new Task
     *
     * @zh
     * 创建一个任务
     *
     * @param options - Some optional paramters
     * @param options.onComplete - Callback when the task is completed, if the pipeline is synchronous, onComplete is unnecessary.
     * @param options.onProgress - Continuously callback when the task is runing, if the pipeline is synchronous, onProgress is unnecessary.
     * @param options.onError - Callback when something goes wrong, if the pipeline is synchronous, onError is unnecessary.
     * @param options.input - Something will be handled with pipeline
     * @param options.progress - Progress information, you may need to assign it manually when multiple pipeline share one progress
     * @param options.options - Custom parameters
     */
    Task (const ITaskOption& options);

    /**
     * @en
     * Set parameters of this task
     *
     * @zh
     * 设置任务的参数
     *
     * @param options - Some optional parameters
     * @param options.onComplete - Callback when the task is completed, if the pipeline is synchronous, onComplete is unnecessary.
     * @param options.onProgress - Continuously callback when the task is running, if the pipeline is synchronous, onProgress is unnecessary.
     * @param options.onError - Callback when something goes wrong, if the pipeline is synchronous, onError is unnecessary.
     * @param options.input - Something will be handled with pipeline
     * @param options.progress - Progress information, you may need to assign it manually when multiple pipeline share one progress
     * @param options.options - Custom parameters
     *
     * @example
     * var task = new Task();
     * task.set({input: ['test'], onComplete: (err, result) => console.log(err), onProgress: (finish, total) => console.log(finish / total)});
     *
     */
    void set (const ITaskOption& options);

    /**
     * @en
     * Dispatch event
     *
     * @zh
     * 发布事件
     *
     * @param event - The event name
     * @param param1 - Parameter 1
     * @param param2 - Parameter 2
     * @param param3 - Parameter 3
     * @param param4 - Parameter 4
     *
     * @example
     * var task = Task.create();
     * Task.onComplete = (msg) => console.log(msg);
     * Task.dispatch('complete', 'hello world');
     *
     */
    void dispatch (const std::string& event, const std::any& param1, const std::any& param2, const std::any& param3, const std::any& param4); //cjh Use enum for event?

    /**
     * @en
     * Recycle this for reuse
     *
     * @zh
     * 回收 task 用于复用
     *
     */
    void recycle ();

private:
    static uint32_t _taskId;
    static std::vector<Task> _deadPool;
};

} // namespace cc {
