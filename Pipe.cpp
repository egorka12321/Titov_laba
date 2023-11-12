#include "Pipe.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
using namespace std;

int Pipe::max_id_pipe = 0;

Pipe::Pipe() {
	id_pipe = max_id_pipe++;
}

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

ostream& operator << (ostream& out, const Pipe& p) {
    out << "\nPipe:" << endl;
    out << "id: " << p.id_pipe
        << "\nPipe name: " << p.name
        << "\nPipe length: " << p.length
        << "\nPipe diameter: " << p.diameter
        << "\nPipe condition: " << p.repair
        << "\nmax id: " << p.max_id_pipe << endl;
    return out;
}

void Add_pipes(unordered_map <int, Pipe>& pipes) {
    Pipe pipe;
    cin >> pipe;
    pipes.insert({ pipe.get_id_p(),pipe });
}

void View_pipes(unordered_map <int, Pipe>& pipes) {
    if (pipes.size() == 0)
        cout << "You don't have pipes" << endl;
    else {
        for (auto& pipe : pipes) {
            cout << pipe.second << endl;
        }
    }
}

void Save_pipe(ofstream& fout, const Pipe& p) {
    if (p.name.empty())
        cout << "No Pipe data to record" << endl;
    else {
        fout << "Pipe" << endl;
        fout << p.name << endl;
        fout << p.length << endl;
        fout << p.diameter << endl;
        fout << p.repair << endl;
    }
}

Pipe& Load_pipe(ifstream& fin, Pipe& pipe) {
    string pipe_string;
    while (getline(fin, pipe_string)) {
        if (pipe_string == "Pipe") {
            getline(fin, pipe.name);
            fin >> pipe.length >> pipe.diameter >> pipe.repair;
            return pipe;
        }
    }
}
