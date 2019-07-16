#pragma once
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

typedef unsigned int NodeID;
typedef unsigned int Weight;

const Weight MAXIMUMVALUE = 0xFFFFFFFF;

struct Arc
{
    NodeID adj_vertex;
    Weight weight;
public:
    Arc(){}
    Arc(NodeID adj_v, Weight w):
        adj_vertex(adj_v),
        weight(w)
    {}
};
class Graph
{
public:
    bool read_from_file(char* file_name)
    {
        ifstream in_file(file_name);
        if (!in_file)
        {
            cerr << "error! " << file_name << "does not exist";
            return false;
        }
        in_file >> n >> m;
        NodeID source, target;
        Weight weight;
        arcs[0].resize(n);
        arcs[1].resize(n);
        char edge_type;
        while(in_file >> edge_type >> source >> target >> weight)
        {
            arcs[0][source].push_back(Arc(target, weight));
            arcs[1][target].push_back(Arc(source, weight));
        }
        cout << "load file complete" << endl;
        return true;
    }
    inline int node_num() { return n; }

    inline vector<Arc>::iterator get_arcs_itr_begin(int dir, NodeID v)
    {
        return arcs[dir][v].begin();
    }

    inline vector<Arc>::iterator get_arcs_itr_end(int dir, NodeID v)
    {
        return arcs[dir][v].end();
    }

private:
    int n; // ¶¥µãÊý
    int m; // ±ßÊý
    vector< vector<Arc> > arcs[2]; // arcs[0]: outgoing arcs;  arcs[1]: incoming_arcs
};