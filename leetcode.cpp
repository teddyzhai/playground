

#include <iostream>
#include <queue>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

template<typename T>
void pop_println(std::string rem, T& pq)
{
    std::cout << rem << ": ";
    for (; !pq.empty(); pq.pop())
        std::cout << pq.top() << ' ';
    std::cout << '\n';
}

std::vector<int> getTopK(vector<int> &nums, int k)
{
    vector<int> res(k);
    std::cout << "sizeL " << res.size() << std::endl;

    priority_queue<int> heap(nums.begin(), nums.end());
    // pop_println("heap", heap);

    for (size_t i = 0; i < k; i++)
    {
        // check nums has >= k elements
        res.emplace(res.begin(), heap.top());
        heap.pop();
    }

    return res;
}


int main(int argc, char const *argv[])
{
    auto printVec = [](vector<int> v) {
        std::cout << "size: " << v.size() << std::endl;
        for (auto &i : v) {
          std::cout << i << ":  ";
        }
        cout << std::endl;
    };


    vector<int> t = {3, 2, 1, 5, 6, 4};
    auto t_res = getTopK(t, 3);
    std::cout << "size t_res: " << t_res.size() << std::endl;
    printVec(t_res);

    return 0;
}
