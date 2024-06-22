#include <iostream>
#include <memory>

class TestClass {
    private:
        int num;
    public:
        TestClass(int num) : num(num) {}
        
        TestClass(const TestClass&) = delete;
        TestClass& operator=(const TestClass&) = delete;
        TestClass(TestClass&&) = delete;
        TestClass& operator=(TestClass&&) = delete;
        
        void display() {
            std::cout << "TestClass num: " << num << std::endl;
        }
};

void basic_pointers() {
    std::cout << "BASIC POINTERS" << std::endl << std::endl;

    // int pointer
    int* num = new int{10};
    std::cout << "Num value: " << *num << std::endl;
    delete num;

    // pointer to pointer (2d array)
    int rows = 3;
    int cols = 4;
    int** array = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            array[i][j] = i + j;
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;

    //pointer to class instance
    TestClass* myClassPtr = new TestClass(5);
    myClassPtr->display();
    //TestClass t = *myClassPtr; //not allowed because of delete
    delete myClassPtr;

    // testing sanitizer, no deallocation
    // int* numProblem = new int{2}; 

    std::cout << std::endl;
}

void smart_pointers() {
    std::cout << "SMART POINTERS" << std::endl << std::endl;

    // shared_ptr
    std::shared_ptr<int> ptrNum1 = std::make_shared<int>();
    std::shared_ptr<int> ptrNum2 = ptrNum1;

    std::shared_ptr<int> ptrNum3 = std::make_shared<int>(10);

    std::cout << "ptrNum1: " << *ptrNum1 << ", reference count: " << ptrNum1.use_count() << std::endl;
    std::cout << "ptrNum2: " << *ptrNum2 << ", reference count: " << ptrNum2.use_count() << std::endl;
    std::cout << "ptrNum3: " << *ptrNum3 << ", reference count: " << ptrNum3.use_count() << std::endl;

    // unique_ptr
    std::unique_ptr<int> ptrUnique1 = std::make_unique<int>(10);
    std::cout << "ptrUnique1: " << *ptrUnique1 << std::endl;
    // std::unique_ptr<int> ptrUnique2 = ptrUnique1; // not allowed
    std::unique_ptr<int> ptrUnique3 = std::move(ptrUnique1);
    std::cout << "ptrUnique3: " << *ptrUnique3 << std::endl; // transfer ownership to other ptr

    // weak_ptr (non owning reference to an object managed by shared ptr)
    std::weak_ptr<int> ptrWeak = ptrNum3;

    if (auto temp = ptrWeak.lock()) {
        std::cout << "ptrNum3 is still alive." << std::endl;
    } else {
        std::cout << "ptrNum3 has been destroyed." << std::endl;
    }

    ptrNum3.reset();

    if (auto temp = ptrWeak.lock()) {
        std::cout << "ptrNum3 is still alive." << std::endl;
    } else {
        std::cout << "ptrNum3 has been destroyed." << std::endl;
    }

    std::cout << std::endl;
}