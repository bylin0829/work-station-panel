#include "station.h"
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    station work;
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
            work.set_station();
            break;
        case 2:
            work.set_input();
            break;
        case 3:
            work.show_config();
            break;
        case 4:
            work.process_start();
            work.process_init();
            break;
        case 5:
            work.show_products();
            break;
        case 6:
            work.show_station_count();
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