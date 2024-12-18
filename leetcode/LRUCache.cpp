
#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;


class LRUCache
{
public:
    // vector<int> lru_;
    list<int> lru_list_;
    unordered_map<int, int> key_map_;

    const int cap_;
    int curr_size_;

    LRUCache(int capacity) : cap_(capacity), curr_size_(0)
    {
    }

    int get(int key)
    {
        if (key_map_.find(key) == key_map_.end())
        {
            return -1;
        }
        else
        {
            update_lru(key);
            return key_map_[key];
        }
    }

    void put(int key, int value)
    {
        key_map_[key] = value;
        update_lru(key);

        if (curr_size_ < cap_)
        {
            curr_size_++;
        }
        else
        {
            // key_map_.erase(lru_.back());
            key_map_.erase(lru_list_.back());
            // lru_.pop_back();
            lru_list_.pop_back();
        }
        lru_list_.push_front(key);

    }
private:
    void update_lru(int key)
    {
        // log(N) search and delete
        // auto i = find(lru_.begin(), lru_.end(), key);
        auto i = find(lru_list_.begin(), lru_list_.end(), key);
        if (i != lru_list_.end())
        {
            // lru_.erase(i);
            lru_list_.erase(i);

            // Insert will enlarge the vector
            // lru_.insert(lru_.begin(), key);

            // list
            lru_list_.push_front(key);
        }



    }
};

int main(int argc, char const *argv[])
{
    LRUCache cache(3);

    cache.put(1,1);
    cache.put(2,2);
    cache.put(3,3);
    cache.put(4,5);
    std::cout << "3: " << cache.get(3) << std::endl;
    std::cout << "-1 ==: " << cache.get(1) << std::endl;
    std::cout << "2 == : " << cache.get(2) << std::endl;

    cache.put(5,5);
    std::cout << "-1 == : " << cache.get(4) << std::endl;
    std::cout << "3 == : " << cache.get(3) << std::endl;

    return 0;
}
