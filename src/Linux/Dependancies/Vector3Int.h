#ifndef _AKSI_VEC3INT_CH_
#define _AKSI_VEC3INT_CH_

#include <iosfwd>


class Vector3Int {
public:
    int x, y, z;


    constexpr Vector3Int(int x=0, int y=0, int z=0) : x(x), y(y), z(z) {}


    constexpr Vector3Int operator+(const Vector3Int& i) const {
        return Vector3Int(x + i.x, y + i.y, z + i.z);
    }

    template <typename _Type>
    constexpr Vector3Int operator+(const _Type i) const {
        return Vector3Int(x + i, y + i, z + i);
    }

    constexpr void operator+=(const Vector3Int& i) {
        x += i.x;
        y += i.y;
        z += i.z;
    }

    template <typename _Type>
    constexpr void operator+=(const _Type i) {
        x += i;
        y += i;
        z += i;
    }

    constexpr Vector3Int operator-(const Vector3Int& i) const {
        return Vector3Int(x - i.x, y - i.y, z - i.z);
    }

    template <typename _Type>
    constexpr Vector3Int operator-(const _Type i) const {
        return Vector3Int(x - i, y - i, z - i);
    }

    constexpr void operator-=(const Vector3Int& i) {
        x -= i.x;
        y -= i.y;
        z -= i.z;
    }

    template <typename _Type>
    constexpr void operator-=(const _Type i) {
        x -= i;
        y -= i;
        z -= i;
    }

    constexpr Vector3Int operator*(const Vector3Int& i) const {
        return Vector3Int(x * i.x, y * i.y, z * i.z);
    }

    template <typename _Type>
    constexpr Vector3Int operator*(const _Type i) const {
        return Vector3Int(x * i, y * i, z * i);
    }

    constexpr void operator*=(const Vector3Int& i) {
        x *= i.x;
        y *= i.y;
        z *= i.z;
    }

    template <typename _Type>
    constexpr void operator*=(const _Type i) {
        x *= i;
        y *= i;
        z *= i;
    }

    constexpr Vector3Int operator/(const Vector3Int& i) const {
        return Vector3Int(x / i.x, y / i.y, z / i.z);
    }

    template <typename _Type>
    constexpr Vector3Int operator/(const _Type i) const {
        return Vector3Int(x / i, y / i, z / i);
    }

    constexpr void operator/=(const Vector3Int& i) {
        x /= i.x;
        y /= i.y;
        z /= i.z;
    }
    
    template <typename _Type>
    constexpr void operator/=(const _Type i) {
        x /= i;
        y /= i;
        z /= i;
    }

    bool operator==(const Vector3Int& i) const;

    bool operator!=(const Vector3Int& i) const;

    int& operator[](const int i);

    friend std::ostream& operator<<(std::ostream& os, const Vector3Int& i);


    float Magnitude() const;
};

#endif
