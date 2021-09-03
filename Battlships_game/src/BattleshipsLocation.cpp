/**
 * @file      BattleShipsLocation.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     Location of ships on the battlefield for each player
 * @version   0.3
 * @date      25-02-2021
 * @copyright Copyright (c) 2021
 */

#include "BattleShipsLocation.h"

void BattleShipsLocation::printField() const {
  for (size_t i{}; i < 10; ++i) {
    if (0 == i) {
      std::cout << "   ";
      for (size_t j{}; j < 10; ++j) std::cout << j << "  ";
      std::cout << "\n";
    }
    std::cout << i << "  ";
    for (size_t j{}; j < 10; ++j) std::cout << locationField_[i][j] << "  ";
    std::cout << "\n";
  }
  std::cout << "\n";
}

void BattleShipsLocation::fillField() {
  size_t count{};
  Coordinates coord{}, coordBegin{}, coordEnd{};
  std::cout << "Place your ships on the battlefield\n";
  do {
    std::cout << "\n   The single-deck ship\n";
    printField();
    std::cout << "Enter coordinates of the \"" << count + 1
              << "\" single-deck ship: ";
    std::cin >> coord.x_ >> coord.y_;

    if (fillShip(coord))
      ++count;
    else
      printErrorIndex();
  } while (count < 4);
  count = 0;

  do {
    std::cout << "\n   The two-deck ship\n";
    std::cout << "Enter coordinates of the \"" << count + 1
              << "\" two-deck ship\n";
    printField();
    std::cout << "Begin coordinates of the ship:\t";
    std::cin >> coordBegin.x_ >> coordBegin.y_;
    std::cout << "End coordinates of the ship:\t";
    std::cin >> coordEnd.x_ >> coordEnd.y_;

    if (fillShip(coordBegin, coordEnd, 2))
      ++count;
    else
      printErrorIndex();
  } while (count < 3);
  count = 0;

  do {
    std::cout << "\n   The three-deck ship\n";
    std::cout << "Enter coordinates of the \"" << count + 1
              << "\" three-deck ship\n";
    printField();
    std::cout << "Begin coordinates of the ship:\t";
    std::cin >> coordBegin.x_ >> coordBegin.y_;
    std::cout << "End coordinates of the ship:\t";
    std::cin >> coordEnd.x_ >> coordEnd.y_;

    if (fillShip(coordBegin, coordEnd, 3))
      ++count;
    else
      printErrorIndex();
  } while (count < 2);
  count = 0;

  do {
    std::cout << "\n   The four-deck ship\n";
    std::cout << "Enter coordinates of the four-deck ship\n";
    printField();
    std::cout << "Begin coordinates of the ship:\t";
    std::cin >> coordBegin.x_ >> coordBegin.y_;
    std::cout << "End coordinates of the ship:\t";
    std::cin >> coordEnd.x_ >> coordEnd.y_;

    if (fillShip(coordBegin, coordEnd, 4))
      ++count;
    else
      printErrorIndex();
  } while (count < 1);
}

bool BattleShipsLocation::fillShip(const Coordinates& coord) {
  if (coord.x_ > 9 || coord.y_ > 9) return false;

  if (locationField_[coord.x_][coord.y_] == 'o') {
    return false;
  } else if (coord.x_ != 0 && locationField_[coord.x_ - 1][coord.y_] == 'o') {
    return false;
  } else if (coord.x_ != 9 && locationField_[coord.x_ + 1][coord.y_] == 'o') {
    return false;
  } else if (coord.y_ != 0 && locationField_[coord.x_][coord.y_ - 1] == 'o') {
    return false;
  } else if (coord.y_ != 9 && locationField_[coord.x_][coord.y_ + 1] == 'o') {
    return false;
  } else if (coord.x_ != 0 && coord.y_ != 0 &&
             locationField_[coord.x_ - 1][coord.y_ - 1] == 'o') {
    return false;
  } else if (coord.x_ != 0 && coord.y_ != 9 &&
             locationField_[coord.x_ - 1][coord.y_ + 1] == 'o') {
    return false;
  } else if (coord.x_ != 9 && coord.y_ != 0 &&
             locationField_[coord.x_ + 1][coord.y_ - 1] == 'o') {
    return false;
  } else if (coord.x_ != 9 && coord.y_ != 9 &&
             locationField_[coord.x_ + 1][coord.y_ + 1] == 'o') {
    return false;
  }

  locationField_[coord.x_][coord.y_] = 'o';
  return true;
}

bool BattleShipsLocation::fillShip(const Coordinates& begin, const Coordinates& end,
                              const uint16_t& shipSize) {
  if (begin.x_ > 9 || begin.y_ > 9 || end.x_ > 9 || end.y_ > 9) return false;

  if (begin.x_ == end.x_) {
    if (end.y_ - begin.y_ != shipSize - 1) return false;

    for (size_t i{begin.y_}; i <= end.y_; ++i) {
      if (locationField_[begin.x_][i] == 'o') {
        return false;
      } else if (begin.x_ != 0 && locationField_[begin.x_ - 1][i] == 'o') {
        return false;
      } else if (begin.x_ != 9 && locationField_[begin.x_ + 1][i] == 'o') {
        return false;
      }
    }

    if (begin.x_ != 0 && begin.y_ != 0 &&
        locationField_[begin.x_ - 1][begin.y_ - 1] == 'o') {
      return false;
    } else if (begin.x_ != 9 && begin.y_ != 0 &&
               locationField_[begin.x_ + 1][begin.y_ - 1] == 'o') {
      return false;
    } else if (begin.x_ != 0 && end.y_ != 9 &&
               locationField_[begin.x_ - 1][end.y_ + 1] == 'o') {
      return false;
    } else if (begin.x_ != 9 && end.y_ != 9 &&
               locationField_[begin.x_ + 1][end.y_ + 1] == 'o') {
      return false;
    } else if (begin.y_ != 0 && locationField_[begin.x_][begin.y_ - 1] == 'o') {
      return false;
    } else if (end.y_ != 9 && locationField_[begin.x_][end.y_ + 1] == 'o') {
      return false;
    }

  } else if (begin.y_ == end.y_) {
    if (end.x_ - begin.x_ != shipSize - 1) return false;

    for (size_t i{begin.x_}; i <= end.x_; ++i) {
      if (begin.y_ != 0 && locationField_[i][begin.y_ - 1] == 'o') {
        return false;
      } else if (begin.y_ != 9 && locationField_[i][begin.y_ + 1] == 'o') {
        return false;
      }
    }

    if (begin.x_ != 0 && begin.y_ != 0 &&
        locationField_[begin.x_ - 1][begin.y_ - 1] == 'o') {
      return false;
    } else if (begin.x_ != 0 && begin.y_ != 9 &&
               locationField_[begin.x_ - 1][begin.y_ + 1] == 'o') {
      return false;
    } else if (end.x_ != 9 && end.y_ != 0 &&
               locationField_[end.x_ + 1][end.y_ - 1] == 'o') {
      return false;
    } else if (end.x_ != 9 && end.y_ != 9 &&
               locationField_[end.x_ + 1][end.y_ + 1] == 'o') {
      return false;
    } else if (begin.x_ != 0 && locationField_[begin.x_ - 1][begin.y_] == 'o') {
      return false;
    } else if (begin.x_ != 9 && locationField_[end.x_ + 1][begin.y_] == 'o') {
      return false;
    }
  } else {
    return false;
  }

  if (begin.x_ == end.x_)
    for (size_t i{begin.y_}; i <= end.y_; ++i) locationField_[begin.x_][i] = 'o';
  else
    for (size_t i{begin.x_}; i <= end.x_; ++i) locationField_[i][begin.y_] = 'o';
  return true;
}
