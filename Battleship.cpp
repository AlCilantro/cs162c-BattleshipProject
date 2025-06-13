//
// Created by alexa on 5/25/2025.
//
#include "Battleship.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

int main() {
    char playAgain;
            string choice;
            cout << "\n      Battleship! Take out the enemy CPU to win.\n"
                 << "Game Instructions: There is a 10x10 Grid for each player.\n"
                 << "You can see your ships; You can see the misses or hits on the CPU's Board.\n"
                 << "You will be given five ships:\n"
                 << "Carrier (5 Squares), Battleship (4), 2 Cruisers (3), Destroyer (2)\n"
                 << "\nA coin flip will decide who goes first." << endl;

    do {
        Coin c;
        cout << "Heads or Tails (H/T)? ";
        cin >> choice;
        string result = c.getSide();
        cout << "Coin flip result: " << result << endl;

        bool playerStarts = ((choice == "H" && result == "Heads") || (choice == "T" && result == "Tails"));
        if (playerStarts) cout << "Player starts." << endl;
        else cout << "CPU starts.\n" << endl;

        Game game(playerStarts);
        game.play();

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
        choice = tolower(playAgain);

        cin.clear();
        cin.ignore(256, '\n');

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing Battleship!" << endl;
    return 0;
}