﻿#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
using namespace std;

void Save(unordered_map <int, Pipe> pipes, unordered_map <int, CS> stations) {
    if (stations.empty() && pipes.empty())
        cout << "You don't have pipes and compressor stations" << endl;
    else {
        string filename;
        cout << "Enter name of your file" << endl;
        cin >> filename;
        ofstream fout;
        fout.open((filename + ".txt"), ios::trunc);
        fout << pipes.size() << " " << stations.size() << endl;
        if (fout.is_open()) {
            for (const auto& p : pipes) {
                Save_pipe(fout, p.second);
            }
            for (const auto& cs : stations) {
                Save_cstation(fout, cs.second);
            }
        }
        else {
            cout << ("Didn't find the file with name " + filename + " to save") << endl;
        }
        string count_p = to_string(pipes.size());
        cout << ("You saved " + count_p + " pipe(-s)") << endl;
        string count_cs = to_string(stations.size());
        cout << ("You saved " + count_cs + " compressor station(-s)") << endl;
    }
}

void Load(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations) {
    int count_pipes = 0;
    int count_stations = 0;
    string filename;
    cout << "Enter name of your file" << endl;
    cin >> filename;
    ifstream fin;
    fin.open((filename + ".txt"), ios::in);
    if (fin.is_open())
    {
        fin >> count_pipes >> count_stations;
        if (count_pipes == 0 && count_stations == 0)
            cout << "You don't have pipes and compressor stations" << endl;
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
        cout << "Finished loading from file" << endl;
        fin.close();
    }
    else
        cout << ("Didn't find the file with name " + filename + " to save") << endl;
}

void Filter(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations) {
    set<int> matching_pipes;
    set<int> matching_stations;
    int value;
    int filter;
    while (true) {
        cout << "\nChoose Option:"
            << "\n 1. Filter for pipes"
            << "\n 2. Filter for compressor station"
            << "\n 3. Edit filtered objects"
            << "\n 4. Delete filtered objects"
            << "\n 5. Exit" << endl;
        cout << "\nSelect: ";
        value = GetCorrectData(1, 5);
        switch (value) {
        case 1:
            //matching_pipes.clear();
            cout << "Choose filter:" << "\n1. Name" << "\n2. Under repair" << endl;
            cin >> filter;
            if (filter == 1) {
                string pipe_name;
                cout << "Enter pipe's name to find" << endl;
                cin >> ws;
                getline(cin, pipe_name);
                for (const auto& p : pipes) {
                    if (p.second.name.find(pipe_name) != string::npos)
                        matching_pipes.insert(p.first);
                }
                if (!matching_pipes.empty()) {
                    cout << "\nPipes: " << endl;
                    for (int pipe_id : matching_pipes) {
                        cout << pipes[pipe_id] << endl;
                    }
                }
                else
                    cout << "No pipes with this name" << endl;
            }
            else if (filter == 2) {
                bool is_u_r;
                cout << "Enter the status of repairing: 0 or 1" << endl;
                is_u_r = GetCorrectData(0, 1);
                for (const auto& p : pipes) {
                    if (to_string(p.second.repair).find(to_string(is_u_r)) != string::npos)
                        matching_pipes.insert(p.first);
                }
                if (!matching_pipes.empty()) {
                    cout << "\nPipes: " << endl;
                    for (int pipe_id : matching_pipes) {
                        cout << pipes[pipe_id] << endl;
                    }
                }
                else
                    cout << "No pipes with this status of repairing" << endl;
            }
            else
                cout << "No have this filter" << endl;
            break;
        case 2:
            cout << "Choose filter:" << "\n1. Name" << "\n2. Percent" << endl;
            cin >> filter;
            if (filter == 1) {
                string cs_name;
                cout << "Enter compressor station's name to find" << endl;
                cin >> ws;
                getline(cin, cs_name);
                for (const auto& cs : stations) {
                    if (cs.second.name.find(cs_name) != string::npos)
                        matching_stations.insert(cs.first);
                }
                if (!matching_stations.empty()) {
                    cout << "\nCS: " << endl;
                    for (int cs_id : matching_stations) {
                        cout << stations[cs_id] << endl;
                    }
                }
                else
                    cout << "No compressor stations with this name" << endl;
            }
            else if (filter == 2) {
                double percent;
                cout << "Enter the percent: from 0 or 100" << endl;
                percent = GetCorrectData(0, 100);
                for (const auto& cs : stations) {
                    double real_percent = round((cs.second.workshop - cs.second.workshop_on) * 100.0 / cs.second.workshop);
                    if (percent == real_percent)
                        matching_stations.insert(cs.first);
                }
                if (!matching_stations.empty()) {
                    cout << "\nCS: " << endl;
                    for (int cs_id : matching_stations) {
                        cout << stations[cs_id] << endl;
                    }
                }
                else
                    cout << "No compressor stations with this percent status" << endl;
            }
            else
                cout << "No have this filter" << endl;
            break;
        case 3: {
            cout << "Select objects to edit" << endl;
            cout << "1. Edit found pipes" << endl;
            cout << "2. Edit found compressor stations" << endl;
            int edit_choice = GetCorrectData(1, 2);
            if (edit_choice == 1) {
                if (!matching_pipes.empty()) {
                    for (int pipe_id : matching_pipes) {
                        Pipe& p = pipes[pipe_id];
                        p.repair = !p.repair;
                        cout << "The status of pipe " + to_string(pipe_id) + " has been successfully changed" << endl;
                    }
                }
                else
                    cout << "You don'h have filtered pipes";
            }
            if (edit_choice == 2) {
                if (!matching_stations.empty()) {
                    for (int cs_id : matching_stations) {
                        CS& cs = stations[cs_id];
                        cout << ("The number of workshops: " + to_string(cs.workshop)) << endl;
                        cout << ("Type the new number of workshops in operation:") << endl;
                        cs.workshop_on = GetCorrectData(1, cs.workshop);
                        while (cs.workshop < cs.workshop_on) {
                            cout << ("The number of workshops can't be less then the number of workshops in operation") << endl;
                            cout << "Type the right number" << endl;
                            cs.workshop_on = GetCorrectData(1, cs.workshop);
                        }
                        cout << ("The status of compressor station " + to_string(cs_id) + " has been successfully changed") << endl;
                    }
                }
                else
                    cout << "You don'h have filtered compressor stations";
            }
            else
                cout << "No have this filter" << endl;
        }
            break;
        case 4:
            if (!matching_pipes.empty() || !matching_stations.empty()) {
                cout << "Select objects to delete" << endl;
                cout << "1. Delete found pipes" << endl;
                cout << "2. Delete found compressor stations" << endl;
                cout << "3. Delete both" << endl;
                int removal_choice = GetCorrectData(1, 3);
                if (removal_choice == 1 || removal_choice == 3) {
                    for (int id_pipe : matching_pipes) {
                        auto pipe_filtered = pipes.find(id_pipe);
                        pipes.erase(pipe_filtered);
                    }
                    cout << "Pipes removed succesfully" << endl;
                    matching_pipes.clear();
                }
                else if (removal_choice == 2 || removal_choice == 3) {
                    for (int id_cs : matching_stations) {
                        auto cs_filtered = stations.find(id_cs);
                        stations.erase(cs_filtered);
                    }
                    cout << "Compressor stations removed succesfully" << endl;
                    matching_stations.clear();
                }
            }
            else
                cout << "No have objects to remove";
            break;
        case 5:
            return;
        }
    }
}

int main()
{
    unordered_map <int, Pipe> pipes;
    unordered_map <int, CS> stations;
    int value;

    while (true) {
        cout << "\nChoose Option:"
            <<"\n 1. Add pipe"
            <<"\n 2. Add compressor station"
            <<"\n 3. View all objects"
            <<"\n 4. Filter"
            <<"\n 5. Save"
            <<"\n 6. Load"
            <<"\n 7. Exit" << endl;
        cout << "\nSelect: ";
        value = GetCorrectData(1,7);
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
                cout << "You finished the programm";
                return 0;
            default:
                cout << "Enter number from 1 to 8\n";
                break;
        }
    }
}