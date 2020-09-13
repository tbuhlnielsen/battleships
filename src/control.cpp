#include <iostream>
#include <random>
#include <stdexcept>

#include "control.h"

// § InputHandler
void InputHandler::read_line()
{
    std::string line;
    std::getline(std::cin, line);
    input.str(line);
    input.clear();
    len = input.str().length();
}

Square InputHandler::get_row_col(const std::string& prompt)
{
    std::cout << prompt;

    while (true)
    {
        read_line();
        for (char col, row; input.get(col) && input.get(row);)
        {
            if (isalpha(col) && isdigit(row))
            {
                col = tolower(col); // Allows for uppercase.
                if (len > 2)
                    std::cerr << "[read " << col << row << "]\n";

                return Square{row - '0', col - 'a'};
            }
        }
        if (len > 0) // Don't bother outputting a message if no input is given.
            std::cerr << "Please enter a letter followed by a number: ";
    }
}

Square InputHandler::get_coords(const std::string& prompt)
{
    Square sq = get_row_col(prompt);

    while (!is_on_board(sq))
    {
        std::cerr << "That square doesn't exist! Try again.\n";
        sq = get_row_col(prompt);
    }

    return sq;
}

char InputHandler::get_orientation(const std::string& prompt)
{
    std::cout << prompt;

    while (true)
    {
        read_line();
        for (char ch; input.get(ch); )
        {
            ch = tolower(ch); // Allows for uppercase.
            if (ch == K::horizontal || ch == K::vertical)
            {
                if (len > 1) 
                    std::cerr << "[read " << ch << "]\n";

                return ch;
            }
        }
        std::cerr << "Please enter v or h: ";
    }
}

void InputHandler::set_destination(Ship& ship, const Board& b)
{
    ship.origin = get_coords("Coordinates for " + ship.name() + ": ");
    ship.orientation = get_orientation("Orientation (v or h): ");

    while (!can_place(ship, b))
    {
        std::cerr << "Cannot place ship. Try again.\n";
        ship.origin = get_coords("Coordinates for " + ship.name() + ": ");
        ship.orientation = get_orientation("Orientation (v or h): ");
    }
}

// § AI
char AI::decide_orientation()
{
    return (randint(0, 1) == 0) ? K::horizontal : K::vertical;
}

Square AI::decide_coords()
{
    int row = randint(0, Board::height - 1);
    int col = randint(0, Board::width - 1);
    return Square{row, col};
}

void AI::decide_destination(Ship& ship, const Board& b)
{
    ship.orientation = decide_orientation();
    ship.origin = decide_coords();

    while (!can_place(ship, b))
    {
        ship.orientation = decide_orientation();
        ship.origin = decide_coords();
    }
}

int randint(int low, int high)
{
    static std::random_device rd; // used to generate a seed
    static std::default_random_engine rand_gen{rd()};
    std::uniform_int_distribution<int> dist{low, high};
    return dist(rand_gen);
}