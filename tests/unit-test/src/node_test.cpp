/****************************************************************************
Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

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
#include "core/Director.h"
#include "core/Root.h"
#include "core/scene-graph/SceneGraphModuleHeader.h"
#include "gtest/gtest.h"
#include "renderer/GFXDeviceManager.h"
#include "renderer/gfx-base/GFXDef.h"
#include "utils.h"

using namespace cc;
using namespace cc::gfx;

TEST(NodeTest, inverseTransformPoint) {
    initCocos(100, 100);

    auto *director = Director::getInstance();
    auto *scene    = director->getScene();

    auto *parentNode = new Node("");
    auto *subNode    = new Node("");
    parentNode->setPosition(20.F, -30.F, 100.F);
    subNode->setPosition(55, 35, 22);
    parentNode->setParent(scene);
    subNode->setParent(parentNode);
    auto p = Vec3(100.F, 200.F, 0.F);
    subNode->inverseTransformPoint(p, p);

    EXPECT_EQ(p, Vec3(25.F, 195.F, -122.F));

    //xwx FIXME: gfx-validator Assert
    destroyCocos();
}

// TODO(xwx): wait for NodeEventProcessor implementation
// TEST(NodeTest, activeInHierarchyChanged) {}
// test('active-in-hierarchy-changed', () => {
//     const scene = new Scene('');
//     director.runSceneImmediate(scene);
//     const node = new Node();
//     const cb = jest.fn((node: Node) => {
//         expect(node.activeInHierarchy).toBeTruthy();
//     });
//     node.once(NodeEventType.ACTIVE_IN_HIERARCHY_CHANGED, cb);
//     scene.addChild(node);

//     const cb1 = jest.fn((node: Node) => {
//         expect(node.activeInHierarchy).toBeFalsy();
//     });
//     node.once(NodeEventType.ACTIVE_IN_HIERARCHY_CHANGED, cb1);
//     node.active = false;
//     node.once(NodeEventType.ACTIVE_IN_HIERARCHY_CHANGED, cb);
//     node.active = true;

//     const node2 = new Node();
//     scene.addChild(node2);
//     node2.active = false;
//     node.once(NodeEventType.ACTIVE_IN_HIERARCHY_CHANGED, cb1);
//     node2.addChild(node);

//     node.once(NodeEventType.ACTIVE_IN_HIERARCHY_CHANGED, cb);
//     node.setParent(scene);
//     expect(cb).toBeCalledTimes(3);
//     expect(cb1).toBeCalledTimes(2);
// });
