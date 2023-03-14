#include <iostream>
#include <queue>
#include "src/mini/ini.h"
#include <vector>
#include <map>

using namespace std;
using namespace mINI;

class station
{
private:
    /* data */
    int data = 0;
    bool data_flag = false; // set or not
    queue<char> st;
    const string INI_FILENAME = "process_info.ini";
    map<string, int> station_count = {
        {"A", 0},
        {"B", 0},
        {"C", 0},
        {"D", 0}};
    char prev_station = '0';

public:
    void set_station();
    void set_input();
    void show_config();
    void show_products();
    void show_station_count();
    void process_init();
    void process_start();
    void A();
    void B();
    void C();
    void D();
    void ini_init();
    void ini_update();
    void process(char);

    station(/* args */);
    ~station();
};
