#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <time.h>


using namespace std;
int main() {
    string invalid_characters;
    for(unsigned char c = 32; (int)c > 0; c++)
    {
        if(c == '0')
            c = 57;
        else if(c == 'A')
            c = 90;
        else if(c == 'a')
            c = 122;
        else if((int) c == 39)
            continue;
        else if(c == '-' )
            continue;
        else
            invalid_characters += c;
    }

    hash_table dictionary =  hash_table(100000);

    string dict_name;
    cout<<"Enter name of dictionary: ";
    cin >> dict_name;
    ifstream dict_file(dict_name);


    string line;
    time_t dict_start, dict_end;
    time(&dict_start);
    while(getline(dict_file, line))
    {
        transform(line.begin(),line.end(),line.begin(),::tolower);
        dictionary.insert(line);

    }
    time(&dict_end);
    printf("Total time (in seconds) to load dictionary: %.3f\n", difftime(dict_start,dict_end));



    string sc_name, out_name;

    cout <<"Enter name of input file: ";
    cin>> sc_name;
    cout << "Enter name of output file: ";
    cin >> out_name;

    ifstream sc_file(sc_name);
    ofstream out_file(out_name);
    char* words;

    time_t doc_start, doc_end;

    time(&doc_start);
    for(int line_number = 1; getline(sc_file,line); line_number++)
    {
        transform(line.begin(), line.end(), line.begin(),::tolower);
        words = strtok(&line[0],&invalid_characters[0]);
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
    time(&doc_end);
    printf("Total time (in seconds) to check document: %.3f\n", difftime(doc_end, doc_start));

    return 0;


}