/*
    players.h - Definitions of classes representing the human
    and computer players of the game. 
*/

#ifndef PLAYERS_H
#define PLAYERS_H

#include "ai.h"

// ----------------

class Player
{
    public:
        /* Sets blank every Square on both a Player's Boards. */
        void reset_boards();

        /* Sets a Player's damage back to 0 to prepare for a new game. */
        void reset_damage();

        /* Marks a Destination on a Player's primary Board with a Ship's
        symbol. Expects a valid Destination -- one that is actually on the 
        Board and is not overlapping a Ship which has already been put(). */
        void put(Ship, Destination);

        /* Gets valid Destinations for each Ship in a Player's fleet 
        and put()s them there. */
        virtual void setup_ships() = 0;

        /* Updates a Player's primary Board with a hit or miss marker
        in response to a shot at target by their opponent. Returns this 
        marker to give as feedback to the opponent, so that they can 
        update their tracking Board accordingly. */
        virtual char handle_shot(Square target) =0;

        /* Updates a Player's tracking Board with a hit or miss marker
        based on feedback returned by their opponent's handle_shot(). */
        void handle_shot_feedback(Square target, char result);

        /* True if every Ship in a Player's fleet has been sunk. */
        bool defeated() const;

        virtual ~Player() { }

    protected:
        Board primary;    // locations of own Ships and opponent's guesses
        Board tracking;   // guesses of locations of opponent's Ships

        std::vector<Ship> fleet {{'C', 5}, {'B', 4}, {'D', 3}, {'S', 3}, {'P', 2}};

        /* The total number of hits that the Ships in a Player's fleet
        have taken. */
        int damage = 0;
};

// ----------------

struct Human : Player
{
    void setup_ships() override;

    char handle_shot(Square target) override;

    Square get_move(const std::string &prompt); // IMPROVE ERROR HANDLING

    /* Draws a Human's tracking Board. */
    void show_guesses() const;
};

// ----------------

struct Computer : Player
{
    AI ai;

    void setup_ships() override;

    char handle_shot(Square target) override;

    Square choose_move();
};

#endif