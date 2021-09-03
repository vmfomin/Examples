/**
 * @file      Battleships.h
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     The battleships game main class
 * @version   0.3
 * @date      09-03-2021
 * @copyright Copyright (c) 2021
 */

#ifndef INC_BATTLESHIPS_H
#define INC_BATTLESHIPS_H

#include "BattleShipsLocation.h"

class Battleships {
 public:
  /**
   * @brief     Construct a new Battleships game object
   */
  Battleships() {
    for (size_t i{}; i < 10; ++i) {
      for (size_t j{}; j < 10; ++j) {
        playerOneDisplayConsole_[i][j] = '.';
        playerTwoDisplayConsole_[i][j] = '.';
      }
    }
  }

  /**
   * @brief     Destroy the Battleships game object
   */
  virtual ~Battleships() = default;

  /**
   * @brief     launch of the sea battle game
   */
  void launchBattle();

 private:
  /**
   * @brief     Location of ships on the battlefield for each player
   */
  BattleShipsLocation playerOneShipsLocation_;
  BattleShipsLocation playerTwoShipsLocation_;

  /**
   * @brief     The player's playing field is displayed in the console:
   * 'x' -- shot;
   * '*' -- missed
   * '.' -- not shooted place
   */
  char playerOneDisplayConsole_[10][10];
  char playerTwoDisplayConsole_[10][10];

  /**
   * @brief     printing the game screen
   * @param     odd           whose move
   */
  void printScreen(const uint16_t odd);

  /**
   * @brief     shooting routine
   * @param     shipsLocation        location of player ships
   * @param     playerDisplayConsole player's playing field is displayed in
   * the console
   * @param     nShoots              count of shoots for each player
   */
  void shoot(BattleShipsLocation& shipsLocation,
             char playerDisplayConsole[10][10], uint16_t& nShoots);
};

#endif  // INC_BATTLESHIPS_H