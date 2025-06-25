#include "tree.h"
#include <algorithm>

using namespace std;

// составление рандомного дерева 
TreeNode* MakeTree::randTree(int maxDepth, int currentDepth) {
    if (currentDepth >= maxDepth || (currentDepth > 0 && rand() % 100 < 30)) { // новый лист создаётся с шансом 70%
        return nullptr;
    }
    TreeNode* node = new TreeNode(rand() % 90 + 10);
    node->left = randTree(maxDepth, currentDepth + 1);
    node->right = randTree(maxDepth, currentDepth + 1);
    return node;
}

// функция проверки ввода на корректное число
bool MakeTree::checkInput(string input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

// вставка узла
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

// построение дерева поиска с клавиатуры
TreeNode* MakeTree::buildTreeFromInput() {
    TreeNode* root = nullptr;
    string input;
    cout << "Вводите числа для дерева (Q для завершения):\n";

    while (true) {
        cin >> input;
        if (input == "Q" || input == "q") break;
        if (!checkInput(input)) {
            cout << "Ошибка! Введите число или Q: ";
            continue;
        }
        root = Insert(root, stoi(input));
    }
    return root;
}

// построение дерева поиска из файла
TreeNode* MakeTree::buildTreeFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
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

//счёт количества узлов в дереве
int TreeOperations::countNodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}
// копирование дерева
TreeNode* TreeOperations::cloneTree(TreeNode* node) {
    if (!node) return nullptr;
    TreeNode* newNode = new TreeNode(node->val);
    newNode->left = cloneTree(node->left);
    newNode->right = cloneTree(node->right);
    return newNode;
}
// функция удаления дерева
void TreeOperations::deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// счёт высоты дерева
int TreeOperations::Height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(Height(root->left), Height(root->right));
}

// Рекурсивная функция для симметризации двух поддеревьев
int TreeOperations::makeSymmetric(TreeNode*& a, TreeNode*& b) { // вводим ссылки на два поддерева, которые должны стать зеркальными
    // если оба узла пустые, ничего не делаем
    if (!a && !b) return 0;

    int cuts = 0; // счетчик удаленных узлов

    // если одно из поддеревьев отсутствует удаляем его полностью
    if (!a) {
        // подсчитываем все узлы в поддереве b
        cuts = countNodes(b);
        deleteTree(b);
        b = nullptr; // обнуляем указатель
        return cuts;
    }
    if (!b) {
        // аналогично с a
        cuts = countNodes(a);
        deleteTree(a);
        a = nullptr;
        return cuts; // возвращаем количество удаленных узлов
    }

    // рекурсивно делаем симметричными левого потомка левого узла и правого потомка правого и правого потомка левого с левым потомком правого
    cuts += makeSymmetric(a->left, b->right);
    cuts += makeSymmetric(a->right, b->left);

    return cuts;
}

// основная функция для симметризации всего дерева
int TreeOperations::makeTreeSymmetric(TreeNode* root) { // принимает корень дерева
    if (!root) return 0; // если дерево пустое, ничего делать не нужно

    int cuts = 0; // заводим счетчик удаленных узлов

    // если есть оба поддерева делаем их симметричными друг другу
    if (root->left && root->right) {
        cuts = makeSymmetric(root->left, root->right);
    }
    // если есть только левое поддерево, удаляем его полностью
    else if (root->left) {
        cuts = countNodes(root->left);
        deleteTree(root->left);
        root->left = nullptr;
    }
    // Если есть только правое поддерево, тоже удаляем его полностью
    else if (root->right) {
        cuts = countNodes(root->right);
        deleteTree(root->right);
        root->right = nullptr;
    }

    return cuts;
    // Возвращает количество удаленных узлов
}

//вертикальный вывод функии (взято из интернета)
void TreeOperations::printTreeVertical(TreeNode* root) {
    if (!root) {
        cout << "Пустое дерево\n";
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

//функция для вывода меню
void displayMenu() {
    cout << "\nМеню:\n";
    cout << "1. Сгенерировать случайное дерево\n";
    cout << "2. Ввести дерево вручную\n";
    cout << "3. Загрузить дерево из файла\n";
    cout << "4. Выход\n";
    cout << "Выберите: ";
}