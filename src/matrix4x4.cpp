#include "matrix4x4.h"

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
            return this->values[3][3] == other.values[3][3];
        }
        return false;
    }
    return false;
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

float Mat4x4MinorDeterminant(FPUVector const &param_1, FPUVector const &param_2,
                             FPUVector const &param_3) {
    return (param_1.values[2] * param_2.values[0] -
            param_2.values[2] * param_1.values[0]) *
               param_3.values[1] +
           (param_2.values[2] * param_1.values[1] -
            param_2.values[1] * param_1.values[2]) *
               param_3.values[0] +
           param_3.values[2] * (param_1.values[0] * param_2.values[1] -
                                param_1.values[1] * param_2.values[0]);
}
