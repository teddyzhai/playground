
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template<typename T>
inline void printVec(vector<T> v, string name)
{
    std::cout << name << std::endl;
    for (auto &i : v) {
        std::cout << i << ":  ";
    }
    cout << std::endl;
}

template <>
inline void printVec(vector<pair<int, int>> v, string name)
{
    std::cout << name << std::endl;
    for (auto &i : v) {
        std::cout << "<" << i.first << ", " << i.second << ">  " ;
    }
    cout << std::endl;
}