#include <iostream>

#include "players.h"

// ----------------
// Player

void Player::reset_boards()
{
    primary.reset();
    tracking.reset();
}

void Player::reset_damage()
{
    damage = 0;
}

void Player::put(Ship ship, Destination d)
{
    Square sq = d.origin;

    if (d.orientation == horizontal)
    {
        for (int col = 0; col < ship.length; ++col)
            primary.set(sq.y, sq.x + col, ship.symbol);
    }
    else if (d.orientation == vertical)
    {
        for (int row = 0; row < ship.length; ++row)
            primary.set(sq.y + row, sq.x, ship.symbol);
    }
    // Check for an error that should be impossible?
    // (The orientation not being horizontal or vertical.)
}

void Player::handle_shot_feedback(Square sq, char result)
{
    tracking.set(sq.y, sq.x, result);
}

bool Player::defeated() const
{
    int max_dmg = 0;

    for (auto ship : fleet)
        max_dmg += ship.length;

    return (damage == max_dmg);
}

// ----------------
// Human

void Human::setup_ships()
{
    std::cout << "Choose where to place your ships on the grid below.\n";

    primary.draw();

    for (auto ship : fleet)
    {
        auto destination = get_destination(primary, ship);

        put(ship, destination);

        primary.draw();
    }
}

char Human::handle_shot(Square target)
{
    bool hit = has_ship_marker(primary.at(target.y, target.x));

    char result = (hit) ? '!' : 'x';

    primary.set(target.y, target.x, result);

    if (hit)
    {
        std::cout << "The computer hit your ship!\n";
        primary.draw();
        ++damage;
    }
    else
    {
        std::cout << "Miss.\n";
    }

    return result;
}

Square Human::get_move(const std::string& prompt)
{
    auto target = get_coords(prompt, primary.width(), primary.height());

    if (tracking.at(target.y, target.x).marker == blank)
        return target;

    std::cerr << "You made that move already! Choose another square.\n";

    return get_move(prompt);
}

void Human::show_guesses() const
{
    std::cout << "Previous guesses: \n";
    tracking.draw();
}

// ----------------
// Computer

void Computer::setup_ships()
{
    for (auto ship : fleet)
    {
        auto destination = ai.decide_destination(primary, ship);

        put(ship, destination);
    }
}

char Computer::handle_shot(Square target)
{
    bool hit = has_ship_marker(primary.at(target.y, target.x));

    char result = (hit) ? '!' : 'x';

    primary.set(target.y, target.x, result);

    if (hit)
    {
        std::cout << "Hit!\n";
        ++damage;
    }
    else
    {
        std::cout << "Miss.\n";
    }

    return result;
}

Square Computer::choose_move()
{
    auto target = ai.decide_coords();

    if (tracking.at(target.y, target.x).marker == blank)
        return target;

    return choose_move();
}