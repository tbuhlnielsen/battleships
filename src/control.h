/*
    class InputHandler
        Reads input from std::cin to allow a Human to choose
        locations for their Ships and shots.

    class AI
        Decides locations of Ships and shots for a Computer.
*/

#ifndef CONTROL_H
#define CONTROL_H

#include <sstream>
#include <string>

#include "pieces.h"

class InputHandler
{
public:
    Square get_coords(const std::string& prompt);

    void set_destination(Ship& ship, const Board& b);

private:
    std::istringstream input;
    int len = 0;

    void read_line();

    // Gets a letter-digit pair from std::cin and returns a Square
    // with these characters (converted to ints) as its coordinates.
    // Only checks the format of the input, not the values.
    Square get_row_col(const std::string& prompt);

    // Reads characters from std::cin until a letter representing
    // an orientation (v or h) is found. Returns this letter.
    char get_orientation(const std::string& prompt);
};

class AI
{
public:
    virtual Square decide_coords();

    virtual void decide_destination(Ship& ship, const Board& b);

private:
    virtual char decide_orientation();
};

// Returns a randomly generated integer in the interval [low, high].
int randint(int low, int high);

#endif
