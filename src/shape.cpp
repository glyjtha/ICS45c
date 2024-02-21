#include "shape.hpp"
#include <iostream>
#include <string>


// class Shape 
Shape::Shape(Point center, std::string name) : center(center), name(name) {}

void Shape::print(std::ostream& out) const {
    out << name << "(" << center.x << ", " << center.y << ")\n";
}


