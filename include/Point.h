#pragma once
#include <iostream>
#include <memory>
#include <concepts>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point
{
private:
    T x, y;

public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    T getX() const { return x; }
    T getY() const { return y; }
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }

    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << '(' << p.x << ',' << p.y << ')';
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Point &p)
    {
        is >> p.x >> p.y;
        return is;
    }
};