#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
using namespace std;

istream& operator >> (istream& in, Pipe& truba) {
    cout << "Add pipe\n" << "Enter name of the pipe: ";
    in >> ws;
    getline(in, truba.name);
    cout << "Enter length of the pipe: ";
    truba.length = GetCorrectData(0.0, 10000.0);
    cout << "Enter diameter of the pipe: ";
    truba.diameter = GetCorrectData(500, 1400);
    cout << "Enter condition of the pipe: ";
    truba.repair = GetCorrectData(0, 1);
    return in;
}

istream& operator >> (istream& in, CS& comp_station) {
    cout << "Add compressor station\n" << "Enter name of the CS: ";
    in >> ws;
    getline(cin, comp_station.name);
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

ostream& operator << (ostream& out, const Pipe& p) {
    if (p.length == 0)
        out << "\nNo pipes added" << endl;
    else {
        out << "\nPipe:" << endl;
        out << "Pipe name: " << p.name
            << "\nPipe length: " << p.length
            << "\nPipe diameter: " << p.diameter
            << "\nPipe condition: " << p.repair << endl;
    }
    return out;
}

ostream& operator << (ostream& out, const CS& cs) {
    if (cs.workshop == 0)
        out << "\nNo CS added" << endl;
    else {
        out << "\nCompressor station:" << endl;
        out << "CS name: " << cs.name
            << "\nCS number of the workshops: " << cs.workshop
            << "\nCS number of the workshops in operation: " << cs.workshop_on
            << "\nCS efficiency: " << cs.efficciency << endl;
    }
    return out;
}
void Edit_pipe(Pipe& p) {
    if (p.length != 0) {
        cout << "Edit pipe\n" << "Pipe condition: ";
        p.repair = GetCorrectData(0, 1);
    }
    else
        cout << "You don't have a pipe" << endl;
}
void Edit_cs(CS& cs) {
    if (cs.workshop != 0) {
        cout << "Edit compressor station\n" << "CS number of the workshops in operation: ";
        cs.workshop_on = GetCorrectData(1, cs.workshop);
        while (cs.workshop_on > cs.workshop) {
            cout << "Cant be like this!!!\n" << "CS number of the workshops in operation: ";
            cs.workshop_on = GetCorrectData(1, cs.workshop);
        }
    }
    else
        cout << "You don't have a compressor station" << endl;
}
void Input_file_with_pipe(const Pipe& p) {
    ofstream fout("Titov_laba.txt");
    if (p.length != 0) {
        fout << "Pipe" << endl;
        fout << p.name << endl;
        fout << p.length << endl;
        fout << p.diameter << endl;
        fout << p.repair << endl;
        fout.close();
    }
    else
        cout << "No Pipe data to record" << endl;
}

void Input_file_with_cs(const CS& cs) {
    ofstream fout("Titov_laba.txt", ios::app);
    if (cs.workshop != 0) {
        fout << "Compressor station" << endl;
        fout << cs.name << endl;
        fout << cs.workshop << endl;
        fout << cs.workshop_on << endl;
        fout << cs.efficciency << endl;
        fout.close();
    }
    else
        cout << "No CS data to record" << endl;
}

void Output_file_with_pipe(Pipe& pipe) {
    ifstream fin("Titov_laba.txt");
    if (fin) {
        string pipe_name = "no";
        bool p = 0;
        while (getline(fin, pipe_name))
        {
            if (pipe_name == "Pipe")
            {
                cout << "Data received from file about pipe:" << endl;
                cout << "\nPipe" << endl;
                getline(fin,pipe.name);
                cout << "Pipe name: " << pipe.name << endl;
                fin >> pipe.length;
                cout << "Pipe length: " << pipe.length << endl;
                fin >> pipe.diameter;
                cout << "Pipe diameter: " << pipe.diameter << endl;
                fin >> pipe.repair;
                cout << "The pipe attribute: " << pipe.repair << endl;
                p = true;
            }
        }
        if (p == false)
        {
            cout << "No information about pipe." << endl;
        }
        fin.close();
    }
}
void Output_file_with_cs(CS& cs) {
    ifstream fin("Titov_laba.txt");
    if (fin) {
        string cs_name = "no";
        bool s = 0;
        while (getline(fin, cs_name))
        {
            if (cs_name == "Compressor station")
            {
                cout << "Data received from file about CS:" << endl;
                cout << "\nCompressor station" << endl;
                getline(fin, cs.name);
                cout << "CS title: " << cs.name << endl;
                fin >> cs.workshop;
                cout << "Number of workshops of the CS: " << cs.workshop << endl;
                fin >> cs.workshop_on;
                cout << "Number of workshops in operation of the CS: " << cs.workshop_on << endl;
                fin >> cs.efficciency;
                cout << "CS efficiency: " << cs.efficciency << endl;
                s = true;
            }
        }
        if (s == false)
        {
            cout << "No information about station." << endl;
        }
        fin.close();
    }
}
int main()
{
    unordered_map <int, Pipe> pipes;
    unordered_map <int, CS> stations;
    Pipe p;
    CS cs;
    while (true) {
        cout << "\nChoose Option:"
            <<"\n 1. Add pipe"
            <<"\n 2. Add compressor station"
            <<"\n 3. View all objects"
            <<"\n 4. Edit pipe"
            <<"\n 5. Edit comressor station"
            <<"\n 6. Save"
            <<"\n 7. Load"
            <<"\n 8. Exit"<<endl;
        int value;
        cout << "\nSelect: ";
        value = GetCorrectData(1,8);
        switch (value) {
            case 1: {
                cin >> p;
                break;
            }
            case 2: {
                cin >> cs;
                break;
            }
            case 3: {
                cout << "View all objects" << endl;
                cout << p;
                cout << cs;
                break;
            }
            case 4: {
                Edit_pipe(p);
                break;
            }
            case 5: {
                Edit_cs(cs);
                break;
            case 6: {
                Input_file_with_pipe(p);
                Input_file_with_cs(cs);
                break;
            }
            case 7: {
                Output_file_with_pipe(p);
                Output_file_with_cs(cs);
                break;
            }
            case 8: {
                cout << "You finished the programm";
                return 0;
            }
            default:
                cout << "Enter number from 1 to 8\n";
                break;
            }
        }
    }
}