#include <iostream>
#include <sstream>
#include <stdexcept>

#include "utils.h"

// ----------------

char get_orientation(const std::string& prompt)
{
    std::cout << prompt;

    for (char ch; std::cin >> ch; )
    {
        if (ch == 'h' || ch == 'H')
            return horizontal;

        if (ch == 'v' || ch == 'V')
            return vertical;
    }

    throw std::runtime_error("bad input");
}

Square get_coords(const std::string& prompt)
{
    std::cout << prompt;

    char x, y;

    while (true)
    {
        /* When switching between whitespace-separated input (as in 
        get_orientation()) and line-oriented input (as here), we need 
        to clear all whitespace characters left behind. See std::getline 
        on cppreference. */
        std::cin >> std::ws;

        std::string s;
        std::getline(std::cin, s);

        std::istringstream input {s};

        input.get(y);
        input.get(x);

        if (isalpha(y) && isdigit(x))
        {
            /* If the user enters something which starts with a letter 
            and digit but then includes more characters, we interpret 
            this by ignoring the remainder of the input. We tell the 
            user this, since it might not be what they expect. */
            if (input.str().length() > 2)
                std::cerr << "(interpreted as " << y << x << ")\n";

            return Square {y - 'a', x - '0'};
        }

        std::cerr << "Invalid coordinate format! Try again.\n";
    }
}

Square get_coords(const std::string& prompt, int width, int height)
{
    Square sq = get_coords(prompt);

    if (is_in_range(width, height, sq))
        return sq;

    std::cerr << "Square not on board! Try again.\n";

    return get_coords(prompt, width, height);
}

bool available(const Board& b, Destination d)
{
    Square sq = d.origin;

    // Check if the ship fits on the board.
    if (d.orientation == horizontal && b.width() <= sq.x + d.length - 1)
        return false;

    if (d.orientation == vertical && b.height() <= sq.y + d.length - 1)
        return false;

    // Check if the squares are already occupied.
    for (int i = 0; i < d.length; ++i)
    {
        if (d.orientation == horizontal)
        {
            if (b.at(sq.y, sq.x + i).marker != blank)
                return false;
        }
        else // d.orientation == vertical
        {
            if (b.at(sq.y + i, sq.x).marker != blank)
                return false;
        }
    }

    return true;
}

Destination get_destination(const Board& primary, Ship ship)
{
    Square origin = get_coords("Coordinates for " + ship.name() + ": ", 
                                primary.width(), 
                                primary.height());

    char orientation = get_orientation("Orientation (v or h): ");

    Destination d {origin, orientation, ship.length};

    if (available(primary, d))
        return d;

    std::cerr << "Invalid square! Try again.\n";
    
    return get_destination(primary, ship);
}