#include <chrono>
#include <functional>

#include "WorkTree.h"

using namespace std::chrono;


template <typename T>
void newTrees(T** const arrTrees, const int size_arr_trees)
{
    for (size_t i = 0; i < size_arr_trees; i++)
    {
        arrTrees[i] = new T();
    }
}

template <typename T>
void printHeightTrees(T** const arrTrees, const int size_arr_trees)
{
    for (size_t i = 0; i < size_arr_trees; i++)
    {
        cout << arrTrees[i]->getHeightTree() << " " << arrTrees[i]->getCountNodes() << endl;
    }
}

template<typename T>
void printTrees(T** const arrTrees, const int size_arr_trees)
{
    for (size_t i = 0; i < size_arr_trees; i++)
    {
        //cout << "\n" << setw(100) << setfill('=') << "\n" << endl;
        arrTrees[i]->print();
    }
    //cout << "\n" << setw(100) << setfill('=') << "\n" << endl;
}

template<typename T>
void fillTrees(T** const arrTrees, const int size_arr_trees, const int fillMode)
{
    const int numMeasure = 5;
    double averageTime = 0;
    int size_tree = 700;

    cout << "Измерение времени выполнения метода insert" << endl;

    for (int i = 0; i < size_arr_trees; i++)
    {
        averageTime = 0;
        for (int j = 0; j < numMeasure; j++)
        {
            averageTime = measureTime(bind(&T::fillTree, arrTrees[i], size_tree, fillMode));
        }
        size_tree += 700;
        cout << fixed << setprecision(0) << averageTime / numMeasure << endl;
    }

}

template<typename T>
void fillT(T** const arrTrees, const int size_arr_trees, const int fillMode)
{
    int size_tree = 700;
    for (int i = 0; i < size_arr_trees; i++)
    {
        arrTrees[i]->fillTree(size_tree, fillMode);
        size_tree += 700;
    }
}

template<typename T>
void clearTrees(T**& arrTrees, int size_arr_trees, const int fillMode)
{
    const int numMeasure = 5;
    double averageTime = 0;
    int size_tree;

    cout << "Измерение времени выполнения метода clear" << endl;

    for (int i = 0; i < size_arr_trees; i++)
    {
        averageTime = 0;
        size_tree = arrTrees[i]->getCountNodes();
        for (int j = 0; j < numMeasure; j++)
        {
            arrTrees[i]->fillTree(size_tree, fillMode);
            averageTime = measureTime(bind(&T::clear, arrTrees[i]));
        }
        cout << averageTime / numMeasure << endl;
    }
}

template<typename T>
double measureTime(T function)
{
    auto startTime = steady_clock::now();
    function();
    auto endTime = steady_clock::now();
    auto elapsed = duration_cast<nanoseconds>(endTime - startTime);
    return static_cast<double>(elapsed.count());
}



int main()
{
	setlocale(LC_ALL, "Rus");

    cout << "Лабораторная работа №3.\n"
        "Бинарные деревья\n"
        "Автор: Попов Максим. Группа 2309\n\n" << endl;

	/*BinSearchTree searchTree;
	AvlTree avlTree;
    RedBlackTree rbTree;*/

    int size_arr_trees = 20;
    cout << "Укажите желаемое количество элементов деревьев: \n";
    //cin >> size_arr_trees;

    //BinSearchTree** arrTrees = new BinSearchTree *[size_arr_trees];
    AvlTree** arrTrees = new AvlTree * [size_arr_trees];
    //RedBlackTree** arrTrees = new RedBlackTree * [size_arr_trees];

    newTrees(arrTrees, size_arr_trees);
    
    int lenDATA_OPTIONS = sizeof(DATA_OPTIONS) / sizeof(DATA_OPTIONS[0]);

    //fillTrees(arrTrees, size_arr_trees, 1);
    fillT(arrTrees, size_arr_trees, 1);
 
    printHeightTrees(arrTrees, size_arr_trees);

    for (int i = 0; i < lenDATA_OPTIONS; i++)
    {
        //clearTrees(arrTrees, size_arr_trees, i);
    }
    //printTrees(arrTrees, size_arr_trees);

    delete[] arrTrees;

   

    return 0;
}