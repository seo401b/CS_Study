#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
private:
    void dfs(TreeNode* root, std::vector<int>& result){
        if(root==nullptr) return;
        dfs(root->left, result);
        result.push_back(root->val);
        dfs(root->right, result);
    }
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> result;
        dfs(root, result);
        return result;
    }
};




int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(6);
    root->left->right->right = new TreeNode(7);
    root->right->right->left = new TreeNode(9);

    Solution solution;

    std::vector<int> paths = solution.inorderTraversal(root);
    std::cout << "Inorder Traversal Result: ";
    for (int val : paths) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}