/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     Задание 4. Реализация симуляции банкомата.
 * Требуется реализовать упрощённую симуляцию работы банкомата. В банкомате
 * могут храниться только бумажные купюры номиналом от 100 до 5000 рублей.
 * Максимально в банкомате может храниться только 1000 купюр. Все они
 * записываются в отдельный файл. У банкомата, как у устройства, две основных
 * операции — снятие денег пользователем и наполнение деньгами инкассаторами
 * банка.
 * Наполнение банкомата происходит, если при старте программы в консоль вводится
 * символ плюс “+”.  Количество купюр рассчитывается так, чтобы банкомат был
 * заполнен полностью. Все купюры при этом выбираются случайным образом.
 * Если на старте программы в консоль вводится минус (“-”), то симулируется
 * снятие пользователем денег. Пользователь указывает сумму с точностью до 100
 * рублей. Мы будем считать, что каждый клиент обладает неограниченным балансом
 * в системе и теоретически может снять любую сумму. На практике, если данная
 * сумма не может быть снята из-за отсутствия подходящих денег в машине,
 * показывается сообщение, что эта операция невозможна.
 * После выполнения любой из операций программа завершает выполнение. Состояние
 * банкомата должно храниться в отдельном бинарном файле, автономно.
 * @version   0.1
 * @date      05-04-2021
 * @copyright Copyright (c) 2021
 */

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

void atmInitStatus(std::map<int32_t, int32_t>&, uint32_t&);
void addCash(std::map<int32_t, int32_t>&, uint32_t&);
void outputCash(std::map<int32_t, int32_t>&, uint32_t&);
void computeBanknote(std::map<int32_t, int32_t>&, int32_t&, const int32_t);
void changeStatusAtm(const std::map<int32_t, int32_t>&);
bool isWithdrawAtmCheck(std::map<int32_t, bool>&);
void withdraw(int32_t&, int32_t&, const int32_t, std::map<int32_t, bool>&,
              std::map<int32_t, int32_t>&);

void computeBanknote(std::map<int32_t, int32_t>& atm, int32_t& money,
                     const int32_t denomination) {
  if (0 == denomination) return;

  auto banknoteKey = atm.find(denomination);
  if (banknoteKey->second != 0) {
    int32_t nDenominationBanknotes = money / denomination;
    if (nDenominationBanknotes < banknoteKey->second) {
      money -= nDenominationBanknotes * banknoteKey->first;
      banknoteKey->second -= nDenominationBanknotes;
    } else {
      money -= banknoteKey->first * banknoteKey->second;
      banknoteKey->second = 0;
    }
  }
}

void changeStatusAtm(const std::map<int32_t, int32_t>& atm) {
  std::ofstream bank("../bank.bin", std::ios::binary);
  if (!bank) {
    std::cout << "Error: could not be opened!";
    return;
  }

  for (const auto& i : atm) bank << i.first << " " << i.second << std::endl;
  bank.close();
}

void atmInitStatus(std::map<int32_t, int32_t>& atm, uint32_t& nBanknotes) {
  std::ifstream bank("../bank.bin", std::ios::binary);
  if (!bank) {
    std::cout << "Error: could not be opened!";
    return;
  }

  for (auto iter = atm.begin(); iter != atm.end(); ++iter) {
    int32_t banknote = 0;
    bank >> banknote;
    if (banknote == iter->first) bank >> iter->second;
  }

  for (const auto& i : atm) nBanknotes += i.second;
  bank.close();
}

void addCash(std::map<int32_t, int32_t>& atm, uint32_t& nBanknotes) {
  if (1000 == nBanknotes) {
    std::cout << "Sorry. The ATM is full. Please, select another operation";
    return;
  }

  std::cout << "Enter your cash to ATM. For exit enter \"0\"\n";
  while (true) {
    int32_t banknote;
    std::cin >> banknote;
    if (0 == banknote) break;

    auto banknoteKey = atm.find(banknote);
    if (banknote == banknoteKey->first) {
      ++banknoteKey->second;
      ++nBanknotes;
    } else {
      std::cout << "Error: invalid banknote!" << std::endl;
    }

    if (1000 == nBanknotes) {
      std::cout << "The ATM is full. You can only withdraw cash." << std::endl;
      break;
    }
  }
  changeStatusAtm(atm);
}

bool isWithdrawAtmCheck(std::map<int32_t, bool>& isWithdrawBanknotes) {
  bool isCash = false;
  for (auto&& i : isWithdrawBanknotes) isCash += i.second;
  return isCash;
}

void withdraw(int32_t& money, int32_t& currentBanknoteToWithdraw,
              const int32_t denomination,
              std::map<int32_t, bool>& isWithdrawBanknotes,
              std::map<int32_t, int32_t>& atm) {
  if (money >= denomination && isWithdrawBanknotes[denomination] &&
      atm[denomination] != 0) {
    computeBanknote(atm, money, denomination);
    currentBanknoteToWithdraw = denomination;
  } else {
    isWithdrawBanknotes[denomination] = false;
  }
}

void outputCash(std::map<int32_t, int32_t>& atm, uint32_t& nBanknotes) {
  if (0 == nBanknotes) {
    std::cout << "Sorry. The ATM is empty. Please, select another operation";
    return;
  }

  std::cout << "Enter the withdrawal amount: ";
  int32_t money = 0;
  while (true) {
    std::cin >> money;
    if (0 == money % 100 && 0 != money)
      break;
    else
      std::cout
          << "Invalid amount, the amount of the requested funds must be a "
             "multiple of 100\n";
  }

  int32_t maxSumAtm = 0;
  for (auto& i : atm) maxSumAtm += i.first * i.second;

  std::map<int32_t, int32_t> stableAtm(atm);

  std::map<int32_t, bool> isWithdrawBanknotes = {{100, true},  {200, true},
                                                 {500, true},  {1000, true},
                                                 {2000, true}, {5000, true}};
  int32_t currentBanknoteToWithdraw = 0;
  while (isWithdrawAtmCheck(isWithdrawBanknotes)) {
    if (money <= maxSumAtm) {
      int32_t tempMoney = money;
      for (auto iter = atm.rbegin(); iter != atm.rend() && tempMoney != 0;
           ++iter) {
        if (isWithdrawBanknotes[iter->first])
          withdraw(tempMoney, currentBanknoteToWithdraw, iter->first,
                   isWithdrawBanknotes, atm);
      }

      if (0 == tempMoney) {
        changeStatusAtm(atm);
        std::cout << "Amount of funds withdrawn: " << money;
        for (auto&& iter : isWithdrawBanknotes) iter.second = false;
      } else {
        auto findBanknote{isWithdrawBanknotes.find(currentBanknoteToWithdraw)};
        findBanknote->second = false;

        for (auto&& iter : isWithdrawBanknotes)
          if (iter.first < currentBanknoteToWithdraw) iter.second = true;

        atm = stableAtm;
        if (!isWithdrawAtmCheck(isWithdrawBanknotes))
          std::cout
              << "The operation cannot be performed: there are not enough "
                 "banknotes of the required denomination!\n";
      }
    } else {
      std::cout << "Insufficient funds at the ATM to withdraw cash";
      break;
    }
  }
}

int main() {
  std::cout << "\x1b[2J";
  std::map<int32_t, int32_t> atm = {{100, 0},  {200, 0},  {500, 0},
                                    {1000, 0}, {2000, 0}, {5000, 0}};
  uint32_t nBanknotes = 0;
  atmInitStatus(atm, nBanknotes);

  std::cout << "Do you want to withdraw or deposit cash?\n"
            << "Enter \"-\" for withdraw or \"+\" for deposit cash:"
            << std::endl;
  char choice;

  do {
    std::cin >> choice;
  } while ('-' != choice && '+' != choice);

  '+' == choice ? addCash(atm, nBanknotes) : outputCash(atm, nBanknotes);

  std::cout << "\x1b[0m" << std::endl;
  return 0;
}