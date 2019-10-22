//
// Created by minht on 10/9/2019.
//

#include "../headers/heap.h"
#include <limits.h>
#include <iostream>


// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
//
heap::heap(int cap):mapping(cap*2){
    data.resize(cap+1);
    capacity = cap;
    filled = 0;
}
void heap::percolate_down(int pos_cur) {
    int child;

    node copy = std::move(data[pos_cur]);
    for(; pos_cur * 2<= filled; pos_cur = child)
    {
        child = pos_cur * 2;
        if(child != filled && data[child+1].key < data[child].key)
            ++child;
        if(data[child].key < copy.key) {

            data[pos_cur] = std::move(data[child]);
            mapping.set_pointer(data[pos_cur].id, &data[pos_cur]);
        }
        else
            break;
    }

    data[pos_cur] = std::move(copy);
    mapping.set_pointer(data[pos_cur].id, &data[pos_cur]);
}

void heap::percolate_up(int pos_cur)
{
    node tb_inserted = data[pos_cur];
    node copy = data[pos_cur];
    data[0] = std::move(copy);
    for(; tb_inserted.key < data[pos_cur/2].key; pos_cur/=2 ) {
        data[pos_cur] = std::move(data[pos_cur / 2]);
        //mapping.set_pointer(data[pos_cur].id, &data[pos_cur/2]);
//        mapping.set_pointer(data[pos_cur].id, &data[pos_cur/2]);
        mapping.set_pointer(data[pos_cur].id, &data[pos_cur]);
    }
    data[pos_cur] = std::move(data[0]);
    mapping.set_pointer(data[pos_cur].id, &data[pos_cur]);
}

//
// insert - Inserts a new node into the binary heap
//
// Inserts a node with the specified id string, key,
// and optionally a pointer.  They key is used to
// determine the final position of the new node.
//
// Returns:
//   0 on success
//   1 if the heap is already filled to capacity
//   2 if a node with the given id already exists (but the heap
//     is not filled to capacity)
//
int heap::insert(const std::string &id, int key, void *pv)
{
    if(filled >= capacity)
        return 1;
    else if(mapping.contains(id))
        return 2;
    else {
        int cur_pos = ++filled;
        data[cur_pos].id = id;
        data[cur_pos].key = key;
        if (pv != nullptr)
            data[cur_pos].p_data = pv;
        mapping.insert(id, &data[cur_pos]);

        percolate_up(cur_pos);
        return 0;
    }
}



//
// setKey - set the key of the specified node to the specified value
//
// I have decided that the class should provide this member function
// instead of two separate increaseKey and decreaseKey functions.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
//
int heap::setKey(const std::string &id, int key)
{
    bool b;
    node *pn = static_cast<node *> (mapping.get_pointer(id, &b));
    if(!b)
        return 1;
    else
    {
        if(key > pn->key)
        {
            int cur_pos = get_pos(pn);
            pn->key = key;
            percolate_down(cur_pos);
        }
        else if(key < pn->key)
        {
            int cur_pos = get_pos(pn);
            pn->key = key;
            percolate_up(cur_pos);
        }
        return 0;
    }
}

//
// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary heap
//
// If pId is supplied (i.e., it is not nullptr), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the heap is empty
//
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (filled == 0)
        return 1;
    else
    {
        if(pId != nullptr)
            *pId = data[1].id;
        if(pKey != nullptr)
            *pKey = data[1].key;
        if(ppData != nullptr)
            *(static_cast<void **>(ppData)) = data[1].p_data;

        mapping.remove(data[1].id);
        data[1] = std::move(data[filled--]);
        percolate_down(1);
        return 0;
    }
}

//
// remove - delete the node with the specified id from the binary heap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
//
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    bool b;

    node *pn = static_cast<node *> (mapping.get_pointer(id, &b));
    if(!b)
        return 1;
    else
    {
        int cur_pos = get_pos(pn);
        if(pKey != nullptr)
            *pKey = data[cur_pos].key;
        if(ppData != nullptr)
            *(static_cast<void **> (ppData)) = data[cur_pos].p_data;

        /*
        mapping.remove(id);
        data[cur_pos] = std::move(data[filled--]);
        percolate_down(cur_pos);
         */
        setKey(id, INT_MIN);
        deleteMin();
        return 0;
    }
}

int heap::get_pos(heap::node *pn) {
    return (int)(pn - &data[0]);
}