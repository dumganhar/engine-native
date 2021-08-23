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
#include "core/asset-manager/Shared.h"
#include "core/asset-manager/Task.h"

#include <any>
#include <functional>

namespace cc {

using IAsyncPipe = std::function<void(const Task &, CompleteCallbackNoData)>;
using ISyncPipe  = std::function<const Error *(const Task &task)>;
using IPipe      = std::variant<IAsyncPipe, ISyncPipe>;

/**
 * @en
 * Pipeline can execute the task for some effect.
 *
 * @zh
 * 管线能执行任务达到某个效果
 *
 */
class Pipeline final {
public:
    /**
     * @en
     * The id of pipeline
     *
     * @zh
     * 管线的 id
     *
     */
    uint32_t id{0};

    /**
     * @en
     * The name of pipeline
     *
     * @zh
     * 管线的名字
     *
     */
    std::string name;

    /**
     * @en
     * All pipes of pipeline
     *
     * @zh
     * 所有的管道
     *
     */
    std::vector<IPipe> pipes;

    /**
     * @en
     * Create a new pipeline
     *
     * @zh
     * 创建一个管线
     *
     * @param name - The name of pipeline
     * @param funcs - The array of pipe, every pipe must be function which take two parameters,
     * the first is a `Task` flowed in pipeline, the second is complete callback
     *
     * @example
     * var pipeline = new Pipeline('download', [
     * (task, done) => {
     *      var url = task.input;
     *      cc.assetManager.downloader.downloadFile(url, null, null, (err, result) => {
     *          task.output = result;
     *          done(err);
     *      });
     * },
     * (task, done) => {
     *      var text = task.input;
     *      var json = JSON.stringify(text);
     *      task.output = json;
     *      done();
     * }
     * ]);
     *
     */
    Pipeline(const std::string &name, const std::vector<IPipe> &funcs);

    /**
     * @en
     * At specific point insert a new pipe to pipeline
     *
     * @zh
     * 在某个特定的点为管线插入一个新的 pipe
     *
     * @param func - The new pipe
     * @param func.task - The task handled with pipeline will be transferred to this function
     * @param func.done - Callback you need to invoke manually when this pipe is finished. if the pipeline is synchronous, callback is unnecessary.
     * @param index - The specific point you want to insert at.
     * @return pipeline
     *
     * @example
     * var pipeline = new Pipeline('test', []);
     * pipeline.insert((task, done) => {
     *      // do something
     *      done();
     * }, 0);
     *
     */
    Pipeline *insert(const IPipe &func, uint32_t index);

    /**
     * @en
     * Append a new pipe to the pipeline
     *
     * @zh
     * 添加一个管道到管线中
     *
     * @param func - The new pipe
     * @param func.task - The task handled with pipeline will be transferred to this function
     * @param func.done - Callback you need to invoke manually when this pipe is finished. if the pipeline is synchronous, callback is unnecessary.
     * @return pipeline
     *
     * @example
     * var pipeline = new Pipeline('test', []);
     * pipeline.append((task, done) => {
     *      // do something
     *      done();
     * });
     *
     */
    Pipeline *append(const IPipe &func);

    /**
     * @en
     * Remove pipe which at specific point
     *
     * @zh
     * 移除特定位置的管道
     *
     * @param index - The specific point
     * @return pipeline
     *
     * @example
     * var pipeline = new Pipeline('test', (task, done) => {
     *      // do something
     *      done();
     * });
     * pipeline.remove(0);
     *
     */
    Pipeline *remove(uint32_t index);

    /**
     * @en
     * Execute task synchronously
     *
     * @zh
     * 同步执行任务
     *
     * @param task - The task will be executed
     * @returns result
     *
     * @example
     * var pipeline = new Pipeline('sync', [(task) => {
     *      let input = task.input;
     *      task.output = doSomething(task.input);
     * }]);
     *
     * var task = new Task({input: 'test'});
     * console.log(pipeline.sync(task));
     *
     */
    std::any sync(const Task *task);

    /**
     * @en
     * Execute task asynchronously
     *
     * @zh
     * 异步执行任务
     *
     * @param task - The task will be executed
     *
     * @example
     * var pipeline = new Pipeline('sync', [(task, done) => {
     *      let input = task.input;
     *      task.output = doSomething(task.input);
     *      done();
     * }]);
     * var task = new Task({input: 'test', onComplete: (err, result) => console.log(result)});
     * pipeline.async(task);
     *
     */
    void async(const Task *task);

private:
    void flow(uint32_t index, const Task *task);

    static const int _pipelineId = 0;
};

} // namespace cc
