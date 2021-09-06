/**
 * @file      sync_vector_map.h
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     vector and map synchronize class
 * @version   0.1
 * @date      03-09-2021
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <vector>

class SyncVectorMap {
 public:
  SyncVectorMap() = delete;
  SyncVectorMap(std::vector<int32_t>& vec_out,
                std::map<int32_t, int64_t>& map_out);
  ~SyncVectorMap() = default;

 private:
  bool SyncRoutine();

  bool SyncCheck();

  void RemoveLastVectorElements() {
    std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);
    auto n_count_remove{dist_remove_n_counts(rnd_remove_n_counts_)};

    for (size_t i{}; i < n_count_remove; ++i) vec_.pop_back();
  }

  void RemoveLastMapElements();

 private:
  std::vector<int32_t> vec_;
  std::map<int32_t, int64_t> map_;
  std::random_device rnd_remove_n_counts_;
};
