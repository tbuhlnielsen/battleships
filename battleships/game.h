/*
    game.h - Definition of the Battleships class, which controls
    the running of the game (setup, main loop, and end).
*/

#ifndef GAME_H
#define GAME_H

#include "players.h"

// ----------------

/* A strategy board game between a Human and Computer. */
class Battleships
{
    public:
        /* Constructs a new game and welcomes the Human. */
        Battleships();

        /* Prepares for a new game by instructing both Players to 
        reset their Boards and damage, and to set up their Ships. */
        void reset();

        /* The main game loop: the Players take turns firing
        shots at their opponent's fleet. */
        void play();

        /* True if one of the Players has lost the game. */
        bool game_is_over() const;

        /* Gives a report() on the game and asks the Human if 
        they want to play again. */
        void end(const std::string& prompt);

        /* True as long as the Human wants to keep playing. */
        bool is_running() const { return rematch; }

    private:
        Computer pc;
        Human user;

        char turn = 'H';        // 'H' for human, 'C' for computer
        void swap_turn();

        bool rematch = true;    // does the Human want to play again?

        /* Announces the winner of the game. */
        void report() const;

        /* Instructs the Players to update their Boards according to 
        whether or not a shot at target hit a Ship. Expects target to be 
        (part of) a valid Destination. */
        void shot_at(Square target);
};

// ----------------

/* Prints a welcoming message to std::cout. */
void welcome();

#endif 