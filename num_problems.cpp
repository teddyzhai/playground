
#include <algorithm>
#include <unordered_map>
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


int main(int argc, const char** argv){

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


    return 0;
}