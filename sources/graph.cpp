//
// Created by minht on 11/9/2019.
//
#include "../headers/graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
graph::graph():node_hash(50)
{
}

graph::node::node(std::string name)
{
    this->name = name;
}

//Processing input text file to insert an edge
void graph::insert_edge(std::string source, std::string dest, int cost)
{
    auto node_edge = std::make_pair(dest, cost);
    bool has_node;

    node *this_node= static_cast<node *> (node_hash.get_pointer(source, &has_node));

    if(has_node)
    {
        this_node->adj_list.push_back(node_edge);
    } else
    {
        node *my_node = new node(source);
        my_node->adj_list.push_back(node_edge);
        node_list.push_back(my_node);
        node_hash.insert(source, my_node);
    }

    node_hash.get_pointer(dest, &has_node);
    if(!has_node)
    {
        node *dest_node = new node(dest);
        node_list.push_back(dest_node);
        node_hash.insert(dest, dest_node);
    }
}

//For dijkstras to update the heap after moving a node to the known set.
void graph::update_heap(std::string source, heap &min_heap) {
    bool has_node;
    node *this_node = static_cast<node *>(node_hash.get_pointer(source, &has_node));
    if(has_node)
    {
        for(auto it = this_node->adj_list.begin(); it != this_node->adj_list.end(); ++it)
        {
            //could add error checking here
            node *adj_node = static_cast<node *> (node_hash.get_pointer(it->first, nullptr));
            if(this_node->path_cost + it->second < adj_node->path_cost)
            {
                adj_node->path_cost = this_node->path_cost + it->second;
                adj_node->prev_node = this_node;
                if(min_heap.setKey(adj_node->name, adj_node->path_cost))
                    min_heap.insert(adj_node->name, adj_node->path_cost);
            }
        }
    } else
        std::cout<<"Error could not find the node in the hash table";
}

void graph::move_to_known(heap &min_heap,std::string source)
{
    bool valid_source;
    node *source_node = static_cast<node*> (node_hash.get_pointer(source, &valid_source));

    if(valid_source) {
        source_node->is_source = true;
        source_node->path_cost = 0;
        min_heap.insert(source, source_node->path_cost, &source_node);
        while (min_heap.deleteMin(&source, nullptr, nullptr) != 1)
            update_heap(source, min_heap);
    } else {
        std::cout << "Error: Invalid source_node";

    }
}

void graph::input_proc(std::string input_file){
    std::ifstream input(input_file);

    std::string line;
    std::string word;
    while(getline(input, line))
    {
        std::vector<std::string> words;
        char *word = strtok(&line[0], " ");
        while(word != NULL) {
            words.push_back(std::string(word));
            word = strtok(NULL, " ");
        }
        insert_edge(words[0], words[1], stoi(words[2]));
    }
}

int graph::get_num_nodes()
{
    return node_list.size();
}

void graph::print_graph(std::string out_file_name)
{
    std::ofstream out_file(out_file_name);
    for(auto it = node_list.begin(); it != node_list.end(); ++it)
    {
        out_file << (*it)->name << ": ";
        if((*it)->prev_node == nullptr && !(*it)->is_source)
        {
            out_file << "NO PATH\n";
        } else {
            out_file << (*it)->path_cost << " [";
            std::vector<std::string> path;
            node *trace = *it;
            while (!trace->is_source) {
                path.push_back(trace->name);
                trace = (*trace).prev_node;
            }
            path.push_back(trace->name);
            for (int i = path.size() - 1; i >= 0; i--) {
                out_file << path[i];
                if(i!= 0)
                    out_file <<", ";
            }
            out_file  << "]\n";
        }
    }
}

std::string graph::is_valid_start()
{
    std::string start_vertex;
    std::cout << "Enter a valid vertex id for the starting vertex: ";
    std::cin >> start_vertex;

    while(!node_hash.contains(start_vertex)) {
        std::cout << "Error: Invalid source_node, please pick a valid starting vertex\n";
        std::cout << "Enter a valid vertex id for the starting vertex: ";
        std::cin >> start_vertex;
    }
    return start_vertex;
}
