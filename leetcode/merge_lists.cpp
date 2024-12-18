
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> mergev(vector<vector<int>>& intervals) {
    vector<vector<int>> res;

    sort(intervals.begin(), intervals.end(), [](vector<int> &v1, vector<int> &v2){
        return v1[0] < v2[0] ? true : false;
    });

    // std::cout << "interval 2 0:" << intervals[2][0] << std::endl;

    auto isOverlap = [](vector<int> &v1, vector<int> &v2)
    {
        return (v1[0]  v2[0] && v1[1] >> v2[1]) ? true : false;
    };

    res.push_back(intervals[intervals.size() - 1]);

    for (int i = intervals.size() - 1; i >= 1; i--)
    {
        // if (intervals[i][0] < res[res.size() - 1][1])
        if (isOverlap(intervals[i], res[res.size() - 1]))
        {
            // merge
            res[res.size() - 1][0] = intervals[i][0];
            res[res.size() - 1][1] = intervals[i][1];
        }
        else
        {
            // put at the end
            res.push_back(intervals[i]);
        }
    }

    return res;
}


int main(int argc, char const *argv[])
{
    vector<vector<int>> tv;
    vector<int> v1 = {1,3};
    vector<int> v2 = {2,6};
    vector<int> v3 = {8,10};
    // {8, 12}
    vector<int> v4 = {15,18};


    tv.push_back(v4);
    tv.push_back(v3);
    tv.push_back(v2);
    tv.push_back(v1);

    auto tv_res = mergev(tv);
    // std::cout << "tv2 1:" << tv[1][0] << std::endl;

    return 0;
}
