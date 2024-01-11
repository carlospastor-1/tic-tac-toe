#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Graph.h"
#include "GameState.h"
#include <fstream>
#include <string>

#include "ai.h"

int grid = 3;

Vec PlayerMove(GameState game) {
    int x, y;
    std::cout << "Enter move for player "<< (game.currentTurn ? "O" : "X") <<std::endl;
    std::cin >> x;
    std::cin >> y;

    return Vec(x, y);
}

void PlayAgainst(Vec (*opponentMove)(GameState)) {
    system("clear");

    GameState game(grid);

    std::cout << game << std::endl;

    Vec move;

    std::string input = "";

    while (!game.done) {

        if (game.currentTurn) {
            move = opponentMove(game);
        }
        else {
            move = PlayerMove(game);
        }

        if (move.x < 0 || move.y < 0 || move.x > game.size || move.y > game.size || !game.play(move.x, move.y)) {
            std::cout << "Invalid move for " << (game.currentTurn ? "O" : "X") << std::endl;
            continue;
        }

        system("clear");

        std::cout << game << std::endl;
    }
    
    if (game.hasWon(0)) {
        std::cout << "Player X has won" << std::endl;
    }
    else if (game.hasWon(1)) {
        std::cout << "Player O has won" << std::endl;
    }
    else {
        std::cout << "Draw!" << std::endl;
    }

    std::cin.ignore();
    std::cin.ignore();
}

void read() {
    std::ifstream file("settings.txt", std::ios::in);
    std::string temp, temp1;

    if (file.is_open()) {
        while(getline(file, temp1)) {
            temp+=temp1;
        }
        file.close();

        if (temp == "") {
            return;
        }

        grid = stoi(temp);
    }
}

void main_menu() {
    read();

    system("clear");
    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl << std::endl;

    std::cout << "\033[33m";
    std::cout << "========================" << std::endl;
    std::cout << "By Alfred & Ben & Carlos" << std::endl;
    std::cout << "========================" << std::endl << std::endl;
    std::cout << "\033[0m";

    std::cout << "Please enter an option:" << std::endl << std::endl;

    std::cout << "1. Player vs Player" << std::endl;
    std::cout << "2. Player vs AI" << std::endl;
    std::cout << "3. Player vs SmartAI" << std::endl;
    std::cout << "4. Settings" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void settings() {
    std::string dummy;
    read();

    std::cout << "Current setting is a " << grid << "X" << grid << std::endl;
    std::cout << "Enter a number to be the size of the grid." << std::endl;
    int change;
    std::cin >> change;

    std::ofstream file;
    file.open("settings.txt", std::ios::out | std::ios::trunc);

    while (change < 1) {
        std::cout << "Please enter at least 1." << std::endl;
        std::cin >> change;
    }

    if (file.is_open()) {
        file << change << std::endl;
    }

    file.close();

    std::cout << "Successfully updated setting to " << change << "x" << change << ". Press enter to continue." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

#endif