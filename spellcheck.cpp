#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>

using namespace std;

// generate word separators
void generate_invalid_characters(string &invalid_characters)
{
    for(unsigned char c = 32; (int)c > 0; c++)
    {
        if(!(isalpha(c) || isdigit(c) || c == '-' || c == '\''))
            invalid_characters += c;
    }
}

// Inserts the words in the dictionary file into the hash table
void load_dict(hash_table &dictionary)
{
    //Prompt for dictionary file name
    string dict_name, line;
    cout<<"Enter name of dictionary: ";
    cin >> dict_name;
    ifstream dict_file(dict_name);

    // Insert words into the hash table
    auto dict_start = chrono::steady_clock::now();
    while(getline(dict_file, line))
    {
        transform(line.begin(),line.end(),line.begin(),::tolower);
        dictionary.insert(line);
    }
    auto dict_end =chrono::steady_clock::now();
    cout << "Total time (in seconds) to load dictionary: " <<chrono::duration_cast<chrono::microseconds>(dict_end-dict_start).count()/pow(10,6)<<endl;
}

// Checks the words in the input document and prints if they are not found in the dictionary
void check_document(hash_table &dictionary)
{
    string sc_name, out_name, line, invalid_characters;
    generate_invalid_characters(invalid_characters);

    // Prompt for input and output file names
    cout <<"Enter name of input file: ";
    cin>> sc_name;
    cout << "Enter name of output file: ";
    cin >> out_name;

    ifstream sc_file(sc_name);
    ofstream out_file(out_name);
    char* words;

    // Check if words are in the dictionary and word length
    auto doc_start = chrono::steady_clock::now();
    for(int line_number = 1; getline(sc_file,line); line_number++)
    {
        transform(line.begin(), line.end(), line.begin(),::tolower);
        words = strtok(&line[0], &invalid_characters[0]);
        while(words != NULL) {
            string word = string(words);
            if(word.size()>20) {
                out_file << "Long word at line " << line_number << ", starts: " << word.substr(0, 20) << endl;
            }
            else if(!dictionary.contains(word)) {
                bool contains_numbers = false;
                for(int i = 0; !contains_numbers && i < word.size(); i++)
                {
                    if(word[i]>='0' && word[i] <= '9')
                        contains_numbers = true;
                }
                if(!contains_numbers)
                    out_file << "Unknown word at line " << line_number << ": " << word << endl;
            }
            words = strtok(NULL, &invalid_characters[0]);
        }

    }
    auto doc_end = chrono::steady_clock::now();
    cout << "Total time (in seconds) to load dictionary: " <<chrono::duration_cast<chrono::microseconds>(doc_end-doc_start).count()/pow(10,6)<<endl;
}

int main() {
    hash_table dictionary =  hash_table();
    load_dict(dictionary);
    check_document(dictionary);
    return 0;
}