#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <format>
#include "Pipe.h"
#include "CS.h"
#include "Gas_transmission_net.h"
#include "Utils.h"

using namespace std;
using namespace chrono;

int main() {
    unordered_map <int, Pipe> pipes;
    unordered_map <int, CS> stations;
    GTN gtn;
    vector<vector<Connection>> graph(CS::max_id_cs + 1);

    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("log_" + time+".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    while (true) {
        cout << "\nChoose Option:"
            << "\n 1. Add pipe"
            << "\n 2. Add compressor station"
            << "\n 3. View all objects"
            << "\n 4. Filter"
            << "\n 5. Save"
            << "\n 6. Load"
            << "\n 7. Connect pipe and cs in the gas transmission net"
            << "\n 8. Actions with graph"
            << "\n 9. Exit" << endl;
        cout << "\nSelect: ";
        int value = GetCorrectData(1, 9);
        switch (value) {
            case 1:
                gtn.Add_pipes(pipes);
                break;
            case 2:
                gtn.Add_cs(stations);
                break;
            case 3:
                gtn.View_objects(pipes, stations);
                break;
            case 4:
                gtn.Filter(pipes, stations, graph);
                break;
            case 5:
                gtn.Save(pipes, stations);
                break;
            case 6:
                gtn.Load(pipes, stations);
                break;
            case 7:
                gtn.Connect_cs_and_pipes(pipes, stations, graph);
                break;
            case 8:
                gtn.Operations_with_graph(pipes, stations, graph);
                break;
            case 9:
                cout << "You finished the programm";
                return 0;
            default:
                cout << "Enter number from 1 to 8\n";
                break;
        }
    }
}