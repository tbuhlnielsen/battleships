#include <iostream>
#include <stdexcept>

#include "game.h"

int main()
{
    try
    {
        Game battleships;
        battleships.run();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!\n";
        return 2;
    }
}
