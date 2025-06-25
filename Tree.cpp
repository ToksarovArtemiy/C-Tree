#include "tree.h"
#include <algorithm>

using namespace std;

// ����������� ���������� ������ 
TreeNode* MakeTree::randTree(int maxDepth, int currentDepth) {
    if (currentDepth >= maxDepth || (currentDepth > 0 && rand() % 100 < 30)) { // ����� ���� �������� � ������ 70%
        return nullptr;
    }
    TreeNode* node = new TreeNode(rand() % 90 + 10);
    node->left = randTree(maxDepth, currentDepth + 1);
    node->right = randTree(maxDepth, currentDepth + 1);
    return node;
}

// ������� �������� ����� �� ���������� �����
bool MakeTree::checkInput(string input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

// ������� ����
TreeNode* MakeTree::Insert(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);
    if (value < node->val) {
        node->left = Insert(node->left, value);
    }
    else if (value > node->val) {
        node->right = Insert(node->right, value);
    }
    return node;
}

// ���������� ������ ������ � ����������
TreeNode* MakeTree::buildTreeFromInput() {
    TreeNode* root = nullptr;
    string input;
    cout << "������� ����� ��� ������ (Q ��� ����������):\n";

    while (true) {
        cin >> input;
        if (input == "Q" || input == "q") break;
        if (!checkInput(input)) {
            cout << "������! ������� ����� ��� Q: ";
            continue;
        }
        root = Insert(root, stoi(input));
    }
    return root;
}

// ���������� ������ ������ �� �����
TreeNode* MakeTree::buildTreeFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������ �������� �����!\n";
        return nullptr;
    }

    TreeNode* root = nullptr;
    string input;

    while (file >> input) {
        if (!checkInput(input)) continue;
        root = Insert(root, stoi(input));
    }

    file.close();
    return root;
}

//���� ���������� ����� � ������
int TreeOperations::countNodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}
// ����������� ������
TreeNode* TreeOperations::cloneTree(TreeNode* node) {
    if (!node) return nullptr;
    TreeNode* newNode = new TreeNode(node->val);
    newNode->left = cloneTree(node->left);
    newNode->right = cloneTree(node->right);
    return newNode;
}
// ������� �������� ������
void TreeOperations::deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// ���� ������ ������
int TreeOperations::Height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(Height(root->left), Height(root->right));
}

// ����������� ������� ��� ������������� ���� �����������
int TreeOperations::makeSymmetric(TreeNode*& a, TreeNode*& b) { // ������ ������ �� ��� ���������, ������� ������ ����� �����������
    // ���� ��� ���� ������, ������ �� ������
    if (!a && !b) return 0;

    int cuts = 0; // ������� ��������� �����

    // ���� ���� �� ����������� ����������� ������� ��� ���������
    if (!a) {
        // ������������ ��� ���� � ��������� b
        cuts = countNodes(b);
        deleteTree(b);
        b = nullptr; // �������� ���������
        return cuts;
    }
    if (!b) {
        // ���������� � a
        cuts = countNodes(a);
        deleteTree(a);
        a = nullptr;
        return cuts; // ���������� ���������� ��������� �����
    }

    // ���������� ������ ������������� ������ ������� ������ ���� � ������� ������� ������� � ������� ������� ������ � ����� �������� �������
    cuts += makeSymmetric(a->left, b->right);
    cuts += makeSymmetric(a->right, b->left);

    return cuts;
}

// �������� ������� ��� ������������� ����� ������
int TreeOperations::makeTreeSymmetric(TreeNode* root) { // ��������� ������ ������
    if (!root) return 0; // ���� ������ ������, ������ ������ �� �����

    int cuts = 0; // ������� ������� ��������� �����

    // ���� ���� ��� ��������� ������ �� ������������� ���� �����
    if (root->left && root->right) {
        cuts = makeSymmetric(root->left, root->right);
    }
    // ���� ���� ������ ����� ���������, ������� ��� ���������
    else if (root->left) {
        cuts = countNodes(root->left);
        deleteTree(root->left);
        root->left = nullptr;
    }
    // ���� ���� ������ ������ ���������, ���� ������� ��� ���������
    else if (root->right) {
        cuts = countNodes(root->right);
        deleteTree(root->right);
        root->right = nullptr;
    }

    return cuts;
    // ���������� ���������� ��������� �����
}

//������������ ����� ������ (����� �� ���������)
void TreeOperations::printTreeVertical(TreeNode* root) {
    if (!root) {
        cout << "������ ������\n";
        return;
    }

    int height = Height(root);
    int width = (1 << height) - 1;
    vector<vector<string>> display(height, vector<string>(width, "  "));
    queue<tuple<TreeNode*, int, int, int>> q;
    q.push(make_tuple(root, 0, 0, width - 1));

    while (!q.empty()) {
        tuple<TreeNode*, int, int, int> t = q.front();
        q.pop();
        TreeNode* node = get<0>(t);
        int level = get<1>(t);
        int left = get<2>(t);
        int right = get<3>(t);
        int mid = (left + right) / 2;

        if (node) {
            string val = to_string(node->val);
            if (val.length() == 1) val = " " + val;
            display[level][mid] = val;

            if (level + 1 < height) {
                q.push(make_tuple(node->left, level + 1, left, mid - 1));
                q.push(make_tuple(node->right, level + 1, mid + 1, right));
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << display[i][j];
        }
        cout << endl;
    }
}

//������� ��� ������ ����
void displayMenu() {
    cout << "\n����:\n";
    cout << "1. ������������� ��������� ������\n";
    cout << "2. ������ ������ �������\n";
    cout << "3. ��������� ������ �� �����\n";
    cout << "4. �����\n";
    cout << "��������: ";
}