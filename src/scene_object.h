#pragma once

#include "declarations.h"
#include <cstddef>

struct EditableProperty {};

struct SceneObject {
    void *vtable;

    TEXT_ADDRESS(0x468c10) ~SceneObject();
    TEXT_ADDRESS(0x468c10) size_t __getInvocationID() const;
    TEXT_ADDRESS(0x468c10)
    size_t __getEditorProperties(EditableProperty *editable_property) const;
};
