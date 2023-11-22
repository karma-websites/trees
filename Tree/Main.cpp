#include "WorkTree.h"
#include "Functions.h"


int main()
{
	setlocale(LC_ALL, "Rus");

    cout << "Лабораторная работа №3.\n"
        "Бинарные деревья\n"
        "Автор: Попов Максим. Группа 2309\n\n" << endl;
    
    cout << "Укажите желаемое количество деревьев: ";
    int size_arr_trees = getValue();
    cout << endl;

    //BinSearchTree* arrTrees = new BinSearchTree[size_arr_trees];
    //AvlTree* arrTrees = new AvlTree[size_arr_trees];
    RedBlackTree* arrTrees = new RedBlackTree[size_arr_trees];

    /*
    cout << "Выберите формат данных для деревьев:\n"
        "1) отсортированные\n"
        "2) случайные\n"
        "Ваш выбор: ";

    int fill_mode = getFillMode();

    WorkTree::fillTrees(arrTrees, size_arr_trees, fill_mode);
    WorkTree::getHeightTrees(arrTrees, size_arr_trees);
    WorkTree::getCountNodesTrees(arrTrees, size_arr_trees);
    //WorkTree::printTrees(arrTrees, size_arr_trees);
    //WorkTree::exportFileTrees(arrTrees, size_arr_trees);
    WorkTree::deleteTrees(arrTrees, size_arr_trees);
    //WorkTree::printTrees(arrTrees, size_arr_trees);
    */

    for (size_t i = 0; i < 10; i++)
    {
        arrTrees->insertElem(rand() % 100);
    }

    WorkTree::testTree(*arrTrees);

    delete[] arrTrees;

    return 0;
}
