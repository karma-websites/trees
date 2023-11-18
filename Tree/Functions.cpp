#include "Functions.h"


// Функции считывания из консоли

void ignoreLine()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValue()
{
    while (true)
    {
        int value;
        cin >> value;
        if (cin.fail() || value < 0)
        {
            cin.clear();
            ignoreLine();
            cerr << "Неверный формат ввода.\nПопробуйте ввести значение еще раз: ";
        }
        else
        {
            ignoreLine();
            return value;
        }
    }
}

int getFillMode()
{
    int fill_mode = -1;
    while (true)
    {
        fill_mode = getValue();
        if (fill_mode == 0 || fill_mode == 1)
        {
            break;
        }
        else
        {
            cout << "Выбран неверный формат. Пожалуйста, повторите попытку: ";
        }
    }
    cout << endl;
    return fill_mode;
}
