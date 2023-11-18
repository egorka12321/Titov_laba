#include "CS.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
using namespace std;

int CS::max_id_cs = 0;

CS::CS() {
    id_cs = max_id_cs++;
}

istream& operator >> (istream& in, CS& comp_station) {
    cout << "Add compressor station\n" << "Enter name of the CS: ";
    in >> ws;
    getline(in, comp_station.name);
    cout << "Enter number of the workshops: ";
    comp_station.workshop = GetCorrectData(1, 10000);
    cout << "Enter number of the workshops in operation: ";
    comp_station.workshop_on = GetCorrectData(1, comp_station.workshop);
    while (comp_station.workshop_on > comp_station.workshop) {
        cout << "Cant be like this!!!" << endl;
        comp_station.workshop_on = GetCorrectData(1, comp_station.workshop);
    }
    cout << "Enter efficiency of CS: ";
    comp_station.efficciency = GetCorrectData('A', 'D');
    return in;
}

ostream& operator << (ostream& out, const CS& cs) {
    out << "\nCompressor station:" << endl;
    out << "id: " << cs.id_cs
        << "\nCS name: " << cs.name
        << "\nCS number of the workshops: " << cs.workshop
        << "\nCS number of the workshops in operation: " << cs.workshop_on
        << "\nCS efficiency: " << cs.efficciency;
    return out;
}

void View_cs(unordered_map <int, CS>& stations) {
    if (stations.size() == 0)
        cout << "You don't have compressor stations" << endl;
    else {
        for (auto& cs : stations) {
            cout << cs.second << endl;
        }
    }
}

void Save_cstation(ofstream& fout, const CS& cs) {
    if (cs.name.empty())
        cout << "No CS data to record" << endl;
    else {
        fout << "Compressor station" << endl;
        fout << cs.id_cs << endl;
        fout << cs.name << endl;
        fout << cs.workshop << endl;
        fout << cs.workshop_on << endl;
        fout << cs.efficciency << endl;
    }
}

CS& Load_station(ifstream& fin, CS& cs) {
    string station_string;
    while (getline(fin, station_string)) {
        if (station_string == "Compressor station") {
            fin >> cs.id_cs;
            fin.ignore();
            getline(fin, cs.name);
            fin >> cs.workshop >> cs.workshop_on >> cs.efficciency;
            return cs;
        }
    }
}