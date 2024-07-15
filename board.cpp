// Written by Paul Baxter

#include <tuple>
#include <iomanip>

#include "board.h"

/// <summary>
/// board constructor
/// set rows cols and initialize field
/// </summary>
/// <param name="rows">number of rows</param>
/// <param name="cols">number of cols</param>
/// <param name="words">vector of words for puzzle </param>
/// <param name="title">title for puzzle</param>
board::board(int rows, int cols, std::vector<std::string>& words, std::string title)
{
    srand((int)time(0));
    Words.clear();

    Num_rows = rows;
    Num_cols = cols;

    for (auto& word : words)
        Words.push_back(word);
    
    Title = title;

    for (auto row = 0; row < Num_rows; ++row)
    {
        field.push_back(std::vector<char>());
        for (auto col = 0; col < Num_cols; ++col)
        {
            field[row].push_back(' ');
        }
    }

    if (add_words())
        fill();
    else
    {
        std::cout << "Error creating puzzle." << std::endl;
        exit(-1);
    }
}

/// <summary>
/// Add words to the field
/// </summary>
/// <param name="word">word to add</param>
/// <returns>true if word fits</returns>
bool board::add_words()
{
    for (auto& word : Words)
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
    std::vector<int> row_numbers = create_shuffled_array(Num_rows);
    std::vector<int> col_numbers = create_shuffled_array(Num_cols);
    std::vector<int> direction_numbers = create_shuffled_array((int)Direction_offsets.size());

    for (auto& r : row_numbers)
        for (auto& c : col_numbers)
            for (auto& d : direction_numbers)
            {
                if (word_fits(word, r, c, (Direction)d))
                {
                    auto rr = r;
                    auto cc = c;
                    for (auto& ch : word)
                    {

                        field[rr][cc] = ch;

                        rr += std::get<row_offset>(Direction_offsets[d]);
                        cc += std::get<column_offset>(Direction_offsets[d]);
                    }
                    return true;
                }
            }

    return false;
}

/// <summary>
/// check if word can be added at given row column and direction
/// </summary>
/// <param name="word">word to add</param>
/// <param name="row">row for word</param>
/// <param name="col">column for word</param>
/// <param name="direction">direction word should go</param>
/// <returns>true if word fits</returns>
bool board::word_fits(std::string word, int row, int col, Direction direction)
{
    for (auto ch : word)
    {
        if (row < 0 || row >= Num_rows)
            return false;
        if (col < 0 || col >= Num_cols)
            return false;

        auto exisiting_char = field[row][col];
        if (ch != exisiting_char && exisiting_char != ' ')
            return false;

        // now move to next spot in field
        row += std::get<row_offset>(Direction_offsets[direction]);
        col += std::get<column_offset>(Direction_offsets[direction]);
    }

    return true;
}

/// <summary>
/// create a vector 0 - sz in random order
/// </summary>
/// <param name="sz">size of vector</param>
/// <returns>random order vector 0 - sz</returns>
std::vector<int> board::create_shuffled_array(int sz) const
{
    std::vector<int> arr(sz);
    for (auto i = 0; i < sz; ++i)
        arr[i] = i;

    auto m = sz >> 1;
    for (auto i = 0; i < sz; ++i)
    {
        auto a = rand() % m;
        auto b = rand() % ((sz - a - 1)) + a;

        std::swap(arr[a], arr[b]);
    }
    return arr;
}

/// <summary>
/// Fill the blank spots with random letter
/// It would be nice to make sure letter does not create new word
/// </summary>
void board::fill()
{
    for (auto row = 0; row < Num_rows; ++row)
    {
        for (auto col = 0; col < Num_cols; ++col)
        {
            if (field[row][col] == ' ')
            {
                field[row][col] = rand() % 26 + 'A';
            }
        }
    }
}

/// <summary>
/// print the puzzle
/// </summary>
void board::print()
{
    std::cout << std::endl << ' ' << Title << std::endl << std::endl;
    print_field();
    print_words();
}

/// <summary>
/// print the field
/// </summary>
void board::print_field()
{
    for (auto& r : field)
    {
        for (auto& c : r)
        {
            std::cout << ' ' << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

/// <summary>
/// print the words
/// </summary>
void board::print_words()
{
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
