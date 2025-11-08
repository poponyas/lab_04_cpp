#include <iostream>
#include <memory>
#include "src/Triangle.h"
#include "src/Square.h"
#include "src/Octagon.h"
#include "src/FiguresArray.h"

template <Scalar T>
void demonstrateFigures()
{
    FiguresArray<T> arr;
    int cmd;

    std::cout << "=== Working with type: " << typeid(T).name() << " ===\n";

    while (true)
    {
        std::cout << "\nMenu:\n";
        std::cout << "1 - Add Triangle (3 points: x1 y1 x2 y2 x3 y3)\n";
        std::cout << "2 - Add Square (center_x center_y side)\n";
        std::cout << "3 - Add Octagon (center_x center_y radius)\n";
        std::cout << "4 - Show all figures info\n";
        std::cout << "5 - Remove figure by index\n";
        std::cout << "6 - Calculate total area\n";
        std::cout << "0 - Exit\n";
        std::cout << "Current figures count: " << arr.getSize() << "\n";
        std::cout << "Enter your choice: ";

        std::cin >> cmd;

        if (cmd == 0)
        {
            break;
        }

        try
        {
            switch (cmd)
            {
            case 1:
            {
                auto triangle = std::make_unique<Triangle<T>>();
                std::cout << "Enter 3 points for triangle (x1 y1 x2 y2 x3 y3): ";
                std::cin >> *triangle;
                arr.addFigure(std::move(triangle));
                std::cout << "Triangle added successfully!\n";
                break;
            }
            case 2:
            {
                auto square = std::make_unique<Square<T>>();
                std::cout << "Enter square parameters (center_x center_y side): ";
                std::cin >> *square;
                arr.addFigure(std::move(square));
                std::cout << "Square added successfully!\n";
                break;
            }
            case 3:
            {
                auto octagon = std::make_unique<Octagon<T>>();
                std::cout << "Enter octagon parameters (center_x center_y radius): ";
                std::cin >> *octagon;
                arr.addFigure(std::move(octagon));
                std::cout << "Octagon added successfully!\n";
                break;
            }
            case 4:
            {
                if (arr.getSize() == 0)
                {
                    std::cout << "No figures in the array yet.\n";
                }
                else
                {
                    std::cout << "\n=== All Figures Information ===\n";
                    arr.printAllInfo();
                }
                break;
            }
            case 5:
            {
                if (arr.getSize() == 0)
                {
                    std::cout << "No figures to remove.\n";
                }
                else
                {
                    std::cout << "Enter index of figure to remove (0-" << arr.getSize() - 1 << "): ";
                    size_t idx;
                    std::cin >> idx;
                    arr.removeFigure(idx);
                    std::cout << "Figure removed successfully!\n";
                }
                break;
            }
            case 6:
            {
                std::cout << "Total area of all figures: " << arr.totalArea() << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

int main()
{
    std::cout << "=== Figure Management System ===\n\n";

    // Демонстрация работы с разными типами
    std::cout << "1. Working with int type\n";
    demonstrateFigures<int>();

    std::cout << "\n2. Working with double type\n";
    demonstrateFigures<double>();

    std::cout << "\n3. Working with float type\n";
    demonstrateFigures<float>();

    return 0;
}