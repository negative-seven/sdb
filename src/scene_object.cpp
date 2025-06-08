#include "scene_object.h"
#include <cstddef>

SceneObject::~SceneObject() { vtable = reinterpret_cast<void *>(0x5bf710); }

size_t SceneObject::__getInvocationID() const { return 0; }

size_t
SceneObject::__getEditorProperties(EditableProperty *editable_property) const {
    return 0;
}
