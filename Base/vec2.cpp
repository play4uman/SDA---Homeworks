#include "vec2.h"
#include <cassert>
#include <cfloat>



vec2::vec2()
{
}

vec2::vec2(float x, float y) : x(x), y(y)
{
}

vec2::vec2(const vec2& other) : x(other.x), y(other.y)
{
}

vec2& vec2::operator= (const vec2& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

vec2& vec2::operator+=(const vec2& right)
{
    this->x = this->x + right.x;
    this->y = this->y + right.y;
    return *this;
}

vec2 vec2::operator+(const vec2& right) const
{
    return vec2(this->x + right.x, this->y + right.y);
}

vec2 vec2::operator-(const vec2& right) const
{
    return vec2(this->x - right.x, this->y - right.y);
}

vec2 vec2::operator-() const
{
	return vec2(-x, -y);
}

vec2 vec2::operator*(float a) const
{
    return vec2(this->x * a, this->y * a);
}

vec2 vec2::operator/(float a) const
{
	assert(a);
    return vec2(this->x / a, this->y / a);
}

bool vec2::operator==(const vec2& target) const
{
    return (fabs(this->x - target.x) < FLT_EPSILON)
        && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool vec2::operator!=(const vec2& target) const
{
    return !operator==(target);
}

bool vec2::equalWithEpsilon(const vec2& b, float epsilon) const
{
    if(x - epsilon <= b.x && b.x <= x + epsilon)
        if(y - epsilon <= b.y && b.y <= y + epsilon)
            return true;
    return false;
}

vec2 vec2::rotateByAngle(const vec2& pivot, float angle) const
{
    return pivot + (*this - pivot).rotate(angle);
}
