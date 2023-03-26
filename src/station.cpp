#include "station.h"

using namespace std;
using namespace mINI;

namespace station
{
    TestStation::TestStation(/* args */)
    {
        dut_flag = false;
        IniInit();
        ProcessInit();
    }

    TestStation::~TestStation()
    {
    }

    void TestStation::SetStation()
    {
        char p;
        string introduction =
            "Please add station.(A/B/C/D or or others to return to the menu.)\n\
        Example 1: A\n\
        Example 2: BAACD\n\
        Example 3: t (Back to menu);";
        cout << introduction << endl;
        while (1)
        {
            cout << "Add stations : ";
            cin >> p;
            if (p >= 'A' && p <= 'D')
            {
                station_queue.push(p);
                ShowConfig();
            }
            else
            {
                cout << "Go to menu." << endl;
                cin.clear();
                cin.sync();
                break;
            }
        }
    }
    void TestStation::ShowConfig()
    {
        queue<char> temp = station_queue;
        cout << "Data:" << dut << endl;
        cout << "Station:";
        while (!temp.empty())
        {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }

    void TestStation::SetDut()
    {
        int a;
        cout << "Input:";
        cin >> a;
        if (cin.rdstate() == ios::goodbit)
        {
            dut = a;
            dut_flag = true;
            cout << "Set " << dut << endl;
        }
        else
        {
            cout << "Input is not a number." << endl;
            cin.clear();
            cin.sync();
        }
    }
    void TestStation::ProcessSelection(char s)
    {
        switch (s)
        {
        case 'A':
            StationA();
            break;
        case 'B':
            StationB();
            break;
        case 'C':
            StationC();
            break;
        case 'D':
            StationD();
            break;
        default: // No match station
            break;
        }
    }
    void TestStation::ProcessStart()
    {
        if (!dut_flag)
        {
            cout << "Input not ready" << endl;
            return;
        }
        else if (station_queue.empty())
        {
            cout << "Station is empty" << endl;
            return;
        }

        while (!station_queue.empty())
        {
            ProcessSelection(station_queue.front());
            prev_station = (station_queue.front() == 'D') ? PREV_DEFAULT : station_queue.front();
            station_queue.pop();
        }
        cout << "Result=" << dut << endl;
        IniUpdate();
        ProcessInit();
    }
    void TestStation::ProcessInit()
    {
        // Clear product
        dut = 0;
        dut_flag = false;
        prev_station = PREV_DEFAULT;

        // Clear station
        while (!station_queue.empty())
            station_queue.pop();

        for (auto &s : station_count)
        {
            s.second = 0;
        }
    }
    void TestStation::StationA()
    {
        dut++;
        station_count["A"]++;
    }
    void TestStation::StationB()
    {
        dut--;
        station_count["B"]++;
    }

    void TestStation::StationC()
    {
        station_count["C"]++;
        if ((dut % 2) == 0)
            station_queue.pop();
    }

    void TestStation::StationD()
    {
        station_count["D"]++;
        ProcessSelection(prev_station);
    }

    void TestStation::IniInit()
    {
        // first, create a file instance
        INIFile file(INI_FILENAME);

        // next, create a structure that will hold data
        INIStructure ini;

        // now we can read the file
        file.read(ini);

        // read a value
        for (const auto &s : station_count)
        {
            string &pro = ini["process"][s.first];
            if (pro == "")
            {
                ini["process"][s.first] = "0";
            }
        }

        // write updates to file
        file.write(ini);
    }

    void TestStation::IniUpdate()
    {
        // first, create a file instance
        INIFile file(INI_FILENAME);

        // next, create a structure that will hold data
        INIStructure ini;
        file.read(ini);

        // Update station count
        for (const auto &s : station_count)
        {
            ini["process"][s.first] = to_string(stoi(ini["process"][s.first]) + s.second);
        }

        // Update products
        std::string &amountOfApples = ini["products"][to_string(dut)];
        if (amountOfApples == "")
            ini["products"][to_string(dut)] = "0";

        ini["products"][to_string(dut)] = to_string(stoi(ini["products"][to_string(dut)]) + 1);

        file.write(ini);
    }

    void TestStation::ShowStationCount()
    {
        // first, create a file instance
        INIFile file(INI_FILENAME);

        // next, create a structure that will hold data
        INIStructure ini;
        file.read(ini);
        for (auto const &it : ini)
        {
            auto const &section = it.first;
            auto const &collection = it.second;
            if (section != "process")
                continue;
            cout << "Station = counts" << endl;
            std::cout << "[" << section << "]" << std::endl;
            for (auto const &it2 : collection)
            {
                auto const &key = it2.first;
                auto const &value = it2.second;
                std::cout << key << "=" << value << std::endl;
            }
        }
    }

    void TestStation::ShowProducts()
    {
        // first, create a file instance
        INIFile file(INI_FILENAME);

        // next, create a structure that will hold data
        INIStructure ini;
        file.read(ini);
        for (auto const &it : ini)
        {
            auto const &section = it.first;
            auto const &collection = it.second;
            if (section != "products")
                continue;
            cout << "Product name = Count" << endl;

            std::cout << "[" << section << "]" << std::endl;
            for (auto const &it2 : collection)
            {
                auto const &key = it2.first;
                auto const &value = it2.second;
                std::cout << key << "=" << value << std::endl;
            }
        }
    }

} // namespace station