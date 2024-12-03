
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

int main(int argc, const char** argv){

    vector<int> v1 = {1, 2, 3};
    auto res = nextPermutation(v1, 3);
    printVec(res);

    vector<int> v2 = {2, 3, 1, 5, 4};
    printVec(nextPermutation(v2, 5));


    return 0;
}