/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief
 * @version   0.1
 * @date      01-09-2021
 * @copyright Copyright (c) 2021
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename InputIterator1, typename InputIterator2,
          typename OutputIterator>
constexpr void Merge(InputIterator1 first_1, InputIterator1 last_1,
                     InputIterator2 first_2, InputIterator2 last_2,
                     OutputIterator out) {
  while (true) {
    if (first_1 == last_1) {
      std::copy(first_2, last_2, out);
      break;
    }

    if (first_2 == last_2) {
      std::copy(first_1, last_1, out);
      break;
    }

    if (*first_1 <= *first_2)
      *out = *(first_1++);
    else
      *out = *(first_2++);
    ++out;
  }
}

int main() {
  system("cls");
  std::vector<int32_t> v1 = {4,  3,  2,  6,  3,  2,  7,  13, 10, 11,
                             12, 15, 13, 20, 21, 25, 30, 33, 23};
  std::vector<int32_t> v2 = {12, 15, 13, 20, 2, 3, 5, 2, 4, 6, 8, 7};
  std::sort(v1.begin(), v1.end());
  std::copy(v1.begin(), v1.end(),
            std::ostream_iterator<int32_t>(std::cout, " "));
  std::cout << std::endl;

  std::sort(v2.begin(), v2.end());
  std::copy(v2.begin(), v2.end(),
            std::ostream_iterator<int32_t>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int32_t> v(v1.size() + v2.size());
  Merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

  std::copy(v.begin(), v.end(), std::ostream_iterator<int32_t>(std::cout, " "));
}
