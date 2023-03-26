#include "src/station.h"

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    station::TestStation work;
    int process;
    string introduction = "===========\n\
    [Function]\n\
    1.Set process\n\
    2.Set product\n\
    3.Show config\n\
    4.Start process\n\
    5.Show result\n\
    6.Show station counter\n\
    7.Exit\n\
    Select : ";

    while (1)
    {
        cout << introduction;
        cin >> process;
        switch (process)
        {
        case 1:
            work.SetStation();
            break;
        case 2:
            work.SetDut();
            break;
        case 3:
            work.ShowConfig();
            break;
        case 4:
            work.ProcessStart();
            work.ProcessInit();
            break;
        case 5:
            work.ShowProducts();
            break;
        case 6:
            work.ShowStationCount();
            break;
        default:
            cout << "Exit" << endl;
            system("pause");
            exit(0);
            break;
        }
    }
    return 0;
}