#ifndef _AKSI_VEC2_CH_
#define _AKSI_VEC2_CH_

#include <iosfwd>


class Vector3;
class Vector4;

class Vector2 {
public:
    float x, y;


    constexpr Vector2(float x=0, float y=0, float z=0) : x(x), y(y) {}

    constexpr Vector2(const Vector3& i);
    constexpr Vector2(const Vector4& i);


    constexpr Vector2 operator+(const Vector2& i) const {
        return Vector2(x + i.x, y + i.y);
    }

    template <typename _Type>
    constexpr Vector2 operator+(const _Type i) const {
        return Vector2(x + i, y + i);
    }

    constexpr void operator+=(const Vector2& i) {
        x += i.x;
        y += i.y;
    }

    template <typename _Type>
    constexpr void operator+=(const _Type i) {
        x += i;
        y += i;
    }

    constexpr Vector2 operator-(const Vector2& i) const {
        return Vector2(x - i.x, y - i.y);
    }

    template <typename _Type>
    constexpr Vector2 operator-(const _Type i) const {
        return Vector2(x - i, y - i);
    }

    constexpr void operator-=(const Vector2& i) {
        x -= i.x;
        y -= i.y;
    }

    template <typename _Type>
    constexpr void operator-=(const _Type i) {
        x -= i;
        y -= i;
    }

    constexpr Vector2 operator*(const Vector2& i) const {
        return Vector2(x * i.x, y * i.y);
    }

    template <typename _Type>
    constexpr Vector2 operator*(const _Type i) const {
        return Vector2(x * i, y * i);
    }

    constexpr void operator*=(const Vector2& i) {
        x *= i.x;
        y *= i.y;
    }

    template <typename _Type>
    constexpr void operator*=(const _Type i) {
        x *= i;
        y *= i;
    }

    constexpr Vector2 operator/(const Vector2& i) const {
        return Vector2(x / i.x, y / i.y);
    }

    template <typename _Type>
    constexpr Vector2 operator/(const _Type i) const {
        return Vector2(x / i, y / i);
    }

    constexpr void operator/=(const Vector2& i) {
        x /= i.x;
        y /= i.y;
    }

    template <typename _Type>
    constexpr void operator/=(const _Type i) {
        x /= i;
        y /= i;
    }

    bool operator==(const Vector2& i) const;

    bool operator!=(const Vector2& i) const;

    float& operator[](const int i);

    friend std::ostream& operator<<(std::ostream& os, const Vector2& i);


    float Magnitude() const;
    
    Vector2 Normalised() const;

    float Dot(const Vector2& i) const;
    float Cross(const Vector2& i) const;

    Vector2 Rotate(const float angle) const;
};

#endif