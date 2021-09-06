#include "renderer/core/MaterialInstance.h"
#include "core/components/RenderableComponent.h"
#include "renderer/core/PassInstance.h"

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
        for (auto *pass : _passInstances) {
            pass->tryCompile(overrides);
        }
    } else {
        _passInstances[passIdx]->tryCompile(overrides);
    }
}

void MaterialInstance::overridePipelineStates(const PassOverrides &overrides, index_t passIdx /* = CC_INVALID_INDEX */) {
    if (_passes.empty() || _effectAsset == nullptr) {
        return;
    }

    std::vector<IPassInfoFull> &passInfos = _effectAsset->_techniques[getTechniqueIndex()].passes;
    if (passIdx == CC_INVALID_INDEX) {
        for (size_t i = 0, len = _passInstances.size(); i < len; i++) {
            auto *pass = _passInstances[i];
            if (i >= _states.size()) {
                _states.resize(i + 1);
            }
            auto &state = _states[i];
            state       = overrides;
            pass->overridePipelineStates(passInfos[pass->getPassIndex()], state);
        }
    } else {
        if (passIdx >= _states.size()) {
            _states.resize(passIdx + 1);
        }
        auto &state = _states[passIdx];
        state       = overrides;
        _passes[passIdx]->overridePipelineStates(passInfos[passIdx], state);
    }
}

bool MaterialInstance::destroy() {
    doDestroy();
    return true;
}

void MaterialInstance::doDestroy() {
    if (!_passes.empty()) {
        for (auto *pass : _passes) {
            pass->destroy();
        }
    }
    _passes.clear();
}

std::vector<scene::Pass *> MaterialInstance::createPasses() {
    std::vector<scene::Pass *> passes;
    auto &                     parentPasses = _parent->getPasses();

    for (size_t k = 0; k < parentPasses.size(); ++k) {
        passes.emplace_back(new PassInstance(parentPasses[k], this)); //cjh shared_ptr?
    }
    return passes;
}

void MaterialInstance::onPassStateChange(bool dontNotify) {
    _hash = Material::getHashForMaterial(this);
    if (!dontNotify && _owner != nullptr) {
        _owner->onRebuildPSO(_subModelIdx, this);
    }
}

} // namespace cc
