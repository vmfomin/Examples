/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     placement_new
 * @version   0.1
 * @date      04-07-2021
 * @copyright Copyright (c) 2021
 */

#include <iostream>

class Allocate {
 public:
  Allocate(size_t n) : size_{n}, ptr_{new int32_t[n]} {
    std::cout << n << std::endl;
    for (size_t i{}; i < size_; ++i) ptr_[i] = i * 10;
  };

  size_t getSize() const { return size_; }

  ~Allocate() {
    delete[] ptr_;
    ptr_ = nullptr;
  };

  auto& operator[](const size_t i) { return ptr_[i]; }

 private:
  int32_t* ptr_;
  size_t size_;
};

void func() {
  constexpr size_t n{100000000};
  constexpr size_t rows{5};
  // Allocate* alloc{(Allocate*)operator new(sizeof(Allocate) * rows)};
  // for (size_t i{}; i < rows; ++i) new (alloc + i) Allocate(n);
  // for (size_t i{}; i < rows; ++i) delete (alloc + i);

  std::allocator<Allocate> alloc;
  using traits_t = std::allocator_traits<decltype(alloc)>;
  Allocate* ptr{traits_t::allocate(alloc, rows)};
  for (size_t i{}; i < rows; ++i)
    traits_t::construct(alloc, ptr + i, n - (i * 100000));

  std::cout << "\n" << ptr[2].getSize() << " " << ptr[2][20] << std::endl;

  for (size_t i{}; i < rows; ++i) traits_t::destroy(alloc, ptr + i);
  traits_t::deallocate(alloc, ptr, rows);
}

int main() {
  std::cout << "\x1b[2J";

  func();
  system("PAUSE");
  return 0;
}
