#ifndef _AKSI_VEC2INT_CH_
#define _AKSI_VEC2INT_CH_

#include <iosfwd>


class Vector2Int {
public:
    int x, y;


    constexpr Vector2Int(int x=0, int y=0, int z=0) : x(x), y(y) {}


    constexpr Vector2Int operator+(const Vector2Int& i) const {
        return Vector2Int(x + i.x, y + i.y);
    }

    template <typename _Type>
    constexpr Vector2Int operator+(const _Type i) const {
        return Vector2Int(x + i, y + i);
    }

    constexpr void operator+=(const Vector2Int& i) {
        x += i.x;
        y += i.y;
    }

    template <typename _Type>
    constexpr void operator+=(const _Type i) {
        x += i;
        y += i;
    }

    constexpr Vector2Int operator-(const Vector2Int& i) const {
        return Vector2Int(x - i.x, y - i.y);
    }

    template <typename _Type>
    constexpr Vector2Int operator-(const _Type i) const {
        return Vector2Int(x - i, y - i);
    }

    constexpr void operator-=(const Vector2Int& i) {
        x -= i.x;
        y -= i.y;
    }

    template <typename _Type>
    constexpr void operator-=(const _Type i) {
        x -= i;
        y -= i;
    }

    constexpr Vector2Int operator*(const Vector2Int& i) const {
        return Vector2Int(x * i.x, y * i.y);
    }

    template <typename _Type>
    constexpr Vector2Int operator*(const _Type i) const {
        return Vector2Int(x * i, y * i);
    }

    constexpr void operator*=(const Vector2Int& i) {
        x *= i.x;
        y *= i.y;
    }

    template <typename _Type>
    constexpr void operator*=(const _Type i) {
        x *= i;
        y *= i;
    }

    constexpr Vector2Int operator/(const Vector2Int& i) const {
        return Vector2Int(x / i.x, y / i.y);
    }

    template <typename _Type>
    constexpr Vector2Int operator/(const _Type i) const {
        return Vector2Int(x / i, y / i);
    }

    constexpr void operator/=(const Vector2Int& i) {
        x /= i.x;
        y /= i.y;
    }

    template <typename _Type>
    constexpr void operator/=(const _Type i) {
        x /= i;
        y /= i;
    }

    bool operator==(const Vector2Int& i) const;

    bool operator!=(const Vector2Int& i) const;

    int& operator[](const int i);

    friend std::ostream& operator<<(std::ostream& os, const Vector2Int& i);


    float Magnitude() const;
};

#endif