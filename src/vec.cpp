#include "vec.h"

vec2::vec2() {
    x = 0;
    y = 0;
}

vec2::~vec2() {}

vec2::vec2(const float xI, const float yI) {
    x = xI;
    y = yI;
}

vec2::vec2(const vec2& v)
{
    x = v.x;
    y = v.y;
}
vec2& vec2::operator= (const vec2& v)
{
    x = v.x;
    y = v.y;
    return *this;
}

const vec2 operator+ (const vec2& v1, const vec2& v2) {
    return vec2(v1.x + v2.x, v1.y + v2.y);
}

const vec2 operator- (const vec2& v1, const vec2& v2) {
    return vec2(v1.x - v2.x, v1.y - v2.y);
}

const vec2 operator* (const vec2& v, const float k) {
    return vec2(v.x * k, v.y * k);
}

const vec2 operator* (const float k, const vec2& v) {
    return vec2(v.x * k, v.y * k);
}

void operator+= (vec2& v1, const vec2& v2)
{
    v1 = v1 + v2;
}

void operator-= (vec2& v1, const vec2& v2)
{
    v1 = v1 - v2;
}

void operator*= (vec2& v, const float k)
{
    v = v * k;
}

const bool operator== (const vec2& v1, const vec2& v2)
{
    return equalFloats(v1.x, v2.x) && equalFloats(v1.y, v2.y);
    //return v1.x == v2.x && v1.y == v2.y;
}

const bool operator!= (const vec2& v1, const vec2& v2)
{
    return !(v1 == v2);
}

float vec2::quadrance() const {
    return pow(x, 2) + pow(y, 2);
}

float vec2::norm() const {
    return float(sqrt(x * x + y * y));
}
const vec2 vec2::normalize() const {
    float n = norm();
    vec2 v = vec2();
    if (n != 0) {
        v.x = x / n;
        v.y = y / n;
    }
    return v;
}

float vec2::dot(const vec2& other) const {
    return (x * other.x + y * other.y);
}

std::ostream& operator<< (std::ostream& os, const vec2& other) {
    os << '(' << other.x << ',' << other.y << ')';
    return os;
}

std::istream& operator>> (std::istream& is, vec2& other) {
    is >> other.x;
    is >> other.y;
    return is;
}

std::stringstream& operator>> (std::stringstream& is, vec2& other) {
    is >> other.x;
    is >> other.y;
    return is;
}

void vec2::clean() {
    if (x > -1e-5 && x < 1e-5) x = 0;
    if (y > -1e-5 && y < 1e-5) y = 0;
}
