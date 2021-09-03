/**
 * @file      Battleships.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     The battleships game main class
 * @version   0.3
 * @date      09-03-2021
 * @copyright Copyright (c) 2021
 */

#include "Battleships.h"

void Battleships::launchBattle() {
  std::cout << "\x1b[2JThe first player places the ships on the battlefield:\n";
  playerOneShipsLocation_.fillField();
  std::cout << "The first player ships location's battlefield:\n";
  playerOneShipsLocation_.printField();

  std::cout << "\nThe second player places the ships on the battlefield:\n";
  playerTwoShipsLocation_.fillField();
  std::cout << "The second ships location's battlefield:\n";
  playerTwoShipsLocation_.printField();

  uint16_t countOne{}, countTwo{}, odd{};
  while (true) {
    if (0 == (odd & 1)) {
      std::cout << "\x1b[2J\t\t\t   First player move\n";
      printScreen(odd);
      shoot(playerTwoShipsLocation_, playerTwoDisplayConsole_, countOne);
    } else {
      std::cout << "\x1b[2J\t\t\t  Second player move\n";
      printScreen(odd);
      shoot(playerOneShipsLocation_, playerOneDisplayConsole_, countTwo);
    }

    if (20 == countOne) {
      std::cout << "\x1b[2J";
      printScreen(odd);
      std::cout << "\n\x1b[36mThe first player won!\x1b[37m\n";
      break;
    } else if (20 == countTwo) {
      std::cout << "\x1b[2J";
      printScreen(odd);
      std::cout << "\n\x1b[36mThe second player won!\x1b[37m\n";
      break;
    }
    ++odd;
  }
}

void Battleships::printScreen(const uint16_t odd) {
  std::cout
      << (1 == (odd & 1)
              ? "\x1b[31m\t    Player one\x1b[37m\t\t\t\t    Player two\n"
              : "\t    Player one\t\t\t\t    \x1b[31mPlayer two\n\x1b[37m");
  std::cout << "\n";
  for (size_t i{}; i < 10; ++i) {
    if (0 == i) {
      std::cout << "   ";
      for (size_t j{}; j < 10; ++j) std::cout << j << "  ";
      std::cout << "  ||\t    ";
      for (size_t j{}; j < 10; ++j) std::cout << j << "  ";
      std::cout << "\n";
    }
    std::cout << i << "  ";
    for (size_t j{}; j < 10; ++j)
      std::cout << playerOneDisplayConsole_[i][j] << "  ";
    std::cout << "  ||    " << i << "  ";

    for (size_t j{}; j < 10; ++j)
      std::cout << playerTwoDisplayConsole_[i][j] << "  ";
    std::cout << "\n";
  }
  std::cout << "\n";
}

void Battleships::shoot(BattleShipsLocation& shipsLocation,
                        char playerDisplayConsole[10][10], uint16_t& nShoots) {
  do {
    std::cout << "Enter the coordinates to shoot: ";
    uint16_t x, y;
    std::cin >> x >> y;
    if (x > 9 || y > 9) {
      std::cout << "\x1b[31mError: incorrect coordinates!\x1b[37m\n";
      continue;
    }

    if ('o' == shipsLocation.getLocation(x, y) &&
        playerDisplayConsole[x][y] != 'x') {
      playerDisplayConsole[x][y] = 'x';
      std::cout << "\x1b[32mYou hit him!\x1b[37m\n";
      Sleep(350);
      ++nShoots;
      break;
    } else if ('*' == playerDisplayConsole[x][y] ||
               'x' == playerDisplayConsole[x][y]) {
      std::cout << "\x1b[31mYou've already shot at this place!\x1b[37m\n";
      continue;
    } else {
      playerDisplayConsole[x][y] = '*';
      std::cout << "You missed it!\n";
      Sleep(350);
      break;
    }
  } while (true);
}