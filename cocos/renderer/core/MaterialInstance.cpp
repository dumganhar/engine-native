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
        for (const auto &pass : _passes) {
            pass->tryCompile(overrides);
        }
    } else {
        if (passIdx < _passes.size()) {
            auto *pass = _passes[passIdx].get();
            pass->tryCompile(overrides);
        }
    }
}

void MaterialInstance::overridePipelineStates(const PassOverrides &overrides, index_t passIdx /* = CC_INVALID_INDEX */) {
    if (_passes.empty() || _effectAsset == nullptr) {
        return;
    }

    std::vector<IPassInfoFull> &passInfos = _effectAsset->_techniques[getTechniqueIndex()].passes;
    if (passIdx == CC_INVALID_INDEX) {
        for (size_t i = 0, len = _passes.size(); i < len; i++) {
            auto *pass = _passes[i].get();
            if (i >= _states.size()) {
                _states.resize(i + 1);
            }
            auto &state = _states[i];
            state.overrides(overrides);
            pass->overridePipelineStates(passInfos[pass->getPassIndex()], state);
        }
    } else {
        if (passIdx >= _states.size()) {
            _states.resize(passIdx + 1);
        }
        auto &state = _states[passIdx];
        state.overrides(overrides);
        _passes[passIdx]->overridePipelineStates(passInfos[passIdx], state);
    }
}

bool MaterialInstance::destroy() {
    doDestroy();
    return true;
}

void MaterialInstance::doDestroy() {
    if (!_passes.empty()) {
        for (const auto &pass : _passes) {
            pass->destroy();
        }
    }
    _passes.clear();
}

std::vector<SharedPtr<scene::Pass>> MaterialInstance::createPasses() {
    std::vector<SharedPtr<scene::Pass>> passes;
    auto &                              parentPasses = _parent->getPasses();

    for (size_t k = 0; k < parentPasses.size(); ++k) {
        passes.emplace_back(new PassInstance(parentPasses[k], this));
    }
    return passes;
}

void MaterialInstance::onPassStateChange(bool dontNotify) {
    _hash = Material::getHashForMaterial(this);
    if (!dontNotify) {
        if (_rebuildPSOCallback != nullptr) {
            _rebuildPSOCallback(_subModelIdx, this);
        }

        if (_owner != nullptr) {
            _owner->onRebuildPSO(_subModelIdx, this);
        }
    }
}

void MaterialInstance::setRebuildPSOCallback(const RebuildPSOCallback &cb) {
    _rebuildPSOCallback = cb;
}

} // namespace cc
