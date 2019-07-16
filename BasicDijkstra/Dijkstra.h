#pragma once

#include <vector>
#include <memory>
#include "Graph.h"
#include "KeyHeap.h"

template<typename ValueType>
struct MyLess
{
    bool operator ()(const ValueType& v1, const ValueType& v2)
    {
        return v1 < v2;
    }
};

class Dijkstra
{
private:
    Graph* g;
    vector<Weight> dist; // dist[i] = the shortest distance to i
    KeyHeap<NodeID, Weight, MyLess<Weight> > min_heap;
    int dir; // 0..forward search, 1.. backward search
public:
    Dijkstra(Graph* g, int d): g(g), 
        dir(d),
        dist(g->node_num()) 
    {
        min_heap.init(g->node_num());
    }
    
    Weight get_dist(NodeID source, NodeID target)
    {
        memset(dist.data(), 0xFFFFFFFF, sizeof(Weight) * g->node_num());
        min_heap.clear();

        dist[source] = 0;
        min_heap.update(source, 0);
        while (!min_heap.empty())
        {
            NodeID u = min_heap.pop();
            if (u == target)
            {
                break; 
            }
            // visit the outgoing edges of u
            for (auto&& itr = g->get_arcs_itr_begin(dir, u);
                itr != g->get_arcs_itr_end(dir, u);
                itr++)
            {
                NodeID v = itr->adj_vertex; // edge <u,v>
                Weight new_weight = dist[u] + itr->weight;
                if (new_weight < dist[v])
                {
                    dist[v] = new_weight;
                    min_heap.update(v, new_weight);
                }
            }
        }
        return dist[target];
    }
};
