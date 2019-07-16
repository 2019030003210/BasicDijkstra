#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include "Dijkstra.h"
#include "BiDir-Dijkstra.h"
void generate_queries(char* output_file_name,
    NodeID n,
    int query_nums = 1000)
{
    srand((unsigned)time(NULL));
    ofstream out_file(output_file_name);
    for (int i = 0; i < query_nums; i++)
    {
        NodeID source, target;
        source = rand() % n;
        do
        {
            target = rand() % n;
        }
        while (source == target);
        out_file << source << ' ' << target << endl;
    }
    out_file.close();
}

void load_queries(char* query_file_name, vector<pair<NodeID, NodeID> >& queries)
{
    ifstream in_file(query_file_name);
    if (!in_file)
    {
        cerr << "error! " << query_file_name << "does not exist!" << endl;
        exit(1);
    }
    queries.clear();
    NodeID source, target;
    while (in_file >> source >> target)
    {
        queries.push_back(make_pair(source, target));
    }
    in_file.close();
}

void write_result(char* out_file_name, vector<Weight>& results)
{
    ofstream out_file(out_file_name);
    for (auto&& itr = results.begin(); itr != results.end(); itr++)
    {
        out_file << (*itr) << endl;
    }
    out_file.close();
}

int main(int argc, char** argv)
{
    char dataset[100] = "ny";
    
    if (argc > 1)
    {
        strcpy(dataset, argv[1]);
    }
    
    char graph_file_name[100];
    sprintf(graph_file_name, "%s.gr", dataset);
    char query_file_name[100];
    sprintf(query_file_name, "%s.query", dataset);
    char result_file_name[100];
    sprintf(result_file_name, "%s.result", dataset);
    char bidir_result_file_name[100];
    sprintf(bidir_result_file_name, "%s.bidir.result", dataset);

    Graph g;
    g.read_from_file(graph_file_name);

    bool gen_queries = false;
    if (argc == 3 && strcmp(argv[2], "-q") == 0) gen_queries = true;
    if (gen_queries)
    {
        generate_queries(query_file_name, g.node_num());
        return 0;
    }

    // read queries
    vector<pair<NodeID, NodeID> > queries;
    load_queries(query_file_name, queries);
    
    Dijkstra dijkstra(&g,1);
    vector<Weight> results;
    time_t start_time = clock();
    for (auto&& itr = queries.begin(); itr != queries.end(); itr++)
    {
        results.push_back(dijkstra.get_dist(itr->first, itr->second));
    }
    time_t end_time = clock();
    cout << "Dijkstra's algorithm costs "
        << (end_time - start_time) * 1.0 / CLOCKS_PER_SEC
        << "seconds" << endl;
    write_result(result_file_name, results);

    BidirDijkstra bidijkstra(&g);
    results.clear();
    start_time = clock();
    for (auto&& itr = queries.begin(); itr != queries.end(); itr++)
    {
        results.push_back(bidijkstra.get_dist(itr->first, itr->second));
    }
    end_time = clock();
    cout << "Bidir-Dijkstra's algorithm costs "
        << (end_time - start_time) * 1.0 / CLOCKS_PER_SEC
        << "seconds" << endl;
    write_result(bidir_result_file_name, results);
    getchar();
    return 0;
}