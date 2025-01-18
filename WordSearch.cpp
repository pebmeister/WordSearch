// Written by Paul Baxter
#pragma warning(disable:6385)

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

#include "board.h"

using namespace std;

class Solution {
public:
    inline string numberToWords(uint64_t num)
    {
        ostringstream strg;
        strg << num;
        auto s = strg.str();
        string out;

        // create groups
        vector<string> groups;
        while (s.length() >= 3) {
            groups.insert(groups.begin(), s.substr(s.length() - 3, 3));
            s.resize(s.length() - 3);
        }
        if (s.length() > 0)
            groups.insert(groups.begin(), s);

        const static string ones[] = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
        const static string teens[] = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
        const static string tens[] = { "",  "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
        const static string groupnames[] = {
            "Hundred", "Thousand", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", "Sextillion",
            "Septillion", "Octillion", "Nonillion", "Decillion", "Undecillion", "Duodecillion",
            "Tredecillion", "Quattuordecillion", "Quindecillion", "Sexdecillion", "Septendecillion",
            "Octodecillion", "Novemdecillion", "Vigintillion" };

        auto group_name_index = (groups.size()) - 1;
        for (auto& group : groups) {
            const auto group_length = static_cast<int>(group.length());
            const string outstart = out.c_str(); // This is an intentional copy
            auto include_ones = true;

            // hundreds 
            if (group_length > 2) {
                const auto hindex = group[0] - '0';
                if (!out.empty() && hindex > 0)
                    out += " ";
                if (hindex > 0)
                    out += ones[hindex] + " " + groupnames[0];
            }

            // tens
            if (group_length > 1) {
                const auto adjust = 3 - group_length;
                const auto tindex = group[1 - adjust] - '0';
                if (tindex != 0) {
                    if (!out.empty())
                        out += " ";

                    if (tindex == 1) {
                        const auto oindex = group[2 - adjust] - '0';
                        out += teens[oindex];
                        include_ones = false;
                    }
                    else {
                        out += tens[tindex];
                    }
                }
            }

            // ones
            if (include_ones) {
                const auto oindex = group[group_length - 1] - '0';
                if (oindex != 0 || out.empty()) {
                    if (!out.empty())
                        out += " ";
                    out += ones[oindex];
                }
            }

            // name of group
            if (!out.empty() && outstart != out && group_name_index != 0) {
                out += " " + groupnames[group_name_index];
            }

            --group_name_index;
        }
        return out;
    }
};

int parse_args(int argc, char* args[]);
void Useage();

// default rows and cols
int Rows = 5;
int Cols = 5;
vector<string> Words;
string Title = "Puzzle";

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">argument count</param>
/// <param name="args">arguments</param>
/// <returns>0 on success</returns>
int main(int argc, char* args[])
{
    auto sol = new Solution();
    auto num = UINT64_MAX;
    auto words = sol->numberToWords(num);
    cout << num << " = " << words.c_str() << endl;

    // parse the arguments
    if (parse_args(argc, args) != 0)
        return -1;

    string error;
    for (auto t = 0; t < 3; t++) {
        try {
            // create a new board
            board b(Rows, Cols, Words, Title);
            b.print();
            return 0;
        }
        catch (const exception& ex) {
            error = ex.what();
        }
    }

    cout << error << endl;
    return -1;
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
    while (curarg < argc) {
        // -r rows
        if (_strcmpi(args[curarg], "-r") == 0) {
            if (rows_specified) {
                cout << "Number of rows specified more than once." << endl;
                Useage();
                return -1;
            }
            rows_specified = true;
            ++curarg;
            if (curarg >= argc) {
                cout << "Missing row count for -r." << endl;
                Useage();
                return -1;
            }
            Rows = atoi(args[curarg]);
            ++curarg;
            if (Rows <= 0) {
                cout << "Invalid rows count for -r." << endl;
                Useage();
                return -1;
            }
            continue;
        }

        // -c columns
        if (_strcmpi(args[curarg], "-c") == 0) {
            if (cols_specified) {
                cout << "Number of columns specified more than once." << endl;
                Useage();
                return -1;
            }
            cols_specified = true;
            ++curarg;
            if (curarg >= argc) {
                cout << "Missing column count for -c." << endl;
                Useage();
                return -1;
            }
            Cols = atoi(args[curarg]);
            ++curarg;
            if (Cols <= 0) {
                cout << "Invalid column count for -c." << endl;
                Useage();
                return -1;
            }
            continue;
        }

        // -t title
        if (_strcmpi(args[curarg], "-t") == 0) {
            if (title_specified) {
                cout << "Title specified more than once." << endl;
                Useage();
                return -1;
            }
            title_specified = true;
            ++curarg;
            if (curarg >= argc) {
                cout << "Title missing for -t." << endl;
                Useage();
                return -1;
            }

            Title = args[curarg];
            ++curarg;
            continue;
        }

        // this must be a word
        string temp;
        temp.clear();
        for (auto i = 0; args[curarg][i] != 0; ++i)
            temp += args[curarg][i];

        Words.push_back(temp);
        ++curarg;
    }

    // make sure we have at lease one word
    if (Words.size() == 0) {
        cout << "No words specified for puzzle." << endl;
        Useage();
        return -1;
    }

    return 0;
}

void Useage()
{
    cout << "Usage:" << endl;
    cout << "Wordsearch [-r rows] [-c cols] [-t title] word1 word2 word3 ..." << endl;
}
