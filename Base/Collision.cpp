#include <algorithm>
#include <typeinfo>
#include <assert.h>
#include "Collision.h"
#include "Util.h"
OBB& AABB::transform(OBB& target, const Transform2& t) const
{
    OBB o0;
    o0.set(m_min, m_max, 0.0f);
    target.m_transform.setMultiply(t, o0.m_transform);
    return target;
}

const AABB aabbUnit(-vec2One, vec2One);

OBB& OBB::transform(OBB& target, const Transform2& t) const
{
    target.m_transform.setMultiply(t, m_transform);
    return target;
}

Circle& Circle::transform(Circle& target, const Transform2& t) const
{
    vec2 scale = t.getScale();
    assert(equalWithEpsilon(scale.x, scale.y, EPS));
    target.m_center.setMultiply(t, m_center);
    target.m_radius = m_radius * scale.x;
    return target;
}

Line& Line::transform(Line& target, const Transform2& t) const
{
    target.m_p0.setMultiply(t, m_p0);
    target.m_p1.setMultiply(t, m_p1);
    return target;
}

bool inside(const AABB& b0, const vec2& p1)
{
    return b0.m_min.x <= p1.x && p1.x <= b0.m_max.x && 
           b0.m_min.y <= p1.y && p1.y <= b0.m_max.y;
}

bool inside(const OBB& o0, const vec2& p1)
{
    Transform2 inv;
    inv.invert(o0.m_transform);
    vec2 invp = inv * p1;
    return !(invp.x < -1.0f || invp.x > 1.0f || invp.y < -1.0f || invp.y > 1.0f);
}

bool inside(const Circle& c0, const vec2& p1)
{
    return (p1 - c0.m_center).getLengthSq() <= sqr(c0.m_radius);
}

bool inside(const Line& l0, const vec2& p1)
{
    vec2 v0 = l0.m_p1 - l0.m_p0;
    float t = v0.dot(p1 - l0.m_p0) / v0.dot(v0);
    vec2 closest = l0.m_p0 + v0 * t;
    if (!closest.equalWithEpsilon(p1))
        return false;
    return 0.0f <= t && t <= 1.0f;
}

// Closest point on a line segment to a point
vec2 closestPoint(const Line& l0, vec2 p)
{
    vec2 l = l0.m_p1 - l0.m_p0;
    float t = l.dot(p - l0.m_p0) / l.dot(l);
    t = clamp(0.0f, 1.0f, t);
    return l0.m_p0 + l * t;
}

bool intersect(const AABB& b0, const AABB& b1)
{
    return !(b0.m_min.x > b1.m_max.x || b0.m_max.x < b1.m_min.x ||
             b0.m_min.y > b1.m_max.y || b0.m_max.y < b1.m_min.y);
}

// returns true of the OBB is completely on one side of one of AABB's borders.
bool outside(const AABB& b0, const OBB& o1)
{
    using std::min; using std::max;
    vec2 p00 = o1.m_transform * vec2(-1.0f, -1.0f);
    vec2 p01 = o1.m_transform * vec2(-1.0f, 1.0f);
    vec2 p10 = o1.m_transform * vec2(1.0f, -1.0f);
    vec2 p11 = o1.m_transform * vec2(1.0f, 1.0f);
    float maxX = max(p00.x, max(p01.x, max(p10.x, p11.x)));
    float maxY = max(p00.y, max(p01.y, max(p10.y, p11.y)));
    if (maxX < b0.m_min.x || maxY < b0.m_min.y)
        return true;
    float minX = min(p00.x, min(p01.x, min(p10.x, p11.x)));
    float minY = min(p00.y, min(p01.y, min(p10.y, p11.y)));
    if (minX > b0.m_max.x || minY > b0.m_max.y)
        return true;
    return false;
}

bool intersect(const AABB& b0, const OBB& o1)
{
    if (outside(b0, o1))
        return false;
    Transform2 inv;
    inv.invert(o1.m_transform);
    OBB o0Inv;
    o0Inv = b0.transform(inv);
    return !outside(aabbUnit, o0Inv);
}

bool intersect(const AABB& b0, const Circle& c1)
{
    vec2 closest(clamp(b0.m_min.x, b0.m_max.x, c1.m_center.x),
                 clamp(b0.m_min.y, b0.m_max.y, c1.m_center.y));
    return (closest - c1.m_center).getLengthSq() <= sqr(c1.m_radius);
}

bool intersect(const AABB& b0, const Line& l1)
{
    if (inside(b0, l1.m_p0) || inside(b0, l1.m_p1))
        return true;

    Line diag;
    if (l1.m_p0.x < l1.m_p1.x && l1.m_p0.y < l1.m_p1.y || l1.m_p0.x >= l1.m_p1.x && l1.m_p0.y >= l1.m_p1.y)
    {
        diag.m_p0 = vec2(b0.m_max.x, b0.m_min.y);
        diag.m_p1 = vec2(b0.m_min.x, b0.m_max.y);
    }
    else
    {
        diag.m_p0 = b0.m_min;
        diag.m_p1 = b0.m_max;
    }
    return intersect(diag, l1);
}

bool intersect(const OBB& o0, const OBB& o1)
{
    OBB o1Inv = o1.transform(o0.m_transform.getInverse());
    return intersect(aabbUnit, o1Inv);
}

bool intersect(const OBB& o0, const Circle& c1)
{
    Transform2 o0Inv;
    o0Inv.invert(o0.m_transform);
    vec2 scale = o0Inv.getScale();
    Transform2 rescale;
    rescale.setScale(vec2(1.0f, scale.x / scale.y));
    Transform2 transform = rescale * o0Inv;
    vec2 scaleVec(1.0f, scale.x / scale.y);
    AABB b0(-scaleVec, scaleVec);
    return intersect(b0, c1.transform(transform));
}

bool intersect(const OBB& o0, const Line& l1)
{
    Line l1Inv = l1.transform(o0.m_transform.getInverse());
    return intersect(aabbUnit, l1Inv);
}

bool intersect(const Circle& c0, const Circle& c1)
{
    return (c1.m_center - c0.m_center).getLengthSq() <= sqr(c1.m_radius + c0.m_radius);
}

bool intersect(const Circle& c0, const Line& l1)
{
    vec2 closest = closestPoint(l1, c0.m_center);
    return (closest - c0.m_center).getLengthSq() <= sqr(c0.m_radius);
}

bool intersect(const Line& l0, const Line& l1)
{
    vec2 v0 = l0.m_p1 - l0.m_p0;
    vec2 v1 = l1.m_p1 - l1.m_p0;
    vec2 v1n = v1.getPerp();
    float denom = v0.dot(v1n);
    if (equalWithEpsilon(denom, 0.0f, EPS))
    {
        // Parallel lines
        float t0 = v0.dot(l1.m_p0 - l0.m_p0) / v0.dot(v0);
        vec2 closest = l0.m_p0 + v0 * t0;
        if (!closest.equalWithEpsilon(l1.m_p0))
            return false;
        float t1 = v0.dot(l1.m_p1 - l0.m_p0) / v0.dot(v0);
        if (t0 > t1)
            std::swap(t0, t1);
        return !(t1 < 0.0f || t0 > 1.0f);
    }
    float t0 = (l1.m_p0 - l0.m_p0).dot(v1n) / denom;
    if (t0 < 0.0f || t0 > 1.0f)
        return false;
    vec2 v0n = v0.getPerp();
    float t1 = (l0.m_p0 - l1.m_p0).dot(v0n) / v1.dot(v0n);
    return 0.0f <= t1 && t1 <= 1.0f;
}
