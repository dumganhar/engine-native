/****************************************************************************
// References: https://github.com/pcgpcgpcg/testbeastclion/blob/b2b441b4642e68302166d98f42fc42c988132e90/utils/EventEmitter.hpp
// Modified by wanxiang.xie@cocos.com
****************************************************************************/
#include "core/event/EventEmitter.h"

namespace cc {

void EventEmitter::off() {
    _events.clear();
    _events_once.clear();
    this->_listeners = 0;
}

void EventEmitter::off(const std::string &name) {
    auto it = _events.find(name);

    if (it != _events.end()) {
        _events.erase(it);
        this->_listeners--;

        auto once = _events_once.find(name);
        if (once != _events_once.end()) {
            _events_once.erase(once);
        }
    }
}

} // namespace cc
