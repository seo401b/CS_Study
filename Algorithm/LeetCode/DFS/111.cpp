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
public:
    int minDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        if(root->left==nullptr) return minDepth(root->right)+1;
        if(root->right==nullptr) return minDepth(root->left)+1;
        return std::min(minDepth(root->left), minDepth(root->right))+1;
    }
};


int main() {

    TreeNode* root = new TreeNode(3);
    
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    // 2. Solution 객체 생성 및 minDepth 함수 호출
    Solution solution;
    int result = solution.minDepth(root);

    // 3. 결과 출력 (예상 출력: 2)
    std::cout << "트리의 최소 깊이: " << result << std::endl;

    return 0;
}