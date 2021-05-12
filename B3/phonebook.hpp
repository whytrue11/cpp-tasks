#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <list>
#include <iosfwd>
#include <string>

class Phonebook
{
public:
  class PhoneContact
  {
  public:
    PhoneContact() = default;
    PhoneContact(const std::string& name, const std::string& number);

    friend std::ostream& operator<<(std::ostream& output, const Phonebook::PhoneContact& phoneContact);

  private:
    std::string name_;
    std::string number_;
  };

  using value_type = PhoneContact;
  using reference = PhoneContact&;
  using iterator = typename std::list<PhoneContact>::iterator;
  using const_iterator = typename std::list<PhoneContact>::const_iterator;

  bool empty() const noexcept;
  size_t size() const noexcept;

  void erase(const iterator& contactIt);
  void insert(const iterator& contactIt, const PhoneContact& contact);
  void pushBack(const PhoneContact& contact);

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

private:
  std::list<PhoneContact> contacts_;
};

#endif
