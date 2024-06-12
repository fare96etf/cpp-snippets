#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class MyClassNoConstructors {
    public:
        int number;
        std::string text; 

        void display() const {
            std::cout << "Number: " << number << ", Text: " << text << std::endl;
        }
};

class MyClass {
    private:
        int number;
        std::string text;
        int* ptr; 
        std::vector<int> vect;
    public:
        // default constructor
        MyClass() : number(0), text(""), ptr(nullptr) {
            std::cout << "Default constructor is called." << std::endl;
        }

        // parametrized constructor
        MyClass(int number, const std::string& text, int* p, const std::vector<int>& v) : number(number), text(text), ptr(p), vect(v) {
            std::cout << "Parametrized constructor is called." << std::endl;
        }

        // copy constructor
        MyClass(const MyClass& other) : number(other.number), text(other.text), ptr(new int(*other.ptr)), vect(other.vect.size()) {
            std::cout << "Copy constructor is called." << std::endl;
            std::copy(other.vect.begin(), other.vect.end(), vect.begin());
        }

        // move constructor
        MyClass(MyClass&& other) : number(other.number), text(std::move(other.text)), ptr(other.ptr), vect(std::move(other.vect))  {
            std::cout << "Move constructor is called." << std::endl;
            other.ptr = nullptr; // Ensure that the other object's pointer is set to nullptr after moving
        }

        // copy assignment operator
        MyClass& operator=(const MyClass& other) {
            std::cout << "Copy assignment operator is called." << std::endl;
            if (this != &other) {
                number = other.number;
                text = other.text;

                vect.resize(other.vect.size());
                std::copy(other.vect.begin(), other.vect.end(), vect.begin());
            
                if (ptr == nullptr) {
                    ptr = new int(*other.ptr);
                } else {
                    *ptr = *other.ptr;
                }
            }
            return *this;
        }

        // move assignment operator (noexcept enables optimizations, but also prevents from potential partially moved state)
        MyClass& operator=(MyClass&& other) noexcept {
            std::cout << "Move assignment operator is called." << std::endl;
            if (this != &other) {
                number = other.number;
                text = std::move(other.text);
                
                vect = std::move(other.vect);
                
                ptr = other.ptr;
                other.ptr = nullptr; // Ensure that the other object's pointer is set to nullptr after moving
            }
            return *this;
        }

        // comparison operators - tbd

        // destructor
        ~MyClass() {
            std::cout << "Destructor is called." << std::endl;
            delete ptr; // deallocate memory
        }

        // display members
        void display() const {
            std::cout << "Number: " << number << ", Text: " << text << ", Ptr address: " << ptr << ", Vector size: " << vect.size() << std::endl;
        }

};