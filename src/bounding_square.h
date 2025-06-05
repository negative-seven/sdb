#pragma once

#include "declarations.h"
#include "matrix4x4.h"

struct BoundingSquare {
    char unknown_0x0;
    Matrix4x4 unknown_0x4;
    Matrix4x4 unknown_0x44;
    Vector2 initial_scale_maybe;
    Vector2 scale_maybe;

    TEXT_ADDRESS(0x57dfc0)
    BoundingSquare(Vector2 const &translation, float rotation,
                   Vector2 const &scale_maybe) noexcept;
    TEXT_ADDRESS(0x57dfc0)
    void Update(Vector2 const &scale_maybe, float rotation,
                Vector2 const &translation) noexcept;
    TEXT_ADDRESS(0x57dfc0)
    void Change(Vector2 const &scale_maybe, float rotation,
                Vector2 const &translation);
};
