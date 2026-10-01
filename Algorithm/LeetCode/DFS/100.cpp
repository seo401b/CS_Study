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
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr && q==nullptr) return true;
        if(p==nullptr || q==nullptr || p->val!=q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};


int main() {
    // 1번 트리 (p) 생성: [1, 2, 3]
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // 2번 트리 (q) 생성: [1, 2, 3] (p와 동일)
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    // 3번 트리 (r) 생성: [1, 2, 4] (p와 다름)
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(4);

    Solution solution;

    // std::boolalpha를 사용하면 1/0 대신 true/false로 출력됩니다.
    std::cout << std::boolalpha;
    
    std::cout << "p and q are same? " << solution.isSameTree(p, q) << std::endl; // true 예상
    std::cout << "p and r are same? " << solution.isSameTree(p, r) << std::endl; // false 예상

    return 0;
}