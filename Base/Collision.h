#pragma once
#include "vec2.h"

struct OBB
{
    // Transform that maps the AABB[(-1,-1)->(1,1)] to the OBB
    Transform2 m_transform;

    OBB() {}
    OBB(const vec2& min, const vec2& max, float angle) { set(min, max, angle); }

    OBB& set(const vec2& min, const vec2& max, float angle) 
    {
        m_transform.set((min + max) * 0.5f, angle, (max - min) * 0.5f);
        if (angle == 0.0f)
        {
            vec2 minv, maxv;
            minv = m_transform * -vec2One;
            maxv = m_transform * vec2One;
        }
        return *this;
    }

    OBB& transform(OBB& target, const Transform2& t) const;
    OBB transform(const Transform2& t) const { OBB res; return transform(res, t); }
};

struct AABB
{
    vec2 m_min, m_max;

    AABB() {}
    AABB(const vec2& min, const vec2& max): m_min(min), m_max(max) {}

    OBB& transform(OBB& target, const Transform2& t) const;
    OBB transform(const Transform2& t) const { OBB res; return transform(res, t); }
};

struct Circle
{
    vec2 m_center;
    float m_radius;

    Circle() {}
    Circle(const vec2& center, float radius): m_center(center), m_radius(radius) {}

    Circle& transform(Circle& target, const Transform2& t) const;
    Circle transform(const Transform2& t) const { Circle res; return transform(res, t); }
};

struct Line
{
    vec2 m_p0, m_p1;

    Line() {}
    Line(const vec2& p0, const vec2& p1): m_p0(p0), m_p1(p1) {}

    Line& transform(Line& target, const Transform2& t) const;
    Line transform(const Transform2& t) const { Line res; return transform(res, t); }
};

vec2 closestPoint(const Line& l0, vec2 p);

bool inside(const AABB& b0, const vec2& p1);
bool inside(const OBB& o0, const vec2& p1);
bool inside(const Circle& c0, const vec2& p1);
bool inside(const Line& l0, const vec2& p1);

bool intersect(const AABB& b0, const AABB& b1);
bool intersect(const AABB& b0, const OBB& o1);
bool intersect(const AABB& b0, const Circle& c1);
bool intersect(const AABB& b0, const Line& l1);

bool intersect(const OBB& o0, const OBB& o1);
bool intersect(const OBB& o0, const Circle& c1);
bool intersect(const OBB& o0, const Line& l1);
inline bool intersect(const OBB& o0, const AABB& b1) { return intersect(b1, o0); }

bool intersect(const Circle& c0, const Circle& c1);
bool intersect(const Circle& c0, const Line& l1);
inline bool intersect(const Circle& c0, const AABB& b1) { return intersect(b1, c0); }
inline bool intersect(const Circle& c0, const OBB& o1) { return intersect(o1, c0); }

bool intersect(const Line& l0, const Line& l1);
inline bool intersect(const Line& l0, const AABB& b1) { return intersect(b1, l0); }
inline bool intersect(const Line& l0, const OBB& o1) { return intersect(o1, l0); }
inline bool intersect(const Line& l0, const Circle& c1) { return intersect(c1, l0); }


class BaseShape {
public:
    virtual BaseShape* transform(const Transform2& trans) const = 0;
    virtual BaseShape* transform(BaseShape* target, const Transform2& trans) const = 0;
    
    virtual bool inside(const vec2& p1) const = 0;

    virtual bool intersect(const AABB& b1) const = 0;
    virtual bool intersect(const OBB& o1) const = 0;
    virtual bool intersect(const Circle& c1) const = 0;
    virtual bool intersect(const Line& l1) const = 0;

    virtual bool intersect(const BaseShape& other) const = 0;
};

template <class S>
class Shape: public BaseShape {
public:
    S m_Shape;

    virtual BaseShape* transform(const Transform2& trans) const
    {
        auto result = new Shape<decltype(m_Shape.transform(trans))>();
        m_Shape.transform(result->m_Shape, trans);
        return result;
    }

    virtual BaseShape* transform(BaseShape* target, const Transform2& trans) const
    {
        auto result = dynamic_cast<Shape<decltype(m_Shape.transform(trans))>*>(target);
        m_Shape.transform(result->m_Shape, trans);
        return result;
    }

    virtual bool inside(const vec2& p1) const
    {
        return ::inside(m_Shape, p1);
    }

    virtual bool intersect(const AABB& b1) const
    {
        return ::intersect(m_Shape, b1);
    }

    virtual bool intersect(const OBB& o1) const
    {
        return ::intersect(m_Shape, o1);
    }

    virtual bool intersect(const Circle& c1) const
    {
        return ::intersect(m_Shape, c1);
    }

    virtual bool intersect(const Line& l1) const
    {
        return ::intersect(m_Shape, l1);
    }

    virtual bool intersect(const BaseShape& other) const
    {
        return other.intersect(m_Shape);
    }
};

