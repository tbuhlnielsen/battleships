/*
    utils.h - Declarations of "helpers" for getting input from a Human 
    when Ships are being put() during Battleships::setup().
*/

#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "pieces.h"

// ----------------

/* A Destination is a compact description of the set of Squares on a 
Board occupied by a Ship; it consists of three pieces of information: 
    1) a Square where the "head" of a Ship is (origin);
    2) the orientation of the Ship (horizontal or vertical);
    3) the length of the Ship.
Destinations are helpful in simplifying function declarations. */
struct Destination
{
    Square origin;
    char orientation;
    int length;
};

/* Reads characters from std::cin until a letter representing 
an orientation (v or h) is found. Returns this letter. */
char get_orientation(const std::string& prompt);

/* Gets a letter-digit pair from std::cin and returns a Square
with these characters (converted to ints) as its coordinates. 
Only checks the format of the input, not the values. */
Square get_coords(const std::string& prompt);

/* Gets a letter-digit pair from std::cin which represents a Square
which is_in_range() on a Board of dimensions width * height. Returns
a Square with these characters (converted to ints) as its coordinates. */
Square get_coords(const std::string& prompt, int width, int height);

/* Returns true if there is space on b for a Ship of length d.length
starting at d.origin, in the direction d.orientation. Expects a 
Destination whose origin is_in_range() on b. */
bool available(const Board& b, Destination d);

/* Gets a Destination on primary which is a valid Destination for 
a Human to put() a Ship. */
Destination get_destination(const Board& primary, Ship ship);

#endif