#include <iostream>
#include <memory>

void basic_pointers() {
    std::cout << "BASIC POINTERS" << std::endl << std::endl;
}

void smart_pointers() {
    std::cout << "SMART POINTERS" << std::endl << std::endl;

    std::shared_ptr<int> ptrNum1 = std::make_shared<int>();
    std::shared_ptr<int> ptrNum2 = ptrNum1;

    std::shared_ptr<int> ptrNum3 = std::make_shared<int>(10);

    std::cout << "ptrNum1: " << *ptrNum1 << ", reference count: " << ptrNum1.use_count() << std::endl;
    std::cout << "ptrNum2: " << *ptrNum2 << ", reference count: " << ptrNum2.use_count() << std::endl;
    std::cout << "ptrNum3: " << *ptrNum3 << ", reference count: " << ptrNum3.use_count() << std::endl;
}