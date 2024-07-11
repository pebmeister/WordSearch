// Written by Paul Baxter

#include <tuple>
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

        row += std::get<0>(directions[direction]);
        col += std::get<1>(directions[direction]);       
    }

    return true;
}

/// <summary>
/// create a vector 0 - sz in randowm order
/// </summary>
/// <param name="sz">size of vector</param>
/// <returns>random order vector 0 - sz</returns>
std::vector<int> board::create_shuffle_array(int sz) const
{
    std::vector<int> arr(sz);
    for (auto i = 0; i < sz; ++i)
        arr[i] = i;

    for (auto i = 0; i < ShuffleSize; ++i)
    {
        auto a = rand() % (sz / 2);
        auto b = rand() % (sz / 2) + (a + 1);

        auto t = arr[a];
        arr[a] = arr[b];
        arr[b] = t;
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
bool board::add_word(std::string word)
{
    std::vector<int> row_numbers = create_shuffle_array(num_rows);
    std::vector<int> col_numbers = create_shuffle_array(num_cols);
    std::vector<int> direction_numbers = create_shuffle_array((int)directions.size());

    for (auto r : row_numbers)
        for (auto c : col_numbers)
            for (auto d : direction_numbers)
            {
                if (word_fits(word, r, c, d))
                {
                    for (auto ch : word)
                    {
                        field[r][c] = ch;

                        r += std::get<0>(directions[d]);
                        c += std::get<1>(directions[d]);
                    }
                    return true;
                }
            }

    return false;
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
