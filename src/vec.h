#pragma once
#include <cmath>
#include <iostream>
#include <sstream>


static bool equalFloats(const float a, const float b) {
    if (a > 0.0f && b < 0.0f || a < 0.0f && b > 0.0f) return false;
    return trunc(1000.0f * a) == trunc(1000.0f * b);
}

struct vec2 {
    float x, y;

    vec2();
    ~vec2();
    vec2(const float a, const float b);
    vec2(const vec2& v);
    void clean();
    vec2& operator= (const vec2& v);
    friend const vec2 operator+ (const vec2& v1, const vec2& v2);
    friend const vec2 operator- (const vec2& v1, const vec2& v2);
    friend const vec2 operator* (const vec2& v, const float k);
    friend const vec2 operator* (const float k, const vec2& v);

    friend void operator+= (vec2& v1, const vec2& v2);
    friend void operator-= (vec2& v1, const vec2& v2);
    friend void operator*= (vec2& v, const float k);

    friend const bool operator== (const vec2& v1, const vec2& v2);
    friend const bool operator!= (const vec2& v1, const vec2& v2);

    friend std::ostream& operator<< (std::ostream& os, const vec2& other);
    friend std::istream& operator>> (std::istream& is, vec2& other);
    friend std::stringstream& operator>> (std::stringstream& is, vec2& other);


    friend const vec2 lerp(const vec2& v0, const vec2& v1, const float k);
    friend const vec2 slerp(const vec2& v0, const vec2& v1, const float k);

    float quadrance() const;
    float norm() const;
    const vec2 normalize() const;
    float dot(const vec2& other) const;
};