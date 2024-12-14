

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 #include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include "treeHelper.hpp"
#include "vechelper.hpp"

void BFS(TreeNode* root) {

    if (root == nullptr) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        // cout << node->data << " ";
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);

    }
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;

    queue<TreeNode*> q;
    // root can be null.
    q.push(root);

    TreeNode sep(1001 /* invalid val */);
    q.push(&sep);

    vector<int> temp;
    while (!q.empty())
    {
        auto *node = q.front();
        q.pop();


        if (node != nullptr && node->val != 1001)
        {
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
            q.push(&sep);

            temp.push_back(node->val);


        }

        if (node->val == 1001)
        {
            res.push_back(temp);
            temp.clear();
        }
    }


    return res;
}


int getNrNodes(TreeNode *root)
{
    int nrL = 0;
    if (root->left != NULL)
    {
        nrL = getNrNodes(root->left);
    }
    int nrR = 0;
    if (root->right != NULL)
    {
        nrR = getNrNodes(root->right);
    }

    return nrL + nrR + 1;
}

/// basic ops
// In-order DFS: Left, Root, Right
void inOrderDFS(TreeNode* node) {
    if (node == nullptr) return;

    inOrderDFS(node->left);
    // cout << node->data << " ";
    // do something for node.
    inOrderDFS(node->right);
}

// Pre-order DFS: Root, Left, Right
void preOrderDFS(TreeNode* node) {
    if (node == nullptr) return;

    // cout << node->data << " ";
    // do something for node.
    preOrderDFS(node->left);
    preOrderDFS(node->right);
}

// post-order: root, right, left?


vector<int> rightSideView(TreeNode* root) {
    vector<int> res;

    // DS: level -> stack
    map<int, stack<TreeNode*>> level_nodes;

    function<void(TreeNode*, int)> pre_order = [&](TreeNode *n, int level){
        if (n == nullptr)
        {
            return ;
        }
        level_nodes[level].push(n);

        pre_order(n->left, level+1);
        pre_order(n->right, level+1);
    };

    pre_order(root, 0);

    for(auto &i : level_nodes)
    {
        if (!(i.second.empty()))
        {
            auto *n = i.second.top();
            if (n != nullptr)
            {
                res.push_back(n->val);
            }
            else
            {
                res.push_back(0);
            }
        }
        else
        {
            res.push_back(0);
        }
    }

    return res;

}

TreeNode* construct_rightView_tree(/* TreeNode *root */)
{
    // level 0:
    TreeNode *root = new TreeNode(1);

    // level 1:
    TreeNode *l1 = new TreeNode(2);
    TreeNode *r1 = new TreeNode(3);
    root->left = l1;
    root->right = r1;

    // level 2:
    TreeNode *l2_1 = new TreeNode(5);
    TreeNode *l2_2 = new TreeNode(4);
    l1->right = l2_1;
    r1->right = l2_2;

    return root;
}

int main(int argc, const char** argv) {
    TreeNode root(3);

    TreeNode l(9);
    TreeNode r(20);

    root.left = &l;
    root.right = &r;

    TreeNode lr(15);
    TreeNode rr(7);
    r.left = &lr;
    r.right = &rr;

    vector<vector<int>> res = levelOrder(&root);
    for (auto &i : res)
    {
        for (auto &j : i)
        {
            std::cout << "vec: " << j << " ,";
        }
        cout << std::endl;

    }

    std::cout << "node num: " << getNrNodes(&root) << std::endl;

    TreeNode *root2 = construct_rightView_tree(/* root2 */);
    auto res2 = rightSideView(root2);
    printVec(res2, "right side view");



    return 0;
}
