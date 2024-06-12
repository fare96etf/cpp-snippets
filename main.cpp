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

class MyClass : MyClassNoConstructors {
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

int main(int, char**){
    MyClassNoConstructors classDefault;
    classDefault.number = 0;
    classDefault.text = "text0";
    classDefault.display();

    std::vector<int> vect1 = { 1, 2, 3 };
    int* ptr1 = new int(1);
    MyClass class1(1, "text1", ptr1, vect1);
    class1.display();

    MyClass class2{class1}; //copy constructor
    class1.display(); //class1 should be intact

    MyClass class3{std::move(class1)}; //move constructor
    class1.display(); //text should be moved from class1

    MyClass class4 = class2; //copy constructor
    class4.display();

    class3 = class4; //copy assignment operator
    class4.display();

    class2 = std::move(class4); //move assignment operator
    class4.display(); //text should be moved from class4

    //next two examples not working because class4.ptr is nullptr

    //MyClass class5{class4};
    //class5.display(); //testing ptr behaviour because class4.ptr is nullptr

    //MyClass class6{std::move(class4)};
    //class6.display(); //testing ptr behaviour because class4.ptr is nullptr
}
