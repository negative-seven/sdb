#pragma once

#include "declarations.h"

struct Vector2 {
    float x;
    float y;

    TEXT_ADDRESS(0x4736b0)
    ~Vector2();
    TEXT_ADDRESS(0x5be000)
    static float Dot(Vector2 const *left, Vector2 const *right);
    TEXT_ADDRESS(0x5be000)
    static Vector2 *Perpendicular(Vector2 *param_1, Vector2 const *param_2,
                                  int param_3);
    TEXT_ADDRESS(0x5be000) static float Length(Vector2 const *param_1);
    TEXT_ADDRESS(0x5be000) static float LengthSq(Vector2 const *param_1);
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5be000)
    static Vector2 *Normalize(Vector2 *out,
                              Vector2 const *in); // TODO: generates constants
    TEXT_ADDRESS(0x5be100) Vector2 operator-() const;
    TEXT_ADDRESS(0x5be130) Vector2 operator+() const;
    TEXT_ADDRESS(0x5be130) Vector2 operator+(Vector2 const &other) const;
    TEXT_ADDRESS(0x5be130) void operator+=(Vector2 const &other);
    TEXT_ADDRESS(0x5be130) Vector2 operator-(Vector2 const &other) const;
    TEXT_ADDRESS(0x5be130) void operator-=(Vector2 const &other);
    TEXT_ADDRESS(0x5be130) Vector2 operator*(float other) const;
    TEXT_ADDRESS(0x5be130) void operator*=(float other);
    TEXT_ADDRESS(0x5be130) Vector2 operator*(Vector2 const &other) const;
    TEXT_ADDRESS(0x5be130) void operator*=(Vector2 const &other);
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5be130)
    Vector2 operator/(float other) const; // TODO: generates constants
    TEXT_ADDRESS_IGNORE_IN_DIFF(0x5be270)
    void operator/=(float other); // TODO: generates constants
    TEXT_ADDRESS(0x5be270) Vector2 operator/(Vector2 const &other) const;
    TEXT_ADDRESS(0x5be270) void operator/=(Vector2 const &other);
    TEXT_ADDRESS(0x5be270) void operator=(Vector2 const &other);
    TEXT_ADDRESS(0x5be270) int operator==(Vector2 const &other) const;
    TEXT_ADDRESS(0x5be270) int operator!=(Vector2 const &other) const;
    TEXT_ADDRESS(0x5be270) operator float *();
    TEXT_ADDRESS(0x5be270) operator float const *() const;
    TEXT_ADDRESS(0x5be270) float *operator[](int index);
    TEXT_ADDRESS(0x5be270) const float *operator[](int index) const;
};
