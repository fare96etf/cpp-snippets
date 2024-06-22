#include <iostream>

// type deduction based on Scott Meyers - Effective Modern C++
// template<typename T> 
// void f(ParamType param)
// T and ParamType can differ, for example T=int and ParamType=const int&

// case 1: ParamType is reference or pointer type, but not universal reference
template<typename T>
void tFunc1a(T& param) {
    std::cout << "Templates 1a case (ParamType is reference), value: " << param << "\n";
}

template<typename T>
void tFunc1b(const T& param) {
    std::cout << "Templates 1b case (ParamType is const reference), value: " << param << "\n";
}

template<typename T>
void tFunc1c(T* param) {
    std::cout << "Templates 1c case (ParamType is pointer), value: " << *param << "\n";
}

// case 2: ParamType is an universal reference
template<typename T>
void tFunc2(T&& param) {
    std::cout << "Templates 2 case (ParamType is universal reference), value: " << param << "\n";
}

// case 3: ParamType is passed by value
template<typename T>
void tFunc3(T param) {
    std::cout << "Templates 3 case (ParamType is passed by value), value: " << param << "\n";
}

// function template comprehensive example
template<typename T1, typename T2>
T1 myMax(T1 a, T1 b, T2 c) {
    std::cout << "A: " << a << ", B: " << b << ", C: " << c << "\n";
    return (a > b) ? a : b;
}

// class template example
template<typename T1, typename T2>
class MyPair {
    private:
        T1 first;
        T2 second;
    public:
        MyPair(T1 a, T2 b) : first(a), second(b) {}
        T1 getFirst() const { return first; }
        T2 getSecond() const { return second; }
};

void templates_test() {
    std::cout << "TEMPLATES \n";

    //case 1
    int x = 27; // int
    const int cx{x}; // const int
    const int& rx{x}; // reference to an int as a const int

    tFunc1a(x); // T is int, param is int&
    tFunc1a(cx); // T is const int, param is const int&
    tFunc1a(rx); // T is const int, param is const int&, rx reference is ignored during deduction for T

    // no need for constness to be part of T, as it is part of ParamType
    tFunc1b(x); // T is int, param is const int&
    tFunc1b(cx); // T is int, param is const int&
    tFunc1b(rx); // T is int, param is const int&, rx reference is ignored during deduction for T

    const int *px{&x}; // px is a ptr to x as a const int

    tFunc1c(&x); // T is int, param is int*
    tFunc1c(px); // T is const int, param is const int*

    // case 2 : if we pass lvalue, both T and ParamType are lvalue refs, for rvalue rules from case1 apply
    tFunc2(x); // T is int&, param is int& (lvalue passed)
    tFunc2(cx); // T is const int&, param is const int& (lvalue passed)
    tFunc2(rx); // T is const int&, param is const int& (lvalue passed)
    tFunc2(27); // T is int, param is int&& (rvalue passed)

    // case 3 : param will be copy (completely new object), if reference is passed ignore it
    // after ignoring ref, if const is passed ignore it, if volatile is passed ignore it
    tFunc3(x); // T is int, param is int 
    tFunc3(cx); // T is int, param is int 
    tFunc3(rx); // T is int, param is int 

    const char* const ptr = "Fun with pointers"; // const char* const (ptr can't point to another location, nor it's value can be changed)
    tFunc3(ptr); // T type is char*, param type is const char*
    std::cout << "\n";

    // function template comprehensive example
    auto max1 = myMax(5, 105, "additional");
    auto max2 = myMax("Mouse", "Screen", 2.34);
    std::cout << "Max1: " << max1 << ", Max2: " << max2 << "\n";
    std::cout << "\n";

    // class template example
    auto pair1 = MyPair("Citroen", 17000);
    std::cout << "Pair1 .. First: " << pair1.getFirst() << ", Second: " << pair1.getSecond() << "\n";
}