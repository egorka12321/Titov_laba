#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class CS
{
public:
    string name = "None";
    int workshop = 0;
    int workshop_on = 0;
    char efficciency = 'F';
    int id_cs = 0;
    static int max_id_cs;
    CS();
    int get_id_c() { return id_cs; };
    friend ostream& operator << (ostream& out, const CS& cs);
    friend istream& operator >> (istream& in, CS& comp_station);
    friend void Add_cs(unordered_map <int, CS>& stations);
    friend void View_cs(unordered_map <int, CS>& stations);
    friend void Save_cstation(ofstream& fout, const CS& cs);
    friend CS& Load_station(ifstream& fin, CS& cs);
};
