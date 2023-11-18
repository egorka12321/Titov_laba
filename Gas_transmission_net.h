#pragma once
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"

class GTN {
public:
	void Add_pipes(unordered_map <int, Pipe>& pipes);
	void Add_cs(unordered_map <int, CS>& stations);
	void View_objects(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations);
	void Filter(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations);
	void Save(unordered_map <int, Pipe> pipes, unordered_map <int, CS> stations);
	void Load(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations);
};