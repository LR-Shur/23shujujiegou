#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Binary tree node structure
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Print tree (level-order traversal)
void printTree(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->data << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << endl;
}

// Convert forest to binary tree
TreeNode* forestToBinaryTree(vector<TreeNode*>& roots) {
    if (roots.empty()) return nullptr;

    for (size_t i = 0; i < roots.size() - 1; ++i) {
        roots[i]->right = roots[i + 1];
    }

    return roots[0];
}

int main() {
    cout << "Building three trees..." << endl;

    // Hardcoded three trees
    TreeNode* tree1 = new TreeNode('A');
    tree1->left = new TreeNode('B');
    tree1->right = new TreeNode('C');

    TreeNode* tree2 = new TreeNode('D');
    tree2->left = new TreeNode('E');
    tree2->right = new TreeNode('F');

    TreeNode* tree3 = new TreeNode('G');
    tree3->left = new TreeNode('H');
    tree3->right = new TreeNode('I');

    vector<TreeNode*> forest = {tree1, tree2, tree3};

    cout << "The three input trees (level-order):" << endl;
    for (size_t i = 0; i < forest.size(); ++i) {
        cout << "Tree " << i + 1 << ": ";
        printTree(forest[i]);
    }

    // Convert forest to a single binary tree
    TreeNode* combinedTree = forestToBinaryTree(forest);

    cout << "Combined binary tree (level-order):" << endl;
    printTree(combinedTree);

    return 0;
}
