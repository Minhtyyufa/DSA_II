//
// Created by minht on 11/9/2019.
//

#include <iostream>
#include <chrono>
#include "../headers/graph.h"
#include <string>
#include <math.h>
using namespace std;
int main()
{
    graph my_graph;
    string graph_file, start_vertex, output_file;
    cout << "Enter name of graph file: ";
    cin >> graph_file;
    my_graph.input_proc(graph_file);
    heap min_heap(my_graph.get_num_nodes());

    start_vertex = my_graph.is_valid_start();

    auto dijk_start = chrono::steady_clock::now();
    my_graph.move_to_known(min_heap, start_vertex);
    auto dijk_end = chrono::steady_clock::now();

    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " <<chrono::duration_cast<chrono::microseconds>(dijk_end-dijk_start).count()/pow(10,6)<<endl;

    cout << "Enter name of output file: ";
    cin >> output_file;

    my_graph.print_graph(output_file);

    return 0;

}
