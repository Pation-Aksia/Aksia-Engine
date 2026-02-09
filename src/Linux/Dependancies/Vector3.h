#ifndef _AKSI_VEC3_CH_
#define _AKSI_VEC3_CH_

#include <iosfwd>

class Vector3 {
public:
    float x, y, z;


    constexpr Vector3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}
    constexpr Vector3(const Vector2& i, float z) : x(i.x), y(i.y), z(z) {}
    constexpr Vector3(float x, const Vector2& i) : x(x), y(i.x), z(i.y) {}


    constexpr Vector3 operator+(const Vector3& i) const {
        return Vector3(x + i.x, y + i.y, z + i.z);
    }

    constexpr Vector3 operator+(const float i) const {
        return Vector3(x + i, y + i, z + i);
    }

    constexpr void operator+=(const Vector3& i) {
        x += i.x;
        y += i.y;
        z += i.z;
    }

    constexpr void operator+=(const float i) {
        x += i;
        y += i;
        z += i;
    }

    constexpr Vector3 operator-(const Vector3& i) const {
        return Vector3(x - i.x, y - i.y, z - i.z);
    }

    constexpr Vector3 operator-(const float i) const {
        return Vector3(x - i, y - i, z - i);
    }

    constexpr void operator-=(const Vector3& i) {
        x -= i.x;
        y -= i.y;
        z -= i.z;
    }

    constexpr void operator-=(const float i) {
        x -= i;
        y -= i;
        z -= i;
    }

    constexpr Vector3 operator*(const Vector3& i) const {
        return Vector3(x * i.x, y * i.y, z * i.z);
    }

    constexpr Vector3 operator*(const float i) const {
        return Vector3(x * i, y * i, z * i);
    }

    constexpr void operator*=(const Vector3& i) {
        x *= i.x;
        y *= i.y;
        z *= i.z;
    }

    constexpr void operator*=(const float i) {
        x *= i;
        y *= i;
        z *= i;
    }

    constexpr Vector3 operator/(const Vector3& i) const {
        return Vector3(x / i.x, y / i.y, z / i.z);
    }

    constexpr Vector3 operator/(const float i) const {
        return Vector3(x / i, y / i, z / i);
    }

    constexpr void operator/=(const Vector3& i) {
        x /= i.x;
        y /= i.y;
        z /= i.z;
    }

    constexpr void operator/=(const float i) {
        x /= i;
        y /= i;
        z /= i;
    }

    bool operator==(const Vector3& i) const;

    bool operator!=(const Vector3& i) const;

    float& operator[](const int i);

    friend std::ostream& operator<<(std::ostream& os, const Vector3& i);


    float Magnitude() const;
    
    Vector3 Normalised() const;

    float Dot(const Vector3& i) const;
    Vector3 Cross(const Vector3& i) const;

    Vector3 RotateX(const float angle) const;
    Vector3 RotateY(const float angle) const;
    Vector3 RotateZ(const float angle) const;
};

#endif
