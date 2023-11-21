#pragma once

#include <chrono>
#include <functional>
#include <vector>
#include <algorithm>

#include "BinSearchTree.h"
#include "AvlTree.h"
#include "RedBlackTree.h"

using namespace std::chrono;


class WorkTree
{
public:

    template <typename T>
    static void getHeightTrees(const T* const arrTrees, const int size_arr_trees);

    template <typename T>
    static void getCountNodesTrees(const T* const arrTrees, const int size_arr_trees);

    template <typename T>
    static void exportFileTrees(const T* const arrTrees, const int size_arr_trees);
    
    template<typename T>
    static void printTrees(const T* const arrTrees, const int size_arr_trees);

    template<typename T>
    static void fillTrees(T* const arrTrees, const int size_arr_trees, const int fillMode);

    template<typename T>
    static void deleteTrees(T* const arrTrees, const int size_arr_trees);

    template<typename T>
    static void testTree(T& tree);

private:

    template<typename T>
    static double measureTime(T function);
};


template <typename T>
void WorkTree::getHeightTrees(const T* const arrTrees, const int size_arr_trees)
{
    cout << "Высота каждого дерева:\n";
    for (size_t i = 0; i < size_arr_trees; i++)
    {
        cout << arrTrees[i].getHeight() << endl;
    }
    cout << endl;
}


template <typename T>
void WorkTree::getCountNodesTrees(const T* const arrTrees, const int size_arr_trees)
{
    cout << "Реальное количество элементов каждого дерева:\n";

    for (size_t i = 0; i < size_arr_trees; i++)
    {
        cout << arrTrees[i].getCountNodes() << endl;
    }
    cout << endl;
}


template<typename T>
inline void WorkTree::exportFileTrees(const T* const arrTrees, const int size_arr_trees)
{
    const string filename = "tree.dot";
    ofstream dotFile(filename);

    for (size_t i = 0; i < size_arr_trees; i++)
    {
        cout << "Значения элементов дерева " << i + 1 << " успешно записаны в файл " << filename << endl;
        dotFile << "Дерево " << i + 1 << "\n";
        arrTrees[i].exportDotFile(dotFile);
    }
    cout << endl;

    dotFile.close();
}


template<typename T>
void WorkTree::printTrees(const T* const arrTrees, const int size_arr_trees)
{
    for (size_t i = 0; i < size_arr_trees; i++)
    {
        cout << setfill('=') << setw(100) << "\n\n" << setfill(' ');
        arrTrees[i].print();
    }
    cout << setfill('=') << setw(100) << "\n\n" << setfill(' ');
}


template<typename T>
void WorkTree::fillTrees(T* const arrTrees, const int size_arr_trees, const int fillMode)
{
    cout << "Время заполнения элементами каждого дерева (метод insertElem):\n";

    int size_tree = 1000;
    vector<int> vec;
    for (int i = 0; i < size_arr_trees; i++)
    {
        for (int j = 0; j < size_tree; j++)
        {
            vec.push_back(j + 1);
        }

        random_shuffle(vec.begin(),vec.end());

        cout << fixed << setprecision(0) << measureTime(bind(&T::fillTree, &arrTrees[i], vec, size_tree, fillMode)) << endl;
        
        size_tree += 1000;

        vec.clear();
    }
    cout << endl;
}


template<typename T>
void WorkTree::deleteTrees(T* const arrTrees, const int size_arr_trees)
{
    cout << "Время удаления всех элементов каждого дерева (метод deleteElem):\n";

    int max_elem, count_nodes;
    double time;
    for (size_t i = 0; i < size_arr_trees; i++)
    {
        time = 0;
        count_nodes = arrTrees[i].getCountNodes();
        for (size_t j = 0; j < count_nodes; j++)
        {
            max_elem = arrTrees[i].maxElem();
            time += measureTime(bind(&T::deleteElem, &arrTrees[i], max_elem));
        }
        cout << time << endl;
    }
    cout << endl;
}


template<typename T>
double WorkTree::measureTime(T function)
{
    auto startTime = steady_clock::now();
    function();
    auto endTime = steady_clock::now();
    auto elapsed = duration_cast<nanoseconds>(endTime - startTime);
    return static_cast<double>(elapsed.count());
}


template<typename T>
void WorkTree::testTree(T& tree)
{
    int lenTREE_METHODS = sizeof(TREE_METHODS) / sizeof(TREE_METHODS[0]);
    int elem, next_elem, prev_elem;
    int choice;

    cout << "0) Выход из программы.\n";

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
            tree.widthPrint();
            cout << endl;
            break;
        case 3:
            cout << TREE_METHODS[2] << endl;
            tree.inorderPrint();
            cout << endl;
            break;

        case 4:
            cout << TREE_METHODS[3] << endl;
            tree.preorderPrint();
            cout << endl;
            break;

        case 5:
            cout << TREE_METHODS[4] << endl;
            tree.postorderPrint();
            cout << endl;
            break;

        case 6:
            cout << TREE_METHODS[5] << endl;
            cout << tree.getCountNodes() << endl;
            break;

        case 7:
            cout << TREE_METHODS[6] << endl;
            cout << tree.getHeight() << endl;
            break;

        case 8:
            cout << TREE_METHODS[7] << endl;
            cout << "Введите элемент для поиска: ";
            cin >> elem;
            cout << "Найдено элементов: " << tree.searchElem(elem) << endl;
            break;

        case 9:
            cout << TREE_METHODS[8] << endl;
            cout << "Минимальный элемент дерева: " << tree.minElem() << endl;
            break;

        case 10:
            cout << TREE_METHODS[9] << endl;
            cout << "Максимальный элемент дерева: " << tree.maxElem() << endl;
            break;

        case 11:
            cout << TREE_METHODS[10] << endl;
            cout << "Введите элемент, для которого надо найти следующий: ";
            cin >> elem;
            next_elem = tree.nextElem(elem);
            if (next_elem != CODE_ERROR)
            {
                cout << "Следующий элемент для " << elem << ": " << next_elem << endl;
            }
            else
            {
                cout << "Нет следующего элемента для " << elem << endl;
            }
            break;

        case 12:
            cout << TREE_METHODS[11] << endl;
            cout << "Введите элемент, для которого надо найти предыдущий: ";
            cin >> elem;
            prev_elem = tree.prevElem(elem);
            if (prev_elem != CODE_ERROR)
            {
                cout << "Предыдущий элемент для " << elem << ": " << prev_elem << endl;
            }
            else
            {
                cout << "Нет предыдущего элемента для " << elem << endl;
            }
            break;

        case 13:
            cout << TREE_METHODS[12] << endl;
            cout << "Укажите элемент для вставки: ";
            cin >> elem;
            tree.insertElem(elem);
            cout << "Вставка элемента выполнена" << endl;
            break;

        case 14:
            cout << TREE_METHODS[13] << endl;
            cout << "Введите удаляемый элемент: ";
            cin >> elem;
            tree.deleteElem(elem);
            cout << "Удаление элемента завершено" << endl;
            break;

        case 15:
            cout << TREE_METHODS[14] << endl;
            tree.deleteTreeOptim();
            cout << "Удаление всего дерева завершено" << endl;
            break;

        default:
            cout << "Выбран несуществующий метод. Повторите попытку" << endl;
            break;
        }

        cout << endl;

    } while (choice != 0);
}
