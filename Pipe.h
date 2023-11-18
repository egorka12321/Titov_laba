#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class Pipe
{
public:
	string name = "None";
	double length = 0;
	int diameter = 0;
	bool repair = false;
	int id_pipe = 0;
	static int max_id_pipe;
	Pipe();
	int get_id_p() { return id_pipe; };
	friend ostream& operator << (ostream& out, const Pipe& p);
	friend istream& operator >> (istream& in, Pipe& truba);
	friend void Save_pipe(ofstream& fout, const Pipe& p);
	friend Pipe& Load_pipe(ifstream& fin, Pipe& pipe);
};