#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

using occur_pair = pair<int, int>; // <value, occurrence>
vector<int> topKFrequent(vector<int> &nums, int k) {
    vector<int> res;

    // O(N x log(N))
    // vector<occur_pair> occur_vec(nums.size());
    map<int, int> occur_map;
    for (auto &i : nums)
    {
        occur_map[i] += 1;
    }

    // for (auto &i : occur_map)
    // {
    //     std::cout << "key: " << i.first << std::endl;
    //     std::cout << "Val: " << i.second << std::endl;
    // }

    auto occur_comp = [](occur_pair &p1, occur_pair &p2){
        return (p1.second < p2.second) ? true : false;
    };
    priority_queue<occur_pair, vector<occur_pair>, decltype(occur_comp)> h(occur_comp);

    for (auto &i : occur_map)
    {
         h.push(i);
    }

    while (k-- > 0 && !h.empty())
    {
        res.emplace(res.end(), h.top().first);
        h.pop();
    }


    return res;
}

int main(int argc, const char **argv) {

    auto printVec = [](vector<int> v) {
        for (auto &i : v) {
          std::cout << i << ":  ";
        }
        cout << std::endl;
    };

    vector<int> t = {1,1,1,2,2,3};
    auto k = 2;
    auto t_res = topKFrequent(t, k);
    printVec(t_res);

    return 0;
}
