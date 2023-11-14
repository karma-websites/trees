#pragma once
#include "BinSearchTree.h"
#include "AvlTree.h"
#include "RedBlackTree.h"


class WorkTree
{
public:

    template<typename T>
    static bool fillTree(T& tree, const int size, const int fillMode);

    template<typename T>
    static void testTree(T& tree);

    template<typename T>
    static void printTree(T& tree);
};


template<typename T>
static bool WorkTree::fillTree(T& tree, const int size, const int fillMode)
{
    switch (fillMode)
    {
    case 1:
        for (size_t i = 0; i < size; ++i)
        {
            tree.insert(i + 10);
        }
        break;
    case 2:
        for (size_t i = 0; i < size; ++i)
        {
            tree.insert(rand() % 100 + 10);
        }
        break;
    case 3:
        for (size_t i = 0; i < size / 2; ++i)
        {
            tree.insert(i + 10);
        }
        for (size_t i = size / 2; i < size; i++)
        {
            tree.insert(rand() % 100 + 10);
        }
        break;
    default:
        cout << "Ошибка: выбранного режима не существует." << endl;
        return false;
    }
    return true;
}

template<typename T>
void WorkTree::testTree(T& tree)
{
    int lenTREE_METHODS = sizeof(TREE_METHODS) / sizeof(TREE_METHODS[0]);
    int elem, next_elem, prev_elem;
    int choice;

    cout << "0) Выход из программы." << endl;

    for (size_t i = 0; i < lenTREE_METHODS; i++)
    {
        cout << TREE_METHODS[i] << endl;
    }

    do
    {
        cout << "Выберите метод: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 0:
            cout << "Выбран выход из программы" << endl;
            break;

        case 1:
            cout << TREE_METHODS[0] << endl;
            tree.print();
            break;

        case 2:
            cout << TREE_METHODS[1] << endl;
            tree.inorderPrint(true);
            cout << endl;
            break;

        case 3:
            cout << TREE_METHODS[2] << endl;
            tree.preorderPrint();
            cout << endl;
            break;

        case 4:
            cout << TREE_METHODS[3] << endl;
            tree.postorderPrint();
            cout << endl;
            break;

        case 5:
            cout << TREE_METHODS[4] << endl;
            cout << tree.getCountNodes() << endl;
            break;

        case 6:
            cout << TREE_METHODS[5] << endl;
            cout << tree.getHeight() << endl;
            break;

        case 7:
            cout << TREE_METHODS[6] << endl;
            cout << "Введите элемент для поиска: ";
            cin >> elem;
            cout << "Найдено элементов: " << tree.search(elem) << endl;
            break;

        case 8:
            cout << TREE_METHODS[7] << endl;
            cout << "Минимальный элемент дерева: " << tree.minElem() << endl;
            break;

        case 9:
            cout << TREE_METHODS[8] << endl;
            cout << "Максимальный элемент дерева: " << tree.maxElem() << endl;
            break;

        case 10:
            cout << TREE_METHODS[9] << endl;
            cout << "Введите элемент, для которого надо найти следующий: ";
            cin >> elem;
            next_elem = tree.next(elem);
            if (next_elem != CODE_ERROR)
            {
                cout << "Следующий элемент для " << elem << ": " << next_elem << endl;
            }
            else
            {
                cout << "Нет следующего элемента для " << elem << endl;
            }
            break;

        case 11:
            cout << TREE_METHODS[10] << endl;
            cout << "Введите элемент, для которого надо найти предыдущий: ";
            cin >> elem;
            prev_elem = tree.prev(elem);
            if (prev_elem != CODE_ERROR)
            {
                cout << "Предыдущий элемент для " << elem << ": " << prev_elem << endl;
            }
            else
            {
                cout << "Нет предыдущего элемента для " << elem << endl;
            }
            break;

        case 12:
            cout << TREE_METHODS[11] << endl;
            cout << "Укажите элемент для вставки: ";
            cin >> elem;
            tree.insert(elem);
            cout << "Вставка элемента выполнена" << endl;
            break;

        case 13:
            cout << TREE_METHODS[12] << endl;
            cout << "Введите удаляемый элемент: ";
            cin >> elem;
            tree.delElem(elem);
            cout << "Удаление элемента завершено" << endl;
            break;

        case 14:
            cout << TREE_METHODS[13] << endl;
            tree.clear();
            cout << "Удаление всего дерева завершено" << endl;
            break;

        default:
            cout << "Выбран несуществующий метод. Повторите попытку" << endl;
            break;
        }

        cout << endl;
    } while (choice != 0);
}

template<typename T>
inline void WorkTree::printTree(T& tree)
{
    tree.print();
}

