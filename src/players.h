/*
    class Player
        An abstract player (human or computer) of the game with a 
        fleet of Ships and two Boards. The primary Board records 
        the locations of their Ships and their opponent's guesses, 
        while the tracking Board holds their own guesses.

    class Human : public Player
        A Player controlled by input through std::cin.

    class Computer : public Player
        A Player controlled by AI.
*/

#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>

#include "pieces.h"
#include "control.h"

class Player
{
public:
    Player();

    // Sets the location of each Ship in the Player's fleet and place()s them.
    virtual void set_up_ships() =0;

    // Checks if a there is a Ship on the Player's primary Board at target and 
    // updates the Square with a hit or miss Marker accordingly. Returns this 
    // Marker so the Player's opponent can use it to update().
    Marker receive_attack(Square target);

    // Called after the Player's opponent receives an attack; places 
    // hit_or_miss on the Player's tracking Board at shot_target.
    virtual void update(Square shot_target, Marker hit_or_miss) =0;

    bool defeated() const { return damage == max_health; }

    // Clears both Boards and sets damage to 0.
    void reset();

    virtual ~Player() { }

protected:
    Board primary, tracking;

    std::vector<Ship> fleet {Ship{Marker::carrier}, Ship{Marker::battleship}, 
        Ship{Marker::destroyer}, Ship{Marker::submarine}, Ship{Marker::patrol}};

    int damage = 0; // Total number of hits taken by the Player's fleet.
    int max_health; // Set by constructor.

    // Sets the Markers on the Player's primary Board at ship's location.
    void place(Ship ship);
};

class Human : public Player
{
public:
    void set_up_ships() override;

    Square get_move(const std::string& prompt);

    void update(Square shot_target, Marker hit_or_miss) override;

private:
    InputHandler control;
};

class Computer : public Player
{
public:
    void set_up_ships() override;

    Square decide_move();

    void update(Square shot_target, Marker hit_or_miss) override;

private:
    AI control;
};

#endif