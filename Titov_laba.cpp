#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Pipe {
    string name = "None";
    double length = 0;
    int diameter = 0;
    bool repair = false;
};
struct CS {
    string name = "None";
    int workshop = 0;
    int workshop_on = 0;
    char efficciency = 'F';
};

 void Check_int(int& integer) {
    cin >> integer;
    while (cin.fail() || cin.peek() != '\n' || integer <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again \n" << "Enter integer" <<endl;
        cin >> integer;
    }
}
void Check_dbl(double& doub) {
    cin >> doub;
    while (cin.fail() || cin.peek() != '\n' || doub < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again \n" << "Enter double" << endl;
        cin >> doub;
    }
}
void Check_bool(bool& boolean) {
    cin >> boolean;
    while (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again \n" << "Enter bool" << endl;
        cin >> boolean;
    }
}
void Check_char(char& character) {
    cin >> character;
    while (cin.fail() || cin.peek() != '\n' || (character < 'A') || (character > 'D')) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again \n" << "Enter symbol from A to D" << endl;
        cin >> character;
    }
}
Pipe AddPipe() {
    Pipe truba;
    cout << "Enter name of the pipe: ";
    cin.ignore();
    getline(cin,truba.name);
    cout << "Enter length of the pipe: ";
    Check_dbl(truba.length);
    cout << "Enter diameter of the pipe: ";
    Check_int(truba.diameter);
    cout << "Enter condition of the pipe: ";
    Check_bool(truba.repair);
    return truba;
}
CS AddCS() {
    CS comp_station;
    cout << "Enter name of the CS: ";
    cin.ignore();
    getline(cin,comp_station.name);
    cout << "Enter number of the workshops: ";
    Check_int(comp_station.workshop);
    cout << "Enter number of the workshops in operation: ";
    Check_int(comp_station.workshop_on);
    while (comp_station.workshop_on > comp_station.workshop) {
        cout << "Cant be like this!!!" << endl;
        Check_int(comp_station.workshop_on);
    }
    cout << "Enter efficiency of CS: ";
    Check_char(comp_station.efficciency);
    return comp_station;
}
void ViewPipe(const Pipe p) {
    if (p.length == 0)
        cout << "\nNo pipes added" << endl;
    else {
        cout << "\nPipe:" << endl;
        cout << "Pipe name: " << p.name
            << "\nPipe length: " << p.length
            << "\nPipe diameter: " << p.diameter
            << "\nPipe condition: " << p.repair << endl;
    }
}
void ViewCS(const CS cs) {
    if (cs.workshop == 0)
        cout << "\nNo CS added" << endl;
    else {
        cout << "\nCompressor station:" << endl;
        cout << "CS name: " << cs.name
            << "\nCS number of the workshops: " << cs.workshop
            << "\nCS number of the workshops in operation: " << cs.workshop_on
            << "\nCS efficiency: " << cs.efficciency << endl;
    }
}
//void Input_file(Pipe p,CS cs) {
//    ofstream fout("Titov_laba.txt");
//    if (p.length != 0) {
//        fout << "Pipe" << endl;
//        fout << p.name << endl;
//        fout << p.length << endl;
//        fout << p.diameter << endl;
//        fout << p.repair << endl;
//    }
//    else
//        cout << "No Pipe data to record" << endl;
//    if (cs.workshop != 0) {
//        fout << "Compressor station" << endl;
//        fout << cs.name << endl;
//        fout << cs.workshop << endl;
//        fout << cs.workshop_on << endl;
//        fout << cs.efficciency << endl;
//    }
//    else
//        cout << "No CS data to record" << endl;
//    fout.close();
//}
void Input_file_with_pipe(const Pipe& p, fstream& file) {
    if (p.length != 0) {
        file << "Pipe" << endl;
        file << p.name << endl;
        file << p.length << endl;
        file << p.diameter << endl;
        file << p.repair << endl;
    }
    else
        cout << "No Pipe data to record" << endl;
}

void Input_file_with_cs(const CS& cs, fstream& file) {
    if (cs.workshop != 0) {
        file << "Compressor station" << endl;
        file << cs.name << endl;
        file << cs.workshop << endl;
        file << cs.workshop_on << endl;
        file << cs.efficciency << endl;
    }
    else
        cout << "No CS data to record" << endl;
}

void Output_file(Pipe& pipe,CS& cs) {
    ifstream fin("Titov_laba.txt");
    if (fin) {
        string pipe_or_cs_name = "no";
        int p = 0;
        int s = 0;
        while (getline(fin, pipe_or_cs_name))
        {
            if (pipe_or_cs_name == "Pipe")
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
                p += 1;
            }
            if (pipe_or_cs_name == "Compressor station")
            {
                cout << "Data received from file about CS:" << endl;
                cout << "\nCompressor station" << endl;
                getline(fin,cs.name);
                cout << "CS title: " << cs.name << endl;
                fin >> cs.workshop;
                cout << "Number of workshops of the CS: " << cs.workshop << endl;
                fin >> cs.workshop_on;
                cout << "Number of workshops in operation of the CS: " << cs.workshop_on << endl;
                fin >> cs.efficciency;
                cout << "CS efficiency: " << cs.efficciency << endl;
                s += 1;
            }
        }
        if (p == 0)
        {
            cout << "No information about pipe." << endl;
        }
        if (s == 0)
        {
            cout << "No information about station." << endl;
        }
        fin.close();
    }

}
int main()
{
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
        int value = -1;
        cout << "\nSelect: ";
        Check_int(value);
        switch (value) {
            case 1: {
                if ((p.length) == 0) {
                    cout << "Add pipe" << endl;
                    p = AddPipe();
                }
                else
                    cout << "You already have one pipe" << endl;
                break;
            }
            case 2: {
                if (cs.workshop == 0) {
                    cout << "Add compressor station" << endl;
                    cs = AddCS();
                }
                else
                    cout << "You already have one comressor station" << endl;
                break;
            }
            case 3: {
                cout << "View all objects" << endl;
                ViewPipe(p);
                ViewCS(cs);
                break;
            }
            case 4: {
                if (p.length != 0) {
                    cout << "Edit pipe\n" << "Pipe condition: ";
                    Check_bool(p.repair);
                }
                else
                    cout << "You don't have a pipe" << endl;
                break;
            }
            case 5: {
                if (cs.workshop != 0) {
                    cout << "Edit compressor station\n" << "CS number of the workshops in operation: ";
                    Check_int(cs.workshop_on);
                    while (cs.workshop_on > cs.workshop) {
                        cout << "Cant be like this!!!\n" << "CS number of the workshops in operation: ";
                        Check_int(cs.workshop_on);
                    }
                }
                else
                    cout << "You don't have a compressor station" << endl;
                break;
            case 6: {
                //Input_file(p,cs);
                fstream file("Titov_laba.txt", ios::out);
                if (file) {
                    Input_file_with_pipe(p, file);
                    Input_file_with_cs(cs, file);
                    file.close();
                }
                else {
                    cout << "Failed to open file" << endl;
                }
                break;
            }
            case 7: {
                Output_file(p,cs);
                break;
            }
            case 8: {
                cout << "You finished the programm";
                return 0;
            }
            default:
                cout << "Enter number from 0 to 7\n";
                break;
            }
        }
    }

}