#pragma once
#include <iostream>
namespace forge {
class Shape { public: virtual ~Shape() = default; virtual double area() const = 0; virtual void describe(std::ostream& out) const = 0; };
class Circle final : public Shape {
    double radius_;
public: explicit Circle(double r) : radius_(r) {} double area() const override { return 3.141592653589793 * radius_ * radius_; }
    void describe(std::ostream& out) const override { out << "Circle(area=" << area() << ')'; }
};
class Rectangle final : public Shape {
    double width_, height_;
public: Rectangle(double w, double h) : width_(w), height_(h) {} double area() const override { return width_ * height_; }
    void describe(std::ostream& out) const override { out << "Rectangle(area=" << area() << ')'; }
};
}
