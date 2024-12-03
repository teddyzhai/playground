
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
inline void printVec(vector<T> v)
{

    for (auto &i : v) {
        std::cout << i << ":  ";
    }
    cout << std::endl;

}