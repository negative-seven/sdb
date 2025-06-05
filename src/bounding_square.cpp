#include "bounding_square.h"
#include <cstddef>

BoundingSquare::BoundingSquare(Vector2 const &translation, float rotation,
                               Vector2 const &scale_maybe) noexcept {
    unknown_0x0 = 16;
    float rotation_copy = rotation;
    initial_scale_maybe = scale_maybe;
    this->scale_maybe = scale_maybe;
    Matrix4x4::Transformation2DRot(&unknown_0x4, NULL, &rotation_copy,
                                   &translation);
    unknown_0x44 = unknown_0x4;
}

void BoundingSquare::Update(Vector2 const &scale_maybe, float rotation,
                            Vector2 const &translation) noexcept {
    Matrix4x4 *matrix = Matrix4x4::Transformation2DRot(&unknown_0x44, nullptr,
                                                       &rotation, &translation);
    Matrix4x4::Multiply(&unknown_0x44, &unknown_0x4, matrix);
    this->scale_maybe = initial_scale_maybe * scale_maybe;
}

void BoundingSquare::Change(Vector2 const &scale_maybe, float rotation,
                            Vector2 const &translation) {
    initial_scale_maybe = scale_maybe;
    this->scale_maybe = scale_maybe;
    Matrix4x4::Transformation2DRot(&unknown_0x4, nullptr, &rotation,
                                   &translation);
    unknown_0x44 = unknown_0x4;
}
