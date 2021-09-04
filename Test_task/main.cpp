/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     Test task
 * 1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и
 * map[i];
 * 2.удалить случайное число элементов (не более 15) в каждом контейнере;
 * 3.после этого провести синхронизацию, чтобы в vector и map остались
 * только имеющиеся в обоих контейнерах элементы (дубликаты не удалять).
 * @version   0.1
 * @date      03-09-2021
 * @copyright Copyright (c) 2021
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <vector>

template <typename Container>
constexpr void PrintContainer(const Container& container) {
  using Type = typename std::allocator_traits<Container>::value_type;
  if constexpr (std::is_same_v<Container, std::vector<Type>>) {
    std::copy(container.begin(), container.end(),
              std::ostream_iterator<Type>(std::cout, " "));
    std::cout << std::endl;
  } else {
    for (auto&& [key, value] : container)
      std::cout << key << " " << value << std::endl;
  }
}

template <typename Container>
constexpr void RemoveLastElements(Container& container) {
  using Type = typename std::allocator_traits<Container>::value_type;

  std::random_device rnd_remove_n_counts;
  std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);

  auto n_count_remove{dist_remove_n_counts(rnd_remove_n_counts)};
  if constexpr (std::is_same_v<Container, std::vector<Type>>) {
    for (size_t i{}; i < n_count_remove; ++i) container.pop_back();
  } else {
    while (n_count_remove) {
      auto last{container.rbegin()};
      auto tmp{last->second - n_count_remove};
      if (tmp < 0) {
        n_count_remove -= last->second;
        container.erase(last->first);
      } else {
        last->second = tmp;
        if (last->second == 0) container.erase(last->first);
        n_count_remove = 0;
      }
    }
  }
}

void SyncContainers(std::vector<int32_t>& vec,
                    std::map<int32_t, int64_t>& map) {
  std::sort(vec.begin(), vec.end());
  for (size_t i{}; i < vec.size(); ++i) {
    auto iter{map.find(vec.back())};
    if (iter == map.end()) {
      auto it_remove{std::remove(vec.begin(), vec.end(), vec.back())};
      vec.erase(it_remove, vec.end());
    }
  }

  std::map<int32_t, int64_t> new_map;
  for (auto&& [key_digit, n_digits] : map)
    if (std::binary_search(vec.begin(), vec.end(), key_digit))
      new_map[key_digit] = n_digits;
  map = std::move(new_map);
}

bool SyncVectorMapCheck(std::vector<int32_t>& vec,
                        std::map<int32_t, int64_t>& map) {
  std::set<int32_t> vec_unique_digits;
  for (auto&& i : vec) vec_unique_digits.insert(i);

  std::set<int32_t> map_unique_digits;
  for (auto&& i : map) map_unique_digits.insert(i.first);

  return vec_unique_digits == map_unique_digits;
}

int main() {
  system("cls");

  // TODO Clean all unused variables.
  // TODO Clean console output.
  std::random_device rnd_plane_digits;
  std::uniform_int_distribution<int32_t> dist_plane_digits(1, 9);

  std::cout << "Enter the vector's size. Minimum size is 15: ";
  size_t size{};
  std::cin >> size;
  std::cout << "vector init:\t";
  std::vector<int32_t> vec(size);
  for (auto&& i : vec) i = dist_plane_digits(rnd_plane_digits);
  PrintContainer(vec);

  std::cout << "Enter the map's size. Minimum size is 15: ";
  std::cin >> size;
  std::map<int32_t, int64_t> map;  // TODO check int64_t for invalid
  for (size_t i{}; i < size; ++i) ++map[(dist_plane_digits(rnd_plane_digits))];
  PrintContainer(map);

  RemoveLastElements(vec);
  std::cout << "vector erased:\t";
  PrintContainer(vec);

  RemoveLastElements(map);
  std::cout << "map erased:\n";
  PrintContainer(map);

  SyncContainers(vec, map);
  std::cout << "\nvector sync:\t";
  PrintContainer(vec);
  std::cout << "map sync:\n";
  PrintContainer(map);

  // TODO unit-tests
  std::cout << "vector and map are";
  std::cout << (SyncVectorMapCheck(vec, map) ? "\x1b[32m synchronized"
                                             : "\x1b[31m not synchronized");
  std::cout << "\x1b[0m";
}