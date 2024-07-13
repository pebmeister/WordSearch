// Written by Paul Baxter

#include <tuple>
#include <iomanip>
#include "board.h"

/// <summary>
/// check if word can be added at given row column and direction
/// </summary>
/// <param name="word">word to add</param>
/// <param name="row">row for word</param>
/// <param name="col">column for word</param>
/// <param name="direction">direction word should go</param>
/// <returns>true if word fits</returns>
bool board::word_fits(std::string word, int row, int col, int direction)
{
    for (auto ch : word)
    {
        if (row < 0 || row >= num_rows)
            return false;
        if (col < 0 || col >= num_cols)
            return false;

        auto exisiting_char = field[row][col];
        if (ch != exisiting_char && exisiting_char != ' ')
            return false;

        row += std::get<xoffset>(direction_offsets[direction]);
        col += std::get<yoffset>(direction_offsets[direction]);
    }

    return true;
}

/// <summary>
/// create a vector 0 - sz in random order
/// </summary>
/// <param name="sz">size of vector</param>
/// <returns>random order vector 0 - sz</returns>
std::vector<int> board::create_shuffle_array(int sz) const
{
    std::vector<int> arr(sz);
    for (auto i = 0; i < sz; ++i)
        arr[i] = i;

    auto m = sz >> 1;
    for (auto i = 0; i < sz; ++i)
    {
        auto a = rand() % m;
        auto b = rand() % ((sz - a -1)) + a;

        std::swap(arr[a], arr[b]);
    }
    return arr;
}

/// <summary>
/// board constructor
/// set rows cols and initialize field
/// </summary>
/// <param name="rows">number of rows</param>
/// <param name="cols">number of cols</param>
board::board(int rows, int cols)
{
    srand((int)time(0));

    num_rows = rows;
    num_cols = cols;

    for (auto row = 0; row < num_rows; ++row)
    {
        field.push_back(std::vector<char>());
        for (auto col = 0; col < num_cols; ++col)
        {
            field[row].push_back(' ');
        }
    }
}

/// <summary>
/// Add a word to the field
/// </summary>
/// <param name="word">word to add</param>
/// <returns>true if word fits</returns>
bool board::add_words(std::vector<std::string> words)
{
    for (auto& word : words)
        if (!add_word(word))
            return false;
    return true;
}

/// <summary>
/// Add a word to the field
/// </summary>
/// <param name="word">word to add</param>
/// <returns>true if word fits</returns>
bool board::add_word(std::string& word)
{
    std::vector<int> row_numbers = create_shuffle_array(num_rows);
    std::vector<int> col_numbers = create_shuffle_array(num_cols);
    std::vector<int> direction_numbers = create_shuffle_array((int)direction_offsets.size());

    Words.push_back(word);
    for (auto r : row_numbers)
        for (auto c : col_numbers)
            for (auto d : direction_numbers)
            {
                if (word_fits(word, r, c, d))
                {
                    for (auto ch : word)
                    {
                        field[r][c] = ch;

                        r += std::get<xoffset>(direction_offsets[d]);
                        c += std::get<yoffset>(direction_offsets[d]);
                    }
                    return true;
                }
            }

    return false;
}

/// <summary>
/// Set the title of the puzzle
/// </summary>
/// <param name="title"></param>
void board::set_title(std::string& title)
{
    Title = title;
}

/// <summary>
/// Fill the blank spots with random letter
/// It would be nice to make sure letter does not create new word
/// </summary>
void board::fill()
{
    for (auto row = 0; row < num_rows; ++row)
    {
        for (auto col = 0; col < num_cols; ++col)
        {
            if (field[row][col] == ' ')
            {
                field[row][col] = rand() % 26 + 'A';
            }
        }
    }
}

/// <summary>
/// print the board
/// </summary>
void board::print()
{
    // print board
    std::cout << std::endl << ' ' << Title << std::endl << std::endl;

    for (auto& r : field)
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
