#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "../include/Point.h"
#include "../src/Triangle.h"
#include "../src/Square.h"
#include "../src/Octagon.h"
#include "../src/FiguresArray.h"

// Тесты для Point
TEST(PointTest, DefaultConstructor)
{
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor)
{
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), 4.2);
}

TEST(PointTest, InputOutput)
{
    Point<int> p;
    std::istringstream input("10 20");
    input >> p;

    EXPECT_EQ(p.getX(), 10);
    EXPECT_EQ(p.getY(), 20);

    std::ostringstream output;
    output << p;
    EXPECT_EQ(output.str(), "(10,20)");
}

// Тесты для Triangle
TEST(TriangleTest, AreaCalculation)
{
    auto triangle = std::make_unique<Triangle<int>>();
    std::istringstream input("0 0 4 0 0 3");
    input >> *triangle;

    EXPECT_DOUBLE_EQ(triangle->area(), 6.0);
}

TEST(TriangleTest, CenterCalculation)
{
    auto triangle = std::make_unique<Triangle<double>>();
    std::istringstream input("0 0 6 0 0 8");
    input >> *triangle;

    auto center = triangle->getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 2.0);
    EXPECT_DOUBLE_EQ(center.getY(), 8.0 / 3.0);
}

// Тесты для Square
TEST(SquareTest, AreaCalculation)
{
    auto square = std::make_unique<Square<int>>();
    std::istringstream input("0 0 4");
    input >> *square;

    EXPECT_DOUBLE_EQ(square->area(), 16.0);
}

TEST(SquareTest, CenterCalculation)
{
    auto square = std::make_unique<Square<double>>();
    std::istringstream input("5 5 6");
    input >> *square;

    auto center = square->getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 5.0);
    EXPECT_DOUBLE_EQ(center.getY(), 5.0);
}

// Тесты для Octagon
TEST(OctagonTest, AreaCalculation)
{
    auto octagon = std::make_unique<Octagon<double>>();
    std::istringstream input("0 0 1");
    input >> *octagon;

    double area = octagon->area();
    EXPECT_GT(area, 0.0);
    EXPECT_LT(area, 4.0);
}

// Тесты для FiguresArray
TEST(FiguresArrayTest, AddAndRemove)
{
    FiguresArray<int> arr;

    auto triangle = std::make_unique<Triangle<int>>();
    std::istringstream input("0 0 3 0 0 4");
    input >> *triangle;
    arr.addFigure(std::move(triangle));

    EXPECT_EQ(arr.getSize(), 1);

    arr.removeFigure(0);
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(FiguresArrayTest, TotalArea)
{
    FiguresArray<double> arr;

    auto triangle = std::make_unique<Triangle<double>>();
    std::istringstream input1("0 0 3 0 0 4");
    input1 >> *triangle;
    arr.addFigure(std::move(triangle));

    auto square = std::make_unique<Square<double>>();
    std::istringstream input2("0 0 2");
    input2 >> *square;
    arr.addFigure(std::move(square));

    double totalArea = arr.totalArea();
    EXPECT_GT(totalArea, 0.0);
    EXPECT_DOUBLE_EQ(totalArea, 6.0 + 4.0); // triangle (6) + square (4)
}

TEST(FiguresArrayTest, MoveSemantics)
{
    FiguresArray<int> arr1;

    auto triangle = std::make_unique<Triangle<int>>();
    std::istringstream input("0 0 3 0 0 4");
    input >> *triangle;
    arr1.addFigure(std::move(triangle));

    FiguresArray<int> arr2 = std::move(arr1);
    EXPECT_EQ(arr2.getSize(), 1);
    EXPECT_EQ(arr1.getSize(), 0);
}

TEST(FiguresArrayTest, OperatorDouble)
{
    auto triangle = std::make_unique<Triangle<double>>();
    std::istringstream input("0 0 3 0 0 4");
    input >> *triangle;

    double area = static_cast<double>(*triangle);
    EXPECT_DOUBLE_EQ(area, 6.0);
}

// Тесты на сравнение фигур (исправленные для C++20)
TEST(FigureComparisonTest, TriangleEquality)
{
    auto triangle1 = std::make_unique<Triangle<int>>();
    std::istringstream input1("1 1 4 1 1 5");
    input1 >> *triangle1;

    auto triangle2 = std::make_unique<Triangle<int>>();
    std::istringstream input2("1 1 4 1 1 5");
    input2 >> *triangle2;

    // Явно вызываем оператор == чтобы избежать неоднозначности
    bool result = triangle1->operator==(*triangle2);
    EXPECT_TRUE(result);
}

TEST(FigureComparisonTest, SquareEquality)
{
    auto square1 = std::make_unique<Square<double>>();
    std::istringstream input1("0 0 4");
    input1 >> *square1;

    auto square2 = std::make_unique<Square<double>>();
    std::istringstream input2("0 0 4");
    input2 >> *square2;

    // Явно вызываем оператор == чтобы избежать неоднозначности
    bool result = square1->operator==(*square2);
    EXPECT_TRUE(result);
}

TEST(FigureComparisonTest, TriangleInequality)
{
    auto triangle1 = std::make_unique<Triangle<int>>();
    std::istringstream input1("1 1 4 1 1 5");
    input1 >> *triangle1;

    auto triangle2 = std::make_unique<Triangle<int>>();
    std::istringstream input2("2 2 5 2 2 6");
    input2 >> *triangle2;

    // Явно вызываем оператор == чтобы избежать неоднозначности
    bool result = triangle1->operator==(*triangle2);
    EXPECT_FALSE(result);
}

// Тест на разные типы фигур
TEST(FigureComparisonTest, DifferentTypes)
{
    auto triangle = std::make_unique<Triangle<int>>();
    std::istringstream input1("1 1 4 1 1 5");
    input1 >> *triangle;

    auto square = std::make_unique<Square<int>>();
    std::istringstream input2("0 0 4");
    input2 >> *square;

    // Треугольник и квадрат не должны быть равны
    bool result = triangle->operator==(*square);
    EXPECT_FALSE(result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}