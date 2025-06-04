#pragma once

#include "declarations.h"
#include "fpu_vector.h"
#include "matrix4x4.h"

struct BoundingBox {
    char unknown_0x0;
    FPUVector unknown_0x4;
    FPUVector unknown_0x14;
    Matrix4x4 unknown_0x24;
    Matrix4x4 unknown_0x64;

    TEXT_ADDRESS(0x57dd60)
    BoundingBox(FPUVector const &translation, FPUVector const &unknown_vector,
                TQuaternion const &rotation);
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x57dd60)
    void Update(FPUVector const &unknown_vector, TQuaternion const &rotation,
                FPUVector const &translation); // complex
    TEXT_ADDRESS(0x57df60)
    void Change(FPUVector const &unknown_vector_a,
                TQuaternion const &quaternion,
                FPUVector const &unknown_vector_b);
};
