
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int leastInterval(vector<string>& tasks, int n) {
    // map<char, occ>   -> O(N)
    // sorted by highest occ first. (? priority queue)
    // assuming highest occ x, at least the schedule needs (x-1) * n.
    // Filling "gap"

    // 2nd case: when n gaps filled while there are still tasks.
    // start

    using occ_t = pair<string, int>;

    map<string, int> occ_map;
    for(auto &i : tasks)
    {
        occ_map[(i)]++; /// static_cast<int>
    }

    auto occ_cmp = [](occ_t a, occ_t b)
    {
        return (a.second < b.second) ? true : false;
    };
    priority_queue<occ_t, vector<occ_t>, decltype(occ_cmp)> pq(occ_cmp);

    for(auto &i : occ_map)
    {
        pq.push(i);
    }

    int interval = 0;
    int index = 0;
    int m = n;
    while (!pq.empty() ) {


        int curr_max = pq.top().second * (m) + index;
        interval = (curr_max > interval) ? curr_max : interval;

        if (index % m == 0)
        {
            // move index
            index = interval + 1;
        }

        // filling the n gaps.
        index++;
        pq.pop();


    }

    return  interval;
}

int main(int argc, const char** argv) {

    vector<string> v1 = {"A","A","A","B","B","B"};
    vector<string> v2 = {"A","C","A","B","D","B"};
    std::cout << "least interval with 2: 7: " << leastInterval(v1, 2) << std::endl;
    std::cout << "least interval with 1: 5: " << leastInterval(v2, 1) << std::endl;


    return 0;
}