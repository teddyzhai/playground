

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> GreaterElement(vector<int> &nums1) {

    stack<int> lifo;
    lifo.push(-1);
    vector<int> ret(nums1.size());

    for (int i = nums1.size() - 1; i >= 0; i--)
    {
        while (lifo.top() != -1 && nums1[i] > lifo.top())
        {
            lifo.pop();
        }
        ret[i] = lifo.top();
        lifo.push(nums1[i]);


    }

    return ret;
}

// vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {

//     for (auto &i : nums1)
//     {

//     }

// }

int main(int argc, const char **argv) {

    auto printVec = [](vector<int> v) {
        for (auto &i : v) {
          std::cout << i << ":  ";
        }
        cout << std::endl;
    };

    vector<int> v1 = { 2, 1, 2, 4, 3 };
    printVec(v1);
    std::cout << "next greater:" << std::endl;
    auto v1_ans = GreaterElement(v1);
    for (auto &i : v1_ans)
    {
        std::cout << i << ":  ";
    }
    cout << std::endl;

    return 0;
}
