#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <sstream>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
using namespace std;

void Save(unordered_map <int, Pipe> pipes, unordered_map <int, CS> stations) {
    if (stations.empty() && pipes.empty())
        Log("You don't have pipes and compressor stations",1);
    else {
        string filename;
        Log("Enter name of your file: ", 2);
        cin >> filename;
        Log_cin(filename);
        ofstream fout;
        fout.open((filename + ".txt"), ios::trunc);
        fout << pipes.size() << " " << stations.size() << endl;
        if (fout.is_open()) {
            for (const auto& p : pipes) {
                Save_pipe(fout, p.second);
                Log("Pipe with id " + to_string(p.first) + " successfully saved",1);
            }
            for (const auto& cs : stations) {
                Save_cstation(fout, cs.second);
                Log("CS with id " + to_string(cs.first) + " successfully saved",1);
            }
        }
        else {
            Log("Didn't find the file with name " + filename + " to save",1);
        }
        string count_p = to_string(pipes.size());
        Log("You saved " + count_p + " pipe(-s)", 1);
        string count_cs = to_string(stations.size());
        Log("You saved " + count_cs + " compressor station(-s)",1);
    }
}

void Load(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations) {
    int count_pipes = 0;
    int count_stations = 0;
    string filename;
    Log("Enter name of your file",2);
    cin >> filename;
    Log_cin(filename);
    ifstream fin;
    fin.open((filename + ".txt"), ios::in);
    if (fin.is_open())
    {
        fin >> count_pipes >> count_stations;
        if (count_pipes == 0 && count_stations == 0)
            Log("You don't have pipes and compressor stations",1);
        else {
            for (int i = 0; i < count_pipes; i++) {
                Pipe p1;
                pipes.insert({ p1.get_id_p(), Load_pipe(fin, p1) });
                }
            for (int i = 0; i < count_stations; i++) {
                CS cs1;
                stations.insert({ cs1.get_id_c(), Load_station(fin, cs1) });
            }
        }
        Log("Finished loading from file",1);
        fin.close();
    }
    else
        Log("Didn't find the file with name " + filename + " to save",1);
}

void Filter(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations) {
    set<int> matching_pipes;
    set<int> matching_stations;
    int value;
    int filter;
    while (true) {
        Log("Choose Option :", 1);
        Log("1. Filter for pipes", 1);
        Log("2. Filter for compressor stations", 1);
        Log("3. Edit filtered objects", 1);
        Log("4. Delete filtered objects", 1);
        Log("5. Exit", 1);
        Log("Select: ",2);
        value = GetCorrectData(1, 5);
        Log_cin(to_string(value));
        switch (value) {
        case 1:
            Log("Choose filter's number:", 1);
            Log("1. Name", 1);
            Log("2. Under repair", 1);
            cin >> filter;
            Log_cin(to_string(filter));
            if (filter == 1) {
                string pipe_name;
                Log("Enter pipe's name to find: ", 2);
                cin >> ws;
                getline(cin, pipe_name);
                Log_cin(pipe_name);
                for (const auto& p : pipes) {
                    if (p.second.name.find(pipe_name) != string::npos)
                        matching_pipes.insert(p.first);
                }
                if (!matching_pipes.empty()) {
                    Log("Pipes: ", 1);
                    for (int pipe_id : matching_pipes) {
                        Log(pipes[pipe_id], 1);
                    }
                }
                else
                    Log("No pipes with this name", 1);
            }
            else if (filter == 2) {
                bool is_u_r;
                Log("Enter the status of repairing: 0 or 1", 1);
                is_u_r = GetCorrectData(0, 1);
                Log_cin(to_string(is_u_r));
                for (const auto& p : pipes) {
                    if (to_string(p.second.repair).find(to_string(is_u_r)) != string::npos)
                        matching_pipes.insert(p.first);
                }
                if (!matching_pipes.empty()) {
                    Log("Pipes: ", 1);
                    for (int pipe_id : matching_pipes) {
                        Log(pipes[pipe_id], 1);
                    }
                }
                else
                    Log("No pipes with this status of repairing", 1);
            }
            else
                Log("No have this filter", 1);
            break;
        case 2:
            Log("Choose filter's number:", 1);
            Log("1. Name", 1);
            Log("2.Percent", 1);
            cin >> filter;
            Log_cin(to_string(filter));
            if (filter == 1) {
                string cs_name;
                Log("Enter compressor station's name to find: ", 2);
                cin >> ws;
                getline(cin, cs_name);
                for (const auto& cs : stations) {
                    if (cs.second.name.find(cs_name) != string::npos)
                        matching_stations.insert(cs.first);
                }
                if (!matching_stations.empty()) {
                    Log("CS: ", 1);
                    for (int cs_id : matching_stations) {
                        Log(stations[cs_id], 1);
                    }
                }
                else
                    Log("No compressor stations with this name", 1);
            }
            else if (filter == 2) {
                double percent;
                Log("Enter the percent: from 0 to 100", 1);
                percent = GetCorrectData(0, 100);
                Log_cin(to_string(percent));
                for (const auto& cs : stations) {
                    double real_percent = ((cs.second.workshop - cs.second.workshop_on) * 100.0 / cs.second.workshop);
                    if (abs(percent-real_percent)<=1)
                        matching_stations.insert(cs.first);
                }
                if (!matching_stations.empty()) {
                    Log("CS: ", 1);
                    for (int cs_id : matching_stations) {
                        Log(stations[cs_id], 1);
                    }
                }
                else
                    Log("No compressor stations with this percent status", 1);
            }
            else
                Log("No have this filter",1);
            break;
        case 3: {
            Log("Select objects to edit:", 1);
            Log("1. Edit found pipes", 1);
            Log("2. Edit found compressor stations", 1);
            int edit_choice = GetCorrectData(1, 2);
            Log_cin(to_string(edit_choice));
            if (edit_choice == 1) {
                Log("1. Edit all filtered pipes", 1);
                Log("2. Edit using choosing", 1);
                int changeChoice = GetCorrectData(1, 2);
                Log_cin(to_string(changeChoice));
                if (matching_pipes.empty())
                    Log("You don'h have filtered pipes", 1);
                else {
                    if (changeChoice == 1) {
                        for (int pipe_id : matching_pipes) {
                            Pipe& p = pipes[pipe_id];
                            p.repair = !p.repair;
                            Log("The status of pipe " + to_string(pipe_id) + " has been successfully changed", 1);
                        }
                    }
                    else if (changeChoice == 2) {
                        Log("Enter pipes id's set: ", 2);
                        string id_input;
                        int n;
                        set<int> idPipe;
                        cin >> ws;
                        getline(cin, id_input);
                        Log_cin(id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idPipe.insert(n);
                        for (int pipe_id : idPipe) {
                            Pipe& p = pipes[pipe_id];
                            p.repair = !p.repair;
                            Log("The status of pipe " + to_string(pipe_id) + " has been successfully changed", 1);
                        }
                    }
                }
            }
            else if (edit_choice == 2) {
                Log("1. Edit all filtered compressor stations", 1);
                Log("2. Edit using choosing", 1);
                int changeChoice = GetCorrectData(1, 2);
                Log_cin(changeChoice);
                if (matching_stations.empty())
                    Log("You don'h have filtered comressor stations", 1);
                else {
                    if (changeChoice == 1) {
                        for (int cs_id : matching_stations) {
                            CS& cs = stations[cs_id];
                            Log("The number of workshops: " + to_string(cs.workshop), 1);
                            Log("Type the new number of workshops in operation:", 2);
                            cs.workshop_on = GetCorrectData(1, cs.workshop);
                            Log_cin(to_string(cs.workshop_on));
                            while (cs.workshop < cs.workshop_on) {
                                Log("The number of workshops can't be less then the number of workshops in operation", 1);
                                Log("Type the right number", 1);
                                cs.workshop_on = GetCorrectData(1, cs.workshop);
                                Log_cin(to_string(cs.workshop_on));
                            }
                            Log("The status of compressor station " + to_string(cs_id) + " has been successfully changed", 1);
                        }
                    }
                    else if (changeChoice == 2) {
                        Log("Enter cs id's set: ", 2);
                        string id_input;
                        int n;
                        set<int> idCS;
                        cin >> ws;
                        getline(cin, id_input);
                        Log_cin(id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idCS.insert(n);
                        for (int cs_id : idCS) {
                            CS& cs = stations[cs_id];
                            Log("The number of workshops: " + to_string(cs.workshop), 1);
                            Log("Type the new number of workshops in operation:", 1);
                            cs.workshop_on = GetCorrectData(1, cs.workshop);
                            Log_cin(to_string(cs.workshop_on));
                            while (cs.workshop < cs.workshop_on) {
                                Log("The number of workshops can't be less then the number of workshops in operation", 1);
                                Log("Type the right number", 1);
                                cs.workshop_on = GetCorrectData(1, cs.workshop);
                                Log_cin(to_string(cs.workshop_on));
                            }
                            Log("The status of compressor station " + to_string(cs_id) + " has been successfully changed", 1);
                        }
                    }
                }
            }
            else
                Log("No have this filter", 1);
        }
            break;
        case 4:
            if (!matching_pipes.empty() || !matching_stations.empty()) {
                Log("Select objects to delete:", 1);
                Log("1. Delete found pipes", 1);
                Log("2. Delete found compressor stations", 1);
                Log("3. Delete both", 1);
                int removal_choice = GetCorrectData(1, 3);
                Log_cin(to_string(removal_choice));
                if (removal_choice == 1 || removal_choice == 3) {
                    Log("1. Delete all filtered pipes", 1);
                    Log("2. Delete using choosing", 1);
                    int deleteChoice = GetCorrectData(1, 2);
                    Log_cin(to_string(deleteChoice));
                    if (deleteChoice == 1) {
                        for (int id_pipe : matching_pipes) {
                            auto pipe_filtered = pipes.find(id_pipe);
                            pipes.erase(pipe_filtered);
                            Log("The pipe " + to_string(id_pipe) + " has been successfully deleted", 1);
                        }
                        matching_pipes.clear();
                    }
                    else if (deleteChoice == 2) {
                        Log("Enter pipes id's set: ", 2);
                        string id_input;
                        int n;
                        set<int> idPipe;
                        cin >> ws;
                        getline(cin, id_input);
                        Log_cin(id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idPipe.insert(n);
                        for (int id_pipe : idPipe) {
                            auto pipe_filtered = pipes.find(id_pipe);
                            pipes.erase(pipe_filtered);
                            Log("The pipe " + to_string(id_pipe) + " has been successfully deleted", 1);
                        }
                    }
                    else
                        Log("No have this filter", 1);
                }
                else if (removal_choice == 2 || removal_choice == 3) {
                    Log("1. Delete all filtered compressor stations", 1);
                    Log("2. Delete using choosing", 1);
                    int deleteChoice = GetCorrectData(1, 2);
                    Log_cin(to_string(deleteChoice));
                    if (deleteChoice == 1) {
                        for (int id_cs : matching_stations) {
                            auto cs_filtered = stations.find(id_cs);
                            stations.erase(cs_filtered);
                            Log("The cs " + to_string(id_cs) + " has been successfully deleted", 1);
                        }
                        matching_stations.clear();
                    }
                    else if (deleteChoice == 2) {
                        Log("Enter cs id's set: ", 2);
                        string id_input;
                        int n;
                        set<int> idCS;
                        cin >> ws;
                        getline(cin, id_input);
                        Log_cin(id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idCS.insert(n);
                        for (int id_cs : idCS) {
                            auto cs_filtered = stations.find(id_cs);
                            stations.erase(cs_filtered);
                            Log("The cs " + to_string(id_cs) + " has been successfully deleted", 1);
                        }
                    }
                    else
                        Log("No have this filter", 1);
                }
            }
            else
                Log("No have objects to remove", 1);
            break;
        case 5:
            return;
        }
    }
}

void ClearLogFile() {
    ofstream logFile("log.txt", ios::trunc);
    logFile.close();
}

int main()
{
    unordered_map <int, Pipe> pipes;
    unordered_map <int, CS> stations;
    int value;
    ClearLogFile();
    while (true) {
        Log("Choose Option:",1);
        Log("1. Add pipe",1);
        Log("2. Add compressor station",1);
        Log("3. View all objects",1);
        Log("4. Filter",1);
        Log("5. Save",1);
        Log("6. Load",1);
        Log("7. Exit",1);
        Log("Select: ",2);
        value = GetCorrectData(1,7);
        Log_cin(to_string(value));
        switch (value) {
            case 1:
                Add_pipes(pipes);
                break;
            case 2:
                Add_cs(stations);
                break;
            case 3:
                View_pipes(pipes);
                View_cs(stations);
                break;
            case 4:
                Filter(pipes,stations);
                break;
            case 5:
                Save(pipes,stations);
                break;
            case 6:
                Load(pipes, stations);
                break;
            case 7:
                Log("You finished the programm", 1);
                return 0;
            default:
                Log("Enter number from 1 to 8", 1);
                break;
        }
    }
}