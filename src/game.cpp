#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "game.h"

// § Game
void Game::run()
{
    std::cout << "~*~* Welcome to BATTLESHIPS! *~*~\n";

    while (!quit)
    {
        reset();
        play();
        print_summary();
        if (!ask_yes_no("Do you want to play again? "))
            quit = true;
    }

    std::cout << "\nGoodbye!\n";
}

void Game::reset()
{
    user.reset();
    user.set_up_ships();
    pc.reset();
    pc.set_up_ships();
}

void Game::play()
{
    while (!is_over())
    {
        if (turn == 'H') // human
        {
            wait_for_input("Press enter to continue. ");
            Square target = user.get_move(">>> ");
            Marker result = pc.receive_attack(target);
            user.update(target, result);
        }
        else if (turn == 'C') // computer
        {
            std::cout << "Computer's turn";
            delayed_print("...", 400);
            std::cout << ' ';
            Square target = pc.decide_move();
            Marker result = user.receive_attack(target);
            pc.update(target, result);
        }
        std::cout << '\n';
        swap_turn();
    }
}

void Game::print_summary() const
{
    if (user.defeated())
        std::cout << "Sorry, you lost!\n";
    else if (pc.defeated())
        std::cout << "Congratulations, you won!\n";
}

bool Game::is_over() const
{
    return (user.defeated() || pc.defeated());
}

// § Helper I/O functions
void delayed_print(const std::string& s, int pause)
{
    for (char ch : s)
    {
        std::cout << ch << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(pause));
    }
}

void wait_for_input(const std::string& prompt)
{
    std::cout << prompt;
    // std::cin >> std::ws;
    std::string s;
    std::getline(std::cin, s);
}

bool ask_yes_no(const std::string& prompt)
{
    std::cout << prompt;

    while (true)
    {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream input{line};
        char ch = ' ';
        input >> ch;
        ch = tolower(ch); // Allow uppercase.
        if (ch == 'y')
            return true;
        if (ch == 'n')
            return false;
        std::cerr << "Please enter y or n: ";
    }
}