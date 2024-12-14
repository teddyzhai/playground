#include "graph.hpp"
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

Node* cloneGraph(Node* node) {

    // DFS, BFS ?

    // vector<Node*> copied;
    unordered_map<int, Node*> copied;

    function<void(Node*)> bfs = [&](Node *n){
        Node *n_copy = new Node(n->val);
        copied[n->val] = n_copy;

        for(auto &i : n->neighbors)
        {
            if (copied.find(i->val) != copied.end())
            {
                copied[n->val]->neighbors.push_back(copied[i->val]);
            }
            else
            {
                bfs(i);
            }
        }
    };

    bfs(node);

    Node *n = copied.begin()->second;
    return n;
}

int main(int argc, const char** argv) {
    vector<Node*> graph;
    for (size_t i = 0; i < 4; i++)
    {
         auto n = new Node(i+1);
         graph.push_back(n);
    }
    graph[0]->neighbors.push_back(graph[1]);
    graph[0]->neighbors.push_back(graph[3]);

    graph[1]->neighbors.push_back(graph[0]);
    graph[1]->neighbors.push_back(graph[2]);

    graph[2]->neighbors.push_back(graph[1]);
    graph[2]->neighbors.push_back(graph[3]);

    graph[3]->neighbors.push_back(graph[0]);
    graph[3]->neighbors.push_back(graph[2]);

    Node* n_copy = cloneGraph(graph[0]);
    std::cout << "n copy val: "<< n_copy->val << std::endl;
    std::cout << "n copy neighbour: "<<  std::endl;
    for(auto &i : n_copy->neighbors)
    {
        std::cout << "  - neighbour val: " << i->val << std::endl;
    }



    return 0;
}