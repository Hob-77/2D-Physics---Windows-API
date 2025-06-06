#pragma once

#include <cmath> // Only used for sqrt (for now)

struct Vec2 {
    float x;
    float y;

    Vec2 operator-() const;

    // Constructors
    Vec2();                    // Zero vector
    Vec2(float x, float y);    // Custom vector

    // Arithmetic operators (immutable)
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;

    // Compound assignment (mutable)
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator*=(float scalar);
    Vec2& operator/=(float scalar);

    // Math utilities
    float Length() const;
    float LengthSquared() const;
    Vec2 Normalized() const;

    float Dot(const Vec2& rhs) const;
    float Cross(const Vec2& rhs) const;

    static float Distance(const Vec2& a, const Vec2& b);
};