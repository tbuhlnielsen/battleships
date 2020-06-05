#include <iostream>

#include "game.h"

// ----------------

Battleships::Battleships()
{
    welcome();
}

// ----------------

void Battleships::reset()
{
    user.reset_boards();
    pc.reset_boards();

    user.reset_damage();
    pc.reset_damage();

    user.setup_ships();
    pc.setup_ships();
}

// ----------------

void Battleships::play()
{
    while (!game_is_over())
    {
        if (turn == 'H')
        {
            std::cout << "Your turn... \n";
            user.show_guesses();
            auto target = user.get_move("Enter strike coordinates: ");
            shot_at(target);
        }
        else if (turn == 'C')
        {
            std::cout << "Computer's turn... \n";
            auto target = pc.choose_move();
            shot_at(target);
        }
        std::cout << '\n';
        swap_turn();
    }
}

// ----------------

bool Battleships::game_is_over() const
{
    return (user.defeated() || pc.defeated());
}

// ----------------

void Battleships::end(const std::string& prompt)
{
    report();

    std::cout << prompt;

    for (char ch; std::cin >> ch; )
    {
        if (ch == 'y' || ch == 'Y')
            return; // rematch is true by default
        else if (ch == 'n' || ch == 'N')
        {
            rematch = false;
            return;
        }
    }
}

// ----------------

void Battleships::swap_turn()
{
    turn = (turn == 'H') ? 'C' : 'H';
}

// ----------------

void Battleships::report() const
{
    if (user.defeated())
        std::cout << "Sorry, you lost!\n";
    else if (pc.defeated())
        std::cout << "Congratulations, you won!\n";
}

// ----------------

void Battleships::shot_at(Square target)
{
    if (turn == 'H')
    {
        char result = pc.handle_shot(target);
        user.handle_shot_feedback(target, result);
    }
    else if (turn == 'C')
    {
        char result = user.handle_shot(target);
        pc.handle_shot_feedback(target, result);
    }
}

// ----------------

void welcome()
{
    std::cout << "~*~* Welcome to BATTLESHIPS! *~*~\n";
}