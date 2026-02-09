#ifndef _AKSI_VEC4INT_CH_
#define _AKSI_VEC4INT_CH_

#include <iosfwd>


class Vector4Int {
public:
    int x, y, z, w;


    constexpr Vector4Int(int x=0, int y=0, int z=0, int w=0) : x(x), y(y), z(z), w(w) {}


    constexpr Vector4Int operator+(const Vector4Int& i) const {
        return Vector4Int(x + i.x, y + i.y, z + i.z, w + i.w);
    }

    template <typename _Type>
    constexpr Vector4Int operator+(const _Type i) const {
        return Vector4Int(x + i, y + i, z + i, w+i);
    }

    constexpr void operator+=(const Vector4Int& i) {
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

    constexpr Vector4Int operator-(const Vector4Int& i) const {
        return Vector4Int(x - i.x, y - i.y, z - i.z, w - i.w);
    }

    template <typename _Type>
    constexpr Vector4Int operator-(const _Type i) const {
        return Vector4Int(x - i, y - i, z - i, w - i);
    }

    constexpr void operator-=(const Vector4Int& i) {
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

    constexpr Vector4Int operator*(const Vector4Int& i) const {
        return Vector4Int(x * i.x, y * i.y, z * i.z, w * i.w);
    }

    template <typename _Type>
    constexpr Vector4Int operator*(const _Type i) const {
        return Vector4Int(x * i, y * i, z * i, w * i);
    }

    constexpr void operator*=(const Vector4Int& i) {
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

    constexpr Vector4Int operator/(const Vector4Int& i) const {
        return Vector4Int(x / i.x, y / i.y, z / i.z, w / i.w);
    }

    template <typename _Type>
    constexpr Vector4Int operator/(const _Type i) const {
        return Vector4Int(x / i, y / i, z / i, w / i);
    }

    constexpr void operator/=(const Vector4Int& i) {
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

    bool operator==(const Vector4Int& i) const;

    bool operator!=(const Vector4Int& i) const;

    int& operator[](const int i);

    friend std::ostream& operator<<(std::ostream& os, const Vector4Int& i);


    float Magnitude() const;
};

#endif