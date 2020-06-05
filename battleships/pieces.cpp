#include <iostream>
#include <stdexcept>

#include "pieces.h"

// ----------------

void Square::draw() const 
{
    std::cout << blank << marker << blank;
}

Square::Square(int row, int col, char ch)
    :x{col}, y{row}, marker{ch}
{
}

bool has_ship_marker(Square sq)
{
    char m = sq.marker;

    return (m == 'C' || m == 'B' || m == 'D' || m == 'S' || m == 'P');
}

bool is_in_range(int width, int height, Square sq)
{
    return (0 <= sq.x && sq.x < width && 0 <= sq.y && sq.y < height);
}

// ----------------

Board::Board()
{
    for (int row = 0; row < rows; ++row)
    {
        std::vector<Square> vs;

        for (int col = 0; col < cols; ++col)
            vs.push_back(Square{row, col});

        squares.push_back(vs);
    }
}

// ----------------

// Board drawing functions

void Board::draw() const
{
    std::cout << '\n';

    draw_x_labels(cols);
    for (int row = 0; row < rows; ++row)
    {
        draw_y_label(row);
        draw_row(row);
        draw_row_sep(cols);
    }
    
    std::cout << '\n';
}

void Board::draw_row(int y) const
{
    for (int x = 0; x < cols; ++x)
    {
        squares[y][x].draw();
        std::cout << column_sep;
    }

    std::cout << '\n';
}

void draw_x_labels(int width)
{
    std::cout << blank << blank << blank << blank;

    for (int x = 0; x < width; ++x)
        std::cout << blank << x << blank << blank;
        
    std::cout << '\n';

    draw_row_sep(width);
}

void draw_y_label(int y)
{
    std::cout << blank << static_cast<char>('a' + y) << blank << column_sep;
}

void draw_row_sep(int width)
{
    std::cout << blank << blank << blank << '+';

    for (int x = 0; x < width; ++x)
        std::cout << "---+";

    std::cout << '\n';
}

// ----------------

// Board access functions

Square Board::at(int row, int col) const
{
    if (row < 0 || rows <= row || col < 0 || cols <= col)
        throw std::runtime_error("at() coordinate out of range");

    return squares[row][col];
}

void Board::set(int row, int col, char ch)
{
    if (row < 0 || rows <= row || col < 0 || cols <= col)
        throw std::runtime_error("set() coordinate out of range");

    squares[row][col].marker = ch;
}

// ----------------

void Board::reset()
{
    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
            set(row, col, blank);
    }
}

// ----------------

/* This could be done with a std::map, but for some reason 
I got a linker error when I tried to define one in constants.h.*/

std::string Ship::name() const
{
    std::string s;

    switch (symbol)
    {
        case 'C':
            s = "carrier";
            break;

        case 'B':
            s = "battleship";
            break;

        case 'D':
            s = "destroyer";
            break;

        case 'S':
            s = "submarine";
            break;

        case 'P':
            s = "patrol boat";
            break;
        
        default:
            throw std::runtime_error("invalid ship symbol");
    }

    return s;
}
