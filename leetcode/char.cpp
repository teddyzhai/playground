

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>

using namespace std;

// O(N)
bool uniqueChar(std::string str)
{
    // Use bit array to check if more than 1 chars are the same (the same bit set)
    uint32_t asciTable[8];

    memset(asciTable, 0, sizeof(asciTable));

    auto len = str.length();
    for (size_t i = 0; i < len; i++)
    {
        auto unit = str[i] / 32;
        auto offset = str[i] % 32;

        // check if bit already set, if yes, return false.
        // if no, set it.

        auto isBitSet = [](auto val, auto k)
        {
            if ((val & (1 << k)) > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        };

        if (isBitSet(asciTable[unit], offset))
        {
            return false;
        }
        else
        {
            // set the bit
            asciTable[unit] |= (1 << (uint32_t)offset);
        }
    }
    return true;
}

// O(N)
bool isPermutationStr(std::string &str1, std::string &str2)
{
    uint32_t asciTable1[8];
    uint32_t asciTable2[8];

    memset(asciTable1, 0, sizeof(asciTable1));
    memset(asciTable2, 0, sizeof(asciTable2));

    // one scans forward and the second one scans backwards
    auto len1 = str1.length();
    auto len2 = str2.length();
    if (len2 != len1)
    {
        return false;
    }

    for (size_t i = 0; i < str1.length(); i++)
    {
        if (str1[i] != str2[len2 - i - 1])
        {
            return false;
        }
    }

    return true;
}

// https://leetcode.com/problems/sort-characters-by-frequency/description/
string frequencySort(string s) {
    string ret;
    // map<char, int> occ_map;

    // // pair <char, int>
    // using char_occ_t = pair<char, int>;
    // vector<char_occ_t> char_occs;

    vector<int> occ_vec(256, 0);
    for (size_t i = 0; i < s.length(); i++)
    {
        occ_vec[(int)s[i]]++;
    }

    using occ_t = pair<int, int>;
    auto cmp = [](occ_t &p1, occ_t &p2){
        return (p2.second > p1.second);
    };
    priority_queue<pair<int, int>, vector<occ_t>, decltype(cmp)> pq(cmp);
    for (size_t i = 0; i < occ_vec.size(); i++)
    {
        if (occ_vec[i] == 0)
        {
            continue;
        }
        pq.push(make_pair(i, occ_vec[i]));
    }

    while (!pq.empty()) {
        auto p = pq.top();
        if (p.second == 0)
        {
            // end
            break;
        }
        string temp(p.second, p.first);
        ret.append(temp);
        pq.pop();
    }

    return ret;
}

int main(int argc, const char** argv) {

    std::string word1("copyrightable");

    if (uniqueChar(word1)) {
        std::cout << "right!" << std::endl;
    }

    std::string word2("blab");
    if (uniqueChar(word2) == false) {
        std::cout << "right for dup!" << std::endl;
    }

    // permutation tests
    std::string str1p("abc");
    std::string str2p("cba");

    if (isPermutationStr(str1p, str2p))
        std::cout << "Right for permutation" << std::endl;

    std::string str3p("abcd");
    std::string str4p("cbad");
    if (isPermutationStr(str3p, str4p) == false) {
        std::cout << "Right for not permutation" << std::endl;
    }

    string str5("tree");
    std::cout << "frequencySort:" << frequencySort(str5) << std::endl;


    return 0;
}
