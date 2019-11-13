//
// Created by minht on 11/9/2019.
//

#ifndef PROGRAM_2_GRAPH_H
#define PROGRAM_2_GRAPH_H

#include <string>
#include <list>
#include "hash.h"
#include "heap.h"

class graph {
    class node{
    public:
        std::string name;
        node* prev_node = nullptr;
        bool is_source = false;
        int path_cost = INT32_MAX;
        std::list<std::pair<std::string, int>> adj_list;
        explicit node(std::string name);
    };
public:
    std::list<node *> node_list;
    hash_table node_hash;
    graph();
    void insert_edge(std::string source,std::string dest, int cost);
    void update_heap(std::string source, heap &min_heap);
    void move_to_known(heap &min_heap, std::string source);
    void input_proc(std::string input_file);
    int get_num_nodes();
    void print_graph(std::string out_file_name);
    std::string is_valid_start();
};
#endif //PROGRAM_2_GRAPH_H
