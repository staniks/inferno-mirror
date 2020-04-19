#ifndef MAU_VEC2_H
#define MAU_VEC2_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <cmath>

namespace Mau
{
    template <typename T>
    class Vec2
    {
    public:
        T x, y;

        Vec2() : x(0), y(0)
        {
        }

        Vec2(T x, T y) : x(x), y(y)
        {
        }

        Vec2(const Vec2& v) : x(v.x), y(v.y)
        {
        }

        Vec2& operator=(const Vec2& v);

        bool operator==(const Vec2& v) const;

        Vec2 operator+(const Vec2& v) const;
        Vec2 operator-(const Vec2& v) const;

        Vec2& operator+=(const Vec2& v);
        Vec2& operator-=(const Vec2& v);

        Vec2 operator*(const float s) const;
        Vec2 operator/(const float s) const;

        Vec2& operator*=(const float s);
        Vec2& operator/=(const float s);

        Vec2& Normalize();

        Vec2 Normalized() const;

        float Length() const;

        static float Dot(const Vec2 v1, const Vec2 v2);
        static float Det(const Vec2 v1, const Vec2 v2);
        static float Cross(const Vec2 v1, const Vec2 v2);
        static Vec2 Lerp(const float t, const Vec2 v1, const Vec2 v2);
        static Vec2 MoveTowards(const Vec2 v1, const Vec2 v2, float delta);
    };

    template <typename T>
    Vec2<T>& Vec2<T>::operator=(const Vec2& v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    template <typename T>
    bool Vec2<T>::operator==(const Vec2& v) const
    {
        return v.x == x && v.y == y;
    }

    template <typename T>
    Vec2<T> Vec2<T>::operator+(const Vec2& v) const
    {
        return Vec2(x + v.x, y + v.y);
    }

    template <typename T>
    Vec2<T> Vec2<T>::operator-(const Vec2& v) const
    {
        return Vec2(x - v.x, y - v.y);
    }

    template <typename T>
    Vec2<T>& Vec2<T>::operator+=(const Vec2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    template <typename T>
    Vec2<T>& Vec2<T>::operator-=(const Vec2& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template <typename T>
    Vec2<T> Vec2<T>::operator*(const float s) const
    {
        return Vec2(x * s, y * s);
    }

    template <typename T>
    Vec2<T> Vec2<T>::operator/(const float s) const
    {
        return Vec2(x / s, y / s);
    }

    template <typename T>
    Vec2<T>& Vec2<T>::operator*=(const float s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    template <typename T>
    Vec2<T>& Vec2<T>::operator/=(const float s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    template <typename T>
    Vec2<T>& Vec2<T>::Normalize()
    {
        *this *= (1.0 / Length());
        return *this;
    }

    template <typename T>
    Vec2<T> Vec2<T>::Normalized() const
    {
        return (*this) * (1.0 / Length());
    }

    template <typename T>
    float Vec2<T>::Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    template <typename T>
    float Vec2<T>::Dot(const Vec2 v1, const Vec2 v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <typename T>
    float Vec2<T>::Det(const Vec2 v1, const Vec2 v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }

    template <typename T>
    float Vec2<T>::Cross(const Vec2 v1, const Vec2 v2)
    {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }

    template <typename T>
    Vec2<T> Vec2<T>::Lerp(const float t, const Vec2 v1, const Vec2 v2)
    {
        return v1 * (1.0f - t) + v2 * t;
    }

    template <typename T>
    Vec2<T> Vec2<T>::MoveTowards(const Vec2 v1, const Vec2 v2, float delta)
    {
        if (v1 == v2)
            return {0, 0};

        const Vec2 difference = v2 - v1;
        const Vec2 direction = difference.Normalized();
        Vec2 current = v1 + direction * delta;
        if ((current - v1).Length() > difference.Length())
        {
            current = v2;
        }
        return current;
    }
}

#endif
