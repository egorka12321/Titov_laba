#pragma once
#include <string>
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
    friend istream& operator >> (istream& in, CS& comp_station);
    friend ostream& operator << (ostream& out, const CS& cs);
    friend void Input_file_with_cs(const CS& cs);
    friend void Output_file_with_cs(CS& cs);
    CS();
};
