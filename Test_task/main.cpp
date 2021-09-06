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

#include "header/sync_vector_map.h"

bool SyncVectorMapCheck(std::vector<int32_t>& vec,
                        std::map<int32_t, int64_t>& map) {
  std::set<int32_t> vec_unique_digits;
  for (auto&& i : vec) vec_unique_digits.insert(i);

  std::set<int32_t> map_unique_digits;
  for (auto&& i : map) map_unique_digits.insert(i.first);

  return vec_unique_digits == map_unique_digits;
}

bool TestSyncVectorMapClass() {
  bool is_sync{true};
  std::random_device rnd_plane_digits;
  std::uniform_int_distribution<int32_t> dist_plane_digits(1, 9);

  std::random_device rnd_size;
  std::uniform_int_distribution<size_t> dist_rnd_size(15, 10000);

  const size_t test_loops{10000};
  std::vector<bool> checks(test_loops);
  for (size_t i{}; i < test_loops; ++i) {
    std::vector<int32_t> vec(dist_rnd_size(rnd_size));
    for (auto&& i : vec) i = dist_plane_digits(rnd_plane_digits);

    std::map<int32_t, int64_t> map;
    for (size_t i{}; i < dist_rnd_size(rnd_size); ++i)
      ++map[(dist_plane_digits(rnd_plane_digits))];

    SyncVectorMap sync_vector_map(vec, map);
    checks[i] = SyncVectorMapCheck(vec, map);
  }

  for (auto&& i : checks) is_sync &= i;
  return is_sync;
}

int main() {
  system("cls");

  std::cout << "vector and map are";
  std::cout << (TestSyncVectorMapClass() ? "\x1b[32m synchronized"
                                         : "\x1b[31m not synchronized");
  std::cout << "\x1b[0m" << std::endl;
}