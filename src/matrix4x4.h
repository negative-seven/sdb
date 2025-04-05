#pragma once

#include "declarations.h"
#include "fpu_vector.h"

struct Matrix4x4 {
    static const float IDENTITY_MATRIX_VALUES[4][4];

    float values[4][4];

    TEXT_ADDRESS(0x5baf00) operator float *();
    TEXT_ADDRESS(0x5baf00) operator float const *() const;
    TEXT_ADDRESS(0x5baf00) float *operator[](int index);
    TEXT_ADDRESS(0x5baf00) float const *operator[](int index) const;
    TEXT_ADDRESS(0x5baf00) float *GetElement(unsigned char i, unsigned char j);
    TEXT_ADDRESS(0x5baf00)
    float const *GetElement(unsigned char i, unsigned char j) const;
    TEXT_ADDRESS(0x5baf00) void operator=(Matrix4x4 const &other);
    TEXT_ADDRESS(0x5baf00) int operator==(Matrix4x4 const &other) const;
    TEXT_ADDRESS(0x5baf00) int operator!=(Matrix4x4 const &other) const;
    TEXT_ADDRESS(0x5baf00) void operator*=(float other);
    TEXT_ADDRESS(0x5baf00) void operator/=(float other); // generates constant
    TEXT_ADDRESS(0x5baf00)
    static Matrix4x4 *Identity(Matrix4x4 *matrix); // generates constant
    TEXT_ADDRESS(0x5baf00)
    static float Determinant(Matrix4x4 const *matrix); // complex
};

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bb3f0)
float Mat4x4MinorDeterminant(FPUVector const &param_1, FPUVector const &param_2,
                             FPUVector const &param_3);
