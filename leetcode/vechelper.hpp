
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

template <>
inline void printVec(vector<vector<int>> v, string name)
{
    std::cout << name << std::endl;

    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << "v" << i << std::endl;
        for(auto &j : v[i])
        {
            std::cout << j << ":  ";
        }
        cout << std::endl;
    }
    cout << std::endl;
}