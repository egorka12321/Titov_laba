#pragma once
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
struct Connection {
	int input_station;
	int pipe;
	int output_station;
};
class GTN {
public:
	void Add_pipes(unordered_map <int, Pipe>& pipes);
	void Add_cs(unordered_map <int, CS>& stations);
	void View_objects(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations);
	void Filter(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations, vector<vector<Connection>>& graph);
	void Save(unordered_map <int, Pipe> pipes, unordered_map <int, CS> stations);
	void Load(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations);
	int Add_newpipe_connect(unordered_map <int, Pipe>& pipes, int diameter);
	void Connect_cs_and_pipes(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations, vector<vector<Connection>>& graph);
	void Remove_vertex(int vertex, vector<vector<Connection>>& graph);
	void Remove_edge_and_unused_vertices(int id_pipe, vector<vector<Connection>>& graph);
	void Remove_connection(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, vector<vector<Connection>>& graph);
	void Operations_with_graph(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations, vector<vector<Connection>>& graph);
	void Topological_sort(vector<vector<Connection>>& graph);
};