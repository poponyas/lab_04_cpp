#include <iostream>
#include <memory>
#include <sstream>
#include "src/Triangle.h"
#include "src/Square.h"
#include "src/Octagon.h"
#include "src/FiguresArray.h"

void demonstrateArraySpecializations()
{
    std::cout << "\n1. Array<std::shared_ptr<Figure<int>>> (base type):\n";
    Array<std::shared_ptr<Figure<int>>> figureArray;

    auto triangle = std::make_shared<Triangle<int>>();
    std::istringstream input1("0 0 3 0 0 4");
    input1 >> *triangle;
    figureArray.add(triangle);

    auto square = std::make_shared<Square<int>>();
    std::istringstream input2("0 0 5");
    input2 >> *square;
    figureArray.add(square);

    std::cout << "   Size: " << figureArray.size() << "\n";
    std::cout << "   Total area: ";
    double total = 0;
    for (size_t i = 0; i < figureArray.size(); ++i)
    {
        total += figureArray[i]->area();
    }
    std::cout << total << "\n";

    std::cout << "\n2. Array<Square<double>> (derived type, non-pointer):\n";
    Array<Square<double>> squareArray;

    Square<double> sq1, sq2;
    std::istringstream input3("1 1 3");
    input3 >> sq1;
    std::istringstream input4("2 2 4");
    input4 >> sq2;

    squareArray.add(sq1);
    squareArray.add(std::move(sq2));

    std::cout << "   Size: " << squareArray.size() << "\n";
    std::cout << "   Areas: ";
    for (size_t i = 0; i < squareArray.size(); ++i)
    {
        std::cout << squareArray[i].area() << " ";
    }
    std::cout << "\n";

    std::cout << "\n3. Demonstration of copying:\n";
    Array<Square<double>> copiedArray = squareArray;
    std::cout << "   Original size: " << squareArray.size() << "\n";
    std::cout << "   Copied size: " << copiedArray.size() << "\n";
    std::cout << "   Copy successful: " << (squareArray.size() == copiedArray.size() ? "YES" : "NO") << "\n";

    std::cout << "\n4. Demonstration of conversion to double:\n";
    std::cout << "   Triangle area as double: " << static_cast<double>(*triangle) << "\n";
    std::cout << "   Square area as double: " << static_cast<double>(*square) << "\n";

    std::cout << "\n5. Demonstration of comparison:\n";
    Square<double> sq3, sq4;
    std::istringstream input5("0 0 5");
    std::istringstream input6("0 0 5");
    input5 >> sq3;
    input6 >> sq4;

    bool areEqual = sq3.operator==(sq4);
    std::cout << "   Two identical squares are equal: " << (areEqual ? "YES" : "NO") << "\n";

    std::cout << std::string(60, '=') << "\n\n";
}

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
        std::cout << "7 - Show Array specializations demo\n";
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
            case 7:
            {
                demonstrateArraySpecializations();
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

    demonstrateArraySpecializations();

    std::cout << "1. Working with int type\n";
    demonstrateFigures<int>();

    std::cout << "\n2. Working with double type\n";
    demonstrateFigures<double>();

    std::cout << "\n3. Working with float type\n";
    demonstrateFigures<float>();

    return 0;
}