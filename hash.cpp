//
// Created by minht on 9/12/2019.
//

#include "hash.h"
#include <iostream>
#include <exception>

hash_table::hash_table(int size)
{
    unsigned int new_size = get_prime(size);
    capacity = new_size;
    filled = 0;
    data.resize(new_size);

}

int hash_table::insert(const std::string &key, void *pv) {


    filled ++;
    if(filled > capacity/2) {
        if (!rehash())
            return 2;
    }

    while(1) {
        int index = hash(key);
        int rel_index = index;
        for (int offset = 0; offset < capacity / 4; offset++) {
            if (data[rel_index].isOccupied && !data[rel_index].isDeleted && data[rel_index].key == key)
                return 1;
            else if (!data[rel_index].isOccupied || (data[rel_index].isOccupied && data[rel_index].isDeleted)) {
                data[rel_index].key = key;
                data[rel_index].isOccupied = true;
                data[rel_index].isDeleted = false;
                data[rel_index].pv = pv;
                return 0;
            } else
                rel_index = (index + offset) % capacity;
        }
        if(!rehash())
            return 2;
    }



}

bool hash_table::contains(const std::string &key) {
    return (find_pos(key) != -1);
}

int hash_table::hash(const std::string &key)
{
    unsigned int hash_val = 0;

    for(char c: key) {
        hash_val = hash_val * 37 + c;
    }

    return hash_val % capacity;
}

unsigned int hash_table::get_prime(int size)
{
    unsigned int primes[26] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157,
                               98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
                               100663319, 201326611, 402653189, 805306457 ,1610612741};
    for(unsigned int prime: primes)
    {
        if (prime > (unsigned int)size)
            return prime;
    }
    return primes[25];
}

int hash_table::find_pos(const std::string &key)
{
    int index = hash(key);
    while(1)
    {
        if(data[index].isOccupied && !data[index].isDeleted &&
           data[index].key == key)
            return index;
        else if(!data[index].isOccupied)
            return -1;
        else
            index = (index + 1) % capacity;
    }
}

bool hash_table::remove(const std::string &key)
{
    int index = find_pos(key);
    if(index == -1)
        return false;
    else{
        data[index].isDeleted = true;
        return true;
    }
}

bool hash_table::rehash()
{
    int new_cap = get_prime(capacity);
    if(capacity == new_cap)
        return false;
    else {
        std::vector<hash_item> temp;
        try {
            temp.resize(new_cap);
        }
        catch(std::exception& e)
        {
            std::cout<<"Error: "<< e.what() << std::endl;
            return false;
        }
        std::vector<hash_item> test;
        capacity = new_cap;
        for(auto i : data)
        {
            if(i.isOccupied && !i.isDeleted)
            {
                unsigned int hash_index = hash(i.key);
                while(temp[hash_index].isOccupied)
                    hash_index = (hash_index + 1) % capacity;
                temp[hash_index] = i;
            }
        }

        data = temp;
        return true;
    }
}
void *hash_table::get_pointer(const std::string &key, bool *b)
{
    int index = find_pos(key);
    if(index == -1)
    {
        *b = false;
        return nullptr;
    } else
        return data[index].pv;
}

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hash_table::set_pointer(const std::string &key, void *pv)
{
    int index = find_pos(key);
    if(index == -1)
        return 1;
    else
    {
        data[index].pv = pv;
        return 0;
    }

}

int hash_table::get_filled() {
    return filled;
}


