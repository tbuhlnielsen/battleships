#include "ai.h"

// ----------------

char AI::decide_orientation()
{
    return (randint(0, 1) == 0) ? horizontal : vertical;
}

Square AI::decide_coords()
{
    int x = randint(0, default_board_height-1);

    int y = randint(0, default_board_width-1);

    return Square {y, x};
}

Destination AI::decide_destination(const Board& primary, Ship ship)
{
    char orientation = decide_orientation();

    Square origin = decide_coords();

    Destination d {origin, orientation, ship.length};

    if (available(primary, d))
        return d;

    return decide_destination(primary, ship);
}

// ----------------

int randint(int low, int high)
{
    static std::random_device rd; // used to generate a seed

    static std::default_random_engine rand_gen {rd()};

    std::uniform_int_distribution<int> dist {low, high};

    return dist(rand_gen);
}