#include <iostream>
#include <string>
#include <numbers>
#include <vector>

// encapsulation: bundling of attributes and methods into a single unit (class)
// abstraction: hiding complex implementation and only exposing essential features
// inheritance: allows one class to be derived from another (reusability and class hierarchy)
// polymorphism: objects of different classes treated as objects of a common base class (methods overriden and invoked in runtime)
class Shape {
public:
    virtual double area() const = 0; // Pure virtual function, must be overriden
    virtual double perimeter() const = 0; // Pure virtual function
    virtual void printType() const { // not pure, has default implementation
        std::cout << "This is shape - base class or derived class is using default base implementation.\n";
    } 
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return std::numbers::pi * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * std::numbers::pi * radius;
    }

    void printType() const override {
        std::cout << "This is circle.\n";
    }
};

class Rectangle : public Shape {
private:
    double a;
    double b;
    
public:
    Rectangle(double a, double b) : a(a), b(b) {}
    
    double area() const override {
        return a * b;
    }
    
    double perimeter() const override {
        return 2*a + 2*b;
    }
};

void try_oop() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(5));
    shapes.push_back(new Rectangle(3, 4));

    std::cout << "Circle\n";
    shapes[0]->printType();
    std::cout << "Area: " << shapes[0]->area() << ", Perimeter: " << shapes[0]->perimeter() << "\n";
    std::cout << "Rectangle\n";
    shapes[1]->printType();
    std::cout << "Area: " << shapes[1]->area() << ", Perimeter: " << shapes[1]->perimeter() << "\n";

    for (auto shape : shapes) {
        delete shape;
    }

    std::cout << "OOP\n";
} 