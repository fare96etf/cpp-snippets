#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "libs/class_setup.hpp"


int main(int, char**) {
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