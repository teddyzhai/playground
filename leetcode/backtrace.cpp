


#include <algorithm>
#include <functional>
#include <numeric>
#include <set>
#include <vector>
#include "vechelper.hpp"
using namespace std;


// Reference
class Solution {
private:
    vector<vector<int>> res;
public:
    // 主函数，输入一组不重复的数字，返回它们的全排列
    vector<vector<int>> permute(vector<int>& nums) {
        // 记录「路径」
        vector<int> track;
        // 「路径」中的元素会被标记为true，避免重复使用
        vector<bool> used(nums.size(), false);

        backtrack(nums, track, used);
        return res;
    }

    // 路径：记录在 track 中
    // 选择列表：nums 中不存在于 track 的那些元素
    // 结束条件：nums 中的元素全都在 track 中出现
    void backtrack(vector<int>& nums, vector<int>& track, vector<bool>& used) {
        // 触发结束条件
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // 排除不合法的选择
            if (used[i]) {


                // nums[i] 已经在 track 中，跳过
                continue;
            }
            // 做选择
            track.push_back(nums[i]);
            used[i] = true;
            // 进入下一层决策树
            backtrack(nums, track, used);
            // 取消选择
            track.pop_back();
            used[i] = false;
        }
    }
};

// https://leetcode.cn/problems/permutations/
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;

    // track: partial path has been searched.
    vector<int> track;
    vector<bool> visited(nums.size(), false);

    function<void(vector<int>)> backtrack = [&](vector<int> t){

        for (size_t i = 0; i < nums.size(); i++)
        {
            if (track.size() == nums.size())
            {
                // found
                res.push_back(track);
                return ;
            }

            if (visited[i])
            {
                continue;
            }

            track.push_back(nums[i]);
            visited[i] = true;
            // backtrack
            backtrack(track);

            track.pop_back();
            visited[i] = false;
        }
    };

    backtrack(track);

    return res;
}

// https://leetcode.com/problems/combination-sum/
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

    vector<vector<int>> res;
    vector<int> combi;  // intermediate sub-choice and result.
    // vector<bool> visited(candidates.size(), false);


    // I think we need to sort the input ?
    sort(candidates.begin(), candidates.end());

    // combi: current sub-choice. Shall not be set, because an element can be used multiple times.
    // current total: can be derived from combi.
    function<void(int, int)> backtrack = [&](int idx, int total)
    {
        // it must iterate itself
        // for (size_t i = 0; i < candidates.size(); i++)
        // {
            // auto current = accumulate(combi.begin(), combi.end(), 0);
            if (total == target)
            {
                // found
                vector<int> temp(combi.begin(), combi.end());
                // how to avoid copy?
                res.emplace_back(temp);
                return ;
            }

            if (total > target)
            {
                return; // move to the next
            }

            // if (visited[i])
            // {
            //     continue; ;
            // }

            // combi.insert(candidates[i]);
            // combi.push_back(candidates[i]);
            combi.push_back(candidates[idx]);
            // visited[i] = true;
            backtrack(idx, total + candidates[idx]);

            combi.pop_back();
            // combi.push_back(candidates[idx+1]);
            backtrack(idx+1, total+candidates[idx+1]);
            // visited[i] = false;
        // }
    };

    backtrack(0, 0);

    return res;
}

// vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
// }

int main(int argc, const char** argv) {
    vector<int> v1 = {1,2,3};
    Solution s;
    auto res1 = s.permute(v1);
    printVec(res1, "permutation");

    auto res_my = permute(v1);
    printVec(res_my, "my permutation");

    vector<int> v2 ={2,3,6,7};
    auto target = 7;
    auto res2 = combinationSum(v2, target);
    printVec(res2, "comb sum");

    return 0;
}