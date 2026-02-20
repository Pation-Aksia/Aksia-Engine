#ifndef _AKSI_VEC4_CH_
#define _AKSI_VEC4_CH_

#include <iosfwd>


class Vector4 {
public:
    float x, y, z, w;


    constexpr Vector4(float x=0, float y=0, float z=0, float w=0) : x(x), y(y), z(z), w(w) {}

    constexpr Vector4(const Vector2& i, float z, float w) : x(i.x),   y(i.y),   z(z),   w(w) {}
    constexpr Vector4(float x, const Vector2& i, float w) : x(x),     y(i.x),   z(i.y), w(w) {}
    constexpr Vector4(float x, float y, const Vector2& i) : x(x),     y(y),     z(i.x), w(i.y) {}
    constexpr Vector4(const Vector2& i, const Vector2& j) : x(i.x),   y(i.y),   z(j.x), w(j.y) {}
    constexpr Vector4(const Vector3& i, float w)          : x(i.x),   y(i.y),   z(i.z), w(w) {}
    constexpr Vector4(float x, const Vector3& i)          : x(x),     y(i.x),   z(i.y), w(i.z) {}


    constexpr Vector4 operator+(const Vector4& i) const {
        return Vector4(x + i.x, y + i.y, z + i.z, w + i.w);
    }

    template <typename _Type>
    constexpr Vector4 operator+(const _Type i) const {
        return Vector4(x + i, y + i, z + i, w+i);
    }

    constexpr void operator+=(const Vector4& i) {
        x += i.x;
        y += i.y;
        z += i.z;
        w += i.w;
    }

    template <typename _Type>
    constexpr void operator+=(const _Type i) {
        x += i;
        y += i;
        z += i;
        w += i;
    }

    constexpr Vector4 operator-(const Vector4& i) const {
        return Vector4(x - i.x, y - i.y, z - i.z, w - i.w);
    }

    template <typename _Type>
    constexpr Vector4 operator-(const _Type i) const {
        return Vector4(x - i, y - i, z - i, w - i);
    }

    constexpr void operator-=(const Vector4& i) {
        x -= i.x;
        y -= i.y;
        z -= i.z;
        w -= i.w;
    }

    template <typename _Type>
    constexpr void operator-=(const _Type i) {
        x -= i;
        y -= i;
        z -= i;
        w -= i;
    }

    constexpr Vector4 operator*(const Vector4& i) const {
        return Vector4(x * i.x, y * i.y, z * i.z, w * i.w);
    }

    template <typename _Type>
    constexpr Vector4 operator*(const _Type i) const {
        return Vector4(x * i, y * i, z * i, w * i);
    }

    constexpr void operator*=(const Vector4& i) {
        x *= i.x;
        y *= i.y;
        z *= i.z;
        w *= i.w;
    }

    template <typename _Type>
    constexpr void operator*=(const _Type i) {
        x *= i;
        y *= i;
        z *= i;
        w *= i;
    }

    constexpr Vector4 operator/(const Vector4& i) const {
        return Vector4(x / i.x, y / i.y, z / i.z, w / i.w);
    }

    template <typename _Type>
    constexpr Vector4 operator/(const _Type i) const {
        return Vector4(x / i, y / i, z / i, w / i);
    }

    constexpr void operator/=(const Vector4& i) {
        x /= i.x;
        y /= i.y;
        z /= i.z;
        w /= i.w;
    }

    template <typename _Type>
    constexpr void operator/=(const _Type i) {
        x /= i;
        y /= i;
        z /= i;
        w /= i;
    }

    bool operator==(const Vector4& i) const;

    bool operator!=(const Vector4& i) const;

    float& operator[](const int i);

    friend std::ostream& operator<<(std::ostream& os, const Vector4& i);


    float Magnitude() const;
    
    Vector4 Normalised() const;

    float Dot(const Vector4& i) const;
};

#endif