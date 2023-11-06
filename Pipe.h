#pragma once
#include <string>
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
	friend istream& operator >> (istream& in, Pipe& truba);
	friend ostream& operator << (ostream& out, const Pipe& p);
	friend void Input_file_with_pipe(const Pipe& p);
	friend void Output_file_with_pipe(Pipe& pipe);
	Pipe();
};