#include "tree.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    MakeTree builder; //объект для построения деревьев
    TreeOperations tree; //переменная для работы с деревом
    TreeNode* root = nullptr; //указатель на текущее дерево
    TreeNode* originalTree = nullptr; //указатель на копию исходного дерева

    //цикл пока пользовательне выйдет
    while (true) {
        displayMenu();//вывод меню 
        int choice;//переменная для выбора

        //проверка ввода выбора меню
        while (!(cin >> choice)) {
            cin.clear();  //сброс флагов ошибок
            cin.ignore(); //очистка буфера
            cout << "Ошибка ввода! Введите число от 1 до 4: ";
        }

        //выходим из цикла и из программы, если пользователь ввёл 4
        if (choice == 4) break;

        //выбор пользователя
        switch (choice) {
        case 1: {//вариант генерации случайного дерева
            int depth;
            cout << "Введите максимальную глубину дерева (3-5): ";

            //проверка ввода глубины дерева
            while (!(cin >> depth) or depth < 3 or depth > 5) {
                cin.clear();
                cin.ignore();
                cout << "Ошибка! Введите целое число от 3 до 5: ";
            }
            root = builder.randTree(depth);//рандомная генерация дерева
            break;
        }
        case 2: {//построение дерева с клавы
            root = builder.buildTreeFromInput();
            break;
        }
        case 3: {//построение дерева из файла
            string filename;
            cout << "Введите имя файла: ";
            cin.clear();
            cin.ignore();//очищаем буфер для корректного ввода
            getline(cin, filename);//чтение строки

            if (filename.empty()) {
                cout << "Имя файла не может быть пустым!\n";
                root = nullptr;
            }
            else {
                root = builder.buildTreeFromFile(filename);
            }
            break;
        }
        default: {//обработка неверного ввода
            cout << "Неверный выбор!\n";
            continue;
        }
        }

        //проверка создания дерева
        if (!root) {
            cout << "Не удалось создать дерево!\n";
            continue;
        }

        //сохраненяем копию исходного дерева
        originalTree = tree.cloneTree(root);

        //выводим исходное дерева
        cout << "\nИсходное дерево:\n";
        tree.printTreeVertical(originalTree);

        //преобразование дерева в симметричное и подсчет удаленных узлов
        int removed = tree.makeTreeSymmetric(root);
        cout << "\nЛистьев отрезано: " << removed << endl;

        //вывод преобразованного дерева
        cout << "Симметричное дерево:\n";
        tree.printTreeVertical(root);

        //очистка памяти
        tree.deleteTree(originalTree);
        tree.deleteTree(root);
        originalTree = nullptr;
        root = nullptr;
    }

    return 0;
}