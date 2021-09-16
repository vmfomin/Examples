#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Person {
 public:
  Person() = delete;
  template <typename T, typename = std::enable_if_t<
                            !std::is_base_of_v<Person, std::decay_t<T>> &&
                            !std::is_integral_v<std::remove_reference_t<T>>>>
  explicit Person(T&& surname, T&& name)
      : surname_(std::forward<T>(surname)), name_(std::forward<T>(name)) {
    for (auto&& i : surname_) i = std::toupper(i);
    for (auto&& i : name_) i = std::toupper(i);
  }

  explicit Person(const char* surname, const char* name)
      : surname_(std::move(surname)), name_(std::move(name)) {
    for (auto&& i : surname_) i = std::toupper(i);
    for (auto&& i : name_) i = std::toupper(i);
  }

  template <typename T, typename = std::enable_if_t<
                            !std::is_base_of_v<Person, std::decay_t<T>> &&
                            !std::is_integral_v<std::remove_reference_t<T>>>>
  explicit Person(T&& surname) : surname_(std::forward<T>(surname)) {
    for (auto&& i : surname_) i = std::toupper(i);
  }

  ~Person() = default;

  bool operator<(const Person& rhs) const {
    for (size_t i = 0; i < surname_.size(); ++i) {
      if (surname_[i] == rhs.surname_[i]) {
        if (surname_.size() < rhs.surname_.size()) return true;
        continue;
      }
      if (surname_[i] < rhs.surname_[i]) return true;
      return false;
    }

    for (size_t i = 0; i < name_.size(); ++i) {
      if (name_[i] == rhs.name_[i]) {
        if (name_.size() < rhs.name_.size()) return true;
        continue;
      }
      if (name_[i] < rhs.name_[i]) return true;
      return false;
    }
    return false;
  };

  friend std::ostream& operator<<(std::ostream& out, const Person& person) {
    out << person.surname_ << " " << person.name_ << std::endl;
    return out;
  }

 private:
  std::string name_ = "";
  std::string surname_ = "";
};

template <typename... Args>
std::unique_ptr<Person> MakePerson(Args&&... arg) {
  return std::make_unique<Person>(Person(std::forward<Args>(arg)...));
}

int main() {
  system("cls");
  std::vector<std::unique_ptr<Person>> persons;

  for (size_t i = 0; i < 3; ++i) {
    std::string surname;
    std::cin >> surname;

    std::string name;
    std::cin >> name;

    persons.emplace_back(MakePerson(surname, name));
  }
  persons.emplace_back(MakePerson("Meyers"));
  persons.emplace_back(MakePerson("Sutter", "herb"));
  std::cout << std::endl;

  std::cout << "Before\n";
  for (auto&& i : persons) std::cout << *i;
  std::cout << std::endl;

  std::cout << "sorted\n";
  std::sort(persons.begin(), persons.end(),
            [](const auto& lhs, const auto& rhs) { return *lhs < *rhs; });
  for (auto&& i : persons) std::cout << *i;
}
