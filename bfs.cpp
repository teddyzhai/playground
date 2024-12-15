
#include <functional>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include "vechelper.hpp"
using namespace std;

constexpr int m = 2;
constexpr int n = 2;

//https://leetcode.com/problems/flood-fill/
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {

    auto direct_neighbor = [](int x, int y)
    {
        vector<pair<int, int>> neighbors;

        if (x > 0)
        {
            neighbors.push_back(make_pair(x-1, y));
        }

        if (y > 0)
        {
            neighbors.push_back(make_pair(x, y-1));
        }

        if (x < m)
        {
            neighbors.push_back(make_pair(x+1, y));
        }

        if (y < n)
        {
            neighbors.push_back(make_pair(x, y+1));
        }

        return neighbors;
    };

    vector<vector<int>> ret;
    set<pair<int, int>> visited;
    int origin_color = image[sr][sc];

    function<void(int, int)> bfs = [&](int x, int y){
        image[x][y] = color;
        visited.insert(make_pair(x, y));

        auto nn = direct_neighbor(x, y);
        for(auto &i : nn)
        {
            auto nx = i.first;
            auto ny = i.second;

            if (visited.find(make_pair(nx, ny)) != visited.end())
            {
                continue ;
            }
            else
            {
                if (image[nx][ny] == origin_color)
                {
                    // found.

                    bfs(nx, ny);
                }

            }
        }
    };

    bfs(sr, sc);

    return image;
};

int main(int argc, const char** argv) {
    vector<vector<int>> image = {{1,1,1}, {1,1,0}, {1,0,1}};
    auto ret = floodFill(image, 1, 1, 2);
    std::cout << "flood fill image:" << std::endl;
    for (size_t i = 0; i < ret.size(); i++)
    {
        std::cout << "row: "<< i << std::endl;
        printVec(ret[i], "Col:");
    }

    return 0;
}