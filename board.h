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
    enum Direction
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

    enum
    {
        row_offset = 0,
        column_offset = 1
    };

    std::vector<std::string> words;
    std::string title;

    /// <summary>
    /// row column increments for directions
    /// </summary>
    const std::vector<std::tuple<int, int>> direction_offsets =
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

    /// <summary>
    /// number of rows
    /// </summary>
    int num_rows;

    /// <summary>
    /// number of columns
    /// </summary>
    int num_cols;

    bool word_fits(std::string& word, int x, int y, Direction direction);
    bool add_words();
    bool add_word(std::string& word);
    void fill();
    std::vector<int> create_shuffled_array(int sz) const;
    void print_field();
    void print_words();

public:
    /// <summary>
    /// field of chars
    /// </summary>
    std::vector<std::vector<char>> field;

    board(int rows, int cols, std::vector<std::string>& word_list, std::string title);
    void print();
};
