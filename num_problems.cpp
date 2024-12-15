
#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include "vechelper.hpp"
using namespace std;


vector<int> nextPermutation(vector<int> &permutation, int n)
{
    vector<int> res;
    // double pointer

    // Assuming permutation.size() >= n.

    auto i = n - 1;
    auto j = i - 1;
    while (i > 0) {
        if (permutation[j] < permutation[i])
        {
            // swap
            auto temp = permutation[j];
            permutation[j] = permutation[i];
            permutation[i] = temp;
            res = permutation;
            break;
        }
        else
        {
            if (j >0)
            {
                j--;
            }
            else {
                i--;
                j= i;
            }

        }
    }



    return res;
}

vector<int> smallestSubarrayWithKDistinct(vector<int> &arr, int k)
{
    // sliding window
    auto i = 0;
    auto j = i + 1;

    vector<int> sub_arr(k);

    // i = 0, j = i+1
    // one iter:
    // check unique? using unordered_map
    //  No: move i to pass arr[j].
    //  Yes: j++

    unordered_map<int, int> occ_map; // <number, occurrence
    occ_map[arr[i]] = 1;

    while (j < arr.size()) {
        auto it = occ_map.find(arr[j]);
        if (it == occ_map.end())
        {
            occ_map[arr[j]] = 1;
        }
        else
        {
            while (i <j) {
                // find the duplicate.
                if (arr[i] != arr[j])
                {
                    occ_map.erase(arr[i]);
                    i++;
                }
                else
                {
                    i++;
                    break;
                }
            }
        }



        if (j - i == (k-1))
        {
            // found
            // end index - start index = length!
            copy(arr.begin()+i, arr.begin()+j+1, sub_arr.begin());
            return sub_arr;
        }

        j++;
    }

    return sub_arr;

}

// From leetcode
class SubArrayDistinctK {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return slidingWindowAtMost(nums, k) - slidingWindowAtMost(nums, k - 1);
    }

private:
    // Helper function to count the number of subarrays with at most k distinct elements.
    int slidingWindowAtMost(vector<int>& nums, int distinctK) {
        // To store the occurrences of each element.
        unordered_map<int, int> freqMap;
        int left = 0, totalCount = 0;

        // Right pointer of the sliding window iterates through the array.
        for (int right = 0; right < nums.size(); right++) {
            freqMap[nums[right]]++;

            // If the number of distinct elements in the window exceeds k,
            // we shrink the window from the left until we have at most k distinct elements.
            while (freqMap.size() > distinctK) {
                freqMap[nums[left]]--;
                if (freqMap[nums[left]] == 0)
                    freqMap.erase(nums[left]);
                left++;
            }

            // Update the total count by adding the length of the current subarray.
            totalCount += (right - left + 1);
        }
        return totalCount;
    }
};

vector<int> smallestSubarrayWithKDistinct2(vector<int> &arr, int k)
{
    unordered_map<int, int> occ_map; // <number, occurrence>
    vector<int> sub_arr(k);

    auto j = 0;
    auto i = 0;
    while (j < arr.size())
    {
        if (occ_map.find(arr[j]) != occ_map.end())
        {
            occ_map[arr[j]] = 1;
        }
        else
        {
            // move i to the position after arr[j]
            while (arr[i] != arr[j])
            {
                occ_map.erase(arr[i]);
                i++;
            }
            // erase the duplicate as well.
            occ_map.erase(arr[i]);
            // start from the one after the duplicate.
            i++;
        }

        if (j - i == k +1)
        {
            // found
            // end index - start index = length!
            copy(arr.begin()+i, arr.begin()+j+1, sub_arr.begin());
            return sub_arr;
        }

        j++;
    }

    // not found.
    return sub_arr;;
}

// https://www.naukri.com/code360/problems/house-robber_839733?topList=top-uber-coding-interview-questions&problemListRedirection=true&company%5B%5D=Uber&difficulty%5B%5D=Medium&sort_entity=reactions_count&sort_order=DESC
long long int houseRobber(vector<int>& valueInHouse)
{
    // num cannot be in the adjacent elements.
    // size-1 adjacent to 0.

    // odd index sum
    // even index sum
    // take care of the last element.

    // Log(N)
    auto isLastEven = ((valueInHouse.size()-1 % 2) == 0) ? true : false;

    auto odd_sum = 0;
    auto odd_min = 0;
    auto even_sum = 0;
    auto even_min = 0;
    for (size_t i = 0; i < valueInHouse.size(); i++)
    {
        if (i%2 == 0)
        {
            even_sum+= valueInHouse[i];
            even_min = (valueInHouse[i]<even_min) ? valueInHouse[i] : even_min;
        }
        else
        {
            odd_sum += valueInHouse[i];
        }
    }

    if (isLastEven)
    {
        even_sum -= even_min;
    }

    return (even_sum > odd_sum)? even_sum : odd_sum;
}

// int minMoveNextGreater(vector<int> nums, int k)
// {

// }

// int lengthOfLongestConsecutiveSequence(vector<int> &arr, int n) {
//     // slow, fast pointer

//     auto ret = 0;
//     auto i = 0;
//     auto j = i + 1;
//     while (j < arr.size()-1)
//     {
//         if (j-i == arr[j]-arr[i])
//         {
//             // move j
//             j++;
//         }
//         else if (j - i < arr[j]-arr[i]) {
//             i++;
//         }
//     }

//     return ret;
// }

int getTotalIslands(int arr[][5], int n, int m)
{
    int ret = 0;
    // iterate: find 1,
    // search neighbor 1s. using bfs
    // Yes:
    //      already in visited?
    //        Yes:
    //        No: put in visited

    set<pair<int, int>> visited;

    auto construct_n = [](pair<int, int> &p, int n, int m){
        vector<pair<int, int>> res;
        auto i = p.first;
        if (p.first>0 && p.first<n)
        {
            res.emplace_back(make_pair(p.first-1, p.second));
            res.emplace_back(make_pair(p.first+1, p.second));
        }
        auto j = p.second;
        if (j>0 && j<m)
        {
            res.emplace_back(make_pair(p.first, p.second-1));
            res.emplace_back(make_pair(p.first, p.second+1));
        }

        if (i == 0 && j> 0)
        {
            res.emplace_back(make_pair(p.first, p.second-1));
        }
        if (i == 0 && j<m)
        {
            res.emplace_back(make_pair(p.first, p.second+1));
        }

        if (j == 0 && i>0)
        {
            res.emplace_back(make_pair(p.first-1, p.second));
        }
        if (j == 0 && i<m)
        {
            res.emplace_back(make_pair(p.first+1, p.second));
        }

        // diagonal
        if (i > 0 && j > 0)
        {
            res.emplace_back(make_pair(p.first-1, p.second-1));
        }
        if (i < n && j < m)
        {
            res.emplace_back(make_pair(p.first+1, p.second+1));
        }

        if (i > 0 && j < m)
        {
            res.emplace_back(make_pair(p.first-1, p.second+1));
        }

        if (i < n && j > 0)
        {
            res.emplace_back(make_pair(p.first+1, p.second-1));
        }

        return res;
    };

    function<void(pair<int, int>)> neighbor_bfs = [&](pair<int, int> p){
        queue<pair<int, int>> bfs;
        bfs.push(p);

        auto n_vec = construct_n(p, n, m);

        while (!bfs.empty())
        {
            auto qn = bfs.front();
            bfs.pop();

            if (visited.find(qn) == visited.end())
            {
                visited.insert(qn);

                if (arr[p.first][p.second] == 1)
                {
                    ret++;
                }
            }
            else
            {
                continue;
            }

            for(auto &np : n_vec)
            {
                neighbor_bfs(np);
            }

        }
    };

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (arr[i][j] == 0)
            {
                continue;
            }
            neighbor_bfs(make_pair(i, j));
        }
    }

    return ret;
}

// https://leetcode.com/problems/is-graph-bipartite/description/
bool isBipartite(vector<vector<int>>& graph) {

    auto ret = false;

    set<int> s1; // node id
    set<int> s2; // node id
    vector<set<int>> colors;
    colors.push_back(s1);
    colors.push_back(s2);

    set<int> visited;

    function<bool(int, vector<int>&)> dfs = [&](int color_set, vector<int> &nn)
    {

        for(auto &j : nn)
        {
            if (visited.find(j) != visited.end())
            {
                // neighbors cannot have the same color.
                if (colors[color_set].find(j) != colors[color_set].end())
                {
                    return false;
                }
            }
            else
            {
                visited.insert(j);
                return dfs(1-color_set, graph[j]);
            }
        }

        return true;
    };

    // iterate nodes.
    for (size_t i = 0; i < graph.size(); i++)
    {
        // not visited yet.
        if (visited.find(i) == visited.end())
        {
            visited.insert(i);
            colors[0].insert(i);
            // dfs: set 1, neighbor nodes.
            if (!dfs(0, graph[i]))
            {
                return false;
            }
        }
    }

    return true;
}

// vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

// }

int maxLengthChain(vector<pair<int, int>> &p, int n) {
    // backtracking?
    // using pint_t = pair<int, int>;
    // set<pair<int, int>> visited;
    auto max_len = 0;

    // function<void(pint_t&)> backtracking = [&](pint_t &pp){
    //     if (visited.size() == p.size())
    //     {
    //         // end
    //         return ;
    //     }

    //     for (size_t i = 0; i < p.size(); i++)
    //     {
    //         if (visited.find(p[i]) != visited.end())
    //         {
    //             continue;
    //         }
    //         if (pp.second == p[i].first)
    //         {
    //             visited.insert(p[i]);
    //             max_len++;
    //             backtracking(p[i]);
    //         }
    //     }
    // };

    sort(p.begin(), p.end());
    // double pointer
    auto i = 0;
    auto j = i+1;
    auto len = 0;
    while (j < p.size())
    {
        if (p[j].first == p[i].second)
        {
            // found
            len++;
            if (len > max_len)
            {
                max_len = len;
            }
            j++;
        }
        else
        {
            i++;
            j=i+1;
            len=0;
        }
    }



    return max_len;
}

int main(int argc, const char** argv){

    {
        vector<int> v1 = {1, 2, 3};
        auto res = nextPermutation(v1, 3);
        printVec(res, "next permu");

        vector<int> v2 = {2, 3, 1, 5, 4};
        printVec(nextPermutation(v2, 5), "next permu 2");

        vector<int> v3 = {1, 2, 2, 3, 1, 3};
        auto v3_res = smallestSubarrayWithKDistinct(v3, 3);
        printVec(v3_res, "smallest subarray");
        auto v3_res2 = smallestSubarrayWithKDistinct(v3, 2);
        printVec(v3_res2, "smallest subarray2");

        vector<int> v4 = {2,7,9,3};
        std::cout << "house robber: " << houseRobber(v4) << std::endl;

        // int tarr[4][5] = {{0, 1, 1, 0, 0},
        //                 {1, 0, 0, 1, 0},
        //                 {0, 0, 1, 0, 0},
        //                 {1, 0, 0, 0, 1}};
        // int res_tarr = getTotalIslands(tarr, 4, 5);

        vector<vector<int>> g = {
            {1,2,3},
            {0,2,},
            {0,1,3},
            {0,2}};
        std::cout << "isBipartite? " << isBipartite(g) << std::endl;

    }

    {
        pair<int, int> v1 = {3,4};
        pair<int, int> v2 = {1,2};
        pair<int, int> v3 = {2,3};
        vector<pair<int, int>> c = {v1, v2, v3};
        std::cout << "max len chain: "<< maxLengthChain(c, 3) << std::endl;
    }


    return 0;
}