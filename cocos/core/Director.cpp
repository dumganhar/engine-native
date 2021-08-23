/*
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.

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
*/

#include "core/Director.h"

namespace cc {
std::string Director::EVENT_INIT{"director_init"};
std::string Director::EVENT_RESET{"director_reset"};
std::string Director::EVENT_BEFORE_SCENE_LOADING{"director_before_scene_loading"};
std::string Director::EVENT_BEFORE_SCENE_LAUNCH{"director_before_scene_launch"};
std::string Director::EVENT_AFTER_SCENE_LAUNCH{"director_after_scene_launch"};
std::string Director::EVENT_BEFORE_UPDATE{"director_before_update"};
std::string Director::EVENT_AFTER_UPDATE{"director_after_update"};
std::string Director::EVENT_BEFORE_DRAW{"director_before_draw"};
std::string Director::EVENT_AFTER_DRAW{"director_after_draw"};
std::string Director::EVENT_BEFORE_COMMIT{"director_before_commit"};
std::string Director::EVENT_BEFORE_PHYSICS{"director_before_physics"};
std::string Director::EVENT_AFTER_PHYSICS{"director_after_physics"};
std::string Director::EVENT_BEGIN_FRAME{"director_begin_frame"};
std::string Director::EVENT_END_FRAME{"director_end_frame"};

} // namespace cc