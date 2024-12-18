
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findDuplicate(vector<int>& nums) {
    // 2 pointers

    // O(N x Log(N))
    sort(nums.begin(), nums.end(), std::less<int>());

    // O(N)
    for (size_t i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] == nums[i+1])
        {
            return nums[i];
        }
    }
    return 0; // not found.
}

// no modify to nums
// only one constant extra space.
int findDuplicate1(vector<int>& nums) {
    // fast-slow pointers

    // Hare & Tortoise Method:
    // consider the array as linked list.
    // index -> node, value -> next node.

    auto slow = nums[0];
    auto fast = nums[0];

    // cycle detection
    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // cycle start detection
    slow = nums[0];
    while(slow != fast){
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}


int main(int argc, char const *argv[])
{
    {
        // vector t1 = {1,3,4,2,2};
        vector<int> t2 = {1,3,4,2,2};

        std::cout << "dup: " << findDuplicate1(t2) << std::endl;

        vector<int> t1 = {3,1,3,4,2};
        std::cout << "dup1: " << findDuplicate1(t1) << std::endl;

        vector<int> t3 = {2,5,9,6,9,3,8,9,7,1};
        std::cout << "dup3: " << findDuplicate1(t3) << std::endl;
    }
    return 0;
}
