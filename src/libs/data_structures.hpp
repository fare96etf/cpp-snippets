#include <iostream>
#include <vector>
#include <deque>
#include <compare>
#include <array>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>
#include <forward_list>
#include <set>
#include <map>

// dynamic contiguous array
void try_vectors() {
    std::cout << "VECTORS" << std::endl << std::endl;

    std::vector<int> numVec { 2, 3 };
    std::cout << "Vector size: " << numVec.size() << ", Vector capacity: " << numVec.capacity() << std::endl;
    numVec.insert(numVec.begin(), { 0, 1 });
    std::cout << "Vector size: " << numVec.size() << ", Vector capacity: " << numVec.capacity() << std::endl;
    numVec.push_back(4);
    std::cout << "Vector size: " << numVec.size() << ", Vector capacity: " << numVec.capacity() << std::endl;
    numVec.emplace_back(5);
    std::cout << "Vector size: " << numVec.size() << ", Vector capacity: " << numVec.capacity() << std::endl;
    numVec.emplace(numVec.end(), 6);
    std::cout << "Vector size: " << numVec.size() << ", Vector capacity: " << numVec.capacity() << std::endl;
    numVec.resize(10);
    std::cout << "Vector size: " << numVec.size() << ", Vector capacity: " << numVec.capacity() << std::endl;

    for (auto num : numVec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    numVec.clear();
    numVec.push_back(10);
    std::cout << "New element: " << numVec.at(0) << std::endl;

    numVec.pop_back();
    std::cout << "Size after clear and popback: " << numVec.size() << std::endl;
    
    std::vector<int> numVec2 { 1, 3, 5 };
    //auto comparisonResult = numVec <=> numVec2; //this should work in c++20

    std::cout << std::endl;
}

// double-ended queue that enables indexing and fast insertion and deletion at both ends
void try_deque() {
    std::cout << "DEQUES" << std::endl << std::endl;

    std::deque<int> dq { 2, 3 };
    dq.push_front(1);
    dq.push_back(4);
    dq.emplace_front(0);
    dq.emplace_back(5);
    dq.insert(dq.begin() + 2, { 6, 7 });

    for (auto num : dq) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    dq.pop_back();
    dq.pop_front();
    std::cout << "First element after pop front: " << dq.front() << std::endl;
    std::cout << "Last element after pop back: " << dq.back() << std::endl;

    std::cout << std::endl;
}

// combines the performance and accessibility of a C-style array with the benefits of a standard container, 
// such as knowing its own size, supporting assignment, random access iterators
void try_array() {
    std::cout << "ARRAYS" << "\n\n";

    std::array<int, 3> a1 {2, 3, 1};
    std::sort(a1.begin(), a1.end());
    for (const auto& s : a1)
        std::cout << s << ' ';
    std::cout << '\n';
 
    std::array<std::string, 2> a2{"str1", "str2"};
    for (const auto& s : a2)
        std::cout << s << ' ';
    std::cout << '\n';

    std::array a3{3.0, 1.0, 4.0}; // auto type and size deduction
    double element = a3.at(2);
    std::cout << "Third element: " << element << "\n";

    std::cout << '\n';
}

// std::list is a container that supports constant time insertion and removal of elements from 
// anywhere in the container. Fast random access is not supported. It is usually implemented as a doubly-linked list. 
// Compared to std::forward_list this container provides bidirectional iteration capability 
// while being less space efficient
void try_list_and_forwardList() {
    std::cout << "LIST AND FORWARD LIST" << "\n\n";

    std::list<int> list1 { 2, 3, 4 };
    list1.push_front(0);
    list1.emplace_front(1);
    list1.push_back(5);
    list1.push_back(5);
    list1.emplace_back(6);
    list1.emplace_back(5);
    list1.pop_back();

    // list1.at(0) // not possible
    // list1[0] // not possible

    std::list<int> list2 { 10, 11, 12 };

    list1.splice(list1.end(), list2); // moves pointers from list2 to list1
    std::cout << "List1 after splice: \n";
    for (int n : list1)
        std::cout << n << " ";
    std::cout << "\n";
    if (list2.empty()) {
        std::cout << "List2 should be empty after splice \n";
    }
    list1.unique(); // should remove 5
    std::cout << "List1 after unique: \n";
    for (int n : list1)
        std::cout << n << " ";
    std::cout << "\n";
    
    std::forward_list<int> flist1 { 3, 4, 5 };
    flist1.push_front(2);
    flist1.push_front(1);
    flist1.pop_front();

    std::cout << "Forward list: \n";
    for (int n : flist1) {
        std::cout << n << " ";
    }

    std::cout << "\n";
}

// associative containers
// -set contains set of unique sorted keys, efficient insertion, removal and access (logarithmic complexity) 
// -map contains key-value pairs with unique keys, same efficiency as set, iterate in ascending order of keys
// -multiset and multimap allow duplicate keys
// -unorderedset and map has their values, elements are not sorted in any particular order, but organized into buckets,
//      which bucket an element is placed into depends entirely on the hash of its value, this allows fast access to 
//      individual elements, since once a hash is computed, it refers to the exact bucket the element is placed into.
//      Container elements may not be modified (even by non const iterators) since modification could 
//      change an element's hash and corrupt the container
void try_setmap_multisetmap_unorderedsetmap() {
    std::cout << "SETS AND MAPS" << "\n\n";

    std::set<int> s { 1, 3, 5, 7, 7 };
    s.insert(4);
    s.insert(6);
    s.insert(6);
    s.erase(1);

    std::cout << "Set: ";
    for (int n : s) {
        std::cout << n << " ";
    }
    std::cout<< "\n";

    s.insert(2);
    auto it = s.find(2);

    if (it != s.end()) {
        std::cout << "There is a key in set with value: " << *it << "\n";
    }

    std::map<std::string, double> mapPrices;
    mapPrices["T-Shirt"] = 20.00;
    mapPrices["Sneakers"] = 100.00;
    mapPrices["Laptop"] = 455.99;
    mapPrices["Coffee"] = 3.2;
    mapPrices["Ananas juice"] = 6;
    
    std::cout << "Map: \n";
    for (const auto& [key, value] : mapPrices) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';

    // different comparison function
    auto compare = [](const std::string& lhs, const std::string& rhs) {
        if (lhs.size() != rhs.size()) {
            return lhs.size() < rhs.size(); // First compare by length
        } else {
            return lhs < rhs; // Then compare lexicographically
        }
    };

    std::map<std::string, double, decltype(compare)> mapPrices2(compare);
    for (const auto& pair : mapPrices) {
        mapPrices2.insert(pair);
    }
    std::cout << "Map with new string comparison: \n";
    for (const auto& [key, value] : mapPrices2) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';

    std::cout << '\n';
}

void try_stack_queue_priorityqueue() {

}