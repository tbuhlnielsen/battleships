/*
    pieces.h - Definitions of classes representing the pieces 
    used to play the game: Square, Board, and Ship.

    A Board is an array of Squares. Each Square has (x, y) 
    coordinates indicating where it is on a Board, and a marker 
    indicating one of the following:
    * 'C' = part of a carrier
    * 'B' = part of a battleship
    * 'D' = part of a destroyer
    * 'S' = part of a submarine
    * 'P' = part of a patrol boat
    * '!' = shot has been fired here, hit a Ship
    * 'x' = shot has been fired here, missed
    * ' ' = not part of a Ship, no shot has been fired here

    N.B. There are several functions involved with drawing a
    Board; instead of documenting which parts each one draws, 
    I have included a labelled diagram at the end of this file.
*/

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

#include "constants.h"

// ----------------

struct Square
{
    int x = 0;    // column
    int y = 0;    // row

    char marker {blank};

    void draw() const;

    /* Initialises a Square with coordinates (col, row) and marker ch. */ 
    Square(int row, int col, char ch=blank);
};

/* True if sq's marker represents part of a Ship. */
bool has_ship_marker(Square sq);

/* True if 0 <= sq.x < width and 0 <= sq.y < height. 
Useful for determining if coordinates entered by a player
correspond to a Square on a Board. */
bool is_in_range(int width, int height, Square sq);

// ----------------

class Board
{
    public:
        /* Initialises a blank Board of size rows * cols. */
        Board();

        void draw() const;

        /* Returns squares[row][col]. Throws an error if indices 
        are not in range. */
        Square at(int row, int col) const;

        /* Sets squares[row][col].marker to ch. Throws an error 
        if indices are not in range. */
        void set(int row, int col, char ch);

        /* Sets all Squares on a Board to blank. */
        void reset();

        int width() const { return cols; }

        int height() const { return rows; }

    private:
        std::vector<std::vector<Square>> squares;

        int rows = default_board_width;
        int cols = default_board_height;

        void draw_row(int y) const;
};

// Helper functions for drawing a Board

void draw_x_labels(int width);

void draw_y_label(int y); 

void draw_row_sep(int width);

// ----------------

struct Ship
{
    char symbol;        // 'C', 'B', 'D', 'S', 'P'
    int length;         //  5    4    3    3    2
    int damage = 0;

    /* Gets a Ship's full name from its symbol, e.g. "carrier" from 'C'. */
    std::string name() const;

    bool sunk() const 
    { return damage == length; }
};

#endif

// ----------------

/*
    A Board is drawn in the format below. Note that the axis labels
    are not stored in Board::squares, which is why there are functions
    for drawing them separately from the main grid.

                 0   1   2   3   4   5   6   7   8   9   <-- x labels
               +---+---+---+---+---+---+---+---+---+---+ <-- row separator
y label -->  a |   |   |   |   |   |   | D | D | D |   |
               +---+---+---+---+---+---+---+---+---+---+
             b |   | x |   |   | x |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             c | S |   |   |   | ! |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             d | S |   |   | x | ! |   |   | x |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             e | S | x |   |   | ! |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             f |   |   |   |   | ! | P | P |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             g |   |   |   |   | ! |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             h |   |   |   |   |   |   |   | x |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             i |   | B | B | B | B |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
y label -->  j |   |   |   |   |   |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+

*/