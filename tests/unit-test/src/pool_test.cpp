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
#include "core/memop/Pool.h"
#include "gtest/gtest.h"

#include "utils.h"

using namespace cc;
using namespace memop;

namespace {
class PoolTest {
public:
    int32_t tag{0};
    explicit PoolTest(int32_t num) : tag(num) {}
};
int32_t tagValue = 0;

PoolTest *createTest() {
    return new PoolTest(tagValue++);
}

const int32_t ARRAY_SIZE = 10;
auto *        pool       = new memop::Pool<PoolTest>(createTest, ARRAY_SIZE);

} // namespace

TEST(PoolTest, alloc) {
    for (int32_t i = 0; i < ARRAY_SIZE + 2; ++i) {
        auto *obj = pool->alloc();
        EXPECT_NE(obj, nullptr);
    }
}

TEST(PoolTest, free) {
    auto * tmp = createTest();
    pool->free(tmp);
    auto * newElement = pool->alloc();
    EXPECT_EQ(newElement, tmp);
}

TEST(PoolTest, freeArray) { 
    const int32_t TEST_SIZE = 5;
    std::vector<PoolTest *> tmpArr(TEST_SIZE);
   for(int32_t i = 0; i < TEST_SIZE; ++i) {
       PoolTest* a = createTest();
   }
    pool->freeArray(tmpArr);
    for(int32_t i = 0; i < TEST_SIZE; ++i) {
        auto * tmpObj = pool->alloc();
        EXPECT_EQ(tmpArr[TEST_SIZE - i - 1], tmpObj);
    }

}
