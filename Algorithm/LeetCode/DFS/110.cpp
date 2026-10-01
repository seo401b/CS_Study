#include <iostream>
#include <vector>
#include <algorithm>

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
    int getDepth(TreeNode* root){
        if(root==nullptr) return 0;

        int leftDepth = getDepth(root->left);
        int rightDepth = getDepth(root->right);

        return std::max(leftDepth, rightDepth) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        if(root==nullptr) return true;

        int leftDepth = getDepth(root->left);
        int rightDepth = getDepth(root->right);
        if(std::abs(leftDepth - rightDepth) > 1) return false;

        return isBalanced(root->left) && isBalanced(root->right);
    }
};


int main() {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->right->right = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    root->right->right->right = new TreeNode(4);

    // 객체 생성 및 함수 호출
    Solution solution;
    bool result = solution.isBalanced(root);

    // 결과 출력
    std::cout << result << std::endl;

    return 0;
}