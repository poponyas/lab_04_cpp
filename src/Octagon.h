#pragma once
#include "../include/Figure.h"
#include <cmath>
#include <numbers>

template <Scalar T>
class Octagon : public Figure<T>
{
private:
    std::unique_ptr<Point<T>[]> vertices;
    static const int VERTICES_COUNT = 8;

public:
    Octagon() : vertices(std::make_unique<Point<T>[]>(VERTICES_COUNT)) {}

    Octagon(const Octagon &other) : vertices(std::make_unique<Point<T>[]>(VERTICES_COUNT))
    {
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            vertices[i] = other.vertices[i];
        }
    }

    Octagon &operator=(const Octagon &other)
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

    Octagon(Octagon &&other) noexcept = default;
    Octagon &operator=(Octagon &&other) noexcept = default;

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
        double area = 0.0;
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            int j = (i + 1) % VERTICES_COUNT;
            area += vertices[i].getX() * vertices[j].getY();
            area -= vertices[j].getX() * vertices[i].getY();
        }
        return std::abs(area) / 2.0;
    }

    void printVertices(std::ostream &os) const override
    {
        os << "Octagon vertices: ";
        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            os << vertices[i];
            if (i < VERTICES_COUNT - 1)
                os << ", ";
        }
    }

    void readFromStream(std::istream &is) override
    {
        Point<T> center;
        T radius;
        is >> center >> radius;

        T x = center.getX(), y = center.getY();

        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            double angle = 2 * std::numbers::pi * i / VERTICES_COUNT;
            T vertex_x = x + radius * std::cos(angle);
            T vertex_y = y + radius * std::sin(angle);
            vertices[i] = Point<T>(vertex_x, vertex_y);
        }
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Octagon *otherOctagon = dynamic_cast<const Octagon *>(&other);
        if (!otherOctagon)
            return false;

        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            if (vertices[i].getX() != otherOctagon->vertices[i].getX() ||
                vertices[i].getY() != otherOctagon->vertices[i].getY())
            {
                return false;
            }
        }
        return true;
    }
};