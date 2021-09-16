/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     implemented types of sorting
 * @version   0.1
 * @date      02-03-2021
 * @copyright Copyright (c) 2021
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Timer.h"

/**
 * @brief     QuickSort with insertion sort
 */
template <typename T>
constexpr void quickSort(T begin, T end) noexcept;

template <typename T>
constexpr void InsertSort(T& array) noexcept;

template <typename T>
constexpr void quickSort(T begin, T end) noexcept {
  if (end - begin < 10) {
    size_t size = static_cast<size_t>(end - begin);
    for (int i = 1; i < size; ++i) {
      for (int j = i; j > 0 && begin[j - 1] > begin[j]; --j)
        std::swap(begin[j - 1], begin[j]);
    }
    return;
  }

  T i = begin;
  T j = end;
  auto pivot =
      std::max(*(begin + ((end - begin) >> 1)), std::max(*(begin), *(end - 1)));

  while (i < j) {
    while (*(i) < pivot) ++i;
    while (*(j) > pivot) --j;
    if (i <= j) std::swap(*(i++), *(j--));
  }

  if (j > begin) quickSort(begin, j);
  if (end > i) quickSort(i, end);
}

template <typename T>
constexpr void InsertSort(T& array) noexcept {
  for (int i = 1; i < array.size(); ++i) {
    for (int j = i; j > 0 && array[j - 1] > array[j]; --j)
      std::swap(array[j - 1], array[j]);
  }
}

template <typename T>
constexpr void selectSort(T& array) noexcept {
  for (int i = array.size() - 1; i >= 0; --i) {
    int max_index = 0;
    for (int j = 0; j <= i; ++j)
      if (array[j] > array[max_index]) max_index = j;
    std::swap(array[i], array[max_index]);
  }
}

template <typename T>
constexpr void bubbleSort(T& array) noexcept {
  for (int i = 0; i < array.size(); ++i)
    for (int j = 0; j < array.size() - i - 1; ++j)
      if (array[j] > array[j + 1]) std::swap(array[j], array[j + 1]);
}

int main() {
  system("cls");

  std::vector<int32_t> array(1000000);
  for (auto&& i : array) i = std::random_device()();

  {
    Timer t;
    std::cout << "\nstd::sort:         ";
    std::vector<int32_t> sort_vec(array);
    std::sort(sort_vec.begin(), sort_vec.end());
    std::cout << "\nTime elapsed:       " << t.elapsed() << "\n";
  }

  {
    Timer t;
    std::cout << "\nQuick sorting:     ";
    std::vector<int32_t> q_sortVec(array);
    quickSort(q_sortVec.begin(), q_sortVec.end());
    std::cout << "\nTime elapsed:       " << t.elapsed() << "\n";
  }

  // {
  //   Timer t;
  //   std::cout << "\nInsert sorting:    ";
  //   std::vector<int32_t> insert_sort_vec(array);
  //   InsertSort(insert_sort_vec);
  //   std::cout << "\nTime elapsed:       " << t.elapsed() << "\n";
  // }

  std::cout << "\x1b[37m" << std::endl;

  return 0;
}
