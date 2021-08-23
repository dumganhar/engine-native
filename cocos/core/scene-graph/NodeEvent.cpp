
#include "core/scene-graph/NodeEvent.h"

namespace cc {
namespace scenegraph {
const std::string NodeEventType::TOUCH_START{"touch-start"};
const std::string NodeEventType::TOUCH_MOVE{"touch-move"};
const std::string NodeEventType::TOUCH_END{"touch-end"};
const std::string NodeEventType::TOUCH_CANCEL{"touch-cancel"};
const std::string NodeEventType::MOUSE_DOWN{"mouse-down"};
const std::string NodeEventType::MOUSE_MOVE{"mouse-move"};
const std::string NodeEventType::MOUSE_UP{"mouse-up"};
const std::string NodeEventType::MOUSE_WHEEL{"mouse-wheel"};
const std::string NodeEventType::MOUSE_ENTER{"mouse-enter"};
const std::string NodeEventType::MOUSE_LEAVE{"mouse-leave"};
const std::string NodeEventType::KEY_DOWN{"keydown"};
const std::string NodeEventType::KEY_UP{"keyup"};
const std::string NodeEventType::DEVICEMOTION{"devicemotion"};
const std::string NodeEventType::TRANSFORM_CHANGED{"transform-changed"};
const std::string NodeEventType::SCENE_CHANGED_FOR_PERSISTS{"scene-changed-for-persists"};
const std::string NodeEventType::SIZE_CHANGED{"size-changed"};
const std::string NodeEventType::ANCHOR_CHANGED{"anchor-changed"};
const std::string NodeEventType::COLOR_CHANGED{"color-changed"};
const std::string NodeEventType::CHILD_ADDED{"child-added"};
const std::string NodeEventType::CHILD_REMOVED{"child-removed"};
const std::string NodeEventType::PARENT_CHANGED{"parent-changed"};
const std::string NodeEventType::NODE_DESTROYED{"node-destroyed"};
const std::string NodeEventType::LAYER_CHANGED{"layer-changed"};
const std::string NodeEventType::SIBLING_ORDER_CHANGED{"sibling-order-changed"};
} // namespace scenegraph
} // namespace cc
