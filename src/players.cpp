#include <iostream>
#include <sstream>
#include <stdexcept>

#include "players.h"

// § Player
Player::Player()
{
    max_health = 0;
    for (auto ship : fleet)
        max_health += ship.length;
}

Marker Player::receive_attack(Square target)
{
    bool hit = is_ship(primary.at(target));
    if (hit) 
        ++damage;

    auto result = (hit) ? Marker::hit : Marker::miss;
    primary.set(target, result);
    return result;
}

void Player::reset()
{
    primary.clear();
    tracking.clear();
    damage = 0;
}

void Player::place(Ship ship)
{
    Square sq = ship.origin;

    if (ship.orientation == K::horizontal)
    {
        for (int j = 0; j < ship.length; ++j)
            primary.set(sq.row, sq.col + j, ship.type);
    }
    else if (ship.orientation == K::vertical)
    {
        for (int i = 0; i < ship.length; ++i)
            primary.set(sq.row + i, sq.col, ship.type);
    }
    else 
        throw std::runtime_error("Player::place Ship orientation not set");
}

// § Human
void Human::set_up_ships()
{
    std::cout << "Choose where to place your ships on the grid below.\n";
    primary.draw();

    for (auto ship : fleet)
    {
        control.set_destination(ship, primary);
        place(ship);
        primary.draw();
    }
}

Square Human::get_move(const std::string& prompt)
{
    std::cout << "\nYour guesses:\n";
    tracking.draw();

    Square target = control.get_coords(prompt);

    while (tracking.at(target) != Marker::blank)
    {
        std::cerr << "You made that move already! Choose another square.\n";
        target = control.get_coords(prompt);
    }
    
    return target;
}

void Human::update(Square shot_target, Marker hit_or_miss)
{
    tracking.set(shot_target, hit_or_miss);

    if (hit_or_miss == Marker::hit)
        std::cout << "Hit!\n";
    else
        std::cout << "Miss.\n";
}

// § Computer
void Computer::set_up_ships()
{
    for (auto ship : fleet)
    {
        control.decide_destination(ship, primary);
        place(ship);
    }
}

Square Computer::decide_move()
{
    Square target = control.decide_coords();

    while (tracking.at(target) != Marker::blank)
        target = control.decide_coords();

    return target;
}

void Computer::update(Square shot_target, Marker hit_or_miss)
{
    tracking.set(shot_target, hit_or_miss);

    std::ostringstream oss;
    oss << static_cast<char>('a' + shot_target.row) << shot_target.col;

    if (hit_or_miss == Marker::hit)
        std::cout << "Hit on " + oss.str() + "!\n";
    else
        std::cout << "Miss on " + oss.str() + ".\n";
}