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
#include <random>
#include <set>
#include <vector>

template <typename Container>
constexpr void PrintContainer(const Container& container) {
  using Type = typename std::allocator_traits<Container>::value_type;
  std::copy(container.begin(), container.end(),
            std::ostream_iterator<Type>(std::cout, " "));
  std::cout << std::endl;
}

template <typename Container>
constexpr void RemoveElements(Container& container) {
  using Type = typename std::allocator_traits<Container>::value_type;

  std::random_device rnd_remove_n_counts;
  std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);

  for (size_t i{}; i < dist_remove_n_counts(rnd_remove_n_counts); ++i) {
    if constexpr (std::is_same_v<Container, std::vector<Type>>) {
      container.pop_back();
    } else {
      auto last{container.rbegin()};
      container.erase(container.find(*last));
    }
  }
}

// TODO FIXME
void SyncContainers(std::vector<int32_t>& vec, std::multiset<int32_t>& m_set) {
  for (size_t i{}; i < vec.size(); ++i) {
    auto iter{m_set.find(vec.back())};
    if (iter == m_set.end()) {
      auto it_remove{std::remove(vec.begin(), vec.end(), vec.back())};
      vec.erase(it_remove, vec.end());
    }
  }

  std::multiset<int32_t> temp_m_set;
  auto iter{m_set.begin()};
  for (size_t i{}; i < m_set.size(); ++i) {
    if (std::binary_search(vec.begin(), vec.end(), *iter))
      temp_m_set.insert(*iter);
    ++iter;
  }
  m_set = std::move(temp_m_set);
}

int main() {
  system("cls");
  std::random_device rnd_plane_digits;
  std::uniform_int_distribution<int32_t> dist_plane_digits(1, 9);

  std::cout << "vector init:\t";
  std::vector<int32_t> vec(20);
  for (auto&& i : vec) i = dist_plane_digits(rnd_plane_digits);
  PrintContainer(vec);

  std::cout << "m_set init:\t";
  std::multiset<int32_t> m_set;  // FIXME size
  for (size_t i{}; i < vec.size(); ++i)
    m_set.insert(dist_plane_digits(rnd_plane_digits));
  PrintContainer(m_set);

  RemoveElements(vec);
  std::cout << "vector erased:\t";
  PrintContainer(vec);

  RemoveElements(m_set);
  std::cout << "m_set erased:\t";
  PrintContainer(m_set);

  std::cout << "\nvector sort:\t";
  std::sort(vec.begin(), vec.end());  // TODO перенести в функцию
  PrintContainer(vec);
  std::cout << "m_set:\t\t";
  PrintContainer(m_set);

  SyncContainers(vec, m_set);
  std::cout << "\nvector sync:\t";
  PrintContainer(vec);
  std::cout << "m_set sync:\t";
  PrintContainer(m_set);
}