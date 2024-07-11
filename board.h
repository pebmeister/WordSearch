#pragma once

// Written by Paul Baxter

#include <iostream>
#include <tuple>
#include <vector>

class board
{
private:
    /// <summary>
    /// possible directions
    /// </summary>
    enum
    {
        up,
        down,
        left,
        right,
        up_left_diagnal,
        up_right_diagnal,
        down_left_diagnal,
        down_right_diagnal
    };

    /// <summary>
    /// x y increments for directions
    /// </summary>
    std::vector<std::tuple<int, int>> directions =
    {
        {  0, -1 },  //  up
        {  0,  1 },  //  down
        { -1,  0 },  //  left
        {  1,  0 },  //  right
        { -1, -1 },  //  up_left_diagnal
        {  1, -1 },  //  up_right_diagnal
        { -1,  1 },  //  down_left_diagnal
        {  1,  1 },  //  down_right_diagnal
    };

    bool word_fits(std::string word, int x, int y, int direction);
    std::vector<int> create_shuffle_array(int sz) const;

public:
    /// <summary>
    /// number of rows
    /// </summary>
    int num_rows;
    /// <summary>
    /// number of columns
    /// </summary>
    int num_cols;

    /// <summary>
    /// field of chars
    /// </summary>
    std::vector<std::vector<char>> field;

    board(int rows, int cols);
    bool add_word(std::string word);
    void fill();
};
