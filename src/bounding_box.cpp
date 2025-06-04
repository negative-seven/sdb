#include "bounding_box.h"
#include "fpu_vector.h"
#include "quaternion.h"
#include <cstddef>
#include <immintrin.h>

BoundingBox::BoundingBox(FPUVector const &translation,
                         FPUVector const &unknown_vector,
                         TQuaternion const &rotation) {
    unknown_0x4 = FPUVector();
    unknown_0x14 = FPUVector();
    unknown_0x0 = 18;
    unknown_0x14.values[0] = unknown_vector.values[0];
    unknown_0x14.values[1] = unknown_vector.values[1];
    unknown_0x14.values[2] = unknown_vector.values[2];
    unknown_0x14.values[3] = unknown_vector.values[3];
    unknown_0x4.values[0] = unknown_vector.values[0];
    unknown_0x4.values[1] = unknown_vector.values[1];
    unknown_0x4.values[2] = unknown_vector.values[2];
    unknown_0x4.values[3] = unknown_vector.values[3];
    Matrix4x4::Transformation3D(&unknown_0x24, NULL, &rotation, &translation);
    unknown_0x64 = unknown_0x24;
}

void BoundingBox::Update(FPUVector const &unknown_vector,
                         TQuaternion const &rotation,
                         FPUVector const &translation)

{
    typedef float v2sf __attribute__((vector_size(8)));
    typedef float v4sf __attribute__((vector_size(16)));

    v4sf zero;
    zero = __builtin_ia32_xorps(zero, zero);

    float m12 = unknown_0x24.values[1][2];
    float m11 = unknown_0x24.values[1][1];
    float m10 = unknown_0x24.values[1][0];
    float m03 = unknown_0x24.values[0][3];

    __builtin_ia32_storelps(
        reinterpret_cast<v2sf *>(&unknown_0x24.values[0][3]), zero);
    __builtin_ia32_storehps(
        reinterpret_cast<v2sf *>(&unknown_0x24.values[1][1]), zero);

    Matrix4x4 *transformation_result = Matrix4x4::Transformation3D(
        &unknown_0x64, NULL, &rotation, &translation);
    Matrix4x4::Multiply(&unknown_0x64, &unknown_0x24, transformation_result);

    unknown_0x64.values[0][3] += m03;
    unknown_0x64.values[1][0] += m10;
    unknown_0x64.values[1][1] += m11;
    unknown_0x64.values[1][2] += m12;

    unknown_0x24.values[0][3] = m03;
    unknown_0x24.values[1][0] = m10;
    unknown_0x24.values[1][1] = m11;
    unknown_0x24.values[1][2] = m12;

    float v3 = unknown_vector.values[3] * unknown_0x14.values[3];
    float v2 = unknown_vector.values[2] * unknown_0x14.values[2];
    float v1 = unknown_vector.values[1] * unknown_0x14.values[1];
    float v0 = unknown_vector.values[0] * unknown_0x14.values[0];

    unknown_0x4.values[3] = v3;
    unknown_0x4.values[2] = v2;
    unknown_0x4.values[1] = v1;
    unknown_0x4.values[0] = v0;
}

void BoundingBox::Change(FPUVector const &unknown_vector_a,
                         TQuaternion const &quaternion,
                         FPUVector const &unknown_vector_b)

{
    unknown_0x14.values[0] = unknown_vector_a.values[0];
    unknown_0x14.values[1] = unknown_vector_a.values[1];
    unknown_0x14.values[2] = unknown_vector_a.values[2];
    unknown_0x14.values[3] = unknown_vector_a.values[3];
    unknown_0x4.values[0] = unknown_vector_a.values[0];
    unknown_0x4.values[1] = unknown_vector_a.values[1];
    unknown_0x4.values[2] = unknown_vector_a.values[2];
    unknown_0x4.values[3] = unknown_vector_a.values[3];
    Matrix4x4::Transformation3D(&unknown_0x24, NULL, &quaternion,
                                &unknown_vector_b);
    unknown_0x64 = unknown_0x24;
}
