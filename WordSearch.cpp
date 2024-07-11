// WordSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Written by Paul Baxter

#include <iostream>
#include <iomanip>

#include <vector>
#include "board.h"

int main(int argc, char* args[])
{
    // default rows and cols
    int rows = 5;
    int cols = 5;
    // vector to hold words
    std::vector<std::string> words;

    // for command line validation
    bool rows_specified = false;
    bool cols_specified = false;

    // set current argument to 1
    auto curarg = 1;
    while (curarg < argc)
    {
        // -r rows
        if (_strcmpi(args[curarg], "-r") == 0)
        {
            if (rows_specified)
            {
                std::cout << "Number of rows specified more than once." << std::endl;
                return -1;
            }
            rows_specified = true;
            ++curarg;
            if (curarg >= argc)
            {
                std::cout << "Missing row count for -r." << std::endl;
                return -1;
            }
            rows = atoi(args[curarg]);
            ++curarg;
            if (rows <= 0)
            {
                std::cout << "Invalid rows count for -r." << std::endl;
                return -1;
            }
            continue;
        }

        // -c columns
        if (_strcmpi(args[curarg], "-c") == 0)
        {
            if (cols_specified)
            {
                std::cout << "Number of columns specified more than once." << std::endl;
                return -1;
            }
            cols_specified = true;
            ++curarg;
            if (curarg >= argc)
            {
                std::cout << "Missing column count for -c." << std::endl;
                return -1;
            }
            cols = atoi(args[curarg]);
            ++curarg;
            if (cols <= 0)
            {
                std::cout << "Invalid column count for -c." << std::endl;
                return -1;
            }
            continue;
        }

        // this must be a word
        std::string temp;
        temp.clear();
        for (auto i = 0; args[curarg][i] != 0; ++i)
            temp += args[curarg][i];

        words.push_back(temp);
        ++curarg;
    }

    // make sure we have at lease one word
    if (words.size() == 0)
    {
        std::cout << "No words specified for puzzle" << std::endl;
        std::cout << "Usage:" << std::endl;

        std::cout << args[0] << " [-r rows] [-c cols] word1 word2 word3 ..." << std::endl;
        return -1;
    }
    std::cout << std::endl;
    
    // create a new board
    auto b = new board(rows, cols);
    // add words one at a time
    for (auto& word : words)
    {
        if (!b->add_word(word))
        {
            std::cout << "Word " << word << " does not fit." << std::endl;
            return -1;
        }
    }

    // fill empty spaces
    b->fill();

    // print board
    for (auto &r : b->field)
    {
        for (auto& c : r)
        {
            std::cout << ' ' << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //  print the words
    int count = 0;
    for (auto& word : words)
    {
        if (count == 5)
        {
            std::cout << std::endl;
            count = 0;
        }
        count++;
        std::cout << std::setw(10) << word;
    }
    std::cout << std::endl;
    return 0;
}
