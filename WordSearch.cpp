// WordSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Written by Paul Baxter

#include <iostream>
#include <iomanip>
#include <vector>

#include "board.h"

int parse_args(int argc, char* args[]);
void print(board* b);

// default rows and cols
int Rows = 5;
int Cols = 5;
std::vector<std::string> Words;

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">argument count</param>
/// <param name="args">arguments</param>
/// <returns>0 on success</returns>
int main(int argc, char* args[])
{
    // parse the arguments
    if (parse_args(argc, args) != 0)
        return -1;
    
    // create a new board
    auto b = new board(Rows, Cols);
    if (!b->add_words(Words))
    {
        std::cout << "Words do not fit it puzzle. Try adding rows or columns." << std::endl;
        return -1;
    }

    // fill empty spaces
    b->fill();

    // print the board
    print(b);
    return 0;
}

/// <summary>
/// parse the arguments
/// </summary>
/// <param name="argc">argument count</param>
/// <param name="args">arguments</param>
/// <returns>0 on success</returns>
int parse_args(int argc, char* args[])
{
    auto rows_specified = false;
    auto cols_specified = false;

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
            Rows = atoi(args[curarg]);
            ++curarg;
            if (Rows <= 0)
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
            Cols = atoi(args[curarg]);
            ++curarg;
            if (Cols <= 0)
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

        Words.push_back(temp);
        ++curarg;
    }

    // make sure we have at lease one word
    if (Words.size() == 0)
    {
        std::cout << "No words specified for puzzle" << std::endl;
        std::cout << "Usage:" << std::endl;

        std::cout << args[0] << " [-r rows] [-c cols] word1 word2 word3 ..." << std::endl;
        return -1;
    }

    return 0;
}

/// <summary>
/// print the board
/// </summary>
/// <param name="b">board *</param>
void print(board* b)
{
    // print board
    std::cout << std::endl << " Puzzle" << std::endl << std::endl;

    for (auto& r : b->field)
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
    for (auto& word : Words)
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
}
