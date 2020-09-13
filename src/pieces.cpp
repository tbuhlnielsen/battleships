#include <iostream>
#include <stdexcept>

#include "pieces.h"

// § Marker
char to_char(Marker m)
{
    switch (m)
    {
    case Marker::carrier: 
        return 'C';
    case Marker::battleship: 
        return 'B';
    case Marker::destroyer: 
        return 'D';
    case Marker::submarine: 
        return 'S';
    case Marker::patrol: 
        return 'P';
    case Marker::hit: 
        return '!';
    case Marker::miss: 
        return 'x';
    case Marker::blank: 
        return ' ';
    }
}

bool is_ship(Marker m)
{
    switch (m)
    {
    case Marker::carrier: case Marker::battleship: case Marker::destroyer:
    case Marker::submarine: case Marker::patrol:
        return true;
    default:
        return false;
    }
}

// § Ship
Ship::Ship(Marker m)
    : type{m}
{
    switch (type)
    {
    case Marker::carrier:
        length = 5; 
        break;
    case Marker::battleship:
        length = 4; 
        break;
    case Marker::destroyer:
        length = 3; 
        break;
    case Marker::submarine:
        length = 3; 
        break;
    case Marker::patrol:
        length = 2; 
        break;
    default:
        throw std::runtime_error("invalid ship Marker");
    }
}

std::string Ship::name() const
{
    switch (type)
    {
    case Marker::carrier: 
        return "carrier";
    case Marker::battleship: 
        return "battleship";
    case Marker::destroyer: 
        return "destroyer";
    case Marker::submarine: 
        return "submarine";
    case Marker::patrol: 
        return "patrol boat";
    default:
        throw std::runtime_error("Ship::name invalid type");
    }
}

// § Board
Board::Board()
{
    for (int row = 0; row < height; ++row)
    {
        std::vector<Marker> vm;

        for (int col = 0; col < width; ++col)
            vm.push_back(Marker::blank);

        squares.push_back(vm);
    }
}

Marker Board::at(int row, int col) const
{
    if (!is_on_board(row, col))
        throw std::runtime_error("Board::at out of range");

    return squares[row][col];
}

void Board::set(int row, int col, Marker m)
{
    if (!is_on_board(row, col))
        throw std::runtime_error("Board::set out of range");

    squares[row][col] = m;
}

void Board::clear()
{
    for (int row = 0; row < height; ++row) 
    {
        for (int col = 0; col < width; ++col) 
        {
            set(row, col, Marker::blank);
        }    
    }
}

// Helper function for Board::draw
void draw_column_labels(int num_columns)
{
    std::cout << "   "; // space for row labels
    for (int x = 0; x < num_columns; ++x)
        std::cout << "  " << static_cast<char>('a' + x) << ' ';
}

// Helper function for Board::draw
void draw_row_label(int row)
{
    std::cout << ' ' << row << ' ';
}

// Helper function for Board::draw
void draw_row_separator(int num_columns)
{
    std::cout << "   +"; // space for row labels
    for (int x = 0; x < num_columns; ++x)
        std::cout << "---+";
}

void Board::draw_row(int y) const
{
    std::cout << '|';
    for (int x = 0; x < width; ++x)
        std::cout << ' ' << to_char(squares[y][x]) << " |";
}

void Board::draw() const
{
    std::cout << '\n';

    draw_column_labels(width);
    std::cout << '\n';
    draw_row_separator(width);
    std::cout << '\n';
    for (int row = 0; row < height; ++row)
    {
        draw_row_label(row);
        draw_row(row);
        std::cout << '\n';
        draw_row_separator(width);
        std::cout << '\n';
    }

    std::cout << '\n';
}

bool is_on_board(int row, int col)
{
    if (col < 0 || Board::width <= col)
        return false;

    if (row < 0 || Board::height <= row)
        return false;

    return true;
}

bool is_on_board(Square sq)
{
    return is_on_board(sq.row, sq.col);
}

bool can_place(Ship ship, const Board& b)
{
    Square sq = ship.origin;
 
    // Check if ship would actually fit on the board.
    if (ship.orientation == K::horizontal && Board::width <= sq.col + ship.length - 1)
        return false;

    if (ship.orientation == K::vertical && Board::height <= sq.row + ship.length - 1)
        return false;

    // Check if the squares are already occupied.
    for (int i = 0; i < ship.length; ++i)
    {
        if (ship.orientation == K::horizontal)
        {
            if (b.at(sq.row, sq.col + i) != Marker::blank)
                return false;
        }
        else // ship.orientation == K::vertical
        {
            if (b.at(sq.row + i, sq.col) != Marker::blank)
                return false;
        }
    }

    return true;
}