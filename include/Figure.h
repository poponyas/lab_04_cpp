#pragma once
#include <iostream>
#include <memory>
#include "Point.h"

template <Scalar T>
class Figure
{
public:
    virtual ~Figure() = default;

    virtual Point<T> getCenter() const = 0;
    virtual void printVertices(std::ostream &os) const = 0;
    virtual void readFromStream(std::istream &is) = 0;

    virtual double area() const = 0;
    virtual explicit operator double() const { return area(); }

    virtual bool operator==(const Figure<T> &other) const = 0;
};

template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Figure<T> &fig)
{
    fig.printVertices(os);
    return os;
}

template <Scalar T>
inline std::istream &operator>>(std::istream &is, Figure<T> &fig)
{
    fig.readFromStream(is);
    return is;
}