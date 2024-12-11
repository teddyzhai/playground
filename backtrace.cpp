


#include <functional>
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

int main(int argc, const char** argv) {
    vector<int> v1 = {1,2,3};
    Solution s;
    auto res1 = s.permute(v1);
    printVec(res1, "permutation");

    auto res_my = permute(v1);
    printVec(res_my, "my permutation");

    return 0;
}