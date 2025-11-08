#pragma once
#include "../include/Figure.h"
#include <cmath>

template <Scalar T>
class Triangle : public Figure<T>
{
private:
    std::unique_ptr<Point<T>[]> vertices;
    static const int VERTICES_COUNT = 3;

public:
    Triangle() : vertices(std::make_unique<Point<T>[]>(VERTICES_COUNT)) {}

    Triangle(const Triangle &other) : vertices(std::make_unique<Point<T>[]>(VERTICES_COUNT))
    {
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            vertices[i] = other.vertices[i];
        }
    }

    Triangle &operator=(const Triangle &other)
    {
        if (this != &other)
        {
            vertices = std::make_unique<Point<T>[]>(VERTICES_COUNT);
            for (int i = 0; i < VERTICES_COUNT; ++i)
            {
                vertices[i] = other.vertices[i];
            }
        }
        return *this;
    }

    Triangle(Triangle &&other) noexcept = default;
    Triangle &operator=(Triangle &&other) noexcept = default;

    Point<T> getCenter() const override
    {
        T center_x = 0, center_y = 0;
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            center_x += vertices[i].getX();
            center_y += vertices[i].getY();
        }
        return Point<T>(center_x / VERTICES_COUNT, center_y / VERTICES_COUNT);
    }

    double area() const override
    {
        T x1 = vertices[0].getX(), y1 = vertices[0].getY();
        T x2 = vertices[1].getX(), y2 = vertices[1].getY();
        T x3 = vertices[2].getX(), y3 = vertices[2].getY();

        return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    }

    void printVertices(std::ostream &os) const override
    {
        os << "Triangle vertices: ";
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            os << vertices[i];
            if (i < VERTICES_COUNT - 1)
                os << ", ";
        }
    }

    void readFromStream(std::istream &is) override
    {
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            is >> vertices[i];
        }
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
        if (!otherTriangle)
            return false;

        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            if (vertices[i].getX() != otherTriangle->vertices[i].getX() ||
                vertices[i].getY() != otherTriangle->vertices[i].getY())
            {
                return false;
            }
        }
        return true;
    }
};