// Written by Paul Baxter

#include <iostream>
#include <iomanip>
#include <vector>

#include "board.h"

int parse_args(int argc, char* args[]);
void Useage();

// default rows and cols
int Rows = 5;
int Cols = 5;
std::vector<std::string> Words;
std::string Title = "Puzzle";

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
    board b(Rows, Cols);
    b.set_title(Title);
    if (!b.add_words(Words))
    {
        std::cout << "Words do not fit it puzzle. Try adding rows or columns." << std::endl;
        Useage();
        return -1;
    }

    // fill empty spaces
    b.fill();

    // print the board
    b.print();
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
    auto title_specified = false;

    // set current argument to 1
    auto curarg = 1;

    // loop through aruments
    while (curarg < argc)
    {
        // -r rows
        if (_strcmpi(args[curarg], "-r") == 0)
        {
            if (rows_specified)
            {
                std::cout << "Number of rows specified more than once." << std::endl;
                Useage();
                return -1;
            }
            rows_specified = true;
            ++curarg;
            if (curarg >= argc)
            {
                std::cout << "Missing row count for -r." << std::endl;
                Useage();
                return -1;
            }
            Rows = atoi(args[curarg]);
            ++curarg;
            if (Rows <= 0)
            {
                std::cout << "Invalid rows count for -r." << std::endl;
                Useage();
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
                Useage();
                return -1;
            }
            cols_specified = true;
            ++curarg;
            if (curarg >= argc)
            {
                std::cout << "Missing column count for -c." << std::endl;
                Useage();
                return -1;
            }
            Cols = atoi(args[curarg]);
            ++curarg;
            if (Cols <= 0)
            {
                std::cout << "Invalid column count for -c." << std::endl;
                Useage();
                return -1;
            }
            continue;
        }

        // -t title
        if (_strcmpi(args[curarg], "-t") == 0)
        {
            if (title_specified)
            {
                std::cout << "Title specified more than once." << std::endl;
                Useage();
                return -1;
            }
            title_specified = true;
            ++curarg;
            if (curarg >= argc)
            {
                std::cout << "Title missing for -t." << std::endl;
                Useage();
                return -1;
            }

            Title = args[curarg];
            ++curarg;
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
        std::cout << "No words specified for puzzle." << std::endl;
        Useage();
        return -1;
    }

    return 0;
}

void Useage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "Wordsearch [-r rows] [-c cols] [-t title] word1 word2 word3 ..." << std::endl;
}
