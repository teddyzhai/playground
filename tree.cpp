

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

 #include <iostream>
#include <queue>
#include <vector>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

using namespace std;

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


    return 0;
}
