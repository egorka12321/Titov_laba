#include "Gas_transmission_net.h"
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <queue>

void GTN::Add_pipes(unordered_map<int, Pipe>& pipes)
{
    Pipe pipe;
    cin >> pipe;
    pipes.insert({ pipe.get_id_p(),pipe });
}

void GTN::Add_cs(unordered_map<int, CS>& stations)
{
    CS station;
    cin >> station;
    stations.insert({ station.get_id_c(),station });
}

void GTN::View_objects(unordered_map <int, Pipe>& pipes, unordered_map<int, CS>& stations)
{
    if (pipes.size() == 0)
        cout << "You don't have pipes" << endl;
    else {
        for (auto& pipe : pipes) {
            cout << pipe.second << endl;
        }
    }
    if (stations.size() == 0)
        cout << "You don't have compressor stations" << endl;
    else {
        for (auto& cs : stations) {
            cout << cs.second << endl;
        }
    }
}

void GTN::Filter(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations, vector<vector<Connection>>& graph) {
    set<int> matching_pipes;
    set<int> matching_stations;
    int value;
    int filter;
    while (true) {
        cout << "\nChoose Option:"
            << "\n 1. Filter for pipes"
            << "\n 2. Filter for compressor stations"
            << "\n 3. Edit filtered objects"
            << "\n 4. Delete filtered objects"
            << "\n 5. Exit" << endl;
        cout << "\nSelect: ";
        value = GetCorrectData(1, 5);
        switch (value) {
        case 1:
            cout << "Choose filter's number:" << endl;
            cout << "1. Name" << endl;
            cout << "2. Under repair" << endl;
            cout << "Select: ";
            cin >> filter;
            if (filter == 1) {
                matching_pipes.clear();
                string pipe_name;
                cout << "Enter pipe's name to find: ";
                cin >> ws;
                getline(cin, pipe_name);
                for (const auto& p : pipes) {
                    if (p.second.name.find(pipe_name) != string::npos) {
                        matching_pipes.insert(p.first);
                        cout << pipes[p.first] << endl;
                    }
                }
                if (matching_pipes.empty())
                    cout << "No pipes with this name" << endl;
            }
            else if (filter == 2) {
                matching_pipes.clear();
                bool is_u_r;
                cout << "Enter the status of repairing: 0 or 1: ";
                is_u_r = GetCorrectData(0, 1);
                for (const auto& p : pipes) {
                    if (to_string(p.second.repair).find(to_string(is_u_r)) != string::npos) {
                        matching_pipes.insert(p.first);
                        cout << pipes[p.first] << endl;
                    }
                }
                if (matching_pipes.empty())
                    cout << "No pipes with this status of repairing" << endl;
            }
            else
                cout << "No have this filter" << endl;
            break;
        case 2:
            cout << "Choose filter's number:" << endl;
            cout << "1. Name" << endl;
            cout << "2. Percent" << endl;
            cout << "Select: ";
            cin >> filter;
            if (filter == 1) {
                matching_stations.clear();
                string cs_name;
                cout << "Enter compressor station's name to find: ";
                cin >> ws;
                getline(cin, cs_name);
                for (const auto& cs : stations) {
                    if (cs.second.name.find(cs_name) != string::npos) {
                        matching_stations.insert(cs.first);
                        cout << stations[cs.first] << endl;
                    }
                }
                if (matching_stations.empty())
                    cout << "No compressor stations with this name" << endl;
            }
            else if (filter == 2) {
                matching_stations.clear();
                double percent;
                int pr_choice;
                cout << "Enter the percent: from 0 or 100: ";
                percent = GetCorrectData(0, 100);
                cout << "Choose percent's condition:" << endl;
                cout << "1. Less than percent" << endl;
                cout << "2. This percent" << endl;
                cout << "3. More than percent" << endl;
                cout << "Select: ";
                cin >> pr_choice;
                for (const auto& cs : stations) {
                    double real_percent = ((cs.second.workshop - cs.second.workshop_on) * 100.0 / cs.second.workshop);
                    if (pr_choice == 1 && real_percent < percent) {
                        matching_stations.insert(cs.first);
                        cout << stations[cs.first] << endl;
                    }
                    else if (pr_choice == 2 && abs(percent - real_percent) <= 0.5) {
                        matching_stations.insert(cs.first);
                        cout << stations[cs.first] << endl;
                    }
                    else if (pr_choice == 3 && real_percent > percent) {
                        matching_stations.insert(cs.first);
                        cout << stations[cs.first] << endl;
                    }
                }
                if (matching_stations.empty())
                    cout << "No compressor stations with this percent status" << endl;
            }
            else
                cout << "No have this filter" << endl;
            break;
        case 3: {
            cout << "Select objects to edit" << endl;
            cout << "1. Edit found pipes" << endl;
            cout << "2. Edit found compressor stations" << endl;
            cout << "Select: ";
            int edit_choice = GetCorrectData(1, 2);
            if (edit_choice == 1) {
                cout << "\n1. Edit all filtered pipes" << endl;
                cout << "2. Edit using id's choice" << endl;
                cout << "Select: ";
                int changeChoice = GetCorrectData(1, 2);
                if (matching_pipes.empty())
                    cout << "You don'h have filtered pipes";
                else {
                    if (changeChoice == 1) {
                        for (int pipe_id : matching_pipes) {
                            Pipe& p = pipes[pipe_id];
                            p.repair = !p.repair;
                            cout << "The status of pipe " + to_string(pipe_id) + " has been successfully changed" << endl;
                        }
                    }
                    else if (changeChoice == 2) {
                        cout << "Enter pipes id's set: ";
                        string id_input;
                        int n;
                        set<int> idPipe;
                        cin >> ws;
                        getline(cin, id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idPipe.insert(n);
                        for (int pipe_id : idPipe) {
                            Pipe& p = pipes[pipe_id];
                            p.repair = !p.repair;
                            cout << "The status of pipe " + to_string(pipe_id) + " has been successfully changed" << endl;;
                        }
                    }
                }
            }
            else if (edit_choice == 2) {
                cout << "\n1. Edit all filtered compressor stations" << endl;
                cout << "2. Edit using id's choice" << endl;
                cout << "Select: ";
                int changeChoice = GetCorrectData(1, 2);
                if (matching_stations.empty())
                    cout << "You don't have filtered comressor stations";
                else {
                    if (changeChoice == 1) {
                        for (int cs_id : matching_stations) {
                            CS& cs = stations[cs_id];
                            cout << ("\nThe number of workshops: " + to_string(cs.workshop)) << endl;
                            cout << ("Type the new number of workshops in operation: ") << endl;
                            cs.workshop_on = GetCorrectData(1, cs.workshop);
                            cout << ("The status of compressor station " + to_string(cs_id) + " has been successfully changed") << endl;
                        }
                    }
                    else if (changeChoice == 2) {
                        cout << "Enter cs id's set: ";
                        string id_input;
                        int n;
                        set<int> idCS;
                        cin >> ws;
                        getline(cin, id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idCS.insert(n);
                        for (int cs_id : idCS) {
                            CS& cs = stations[cs_id];
                            cout << ("\nThe number of workshops: " + to_string(cs.workshop)) << endl;
                            cout << ("Type the new number of workshops in operation: ") << endl;
                            cs.workshop_on = GetCorrectData(1, cs.workshop);
                            cout << ("The status of compressor station " + to_string(cs_id) + " has been successfully changed") << endl;
                        }
                    }
                }
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
                cout << "Select: ";
                int removal_choice = GetCorrectData(1, 3);
                if (removal_choice == 1 || removal_choice == 3) {
                    cout << "\n1. Delete all filtered pipes" << endl;
                    cout << "2. Delete using id's choice" << endl;
                    cout << "\nSelect: ";
                    int deleteChoice = GetCorrectData(1, 2);
                    if (deleteChoice == 1) {
                        for (int id_pipe : matching_pipes) {
                            auto pipe_filtered = pipes.find(id_pipe);
                            pipes.erase(pipe_filtered);
                            Remove_edge_and_unused_vertices(id_pipe, graph);
                            cout << "The pipe " + to_string(id_pipe) + " has been successfully deleted" << endl;
                        }
                        matching_pipes.clear();
                    }
                    else if (deleteChoice == 2) {
                        cout << "Enter pipes id's set: ";
                        string id_input;
                        int n;
                        set<int> idPipe;
                        cin >> ws;
                        getline(cin, id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idPipe.insert(n);
                        for (int id_pipe : idPipe) {
                            auto pipe_filtered = pipes.find(id_pipe);
                            pipes.erase(pipe_filtered);
                            Remove_edge_and_unused_vertices(id_pipe, graph);
                            cout << "The pipe " + to_string(id_pipe) + " has been successfully deleted" << endl;
                        }
                    }
                    else
                        cout << "No have this filter" << endl;
                }
                else if (removal_choice == 2 || removal_choice == 3) {
                    cout << "\n1. Delete all filtered compressor stations" << endl;
                    cout << "2. Delete using id's choice" << endl;
                    cout << "Select: ";
                    int deleteChoice = GetCorrectData(1, 2);
                    if (deleteChoice == 1) {
                        for (int id_cs : matching_stations) {
                            auto cs_filtered = stations.find(id_cs);
                            stations.erase(cs_filtered);
                            if (id_cs < graph.size()) {
                                Remove_vertex(id_cs, graph);
                            }
                            cout << "The cs " + to_string(id_cs) + " has been successfully deleted" << endl;
                        }
                        matching_stations.clear();
                    }
                    else if (deleteChoice == 2) {
                        cout << "Enter cs id's set: ";
                        string id_input;
                        int n;
                        set<int> idCS;
                        cin >> ws;
                        getline(cin, id_input);
                        istringstream ss(id_input);
                        while (ss >> n)
                            idCS.insert(n);
                        for (int id_cs : idCS) {
                            auto cs_filtered = stations.find(id_cs);
                            stations.erase(cs_filtered);
                            if (id_cs < graph.size()) {
                                Remove_vertex(id_cs, graph);
                            }
                            cout << "The cs " + to_string(id_cs) + " has been successfully deleted" << endl;
                        }
                    }
                    else
                        cout << "No have this filter" << endl;
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

void GTN::Save(unordered_map <int, Pipe> pipes, unordered_map <int, CS> stations) {
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
            cout << ("Wasn't found the file with name " + filename + " to save") << endl;
        }
        string count_p = to_string(pipes.size());
        cout << ("You saved " + count_p + " pipe(-s)") << endl;
        string count_cs = to_string(stations.size());
        cout << ("You saved " + count_cs + " compressor station(-s)") << endl;
    }
}

void GTN::Load(unordered_map <int, Pipe>& pipes, unordered_map <int, CS>& stations) {
    int count_pipes = 0;
    int count_stations = 0;
    string filename;
    cout << "Enter name of your file" << endl;
    cin >> filename;
    ifstream fin;
    fin.open((filename + ".txt"), ios::in);
    if (fin.is_open())
    {
        pipes.clear();
        stations.clear();
        fin >> count_pipes >> count_stations;
        if (count_pipes == 0 && count_stations == 0)
            cout << "You don't have pipes and compressor stations" << endl;
        else {
            for (int i = 0; i < count_pipes; i++) {
                Pipe p1;
                Pipe::max_id_pipe = 0;
                p1 = Load_pipe(fin, p1);
                pipes.insert({ p1.get_id_p(), p1 });
                if (Pipe::max_id_pipe < p1.get_id_p()) {
                    Pipe::max_id_pipe = p1.get_id_p();
                }
            }
            Pipe::max_id_pipe++;
            for (int i = 0; i < count_stations; i++) {
                CS cs1;
                CS::max_id_cs = 0;
                cs1 = Load_station(fin, cs1);
                stations.insert({ cs1.get_id_c(), cs1 });
                if (CS::max_id_cs < cs1.get_id_c()) {
                    CS::max_id_cs = cs1.get_id_c();
                }
            }
            CS::max_id_cs++;
        }
        cout << "Finished loading from file" << endl;
        fin.close();
    }
    else
        cout << ("Wasn't found the file with name " + filename + " to save") << endl;
}

int GTN::Add_newpipe_connect(unordered_map <int, Pipe>& pipes, int diameter) {
    Pipe p;
    cin >> p;
    if (!(p.diameter == diameter))
    {
        p.diameter = diameter;
        cout << "\nYour diameter has been changed to the previously entered one: " << diameter << endl;
    }
    int new_pipe_id = p.get_id_p();
    pipes.insert({ new_pipe_id, p });
    return new_pipe_id;
}

void GTN::Connect_cs_and_pipes(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, vector<vector<Connection>>& graph) {
    int id_in, id_out, diameter;
    cout << "Enter the id of the input cs: ";
    id_in = GetCorrectData(0, CS::max_id_cs);
    if (stations.find(id_in) == stations.end()) {
        cout << "Wasn't found cs with " + to_string(id_in) + " id. Close connection" << endl;
        return;
    }

    int max_id = id_in;
    if (max_id >= graph.size()) {
        graph.resize(max_id + 1);
    }

    int total_connections = 0;
    for (const auto& connection : graph) {
        for (const auto& conn : connection) {
            if ((conn.input_station == id_in) or (conn.output_station == id_in)){
                total_connections++;
            }
        }
    }
    if (total_connections >= 2) {
        cout << "Input cs already has the maximum number of connections (2). Close connection" << endl;
        return;
    }

    cout << "Enter the id of the output cs: ";
    id_out = GetCorrectData(0, CS::max_id_cs);
    if (stations.find(id_out) == stations.end()) {
        cout << "Wasn't found cs with " + to_string(id_out) + " id. Close connection" << endl;
        return;
    }

    max_id = max(id_in, id_out);
    if (max_id >= graph.size()) {
        graph.resize(max_id + 1);
    }

    total_connections = 0;
    for (const auto& connection : graph) {
        for (const auto& conn : connection) {
            if ((conn.input_station == id_out) or (conn.output_station == id_out)) {
                total_connections++;
            }
        }
    }
    if (total_connections >= 2) {
        cout << "Output cs already has the maximum number of connections (2). Close connection" << endl;
        return;
    }

    cout << "Enter the diameter of the pipe: ";
    diameter = GetCorrectData(500, 1400);
    while (!(diameter == 500 || diameter == 700 || diameter == 1000 || diameter == 1400)) {
        cout << "The diameter can only be 500, 700, 1000 or 1400\nEnter diameter of the pipe: ";
        diameter = GetCorrectData(500, 1400);
    }

    int available_pipe_id = -1;
    for (const auto& pipe_entry : pipes) {
        const Pipe& p = pipe_entry.second;
        if (!p.repair && p.diameter == diameter) {
            bool is_pipe_connected = false;
            for (const auto& connection : graph) {
                for (const auto& conn : connection) {
                    if (conn.pipe == pipe_entry.first) {
                        is_pipe_connected = true;
                        break;
                    }
                }
                if (is_pipe_connected)
                    break;
            }
            if (!is_pipe_connected) {
                available_pipe_id = pipe_entry.first;
                break;
            }
        }
    }

    if (available_pipe_id == -1) {
        cout << "No available pipe found. Adding a new pipe" << endl;
        available_pipe_id = Add_newpipe_connect(pipes, diameter);
        cout << "Created a new pipe with id " << available_pipe_id << " and diameter " << diameter << endl;
    }

    if (pipes[available_pipe_id].repair) {
        cout << "Error: The selected pipe is under repair. Close connection" << endl;
        return;
    }

    Connection newConnection = { id_in, available_pipe_id, id_out };
    graph[id_in].push_back(newConnection);
    cout << "\nSuccessfully connected compressor stations " << id_in << " and " << id_out << " with pipe " << available_pipe_id << endl;

    cout << "Graph (Compressor station -> Pipe -> Compressor station):" << endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << " : ";
        for (const auto& connection : graph[i]) {
            cout << "(" << connection.input_station << ", " << connection.pipe << ", " << connection.output_station << ") ";
        }
        cout << endl;
    }
}

void GTN::Remove_vertex(int vertex, vector<vector<Connection>>& graph) {
    for (auto& connections : graph) {
        connections.erase(
            remove_if(connections.begin(), connections.end(), [vertex](const Connection& conn) {
                return conn.input_station == vertex || conn.output_station == vertex;
                }),
            connections.end()
        );
    }

    cout << "Vertex " << vertex << " and its connections removed successfully." << endl;
    cout << "Graph (Compressor station -> Pipe -> Compressor station):" << endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << " : ";
        for (const auto& connection : graph[i]) {
            cout << "(" << connection.input_station << ", " << connection.pipe << ", " << connection.output_station << ") ";
        }
        cout << endl;
    }
}

void GTN::Remove_edge_and_unused_vertices(int id_pipe, vector<vector<Connection>>& graph) {
    for (auto& connections : graph) {
        connections.erase(remove_if(connections.begin(), connections.end(), [id_pipe](const Connection& conn) 
            {return conn.pipe == id_pipe;}),connections.end());
    }

    cout << "Pipe " << id_pipe << " and its connections removed successfully." << endl;
    cout << "Graph (Compressor station -> Pipe -> Compressor station):" << endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << " : ";
        for (const auto& connection : graph[i]) {
            cout << "(" << connection.input_station << ", " << connection.pipe << ", " << connection.output_station << ") ";
        }
        cout << endl;
    }
}

void GTN::Remove_connection(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, vector<vector<Connection>>& graph) {
    int id_in, id_out, id_pipe;
    bool connection_found = false;

    cout << "\nEnter id of the input cs: ";
    id_in = GetCorrectData(0, CS::max_id_cs);
    if (stations.find(id_in) == stations.end()) {
        cout << "Input cs wasn't found. Close connection" << endl;
        return;
    }

    cout << "Enter id of the pipe: ";
    id_pipe = GetCorrectData(0, Pipe::max_id_pipe);
    if (pipes.find(id_pipe) == pipes.end()) {
        cout << "The pipe wasn't found. Close connection" << endl;
        return;
    }

    cout << "Enter id of the output cs: ";
    id_out = GetCorrectData(0, CS::max_id_cs);
    if (stations.find(id_in) == stations.end()) {
        cout << "Output cs wasn't found. Close connection" << endl;
        return;
    }

    for (const auto& connections : graph) {
        for (const Connection& conn : connections) {
            if (conn.input_station == id_in && conn.output_station == id_out && conn.pipe == id_pipe) {
                connection_found = true;
                break;
            }
        }
        if (connection_found) {
            break;
        }
    }

    if (connection_found) {
        for (auto& connections : graph) {
            connections.erase(
                remove_if(connections.begin(), connections.end(), [id_in, id_out, id_pipe](const Connection& conn) {
                    return conn.input_station == id_in && conn.output_station == id_out && conn.pipe == id_pipe;
                    }), connections.end());
        }

        cout << "Connection with input cs id " + to_string(id_in) + ", pipe's id " + to_string(id_pipe) + " and output cs id " + to_string(id_out) + " has been successfully deleted" << endl;

        cout << "Update graph (Compressor station -> Pipe -> Compressor station):" << endl;
        for (int i = 0; i < graph.size(); ++i) {
            cout << i << " : ";
            for (const auto& connection : graph[i]) {
                cout << "(" << connection.input_station << ", " << connection.pipe << ", " << connection.output_station << ") ";
            }
            cout << endl;
        }
    }
    else {
        cout << "The connection wasn't found in the graph" << endl;
    }
}

static bool DFS(int v, const vector<vector<Connection>>& graph, vector<bool>& visited, vector<int>& result, unordered_set<int>& currentPath) {
    visited[v] = true;
    currentPath.insert(v);
    for (const Connection& conn : graph[v]) {
        if (currentPath.find(conn.output_station) != currentPath.end()) {
            cout << "Graph has a cycle." << endl;
            return false;  // Граф содержит цикл
        }
        if (!visited[conn.output_station]) {
            if (!DFS(conn.output_station, graph, visited, result, currentPath)) {
                return false;
            }
        }
    }
    currentPath.erase(v);
    result.push_back(v);
    return true;
}

void GTN::Topological_sort(vector<vector<Connection>>& graph)
{
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);
    vector<int> result;  // Store the topological order here
    unordered_set<int> currentPath;

    for (int i = numVertices - 1; i >= 0; --i) {
        if (!visited[i]) {
            if (!DFS(i, graph, visited, result, currentPath)) {
                return;
            }
        }
    }

    vector<int> stations;
    for (int i = 0; i < graph.size(); i++) {
        for (auto& connections : graph[i]) {
            int firstElement = connections.input_station;
            int thirdElement = connections.output_station;
            if (find(stations.begin(), stations.end(), firstElement) == stations.end())
                stations.push_back(firstElement);
            if (find(stations.begin(), stations.end(), thirdElement) == stations.end())
                stations.push_back(thirdElement);
        }
    }

    result.erase(
        remove_if(result.begin(), result.end(), [&](int station) {
            return find(stations.begin(), stations.end(), station) == stations.end();
            }),
        result.end()
    );

    // Выводим результат топологической сортировки
    cout << "Topological order: ";
    for (int i = result.size() - 1; i >= 0; --i) {
        cout << result[i] << " ";
    }
    cout << endl;
}

void GTN::Dijkstra(unordered_map <int, Pipe>& pipes, unordered_map<int, CS>& stations, const vector<vector<Connection>>& graph) {
    Pipe p;
    int n = graph.size();
    int start, end;
    cout << "Enter the start vertex id: ";
    cin >> start;
    if (stations.find(start) == stations.end()) {
        cout << "Input cs wasn't found. Close connection." << endl;
        return;
    }
    cout << "Enter the end vertex id: ";
    cin >> end;
    if (stations.find(end) == stations.end()) {
        cout << "Output cs wasn't found. Close connection." << endl;
        return;
    }
    vector<double> distance(n, INT_MAX); // Исходные расстояния устанавливаются в бесконечность
    distance[start] = 0; // Расстояние от начальной вершины до самой себя равно 0

    // Создаем приоритетную очередь для хранения вершин и их расстояний
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Обходим все соседние вершины текущей вершины
        for (const auto& connection : graph[u]) {
            int v = connection.output_station;
            double weight = 0;
            for (const auto& p : pipes) {
                if (p.second.id_pipe == connection.pipe)
                    weight = p.second.length;
            }
            // Если нашли более короткий путь до вершины v, обновляем расстояние
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({ distance[v], v });
            }
        }
    }

    // Вывод расстояния между заданными вершинами
    if (distance[end] != INT_MAX)
        cout << "The shortest distance from vertex " << start << " to vertex " << end << ": " << distance[end] << endl;
    else
        cout << "Maybe you want to find the shortest distance from " << end << " to " << start << "?" << endl;
}

static double Calculate_capacity(const Pipe& pipe) {
    if (pipe.repair) {
        return 0.0;
    }
    else {
        return 0.01 * sqrt(pow(pipe.diameter, 5) / pipe.length);
    }
}

void GTN::Find_and_print_capacities(unordered_map<int, Pipe>& pipe, vector<vector<Connection>>& graph) {
    cout << "Capacities for each Pipe:" << endl;

    for (const auto& connections : graph) {
        for (const auto& connection : connections) {
            int pipe_id = connection.pipe;
            double pipe_capacity = Calculate_capacity(pipe[pipe_id]);

            cout << "Pipe " << pipe_id << ": Capacity = " << pipe_capacity << endl;
        }
    }
}

void GTN::Max_flow(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, vector<vector<Connection>>& graph)
{
    int start, end;
    cout << "Enter the start vertex id: ";
    cin >> start;
    if (stations.find(start) == stations.end()) {
        cout << "Input cs wasn't found. Close connection." << endl;
        return;
    }
    cout << "Enter the end vertex id: ";
    cin >> end;
    if (stations.find(end) == stations.end()) {
        cout << "Output cs wasn't found. Close connection." << endl;
        return;
    }

    vector<vector<double>> residual(graph.size(), vector<double>(graph.size(), 0.0));

    for (int i = 0; i < graph.size(); ++i) {
        for (const auto& connection : graph[i]) {
            residual[i][connection.output_station] = Calculate_capacity(pipes[connection.pipe]);
        }
    }

    double max_flow = 0.0;

    while (true) {
        vector<int> parent(graph.size(), -1);
        queue<pair<int, double>> q;
        q.push({ start, INT_MAX });

        while (!q.empty()) {
            int current = q.front().first;
            double capacity = q.front().second;
            q.pop();

            for (const auto& connection : graph[current]) {
                int next = connection.output_station;
                double residual_capacity = residual[current][next];

                if (parent[next] == -1 && residual_capacity > 0) {
                    parent[next] = current;
                    double min_capacity = min(capacity, residual_capacity);
                    q.push({ next, min_capacity });

                    if (next == end) {
                        max_flow += min_capacity;

                        int u = next;
                        while (u != start) {
                            int v = parent[u];
                            residual[v][u] -= min_capacity;
                            residual[u][v] += min_capacity;
                            u = v;
                        }

                        break;
                    }
                }
            }
        }

        if (parent[end] == -1) {
            break;
        }
    }

    cout << "Max flow from vertex " << start << " to vertex " << end << ": "<< max_flow << endl;
}

void GTN::Operations_with_graph(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, vector<vector<Connection>>& graph) {
    while (true) {
        cout << "\nSelect actions:" << endl;
        cout << "1. Delete connection" << endl;
        cout << "2. Topological sort" << endl;
        cout << "3. The shortest length" << endl;
        cout << "4. Maximum flow" << endl;
        cout << "5. Exit" << endl;
        cout << "Select: ";
        int choice = GetCorrectData(1, 5);
        switch (choice) {
            case 1:
                Remove_connection(pipes, stations, graph);
                break;
            case 2:
                Topological_sort(graph);
                break;
            case 3:
                Dijkstra(pipes, stations, graph);
                break;
            case 4:
                Find_and_print_capacities(pipes, graph);
                Max_flow(pipes, stations, graph);
                break;
            case 5:
                return;
        }
    }
}

