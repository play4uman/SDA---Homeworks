#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Util.h"
#include <vector>

class Transform2;

class vec2
{
public:
    vec2();
	vec2(float _x, float _y);
    vec2(const vec2& other);

public:
    float x;
    float y;

public:
    vec2& operator= (const vec2& other);
    vec2 operator+(const vec2& right) const;
    vec2& operator+=(const vec2& right);
    vec2 operator-(const vec2& right) const;
    vec2 operator-() const;
    vec2 operator*(float a) const;
    vec2 operator/(float a) const;
    bool operator== (const vec2& target) const;
    bool operator!= (const vec2& target) const;

    bool equalWithEpsilon(const vec2& target, float epsilon = 0.01f) const;


    inline float getLength() const 
    {
        return sqrtf(x*x + y*y);
    }

    inline float getLengthSq() const 
    {
        return dot(*this);
    }

    inline float dot(const vec2& other) const 
    {
        return x*other.x + y*other.y;
    }

    inline vec2 getPerp() const 
    {
        return vec2(-y, x);
    }

    inline vec2 getRPerp() const 
    {
        return vec2(y, -x);
    }

    inline vec2 normalize() const 
    {
        float length = getLength();
        if(length == 0.f) return vec2(1.f, 0);
        return *this / getLength();
    }

    vec2 rotateByAngle(const vec2& pivot, float angle) const;

    inline vec2 rotate(float angle) const 
    {
        float cos = cosf(angle);
        float sin = sinf(angle);
        return vec2(x*cos - y*sin, x*sin + y*cos);
    }

    inline vec2& setMultiply(const Transform2& t0, const vec2& v1);

	inline static std::vector<vec2> getEdgesOfSquare(vec2 & centre, float radius)
	{
		std::vector<vec2> result;
		vec2 A(centre.x - radius, centre.y + radius); result.push_back(A);
		vec2 B(centre.x + radius, centre.y + radius); result.push_back(B);
		vec2 C(centre.x + radius, centre.y - radius); result.push_back(C);
		vec2 D(centre.x - radius, centre.y - radius); result.push_back(D);
		return result;
	}

	inline static bool doSquaresIntersect(std::vector<vec2>& staticSquare, std::vector<vec2>& toCheck)
	{
		vec2& A = staticSquare[0]; vec2& B = staticSquare[1];
		vec2& C = staticSquare[2]; vec2& D = staticSquare[3];

		for (vec2 vertex : toCheck)
		{
			if (vertex.x <= B.x && vertex.x >= A.x && vertex.y <= B.y && vertex.y >= C.y)
				return true;
		}
		return false;
	}
};

const vec2 vec2Zero = vec2(0.0f, 0.0f);
const vec2 vec2One = vec2(1.0f, 1.0f);
const vec2 vec2UnitX = vec2(1.0f, 0.0f);
const vec2 vec2UnitY = vec2(0.0f, 1.0f);

class Transform2
{
public:
    float m[2][3];

    inline Transform2() {}

    inline Transform2& setIdentity() 
    {
        m[0][0] = m[1][1] = 1.0f;
        m[0][1] = m[0][2] = m[1][0] = m[1][2] = 0.0f;
        return *this;
    }

    inline Transform2& setTranslation(const vec2& trans)
    {
        m[0][0] = m[1][1] = 1.0f;
        m[0][1] = m[1][0] = 0.0f;
        m[0][2] = trans.x;
        m[1][2] = trans.y;
        return *this;
    }

    inline Transform2& setTranslationOnly(const vec2& trans)
    {
        m[0][2] = trans.x;
        m[1][2] = trans.y;
        return *this;
    }

    inline vec2 getTranslation() const { return vec2(m[0][2], m[1][2]); }


    inline Transform2& setRotation(float angle)
    {
        m[0][0] = m[1][1] = cosf(angle);
        m[1][0] = sinf(angle);
        m[0][1] = -m[1][0];
        m[0][2] = m[1][2] = 0.0f;
        return *this;
    }

    inline Transform2 setRotationOnly(float angle)
    {
        vec2 scale = getScale();
        float c = cosf(angle);
        float s = sinf(angle);
        m[0][0] = c * scale.x;
        m[0][1] = -s * scale.x;
        m[1][0] = s * scale.y;
        m[1][1] = c * scale.y;
        return *this;
    }

    inline float getRotation() const
    {
        float scaleX = sqrtf(sqr(m[0][0]) + sqr(m[0][1]));
        float angle = acosf(m[0][0] / scaleX);
        if (m[1][0] < -EPS)
            angle = 2*(float)M_PI - angle;
        return angle;
    };

    inline Transform2& setScale(const vec2& scale)
    {
        m[0][0] = scale.x;
        m[1][1] = scale.y;
        m[0][1] = m[0][2] = m[1][0] = m[1][2] = 0.0f;
        return *this;
    }

    inline Transform2& setScaleOnly(const vec2& scale)
    {
        vec2 oldScale = getScale();
        float factorX = scale.x / oldScale.x;
        float factorY = scale.y / oldScale.y;
        m[0][0] *= factorX;
        m[0][1] *= factorX;
        m[1][0] *= factorY;
        m[1][1] *= factorY;
        return *this;
    }

    inline vec2 getScale() const
    {
        return vec2(sqrtf(sqr(m[0][0]) + sqr(m[0][1])),
                    sqrtf(sqr(m[1][0]) + sqr(m[1][1])));
    }

    inline Transform2& set(const vec2& trans, float angle, const vec2& scale)
    {
        float c = cosf(angle);
        float s = sinf(angle);
        m[0][0] = c * scale.x;
        m[0][1] = -s * scale.x;
        m[1][0] = s * scale.y;
        m[1][1] = c * scale.y;
        m[0][2] = trans.x;
        m[1][2] = trans.y;
        return *this;
    }

    inline Transform2& setMultiply(const Transform2& t0, const Transform2& t1)
    {
        for (int row = 0; row < 2; ++row)
        {
            m[row][0] = t0.m[row][0] * t1.m[0][0] + t0.m[row][1] * t1.m[1][0];
            m[row][1] = t0.m[row][0] * t1.m[0][1] + t0.m[row][1] * t1.m[1][1];
            m[row][2] = t0.m[row][0] * t1.m[0][2] + t0.m[row][1] * t1.m[1][2] + t0.m[row][2];
        }
        return *this;
    }

    inline Transform2& invert(const Transform2& t)
    {
        float invdet = 1.0f / (t.m[0][0] * t.m[1][1] - t.m[0][1] * t.m[1][0]);
        m[0][0] = t.m[1][1] * invdet;
        m[0][1] = -t.m[0][1] * invdet;
        m[0][2] = (t.m[0][1] * t.m[1][2] - t.m[0][2] * t.m[1][1]) * invdet;
        m[1][0] = -t.m[1][0] * invdet;
        m[1][1] = t.m[0][0] * invdet;
        m[1][2] = (t.m[0][2] * t.m[1][0] - t.m[0][0] * t.m[1][2]) * invdet;
        return *this;
    }

    inline Transform2 getInverse() const
    {
        Transform2 res;
        return res.invert(*this);
    }

    inline Transform2 operator*(const Transform2& t) const
    {
        Transform2 res;
        return res.setMultiply(*this, t);
    }

    inline vec2 operator*(const vec2& v) const
    {
        vec2 res;
        return res.setMultiply(*this, v);
    }

};

inline vec2& vec2::setMultiply(const Transform2& t0, const vec2& v1)
{
    x = t0.m[0][0] * v1.x + t0.m[0][1] * v1.y + t0.m[0][2];
    y = t0.m[1][0] * v1.x + t0.m[1][1] * v1.y + t0.m[1][2];
    return *this;
}


