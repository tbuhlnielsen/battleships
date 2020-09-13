/*
    class Board
        A 10-by-10 grid of Markers. Drawn in the format shown at the bottom
        of this file.

    enum class Marker
        The contents of one square on a Board: part of a Ship or 
        an indicator of the outcome of a shot (or blank).

    struct Ship
        Carries a Marker indicating whether it is a carrier, battleship, 
        destroyer, submarine, or patrol boat. Has an origin Square and 
        an orientation to store the location given to it by a Player.

    struct Square
        2D coordinates (row and column) used to simplify access to 
        Board squares.
*/

#ifndef PIECES_H
#define PIECES_H

#include <string>
#include <vector>

#include "constants.h"

// § Marker
enum class Marker 
{
    carrier, battleship, destroyer, submarine, patrol, 
    hit, miss, blank
};

char to_char(Marker m); // e.g. 'C' for a carrier
bool is_ship(Marker m);

// § Square
struct Square
{
    int row, col;
};

// § Ship
struct Ship
{
    explicit Ship(Marker m);

    Marker type;
    int length;
    Square origin;
    char orientation;

    std::string name() const;
};

// § Board
class Board
{
public:
    Board(); 

    void draw() const;

    // Returns the Marker on squares[row][col].
    // Throws an error if indices are not in range.
    Marker at(int row, int col) const;
    Marker at(Square sq) const { return at(sq.row, sq.col); }

    // Sets the Marker on squares[row][col] to m.
    // Throws an error if indices are not in range.
    void set(int row, int col, Marker m);
    void set(Square sq, Marker m) { set(sq.row, sq.col, m); }

    // Sets all squares blank.
    void clear();

    static const int width  = 10;
    static const int height = 10;

private:
    std::vector<std::vector<Marker>> squares;

    // Draws the yth row of squares. Helper function for draw().
    void draw_row(int y) const;
};

// True iff sq's coordinates are in the range of a Board's dimensions.
bool is_on_board(int row, int col);
bool is_on_board(Square sq);

// True iff ship can be placed on b. Requires ship's orientation and 
// origin to be set!
bool can_place(Ship ship, const Board& b);

#endif

/*
    HOW A BOARD IS DRAWN:

                 a   b   c   d   e   f   g   h   i   j   <-- x labels
               +---+---+---+---+---+---+---+---+---+---+ <-- row separator
y label -->  0 |   |   |   |   |   |   | D | D | D |   |
               +---+---+---+---+---+---+---+---+---+---+
             1 |   | x |   |   | x |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             2 | S |   |   |   | ! |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             3 | S |   |   | x | ! |   |   | x |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             4 | S | x |   |   | ! |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             5 |   |   |   |   | ! | P | P |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             6 |   |   |   |   | ! |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             7 |   |   |   |   |   |   |   | x |   |   |
               +---+---+---+---+---+---+---+---+---+---+
             8 |   | B | B | B | B |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+
y label -->  9 |   |   |   |   |   |   |   |   |   |   |
               +---+---+---+---+---+---+---+---+---+---+

*/