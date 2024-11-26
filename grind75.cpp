#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/course-schedule/description/
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {


    // std::map<int, std::vector<int>> prec_map;
    // use set for its uniqueness
    map<int, set<int>> prec_map;
    for (auto &i : prerequisites)
    {
        prec_map[i[0]].insert(i[1]);
    }

    set<int> take;

    function<bool(int)> can_take = [&](int c)
    {
        if (prec_map.find(c) == prec_map.end())
        {
            // no dependent course.

            return true;
        }

        if (take.find(c) != take.end())
        {
            // one needs c that is already in the needed course, cycle.
            return false;
        }

        take.insert(c);


        for (auto &i : prec_map[c])
        {
            if (can_take(i) == true)
            {
                // take.insert(i);
                return true;
            }
            else
            {
                return false;
            }
        }

        return true;
    };

    // find cycle for each element.
    // return false if found.
    for (auto & [k, v] : prec_map) // c++17
    {
        if (!can_take(k))
        {
            return false;
        }
    }

    return true;
}

int main(int argc, const char** argv) {
    vector<int> v1 = {1, 0};
    vector<int> v2 = {0, 1};

    vector<vector<int>> v = {v1, v2};
    std::cout << "can ?" << canFinish(2, v) << std::endl;

    return 0;
}
