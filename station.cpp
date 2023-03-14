#include "station.h"

station::station(/* args */)
{
    data_flag = false;
    ini_init();
    process_init();
}

station::~station()
{
}

void station::set_station()
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
            st.push(p);
            show_config();
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
void station::show_config()
{
    queue<char> temp = st;
    cout << "Data:" << data << endl;
    cout << "Station:";
    while (!temp.empty())
    {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
}

void station::set_input()
{
    int a;
    cout << "Input:";
    cin >> a;
    if (cin.rdstate() == ios::goodbit)
    {
        data = a;
        data_flag = true;
        cout << "Set " << data << endl;
    }
    else
    {
        cout << "Input is not a number." << endl;
        cin.clear();
        cin.sync();
    }
}
void station::process(char s)
{
    switch (s)
    {
    case 'A':
        A();
        break;
    case 'B':
        B();
        break;
    case 'C':
        C();
        break;
    case 'D':
        D();
        break;
    default: // No match station
        break;
    }
}
void station::process_start()
{
    if (!data_flag)
    {
        cout << "Input not ready" << endl;
        return;
    }
    else if (st.empty())
    {
        cout << "Station is empty" << endl;
        return;
    }

    while (!st.empty())
    {
        process(st.front());
        prev_station = st.front();
        st.pop();
    }
    cout << "Result=" << data << endl;
    ini_update();
    process_init();
}
void station::process_init()
{
    // Clear product
    data = 0;
    data_flag = false;
    prev_station = '0';
    // Clear station
    while (!st.empty())
        st.pop();

    for (auto &s : station_count)
    {
        s.second = 0;
    }
}
void station::A()
{
    data++;
    station_count["A"]++;
}
void station::B()
{
    data--;
    station_count["B"]++;
}

void station::C()
{
    station_count["C"]++;
    if ((data % 2) == 0)
        st.pop();
}

void station::D()
{
    station_count["D"]++;
    process(prev_station);
}

void station::ini_init()
{
    // first, create a file instance
    INIFile file(INI_FILENAME);

    // next, create a structure that will hold data
    INIStructure ini;

    // now we can read the file
    file.read(ini);

    // read a value
    string s[] = {"A", "B", "C", "D"};
    int size = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < size; ++i)
    {

        std::string &pro = ini["process"][s[i]];
        if (pro == "")
            ini["process"][s[i]] = "0";
    }

    // cout << stoi(amountOfApples) << endl;

    // write updates to file
    file.write(ini);
}

void station::ini_update()
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
    std::string &amountOfApples = ini["products"][to_string(data)];
    if (amountOfApples == "")
        ini["products"][to_string(data)] = "0";

    ini["products"][to_string(data)] = to_string(stoi(ini["products"][to_string(data)]) + 1);

    file.write(ini);
}

void station::show_station_count()
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

void station::show_products()
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