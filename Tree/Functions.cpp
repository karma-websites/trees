#include "Functions.h"


// ������� ���������� �� �������

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
            cerr << "�������� ������ �����.\n���������� ������ �������� ��� ���: ";
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
            cout << "������ �������� ������. ����������, ��������� �������: ";
        }
    }
    cout << endl;
    return fill_mode;
}
