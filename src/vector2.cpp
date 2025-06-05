#include <math.h>

#include "vector2.h"

float Vector2::Dot(Vector2 const *left, Vector2 const *right) {
    float x_product = left->x * right->x;
    float y_product = left->y * right->y;
    return x_product + y_product;
}

Vector2 *Vector2::Perpendicular(Vector2 *param_1, Vector2 const *param_2,
                                int param_3) {
    float fVar1;
    float fVar2;

    fVar1 = param_2->x;
    fVar2 = param_2->y;
    if (param_3 != 1) {
        param_1->x = -fVar2;
        param_1->y = fVar1;
        return param_1;
    }
    param_1->x = fVar2;
    param_1->y = -fVar1;
    return param_1;
}

float Vector2::Length(Vector2 const *param_1) {
    float x_squared = param_1->x * param_1->x;
    float y_squared = param_1->y * param_1->y;
    return sqrt(y_squared + x_squared);
}

float Vector2::LengthSq(Vector2 const *param_1) {
    float x_squared = param_1->x * param_1->x;
    float y_squared = param_1->y * param_1->y;
    return y_squared + x_squared;
}

Vector2 *Vector2::Normalize(Vector2 *out, Vector2 const *in) {
    float x = in->x;
    float y = in->y;
    float x_squared = x * x;
    float y_squared = y * y;
    float scale = 1.0f / sqrt(y_squared + x_squared);
    out->x = scale * x;
    out->y = scale * in->y;
    return out;
}

Vector2 Vector2::operator-() const {
    float x = -this->x;
    float y = -this->y;

    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

Vector2 Vector2::operator+() const { return *this; }

Vector2 Vector2::operator+(Vector2 const &other) const {
    float x = this->x + other.x;
    float y = this->y + other.y;

    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

void Vector2::operator+=(Vector2 const &other) {
    this->x += other.x;
    this->y += other.y;
}

Vector2 Vector2::operator-(Vector2 const &other) const {
    float x = this->x - other.x;
    float y = this->y - other.y;

    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

void Vector2::operator-=(Vector2 const &other) {
    this->x -= other.x;
    this->y -= other.y;
}

Vector2 Vector2::operator*(float other) const {
    Vector2 result;
    result.y = y * other;
    result.x = x * other;
    return result;
}

void Vector2::operator*=(float other) {
    this->x *= other;
    this->y *= other;
}

Vector2 Vector2::operator*(Vector2 const &other) const {
    float x = this->x * other.x;
    float y = this->y * other.y;

    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

void Vector2::operator*=(Vector2 const &other) {
    this->x *= other.x;
    this->y *= other.y;
}

Vector2 Vector2::operator/(float other) const { return *this * (1 / other); }

void Vector2::operator/=(float other) { *this *= 1 / other; }

Vector2 Vector2::operator/(Vector2 const &other) const {
    float x = this->x / other.x;
    float y = this->y / other.y;

    Vector2 result;
    result.x = x;
    result.y = y;
    return result;
}

void Vector2::operator/=(Vector2 const &other) {
    this->x /= other.x;
    this->y /= other.y;
}

void Vector2::operator=(Vector2 const &other) {
    x = other.x;
    y = other.y;
}

int Vector2::operator==(Vector2 const &other) const {
    return other.x == x && other.y == y;
}

int Vector2::operator!=(Vector2 const &other) const {
    return other.x != x || other.y != y;
}

Vector2::operator float *() { return &x; }

Vector2::operator float const *() const { return &x; }

float *Vector2::operator[](int index) {
    return &(static_cast<float *>(*this))[index];
}

const float *Vector2::operator[](int index) const {
    return &(static_cast<float const *>(*this))[index];
}
