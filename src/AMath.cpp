#include "AMath.h"

#include <cmath>
#include <limits>
#include <iostream>


bool AMath::ReliableFloatComp(float i, float j) {
    return (std::abs(i - j) <= std::numeric_limits<float>::epsilon() * std::max(std::abs(i), std::abs(j)));
}



constexpr Vector2::Vector2(const Vector3& i) : x(i.x), y(i.y) {}
constexpr Vector2::Vector2(const Vector4& i) : x(i.x), y(i.y) {}

bool Vector2::operator==(const Vector2& i) const {
    return AMath::ReliableFloatComp(x, i.x)
        && AMath::ReliableFloatComp(y, i.y);
}

bool Vector2::operator!=(const Vector2& i) const {
    return !(*this == i);
}

float& Vector2::operator[](const int i) {
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    default:
        std::cerr << "Vector2 array access only accepts range 0-1 inclusive! [" << i << "] is out of range" << std::endl;
        static thread_local float dummy = 0.0f;
        return dummy;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector2& i) {
    return os << '(' << i.x << ", " << i.y << ')';
}

float Vector2::Magnitude() const {
    return std::sqrt(x*x + y*y);
}

Vector2 Vector2::Normalised() const {
    float mag = (1.0f/this->Magnitude());
    return Vector2(x*mag, y*mag);
}

float Vector2::Dot(const Vector2& i) const {
    return (x*i.x)+(y*i.y);
}

float Vector2::Cross(const Vector2& i) const {
    return (x*i.y)-(y*i.x);
}

Vector2 Vector2::Rotate(float angle) const {
    return Vector2(
        (x*std::cos(angle)) - (y*std::sin(angle)),
        (x*std::sin(angle)) + (y*std::cos(angle))
    );
}



constexpr Vector3::Vector3(const Vector4& i) : x(i.x), y(i.y), z(i.z) {}

bool Vector3::operator==(const Vector3& i) const {
    return AMath::ReliableFloatComp(x, i.x)
        && AMath::ReliableFloatComp(y, i.y)
        && AMath::ReliableFloatComp(z, i.z);
}

bool Vector3::operator!=(const Vector3& i) const {
    return !(*this == i);
}

float& Vector3::operator[](const int i) {
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        std::cerr << "Vector3 array access only accepts range 0-2 inclusive! [" << i << "] is out of range" << std::endl;
        static thread_local float dummy = 0.0f;
        return dummy;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector3& i) {
    return os << '(' << i.x << ", " << i.y << ", " << i.z << ')';
}

float Vector3::Magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::Normalised() const {
    float mag = (1.0f/this->Magnitude());
    return Vector3(x*mag, y*mag, z*mag);
}

float Vector3::Dot(const Vector3& i) const {
    return (x*i.x)+(y*i.y)+(z*i.z);
}

Vector3 Vector3::Cross(const Vector3& i) const {
    return Vector3((y*i.z)-(z*i.y),
                   (z*i.x)-(x*i.z),
                   (x*i.y)-(y*i.x));
}

Vector3 Vector3::RotateX(float angle) const {
    return Vector3(
        x,
        (y*std::cos(angle)) - (z*std::sin(angle)),
        (y*std::sin(angle)) + (z*std::cos(angle))
    );
}

Vector3 Vector3::RotateY(float angle) const {
    return Vector3(
        (x*std::cos(angle)) - (z*std::sin(angle)),
        y,
        (x*std::sin(angle)) + (z*std::cos(angle))
    );
}

Vector3 Vector3::RotateZ(float angle) const {
    return Vector3(
        (x*std::cos(angle)) - (y*std::sin(angle)),
        (x*std::sin(angle)) + (y*std::cos(angle)),
        z
    );
}



bool Vector4::operator==(const Vector4& i) const {
    return AMath::ReliableFloatComp(x, i.x)
        && AMath::ReliableFloatComp(y, i.y)
        && AMath::ReliableFloatComp(z, i.z)
        && AMath::ReliableFloatComp(w, i.w);
}

bool Vector4::operator!=(const Vector4& i) const {
    return !(*this == i);
}

float& Vector4::operator[](const int i) {
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        std::cerr << "Vector4 array access only accepts range 0-3 inclusive! [" << i << "] is out of range" << std::endl;
        static thread_local float dummy = 0.0f;
        return dummy;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector4& i) {
    return os << '(' << i.x << ", " << i.y << ", " << i.z << ", " << i.w << ')';
}

float Vector4::Magnitude() const {
    return std::sqrt(x*x + y*y + z*z + w*w);
}

Vector4 Vector4::Normalised() const {
    float mag = (1.0f/this->Magnitude());
    return Vector4(x*mag, y*mag, z*mag, w*mag);
}

float Vector4::Dot(const Vector4& i) const {
    return (x*i.x)+(y*i.y)+(z*i.z)+(w*i.w);
}




bool Vector2Int::operator==(const Vector2Int& i) const {
    return x == i.x && y == i.y;
}

bool Vector2Int::operator!=(const Vector2Int& i) const {
    return !(*this == i);
}

int& Vector2Int::operator[](const int i) {
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    default:
        std::cerr << "Vector2Int array access only accepts range 0-1 inclusive! [" << i << "] is out of range" << std::endl;
        static thread_local int dummy = 0;
        return dummy;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector2Int& i) {
    return os << '(' << i.x << ", " << i.y << ')';
}

float Vector2Int::Magnitude() const {
    return std::sqrt(x*x + y*y);
}



bool Vector3Int::operator==(const Vector3Int& i) const {
    return x == i.x && y == i.y && z == i.z;
}

bool Vector3Int::operator!=(const Vector3Int& i) const {
    return !(*this == i);
}

int& Vector3Int::operator[](const int i) {
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        std::cerr << "Vector3Int array access only accepts range 0-2 inclusive! [" << i << "] is out of range" << std::endl;
        static thread_local int dummy = 0;
        return dummy;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector3Int& i) {
    return os << '(' << i.x << ", " << i.y << ", " << i.z << ')';
}

float Vector3Int::Magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
}



bool Vector4Int::operator==(const Vector4Int& i) const {
    return x == i.x && y == i.y && z == i.z && w == i.w;
}

bool Vector4Int::operator!=(const Vector4Int& i) const {
    return !(*this == i);
}

int& Vector4Int::operator[](const int i) {
    switch(i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        std::cerr << "Vector4Int array access only accepts range 0-3 inclusive! [" << i << "] is out of range" << std::endl;
        static thread_local int dummy = 0;
        return dummy;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector4Int& i) {
    return os << '(' << i.x << ", " << i.y << ", " << i.z << ", " << i.w << ')';
}

float Vector4Int::Magnitude() const {
    return std::sqrt(x*x + y*y + z*z + w*w);
}