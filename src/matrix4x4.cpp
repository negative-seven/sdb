#include "matrix4x4.h"
#include "fpu_vector.h"
#include <cmath>
#include <cstddef>

Matrix4x4::operator float *() { return *values; }

Matrix4x4::operator float const *() const { return *values; }

float *Matrix4x4::operator[](int index) { return values[(long long int)index]; }

float const *Matrix4x4::operator[](int index) const {
    return values[(long long int)index];
}

float *Matrix4x4::GetElement(unsigned char i, unsigned char j) {
    return &values[i][j];
}

float const *Matrix4x4::GetElement(unsigned char i, unsigned char j) const {
    return &values[i][j];
}

void Matrix4x4::operator=(Matrix4x4 const &other) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            values[j][i] = other.values[j][i];
        }
    }
}

int Matrix4x4::operator==(Matrix4x4 const &other) const {
    if (((((this->values[0][0] == other.values[0][0]) &&
           (this->values[1][0] == other.values[1][0])) &&
          (this->values[2][0] == other.values[2][0])) &&
         ((((this->values[3][0] == other.values[3][0] &&
             (this->values[0][1] == other.values[0][1])) &&
            ((this->values[1][1] == other.values[1][1] &&
              ((this->values[2][1] == other.values[2][1] &&
                (this->values[3][1] == other.values[3][1])))))) &&
           (this->values[0][2] == other.values[0][2])))) &&
        ((((this->values[1][2] == other.values[1][2] &&
            (this->values[2][2] == other.values[2][2])) &&
           (this->values[3][2] == other.values[3][2])) &&
          ((this->values[0][3] == other.values[0][3] &&
            (this->values[1][3] == other.values[1][3])))))) {
        if (this->values[2][3] == other.values[2][3]) {
            return static_cast<int>(this->values[3][3] == other.values[3][3]);
        }
        return 0;
    }
    return 0;
}

int Matrix4x4::operator!=(Matrix4x4 const &other) const {
    int eax = 1;
    if (((((this->values[0][0] != other.values[0][0]) ||
           (this->values[1][0] != other.values[1][0])) ||
          (this->values[2][0] != other.values[2][0])) ||
         (((this->values[3][0] != other.values[3][0] ||
            (this->values[0][1] != other.values[0][1])) ||
           ((this->values[1][1] != other.values[1][1] ||
             ((this->values[2][1] != other.values[2][1] ||
               (this->values[3][1] != other.values[3][1])))))))) ||
        ((this->values[0][2] != other.values[0][2] ||
          (((((this->values[1][2] != other.values[1][2] ||
               (this->values[2][2] != other.values[2][2])) ||
              (this->values[3][2] != other.values[3][2])) ||
             ((this->values[0][3] != other.values[0][3] ||
               (this->values[1][3] != other.values[1][3])))) ||
            (this->values[2][3] != other.values[2][3]))))) ||
        (this->values[3][3] != other.values[3][3])) {
        return eax;
    }
    return 0;
}

void Matrix4x4::operator*=(float other) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            values[j][i] *= other;
        }
    }
}

float Matrix4x4::Determinant(Matrix4x4 const *matrix) {
    return ((matrix->values[2][2] * matrix->values[3][0] -
             matrix->values[3][2] * matrix->values[2][0]) *
                matrix->values[1][3] +
            (matrix->values[2][3] * matrix->values[3][2] -
             matrix->values[3][3] * matrix->values[2][2]) *
                matrix->values[1][0] +
            matrix->values[1][2] *
                (matrix->values[2][3] * matrix->values[3][0] +
                 matrix->values[3][3] * matrix->values[2][0])) *
               matrix->values[0][1] +
           (((matrix->values[3][3] * matrix->values[2][2] -
              matrix->values[2][3] * matrix->values[3][2]) *
                 matrix->values[1][1] -
             (matrix->values[3][1] * matrix->values[2][3] +
              matrix->values[2][1] * matrix->values[3][3]) *
                 matrix->values[1][2]) +
            (matrix->values[2][1] * matrix->values[3][2] -
             matrix->values[3][1] * matrix->values[2][2]) *
                matrix->values[1][3]) *
               matrix->values[0][0] +
           (((matrix->values[2][1] * matrix->values[3][3] -
              matrix->values[3][1] * matrix->values[2][3]) *
                 matrix->values[1][0] -
             (matrix->values[2][3] * matrix->values[3][0] +
              matrix->values[3][3] * matrix->values[2][0]) *
                 matrix->values[1][1]) +
            (matrix->values[3][1] * matrix->values[2][0] -
             matrix->values[2][1] * matrix->values[3][0]) *
                matrix->values[1][3]) *
               matrix->values[0][2] +
           ((matrix->values[2][1] * matrix->values[3][0] -
             matrix->values[3][1] * matrix->values[2][0]) *
                matrix->values[1][2] +
            (matrix->values[3][1] * matrix->values[2][2] -
             matrix->values[2][1] * matrix->values[3][2]) *
                matrix->values[1][0] +
            (matrix->values[2][2] * matrix->values[3][0] +
             matrix->values[3][2] * matrix->values[2][0]) *
                matrix->values[1][1]) *
               matrix->values[0][3];
}

Matrix4x4 *Matrix4x4::Inverse(Matrix4x4 *out, Matrix4x4 const *in) {
    float determinant = Determinant(in);
    if (determinant == 0.0) {
        return NULL;
    }
    determinant = 1.0 / determinant;
    out->values[0][0] = ((in->values[3][1] * in->values[1][2] -
                          in->values[3][2] * in->values[1][1]) *
                             in->values[2][3] +
                         (in->values[2][1] * in->values[3][2] -
                          in->values[3][1] * in->values[2][2]) *
                             in->values[1][3] +
                         (in->values[2][2] * in->values[1][1] -
                          in->values[1][2] * in->values[2][1]) *
                             in->values[3][3]) *
                        determinant;
    out->values[0][1] = -((in->values[3][1] * in->values[0][2] -
                           in->values[3][2] * in->values[0][1]) *
                              in->values[2][3] +
                          (in->values[2][1] * in->values[3][2] -
                           in->values[3][1] * in->values[2][2]) *
                              in->values[0][3] +
                          (in->values[2][2] * in->values[0][1] -
                           in->values[0][2] * in->values[2][1]) *
                              in->values[3][3]) *
                        determinant;
    out->values[0][2] = ((in->values[3][1] * in->values[0][2] -
                          in->values[3][2] * in->values[0][1]) *
                             in->values[1][3] +
                         (in->values[1][1] * in->values[3][2] -
                          in->values[3][1] * in->values[1][2]) *
                             in->values[0][3] +
                         (in->values[1][2] * in->values[0][1] -
                          in->values[0][2] * in->values[1][1]) *
                             in->values[3][3]) *
                        determinant;
    out->values[0][3] = -((in->values[2][1] * in->values[0][2] -
                           in->values[2][2] * in->values[0][1]) *
                              in->values[1][3] +
                          (in->values[1][1] * in->values[2][2] -
                           in->values[2][1] * in->values[1][2]) *
                              in->values[0][3] +
                          (in->values[1][2] * in->values[0][1] -
                           in->values[0][2] * in->values[1][1]) *
                              in->values[2][3]) *
                        determinant;
    out->values[1][0] = -((in->values[3][0] * in->values[1][2] -
                           in->values[3][2] * in->values[1][0]) *
                              in->values[2][3] +
                          (in->values[2][0] * in->values[3][2] -
                           in->values[3][0] * in->values[2][2]) *
                              in->values[1][3] +
                          (in->values[2][2] * in->values[1][0] -
                           in->values[1][2] * in->values[2][0]) *
                              in->values[3][3]) *
                        determinant;
    out->values[1][1] = ((in->values[3][0] * in->values[0][2] -
                          in->values[3][2] * in->values[0][0]) *
                             in->values[2][3] +
                         (in->values[2][0] * in->values[3][2] -
                          in->values[3][0] * in->values[2][2]) *
                             in->values[0][3] +
                         (in->values[2][2] * in->values[0][0] -
                          in->values[0][2] * in->values[2][0]) *
                             in->values[3][3]) *
                        determinant;
    out->values[1][2] = -((in->values[3][0] * in->values[0][2] -
                           in->values[3][2] * in->values[0][0]) *
                              in->values[1][3] +
                          (in->values[1][0] * in->values[3][2] -
                           in->values[3][0] * in->values[1][2]) *
                              in->values[0][3] +
                          (in->values[1][2] * in->values[0][0] -
                           in->values[0][2] * in->values[1][0]) *
                              in->values[3][3]) *
                        determinant;
    out->values[1][3] = ((in->values[2][0] * in->values[0][2] -
                          in->values[2][2] * in->values[0][0]) *
                             in->values[1][3] +
                         (in->values[1][0] * in->values[2][2] -
                          in->values[2][0] * in->values[1][2]) *
                             in->values[0][3] +
                         (in->values[1][2] * in->values[0][0] -
                          in->values[0][2] * in->values[1][0]) *
                             in->values[2][3]) *
                        determinant;
    out->values[2][0] = ((in->values[3][0] * in->values[1][1] -
                          in->values[3][1] * in->values[1][0]) *
                             in->values[2][3] +
                         (in->values[2][0] * in->values[3][1] -
                          in->values[3][0] * in->values[2][1]) *
                             in->values[1][3] +
                         (in->values[2][1] * in->values[1][0] -
                          in->values[1][1] * in->values[2][0]) *
                             in->values[3][3]) *
                        determinant;
    out->values[2][1] = -((in->values[3][0] * in->values[0][1] -
                           in->values[3][1] * in->values[0][0]) *
                              in->values[2][3] +
                          (in->values[2][0] * in->values[3][1] -
                           in->values[3][0] * in->values[2][1]) *
                              in->values[0][3] +
                          (in->values[2][1] * in->values[0][0] -
                           in->values[0][1] * in->values[2][0]) *
                              in->values[3][3]) *
                        determinant;
    out->values[2][2] = ((in->values[3][0] * in->values[0][1] -
                          in->values[3][1] * in->values[0][0]) *
                             in->values[1][3] +
                         (in->values[1][0] * in->values[3][1] -
                          in->values[3][0] * in->values[1][1]) *
                             in->values[0][3] +
                         (in->values[1][1] * in->values[0][0] -
                          in->values[0][1] * in->values[1][0]) *
                             in->values[3][3]) *
                        determinant;
    out->values[2][3] = -((in->values[2][0] * in->values[0][1] -
                           in->values[2][1] * in->values[0][0]) *
                              in->values[1][3] +
                          (in->values[1][0] * in->values[2][1] -
                           in->values[2][0] * in->values[1][1]) *
                              in->values[0][3] +
                          (in->values[1][1] * in->values[0][0] -
                           in->values[0][1] * in->values[1][0]) *
                              in->values[2][3]) *
                        determinant;
    out->values[3][0] = -((in->values[3][0] * in->values[1][1] -
                           in->values[3][1] * in->values[1][0]) *
                              in->values[2][2] +
                          (in->values[2][0] * in->values[3][1] -
                           in->values[3][0] * in->values[2][1]) *
                              in->values[1][2] +
                          (in->values[2][1] * in->values[1][0] -
                           in->values[1][1] * in->values[2][0]) *
                              in->values[3][2]) *
                        determinant;
    out->values[3][1] = ((in->values[3][0] * in->values[0][1] -
                          in->values[3][1] * in->values[0][0]) *
                             in->values[2][2] +
                         (in->values[2][0] * in->values[3][1] -
                          in->values[3][0] * in->values[2][1]) *
                             in->values[0][2] +
                         (in->values[2][1] * in->values[0][0] -
                          in->values[0][1] * in->values[2][0]) *
                             in->values[3][2]) *
                        determinant;
    out->values[3][2] = -((in->values[3][0] * in->values[0][1] -
                           in->values[3][1] * in->values[0][0]) *
                              in->values[1][2] +
                          (in->values[1][0] * in->values[3][1] -
                           in->values[3][0] * in->values[1][1]) *
                              in->values[0][2] +
                          (in->values[1][1] * in->values[0][0] -
                           in->values[0][1] * in->values[1][0]) *
                              in->values[3][2]) *
                        determinant;
    out->values[3][3] = ((in->values[2][0] * in->values[0][1] -
                          in->values[2][1] * in->values[0][0]) *
                             in->values[1][2] +
                         (in->values[1][0] * in->values[2][1] -
                          in->values[2][0] * in->values[1][1]) *
                             in->values[0][2] +
                         (in->values[1][1] * in->values[0][0] -
                          in->values[0][1] * in->values[1][0]) *
                             in->values[2][2]) *
                        determinant;
    return out;
}

Matrix4x4 *Matrix4x4::Multiply(Matrix4x4 *out, Matrix4x4 const *left,
                               Matrix4x4 const *right) {
    out->values[0][0] = right->values[0][0] * left->values[0][0] +
                        right->values[0][1] * left->values[1][0] +
                        right->values[0][2] * left->values[2][0] +
                        right->values[0][3] * left->values[3][0];
    out->values[1][0] = right->values[1][0] * left->values[0][0] +
                        right->values[1][1] * left->values[1][0] +
                        right->values[1][2] * left->values[2][0] +
                        right->values[1][3] * left->values[3][0];
    out->values[2][0] = right->values[2][0] * left->values[0][0] +
                        right->values[2][1] * left->values[1][0] +
                        right->values[2][2] * left->values[2][0] +
                        right->values[2][3] * left->values[3][0];
    out->values[3][0] = left->values[0][0] * right->values[3][0] +
                        left->values[1][0] * right->values[3][1] +
                        left->values[2][0] * right->values[3][2] +
                        left->values[3][0] * right->values[3][3];
    out->values[0][1] = left->values[0][1] * right->values[0][0] +
                        left->values[1][1] * right->values[0][1] +
                        right->values[0][2] * left->values[2][1] +
                        right->values[0][3] * left->values[3][1];
    out->values[1][1] = right->values[1][0] * left->values[0][1] +
                        right->values[1][1] * left->values[1][1] +
                        right->values[1][2] * left->values[2][1] +
                        right->values[1][3] * left->values[3][1];
    out->values[2][1] = right->values[2][0] * left->values[0][1] +
                        right->values[2][1] * left->values[1][1] +
                        right->values[2][2] * left->values[2][1] +
                        right->values[2][3] * left->values[3][1];
    out->values[3][1] = left->values[0][1] * right->values[3][0] +
                        left->values[1][1] * right->values[3][1] +
                        left->values[2][1] * right->values[3][2] +
                        left->values[3][1] * right->values[3][3];
    out->values[0][2] = left->values[0][2] * right->values[0][0] +
                        left->values[1][2] * right->values[0][1] +
                        right->values[0][2] * left->values[2][2] +
                        right->values[0][3] * left->values[3][2];
    out->values[1][2] = right->values[1][0] * left->values[0][2] +
                        right->values[1][1] * left->values[1][2] +
                        right->values[1][2] * left->values[2][2] +
                        right->values[1][3] * left->values[3][2];
    out->values[2][2] = right->values[2][0] * left->values[0][2] +
                        right->values[2][1] * left->values[1][2] +
                        right->values[2][2] * left->values[2][2] +
                        right->values[2][3] * left->values[3][2];
    out->values[3][2] = left->values[0][2] * right->values[3][0] +
                        left->values[1][2] * right->values[3][1] +
                        left->values[2][2] * right->values[3][2] +
                        left->values[3][2] * right->values[3][3];
    out->values[0][3] = right->values[0][0] * left->values[0][3] +
                        right->values[0][1] * left->values[1][3] +
                        left->values[2][3] * right->values[0][2] +
                        left->values[3][3] * right->values[0][3];
    out->values[1][3] = left->values[0][3] * right->values[1][0] +
                        left->values[1][3] * right->values[1][1] +
                        left->values[2][3] * right->values[1][2] +
                        left->values[3][3] * right->values[1][3];
    out->values[2][3] = left->values[0][3] * right->values[2][0] +
                        left->values[1][3] * right->values[2][1] +
                        left->values[2][3] * right->values[2][2] +
                        left->values[3][3] * right->values[2][3];
    out->values[3][3] = left->values[0][3] * right->values[3][0] +
                        left->values[1][3] * right->values[3][1] +
                        left->values[2][3] * right->values[3][2] +
                        left->values[3][3] * right->values[3][3];
    return out;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 const &other) const {
    Matrix4x4 result;
    // TODO
    // Multiply(&result, this, &other);
    return result;
}

void Matrix4x4::operator*=(Matrix4x4 const &other) {
    Multiply(this, this, &other);
}

void Matrix4x4::ConvertToRotationMatrix(Matrix4x4 *result,
                                        TQuaternion const *quaternion) {
    float a = quaternion->a;
    float b = quaternion->b;
    float c = quaternion->c;
    float d = quaternion->d;

    result->values[0][0] = 1.0 - (b * b + c * c) * 2;
    result->values[0][1] = (b * a - c * d) * 2;
    result->values[0][2] = (b * d + c * a) * 2;
    result->values[0][3] = 0.0;
    result->values[1][0] = (c * d + b * a) * 2;
    result->values[1][1] = 1.0 - (a * a + c * c) * 2;
    result->values[1][2] = (c * b - a * d) * 2;
    result->values[1][3] = 0.0;
    result->values[2][0] = (c * a - b * d) * 2;
    result->values[2][1] = (a * d + c * b) * 2;
    result->values[2][2] = 1.0 - (a * a + b * b) * 2;
    result->values[2][3] = 0.0;
    result->values[3][0] = 0.0;
    result->values[3][1] = 0.0;
    result->values[3][2] = 0.0;
    result->values[3][3] = 1.0;
}

Matrix4x4 *Matrix4x4::ConvertToRotationMatrix(Matrix4x4 *result, float angle) {
    float sin_angle;
    float cos_angle;
    sincosf(angle, &sin_angle, &cos_angle);

    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            result->values[i][j] = 0;
        }
    }

    result->values[0][0] = 1;
    result->values[1][1] = 1;
    result->values[2][2] = 1;
    result->values[3][3] = 1;

    result->values[0][0] = cos_angle;
    result->values[0][1] = -sin_angle;
    result->values[1][0] = sin_angle;
    result->values[1][1] = cos_angle;

    return result;
}

Matrix4x4 *Matrix4x4::ConvertToScalingMatrix(Matrix4x4 *result,
                                             FPUVector const *scale) {
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            result->values[i][j] = 0;
        }
    }

    result->values[0][0] = 1;
    result->values[1][1] = 1;
    result->values[2][2] = 1;
    result->values[3][3] = 1;

    result->values[0][0] = scale->values[0];
    result->values[1][1] = scale->values[1];
    result->values[2][2] = scale->values[2];
    return result;
}

Matrix4x4 *Matrix4x4::ConvertToScalingMatrix(Matrix4x4 *result,
                                             Vector2 const *scale) {
    FPUVector fpu_vector = FPUVector{scale->x, scale->y, 0};
    return ConvertToScalingMatrix(result, &fpu_vector);
}

Matrix4x4 *Matrix4x4::ConvertToTranslationMatrix(Matrix4x4 *result,
                                                 FPUVector const *translation) {
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            result->values[i][j] = 0;
        }
    }

    result->values[0][0] = 1;
    result->values[1][1] = 1;
    result->values[2][2] = 1;
    result->values[3][3] = 1;

    result->values[0][3] = translation->values[0];
    result->values[1][3] = translation->values[1];
    result->values[2][3] = translation->values[2];

    return result;
}

Matrix4x4 *Matrix4x4::Transformation3D(Matrix4x4 *out, FPUVector const *scale,
                                       TQuaternion const *rotation,
                                       FPUVector const *translation) {
    Matrix4x4 left;
    Matrix4x4 right;

    if (scale == NULL) {
        left.values[0][0] = 1.0;
        left.values[0][1] = 0.0;
        left.values[1][0] = 0.0;
        left.values[1][1] = 1.0;
        left.values[2][0] = 1.0;
        left.values[2][1] = 0.0;
    } else {
        left.values[0][0] = scale->values[0];
        left.values[0][1] = 0.0;
        left.values[1][0] = 0.0;
        left.values[1][1] = scale->values[1];
        left.values[2][0] = scale->values[2];
        left.values[2][1] = 0.0;
    }

    if (rotation == NULL) {
        right.values[0][0] = 1.0;
        right.values[0][1] = 0.0;
        right.values[0][2] = 0.0;
        right.values[0][3] = 0.0;
        right.values[1][0] = 0.0;
        right.values[1][1] = 1.0;
        right.values[1][2] = 0.0;
        right.values[1][3] = 0.0;
        right.values[2][0] = 0.0;
        right.values[2][1] = 0.0;
        right.values[2][2] = 1.0;
        right.values[2][3] = 0.0;
    } else {
        float a = rotation->a;
        float b = rotation->b;
        float c = rotation->c;
        float d = rotation->d;
        right.values[0][1] = (a * b - d * c) * 2;
        right.values[0][0] = 1.0 - (c * c + c * c + b * b + b * b);
        right.values[2][3] = 0.0;
        right.values[2][2] = (-a * a - a * a - b * b + b * b) + 1.0;
        right.values[1][1] = (-a * a - a * a - c * c + c * c) + 1.0;
        right.values[1][0] = (d * c + a * b) * 2;
        right.values[0][3] = 0.0;
        right.values[0][2] = (d * b + a * c) * 2;
        right.values[2][1] = (a * d + b * c) * 2;
        right.values[2][0] = (a * c - d * b) * 2;
        right.values[1][3] = 0.0;
        right.values[1][2] = (b * c - a * d) * 2;
    }

    left.values[0][2] = 0.0;
    left.values[0][3] = 0.0;
    left.values[2][0] = 0.0;
    left.values[2][1] = 0.0;
    left.values[1][2] = 0.0;
    left.values[1][3] = 0.0;
    left.values[3][0] = 0.0;
    left.values[3][1] = 0.0;
    left.values[3][2] = 0.0;
    left.values[3][3] = 1.0;
    right.values[3][0] = 0.0;
    right.values[3][1] = 0.0;
    right.values[3][2] = 0.0;
    right.values[3][3] = 1.0;

    Multiply(out, &left, &right);

    if (translation != NULL) {
        out->values[0][3] = translation->values[0];
        out->values[1][3] = translation->values[1];
        out->values[2][3] = translation->values[2];
    }

    return out;
}

Matrix4x4 *Matrix4x4::Transformation2DRot(Matrix4x4 *out, Vector2 const *scale,
                                          float const *rotation,
                                          Vector2 const *translation) {
    float scale_y;
    float scale_x;
    if (scale == NULL) {
        out->values[0][0] = 1.0;
        out->values[1][1] = 1.0;

        scale_x = 1.0;
        scale_y = 1.0;
    } else {
        out->values[0][0] = scale->x;
        out->values[1][1] = scale->y;

        scale_x = scale->x;
        scale_y = scale->y;
    }
    out->values[0][1] = 0.0;
    out->values[1][0] = 0.0;
    out->values[2][0] = 0.0;
    out->values[2][1] = 0.0;
    out->values[3][0] = 0.0;
    out->values[3][1] = 0.0;

    if (rotation != NULL) {
        out->values[0][0] = (cos(*rotation) * scale_x);
        out->values[0][1] = (sin(*rotation) * -scale_y);
        out->values[1][0] = (sin(*rotation) * scale_x);
        out->values[1][1] = (cos(*rotation) * scale_y);
    }

    if (translation == (Vector2 *)0x0) {
        out->values[0][3] = 0.0;
        out->values[1][3] = 0.0;
    } else {
        out->values[0][3] = translation->x;
        out->values[1][3] = translation->y;
    }

    out->values[2][3] = 0.0;
    out->values[3][3] = 1.0;
    out->values[0][2] = 0.0;
    out->values[1][2] = 0.0;
    out->values[2][2] = 1.0;
    out->values[3][2] = 0.0;

    return out;
}

Matrix4x4 *Matrix4x4::Transformation2DSkew(Matrix4x4 *out, Vector2 const *scale,
                                           Vector2 const *rotation,
                                           Vector2 const *skew_maybe) {
    float scale_y;
    float scale_x;
    if (scale == NULL) {
        out->values[0][0] = 1.0;
        out->values[1][1] = 1.0;

        scale_x = 1.0;
        scale_y = 1.0;
    } else {
        out->values[0][0] = scale_x;
        out->values[1][1] = scale_y;

        scale_x = scale->x;
        scale_y = scale->y;
    }
    out->values[0][1] = 0.0;
    out->values[1][0] = 0.0;
    out->values[2][0] = 0.0;
    out->values[2][1] = 0.0;
    out->values[3][0] = 0.0;
    out->values[3][1] = 0.0;

    if (rotation != NULL) {
        out->values[0][0] = (float)(cos(rotation->y) * (double)scale_x);
        out->values[0][1] = (float)(sin(rotation->x) * (double)-scale_y);
        out->values[1][0] = (float)(sin(rotation->y) * (double)scale_x);
        out->values[1][1] = (float)(cos(rotation->x) * (double)scale_y);
    }

    if (skew_maybe == NULL) {
        out->values[0][3] = 0.0;
        out->values[1][3] = 0.0;
        out->values[2][3] = 0.0;
        out->values[3][3] = 1.0;
    } else {
        out->values[0][3] = skew_maybe->x;
        out->values[1][3] = skew_maybe->y;
        out->values[2][3] = 0.0;
        out->values[3][3] = 1.0;
    }

    out->values[0][2] = 0.0;
    out->values[1][2] = 0.0;
    out->values[2][2] = 1.0;
    out->values[3][2] = 0.0;

    return out;
}

void Matrix4x4::TransformVector2(Vector2 *out, Vector2 const *in,
                                 Matrix4x4 const *matrix,
                                 int include_translation) {
    float translation_x;
    float translation_y;
    if (include_translation == 1) {
        translation_x = matrix->values[0][3];
        translation_y = matrix->values[1][3];
    } else {
        translation_x = 0;
        translation_y = 0;
    }

    out->x = in->x * matrix->values[0][0] + in->y * matrix->values[0][1] +
             translation_x;
    out->y = in->x * matrix->values[1][0] + in->y * matrix->values[1][1] +
             translation_y;
}

float Mat4x4MinorDeterminant(FPUVector const &a, FPUVector const &b,
                             FPUVector const &c) {
    return (a.values[1] * b.values[2] - a.values[2] * b.values[1]) *
               c.values[0] +
           (a.values[2] * b.values[0] - a.values[0] * b.values[2]) *
               c.values[1] +
           (a.values[0] * b.values[1] - a.values[1] * b.values[0]) *
               c.values[2];
}
