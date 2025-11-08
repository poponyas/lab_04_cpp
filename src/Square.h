#pragma once
#include "../include/Figure.h"
#include <cmath>

template <Scalar T>
class Square : public Figure<T>
{
private:
    std::unique_ptr<Point<T>[]> vertices;
    static const int VERTICES_COUNT = 4;

public:
    Square() : vertices(std::make_unique<Point<T>[]>(VERTICES_COUNT)) {}

    Square(Square &&other) noexcept = default;
    Square &operator=(Square &&other) noexcept = default;

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
        os << "Square vertices: ";
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
        T side;
        is >> center >> side;

        T half = side / 2;
        T x = center.getX(), y = center.getY();

        vertices[0] = Point<T>(x - half, y - half);
        vertices[1] = Point<T>(x + half, y - half);
        vertices[2] = Point<T>(x + half, y + half);
        vertices[3] = Point<T>(x - half, y + half);
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Square *otherSquare = dynamic_cast<const Square *>(&other);
        if (!otherSquare)
            return false;

        for (int i = 0; i < VERTICES_COUNT; ++i)
        {
            if (vertices[i].getX() != otherSquare->vertices[i].getX() ||
                vertices[i].getY() != otherSquare->vertices[i].getY())
            {
                return false;
            }
        }
        return true;
    }
};