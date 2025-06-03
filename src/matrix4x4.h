#pragma once

#include "declarations.h"
#include "fpu_vector.h"
#include "quaternion.h"
#include "vector2.h"

struct Matrix4x4 {
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
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bb290)
    static float Determinant(Matrix4x4 const *matrix); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bb450)
    static Matrix4x4 *Inverse(Matrix4x4 *out, Matrix4x4 const *in); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bbb90)
    static Matrix4x4 *Multiply(Matrix4x4 *out, Matrix4x4 const *left,
                               Matrix4x4 const *right); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc060)
    Matrix4x4 operator*(Matrix4x4 const &other) const; // inlines inner call
    TEXT_ADDRESS(0x5bc070)
    void operator*=(Matrix4x4 const &other);
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc070)
    static void
    ConvertToRotationMatrix(Matrix4x4 *result,
                            TQuaternion const *quaternion); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc1e0)
    static Matrix4x4 *
    ConvertToRotationMatrix(Matrix4x4 *result,
                            float angle); // complex, references libm
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc250)
    static Matrix4x4 *ConvertToScalingMatrix(Matrix4x4 *result,
                                             FPUVector const *scale); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc2a0)
    static Matrix4x4 *ConvertToScalingMatrix(Matrix4x4 *result,
                                             Vector2 const *scale); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc2f0)
    static Matrix4x4 *
    ConvertToTranslationMatrix(Matrix4x4 *result,
                               FPUVector const *translation); // complex
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc340)
    static Matrix4x4 *Transformation3D(
        Matrix4x4 *out, FPUVector const *scale, TQuaternion const *rotation,
        FPUVector const *translation); // complex, unsure if correct
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc5d0)
    static Matrix4x4 *Transformation2DRot(
        Matrix4x4 *out, Vector2 const *scale, float const *rotation,
        Vector2 const *translation); // complex, unsure if correct
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc7a0)
    Matrix4x4 *Transformation2DSkew(
        Matrix4x4 *out, Vector2 const *scale, Vector2 const *rotation,
        Vector2 const *skew_maybe); // complex, unsure if correct
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bc970)
    void TransformVector2(Vector2 *out, Vector2 const *in,
                          Matrix4x4 const *matrix,
                          int include_translation); // complex
};

TEXT_ADDRESS_IGNORE_IN_DIFF(0x5bb3f0)
float Mat4x4MinorDeterminant(FPUVector const &param_1, FPUVector const &param_2,
                             FPUVector const &param_3);
