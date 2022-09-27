/*
https://leetcode.com/problems/invert-binary-tree/
*/
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr)
            return nullptr;
        TreeNode *left = invertTree (root->right);
        TreeNode *right = invertTree (root->left);
        root->left = left;
        root->right = right;
        return root;
    }
};
