#include <iostream>
#include <cmath>
#include <complex>
#include <random>
#include <numbers>
#include <numeric>

void try_random() {
    std::cout << "RANDOM NUMBERS \n";
    
    std::random_device rand; // seed generator
    std::mt19937 gen(rand()); // mersenne_twister_engine generator, there are others..

    // different distributions
    std::uniform_int_distribution<int> dist1(0, 10);
    std::cout << "Random number dist1: " << dist1(gen) << "\n";
    std::uniform_real_distribution<double> dist2(0.1, 0.9);
    std::cout << "Random number dist2: " << dist2(gen) << "\n";
    std::normal_distribution<double> dist3(0.5, 2.5);
    std::cout << "Random number dist3: " << dist3(gen) << "\n";
    std::discrete_distribution<> dist4({100, 50, 50, 100});
    std::cout << "Random number dist4: " << dist4(gen) << "\n";
    std::exponential_distribution<double> dist5(5.0);
    std::cout << "Random number dist5: " << dist5(gen) << "\n";

    std::cout << "\n";
}

void try_complex() {
    std::cout << "COMPLEX NUMBERS \n";

    std::complex<double> z1(2.5, 1);
    std::complex<double> z2(-2, -3.1); 
    auto z3(z1 + z2);
    std::cout << "z1 real: " << z1.real() << ", imag: " << z1.imag() << ", sin: " << std::sin(z1) << "\n";
    std::cout << "z2 real: " << z2.real() << ", imag: " << z2.imag() << ", tan: " << std::tan(z2) << "\n"; 
    std::cout << "z3 real: " << z3.real() << ", imag: " << z3.imag() << ", polar: " << std::polar(z3) << "\n";  

    std::cout << "\n"; 
}

void try_numeric() {
    std::cout << "NUMERIC \n";

    // some constants
    std::cout << "pi: " << std::numbers::pi << ", e: " << std::numbers::e << ", ln2: " << std::numbers::ln2 << ", sqrt3: " << std::numbers::sqrt3 << "\n";
    
    // some math operations
    std::cout << "log(2): " << log(5) << ", log10(2): " << log10(5) << ", sqrt(5): " << sqrt(5) << ", pow3(5): " << pow(5,3) << "\n";

    // numeric algorithms
    std::cout << "Greatest common divisor of (33, 22): " << std::gcd(33, 22) << "\n";
    std::cout << "Least common multiple of (550, 100): " << std::lcm(100, 550) << "\n";
    
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum(std::accumulate(v.begin(), v.end(), 0));
    int product(std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>()));
    std::cout << "Sum of first 10 numbers: " << sum << "\n";
    std::cout << "Product of first 10 numbers: " << product << "\n";

    // linear algebra coming in c++26
    std::cout << "\n";
}