/*
    main.cpp - Responsible for creating and running a Battleships game.
*/

#include <iostream>
#include <stdexcept>

#include "game.h"

// ----------------

/* Creates and runs a Battleships game between a Human and a Computer.
At the end of the game, the human will be asked if they want to play again. */
void run()
{
    Battleships game;

    while (game.is_running())
    {
        game.reset();
        game.play();
        game.end("Do you want to play again? ");
    }
}

// ----------------

int main()
{
    try
    {
        run();

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
