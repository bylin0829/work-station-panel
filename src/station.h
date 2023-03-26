#ifndef STATION_H_
#define STATION_H_

#include "ini.h"

#include <iostream>
#include <queue>
#include <vector>
#include <map>

namespace station
{
    class TestStation
    {
    private:
        const std::string INI_FILENAME = "process_info.ini";
        int dut = 0;           // device under test
        bool dut_flag = false; // set or not
        std::queue<char> station_queue;
        std::map<std::string, int> station_count = {
            {"A", 0},
            {"B", 0},
            {"C", 0},
            {"D", 0}};
        const char PREV_DEFAULT = '0';
        char prev_station = PREV_DEFAULT;

    public:
        void SetStation();
        void SetDut();
        void ShowConfig();
        void ShowProducts();
        void ShowStationCount();
        void ProcessInit();
        void ProcessStart();
        void StationA();
        void StationB();
        void StationC();
        void StationD();
        void IniInit();
        void IniUpdate();
        void ProcessSelection(char);

        TestStation(/* args */);
        ~TestStation();
    };
} // namespace station
#endif // STATION_H_