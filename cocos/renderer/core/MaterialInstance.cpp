#include "MaterialInstance.h"

namespace cc {

MaterialInstance::MaterialInstance(const IMaterialInstanceInfo &info) {
    _parent      = info.parent;
    _owner       = info.owner;
    _subModelIdx = info.subModelIdx;
    copy(_parent);
}

void MaterialInstance::recompileShaders(const MacroRecord &overrides, index_t passIdx /* = CC_INVALID_INDEX */) {
    if (_passes.empty() || _effectAsset == nullptr) {
        return;
    }

    if (passIdx == CC_INVALID_INDEX) {
        for (auto *pass : _passes) {
            //cjh            pass->tryCompile(overrides);
        }
    } else {
        //cjh        _passes[passIdx]->tryCompile(overrides);
    }
}

void MaterialInstance::overridePipelineStates(const PassOverrides &overrides, index_t passIdx /* = CC_INVALID_INDEX */) {
    if (_passes.empty() || _effectAsset == nullptr) {
        return;
    }

    const auto &passInfos = _effectAsset->_techniques[getTechniqueIndex()].passes;
    if (passIdx == CC_INVALID_INDEX) {
        for (size_t i = 0, len = _passes.size(); i < len; i++) {
            const auto *pass = _passes[i];
            if (i >= _states.size()) {
                _states.resize(i + 1);
            }
            auto &state = _states[i];
            state       = overrides;
            //cjh            pass->overridePipelineStates(passInfos[pass->getPassIndex()], state);
        }
    } else {
        if (passIdx >= _states.size()) {
            _states.resize(passIdx + 1);
        }
        auto &state = _states[passIdx];
        state       = overrides;
        //cjh        _passes[passIdx]->overridePipelineStates(passInfos[passIdx], state);
    }
}

bool MaterialInstance::destroy() {
    doDestroy();
    return true;
}

void MaterialInstance::doDestroy() {
    if (!_passes.empty()) {
        for (auto *pass : _passes) {
            //cjh            pass->destroy();
        }
    }
    _passes.clear();
}

std::vector<scene::Pass *> MaterialInstance::createPasses() {
    std::vector<scene::Pass *> passes;
    //cjh    const passes: PassInstance[] = [];
    //    const parentPasses = this._parent.passes;
    //    if (!parentPasses) { return passes; }
    //    for (let k = 0; k < parentPasses.length; ++k) {
    //        passes.push(new PassInstance(parentPasses[k], this));
    //    }
    return passes;
}

void MaterialInstance::onPassStateChange(bool dontNotify) {
    _hash = Material::getHashForMaterial(this);
    if (!dontNotify && _owner != nullptr) {
        //cjh TODO:        _owner->_onRebuildPSO(_subModelIdx, this);
    }
}

} // namespace cc
