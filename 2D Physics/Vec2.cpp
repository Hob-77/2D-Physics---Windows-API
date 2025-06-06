#include "Vec2.h"

// Constructors
Vec2::Vec2() : x(0.0f), y(0.0f) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

// Operator overloads
Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(float scalar) const {
    return Vec2(x / scalar, y / scalar);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2& Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

// Utility functions
float Vec2::Length() const {
    return std::sqrt(x * x + y * y);
}

float Vec2::LengthSquared() const {
    return x * x + y * y;
}

Vec2 Vec2::Normalized() const {
    float len = Length();
    if (len == 0.0f) return Vec2(0.0f, 0.0f);
    return *this / len;
}

float Vec2::Dot(const Vec2& rhs) const {
    return x * rhs.x + y * rhs.y;
}

// 2D "pseudo cross product"
float Vec2::Cross(const Vec2& rhs) const {
    return x * rhs.y - y * rhs.x;
}

float Vec2::Distance(const Vec2& a, const Vec2& b) {
    return (a - b).Length();
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}