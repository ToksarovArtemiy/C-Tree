#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <tuple>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ����� ��� �������� ������
class MakeTree {
public:
    TreeNode* randTree(int maxDepth, int currentDepth = 0);
    bool checkInput(std::string input);
    TreeNode* Insert(TreeNode* node, int value);
    TreeNode* buildTreeFromInput();
    TreeNode* buildTreeFromFile(std::string filename);
};

// ����� ��� ������ � ���������
class TreeOperations {
private:
    int makeSymmetric(TreeNode*& a, TreeNode*& b);
public:
    int countNodes(TreeNode* node);
    TreeNode* cloneTree(TreeNode* node);
    void deleteTree(TreeNode* node);
    int Height(TreeNode* root);
    int makeTreeSymmetric(TreeNode* root);
    void printTreeVertical(TreeNode* root);
};

// ������� ������ ����
void displayMenu();

#endif // TREE_H
