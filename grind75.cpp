#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include "listHelper.hpp"

using namespace std;

// https://leetcode.com/problems/course-schedule/description/
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {


    // std::map<int, std::vector<int>> prec_map;
    // use set for its uniqueness
    map<int, set<int>> prec_map;
    for (auto &i : prerequisites)
    {
        prec_map[i[0]].insert(i[1]);
    }

    set<int> take;

    function<bool(int)> can_take = [&](int c)
    {
        if (prec_map.find(c) == prec_map.end())
        {
            // no dependent course.

            return true;
        }

        if (take.find(c) != take.end())
        {
            // one needs c that is already in the needed course, cycle.
            return false;
        }

        take.insert(c);


        for (auto &i : prec_map[c])
        {
            if (can_take(i) == true)
            {
                // take.insert(i);
                return true;
            }
            else
            {
                return false;
            }
        }

        return true;
    };

    // find cycle for each element.
    // return false if found.
    for (auto & [k, v] : prec_map) // c++17
    {
        if (!can_take(k))
        {
            return false;
        }
    }

    return true;
}

bool containsDuplicate(vector<int>& nums) {

    // Log(N)
    sort(nums.begin(), nums.end(), less<int>());

    for (size_t i = 0; i < nums.size()-1; i++)
    {
        if (nums[i] == nums[i+1])
        {
            return true;
        }
    }
    return false;
}

int majorityElement(vector<int>& nums) {
     // O(log N)
    sort(nums.begin(), nums.end());

    auto occ = 1;
    for (size_t i = 0; i < nums.size()-1; i++)
    {
        if (nums[i] == nums[i+1])
        {
            occ++;
        }
        else
        {
            occ = 1;
        }
        if (occ > nums.size()/2)
        {
            occ = nums[i];
            break;
        }
    }
    return occ;
}

bool canConstruct(string ransomNote, string magazine) {

    map<int, int> occ_map; // char: occurrence

    // Log(N)
    for (size_t i = 0; i < magazine.length(); i++)
    {
        occ_map[magazine[i]] += 1;
    }

    // log (N)
    for (size_t i = 0; i < ransomNote.length(); i++)
    {
        if (occ_map.find(ransomNote[i]) == occ_map.end()
            || occ_map[ransomNote[i]] == 0)
        {
            return false;
        }
        else
        {
            if (occ_map[ransomNote[i]] > 0)
            {
                occ_map[ransomNote[i]]--;
            }

        }

    }

    return true;
}



ListNode* reverseList(ListNode* head) {

    // double pointer, with stack (LIFO).

    // ListNode *slow = head;
    // ListNode *fast = head->next;

    // while (fast != nullptr || slow == nullptr)
    // {
    //     ListNode *temp = fast->next;
    //     fast->next = slow;
    //     slow = temp;
    // }

    stack<ListNode*> lifo;
    ListNode *temp = head;
    // log(N)
    while (temp != nullptr) {
        lifo.push(temp);
        temp = temp->next;
    }

    // log(N)
    auto ret = lifo.top();
    temp = ret;
    lifo.pop();
    while (!lifo.empty()) {
        auto pre = lifo.top();
        lifo.pop();

        temp->next = pre;

        temp = pre;
    }
    temp->next = nullptr;

    return ret;
}

int main(int argc, const char** argv) {
    vector<int> v1 = {1, 0};
    vector<int> v2 = {0, 1};

    vector<vector<int>> v = {v1, v2};
    std::cout << "can finish ?" << canFinish(2, v) << std::endl;

    vector<int> v3 = {1,1,1,3,3,4,3,2,4,2};
    std::cout << "v3 contains dup true ?" << containsDuplicate(v3) << std::endl;

    vector<int> v4 = {2,2,1,1,1,2,2};
    std::cout << "v3 majority ? " << majorityElement(v4) << std::endl;

    string s1("aa");
    string s2("aab");
    std::cout << "ransom note true ? " << canConstruct(s1, s2) << std::endl;

    auto *head = createList(8);
    auto *rhead = reverseList(head);
    printList(rhead);

    return 0;
}
