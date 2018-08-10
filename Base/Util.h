#pragma once

template <typename T, size_t N>
size_t arrSize(T(&arr)[N]) { return N; }

template <class T>
T clamp(T minA, T maxA, T a)
{
    using std::min; using std::max;
    return min(max(minA, a), maxA);
}

template <class T>
T sqr(T a)
{
    return a * a;
}

template <class T, class V>
V lerp(V v0, V v1, T t)
{
    return v0 + t * (v1 - v0);
}

template <class T>
bool equalWithEpsilon(T a, T b, T eps)
{
    return abs(a - b) <= eps;
}

const float EPS = 0.001f;
