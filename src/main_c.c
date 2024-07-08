#include <stdio.h>

void memoryAllocTest() {
    printf("Memory Allocation Test\n");

    // malloc: malloc(2 * sizeof(int)); - values undefined
    // calloc: calloc(2, sizeof(int)); - values set to 0
    // realloc: ptr = (int *)malloc(n * sizeof(int)); ptr = (int *)realloc(ptr, 10 * sizeof(int));
    int *ptrMem = malloc(2 * sizeof(int));
    char* ptrMemC = (char*)ptrMem;

    printf("Address of ptrMem+1: %p\n", ptrMem+1);
    printf("Address of ptrMemC+4: %p\n", ptrMemC+4); // same as previous because char is 1 byte and int is 4 bytes
    printf("Address of ptrMemC+1: %p\n", ptrMemC+1); // second highest byte in first int 

    ptrMem[0] = 1;

    printf("Test2");
    printf("Value1: %d\n", ptrMem[0]);
    printf("Value2: %d\n", ptrMem[1]);

    ptrMemC[1] = 1;
    printf("Value1 after changing 2nd lowest byte: %d\n", ptrMem[0]); //0000000 - 00000000 - 00000001 (this changed) - 00000001
    // note: it is 2nd lowest byte for little endian (in x86_64), in big endian it would be 2nd highest

    free(ptrMem);
    ptrMem = NULL;
    ptrMemC = NULL;
}

void structUnionTest() {
    printf("Struct and Union test\n");

    typedef struct {
        char fullName[32];
        int age;
        int year;
        double gpa;
    } Student;

    Student student;
    strcpy(student.fullName, "Faris Kantic");
    student.age = 20;
    student.year = 2;
    student.gpa = 8.34;

    printf("Struct student name: %s\n", student.fullName);
    printf("Struct student age: %d\n", student.age);
    printf("Struct student year: %d\n", student.year);
    printf("Struct student gpa: %.2f\n", student.gpa);

    typedef struct {
        char a;    // 1 byte
        int b;     // 4 bytes
        double c;  // 8 bytes
    } PaddingTest1;

    typedef struct {
        int b;     // 4 bytes
        char a;    // 1 byte
        double c;  // 8 bytes
    } PaddingTest2;

    typedef struct {
        double c;  // 8 bytes
        int b;     // 4 bytes
        char a;    // 1 byte
    } PaddingTest3;

    typedef struct {
        double c;  // 8 bytes
        char a;    // 1 byte
        int b;     // 4 bytes
    } PaddingTest4;

    typedef struct {
        char a;    // 1 byte
        double c;  // 8 bytes
        int b;     // 4 bytes
    } PaddingTest5;

    typedef struct {
        int b;     // 4 bytes
        double c;  // 8 bytes
        char a;    // 1 byte
    } PaddingTest6;

    printf("Sizeof PaddingTest1: %d\n", sizeof(PaddingTest1));
    printf("Sizeof PaddingTest2: %d\n", sizeof(PaddingTest2));
    printf("Sizeof PaddingTest3: %d\n", sizeof(PaddingTest3));
    printf("Sizeof PaddingTest4: %d\n", sizeof(PaddingTest4));
    printf("Sizeof PaddingTest5: %d\n", sizeof(PaddingTest5));
    printf("Sizeof PaddingTest6: %d\n", sizeof(PaddingTest6));

    // in union only one member can take the allocated memory
    // here it will allocate sizeof(double) memory as it is the biggest one
    typedef union {
        char priceC;
        int prizeI;
        double prizeD;
    } BasicUnion;

    BasicUnion bun;
    bun.priceC = '1';
    bun.prizeI = 1;
    bun.prizeD = 1.2;

    // useful case 1: in embedded it provides different access to same register (byte-by-byte or the whole value)
    // struct (4 chars-4 bytes) and dword (int-4 bytes) are the same size
    typedef union
    {
        struct {
            unsigned char byte1;
            unsigned char byte2;
            unsigned char byte3;
            unsigned char byte4;
        } bytes;
        unsigned int dword;
    } HW_Register;
    
    HW_Register reg;
    reg.dword = 0x12345678;
    reg.bytes.byte3 = 4;

    // useful case 2: in embedded you can implement control register
    typedef union {
        unsigned char control_byte;
        struct {
            unsigned int nibble  : 4; // occupies 4 bits
            unsigned int nmi     : 1; // occupies 1 bit
            unsigned int enabled : 1;
            unsigned int fired   : 1;
            unsigned int control : 1;
        };
    } ControlRegister;

    // useful case 3: which_one tells which one is currently assigned a, b or c
    typedef struct {
        int which_one;
        union _data {
                int a;
                float b;
                char c;
        } foo;
    } MyData;
}

// executed before compilation, generates a single file that is passed to the actual compiler
// consist of directives defined with #
// modifies the source code before compilation begins, allowing for modularization, conditional compilation, and macro substitution
void preProcessorTest() {
    printf("Preprocessor test\n");

    #include "libs/dummy.c" // include directive, for modularization

    #pragma once // ensures that a header file is included only once
    #pragma pack(push, 1)  // Set packing alignment to 1 byte
    typedef struct {
        char a;    // 1 byte
        int b;     // 4 bytes
        double c;  // 8 bytes
    } PragmaPack1;
    #pragma pack(pop) // Restore default packing alignment
    typedef struct {
        char a;    // 1 byte
        int b;     // 4 bytes
        double c;  // 8 bytes
    } PragmaPack2;
    #pragma warning(disable: 4477)  // Disable warning 4477
    
    printf("Sizeof PragmaPack1: %d\n", sizeof(PragmaPack1));
    printf("Sizeof PragmaPack2: %d\n", sizeof(PragmaPack2));

    // define is used to create macros, which are symbolic names representing constant values or code snippets
    #define PI 3.14159
    #define SQUARE(x) ((x)*(x))
    
    // conditional compilation
    #ifdef _WIN32
        // Windows-specific code
        #pragma message("Windows env")
    #elif defined(__linux__)
        // Linux-specific code
        #pragma message("Linux env")
    #else
        #error "Unsupported platform detected"
    #endif

    #ifdef DEBUG_MODE
        #define DEBUG_PRINT(msg) printf("Debug: %s\n", msg)
    #else
        #define DEBUG_PRINT(msg)
        // #warning "Debug mode is disabled" // check this, added lately to C
    #endif
}

int main() {
    //memoryAllocTest();
    //structUnionTest();
    preProcessorTest();

    return 0;
}

// create linked list