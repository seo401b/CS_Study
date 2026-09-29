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
    void dfs(TreeNode* root, int targetSum, std::vector<std::vector<int>>& result, std::vector<int>& cur){
        if(root==nullptr) return;

        int remaining = targetSum - root->val;
        cur.push_back(root->val);

        if(root->left==nullptr && root->right==nullptr){
            if(remaining==0){
                result.push_back(cur);
            }
        }
        else{
            dfs(root->left, remaining, result, cur);
            dfs(root->right, remaining, result, cur);
        }
        cur.pop_back();
    }
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum) {
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        dfs(root, targetSum, result, cur);
        return result;
    }
};





int main() {
    // 예시 트리 구성: [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1]
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->right->right = new TreeNode(1);

    Solution solution;
    int targetSum = 22;

    std::vector<std::vector<int>> paths = solution.pathSum(root, targetSum);

    // 결과 출력
    std::cout << "TargetSum " << targetSum << "인 경로들:\n";
    for (const auto& path : paths) {
        std::cout << "[ ";
        for (int val : path) {
            std::cout << val << " ";
        }
        std::cout << "]\n";
    }

    return 0;
}