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
    void dfs(TreeNode* root, int cnt, int& max){
        if(root==nullptr) {
            if(max<cnt) max = cnt;
            return;
        }
        dfs(root->left, cnt+1, max);
        dfs(root->right, cnt+1, max);
    }
public:
    int maxDepth(TreeNode* root) {
        int max = 0;
        dfs(root, 0, max);
        return max;
    }
};


int main() {
    // 테스트용 이진 트리 생성
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    // 객체 생성 및 함수 호출
    Solution solution;
    int result = solution.maxDepth(root);

    // 결과 출력
    std::cout << "Max Depth: " << result << std::endl;

    return 0;
}