#ifndef GAME_H
#define GAME_H

#include <string>

#include "players.h"

class Game
{
public:
    // Plays the game over and over until the human quits.
    void run();

private:
    Human user;
    Computer pc;

    bool quit = false;

    char turn = 'H'; // 'H' for human or 'C' for computer
    void swap_turn() { turn = (turn == 'H') ? 'C' : 'H'; }

    // Checks if one of the players has lost.
    bool is_over() const;

    // Tells both players to clear their boards and set up their ships.
    void reset();

    // Main loop: players take turns firing shots at their opponent's fleet.
    void play();

    // Reports who won, how many ships they had left etc. INCOMPLETE!
    void print_summary() const;
};

// Prints the characters in s one at a time, with a delay of pause milliseconds 
// between each one.
void delayed_print(const std::string& s, int pause);

// Waits for the user to press the enter key; anything typed before they do so
// is discarded.
void wait_for_input(const std::string& prompt); 

// Returns true iff the user enters some text starting with 'y'.
bool ask_yes_no(const std::string& prompt);

#endif 