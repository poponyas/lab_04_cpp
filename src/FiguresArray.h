#pragma once
#include "Array.h"
#include "Figure.h"
#include <memory>

template <Scalar T>
class FiguresArray
{
private:
    Array<std::unique_ptr<Figure<T>>> figures;

public:
    FiguresArray() = default;

    FiguresArray(const FiguresArray &) = delete;
    FiguresArray &operator=(const FiguresArray &) = delete;

    FiguresArray(FiguresArray &&) = default;
    FiguresArray &operator=(FiguresArray &&) = default;

    void addFigure(std::unique_ptr<Figure<T>> figure)
    {
        figures.add(std::move(figure));
    }

    void removeFigure(size_t index)
    {
        figures.remove(index);
    }

    double totalArea() const
    {
        double total = 0.0;
        for (size_t i = 0; i < figures.size(); ++i)
        {
            total += figures[i]->area();
        }
        return total;
    }

    void printAllInfo() const
    {
        for (size_t i = 0; i < figures.size(); ++i)
        {
            std::cout << "Figure " << i + 1 << ":\n";
            std::cout << "Vertices: " << *figures[i] << "\n";
            auto center = figures[i]->getCenter();
            std::cout << "Geometric Center: (" << center.getX() << ", " << center.getY() << ")\n";
            std::cout << "Area: " << figures[i]->area() << "\n\n";
        }
    }

    size_t getSize() const
    {
        return figures.size();
    }

    std::unique_ptr<Figure<T>> &operator[](size_t index)
    {
        return figures[index];
    }

    const std::unique_ptr<Figure<T>> &operator[](size_t index) const
    {
        return figures[index];
    }
};