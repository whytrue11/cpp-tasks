#include "phonebook.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

bool Phonebook::empty() const noexcept
{
  return contacts_.empty();
}

size_t Phonebook::size() const noexcept
{
  return contacts_.size();
}

void Phonebook::erase(const iterator& contactIt)
{
  contacts_.erase(contactIt);
}

void Phonebook::insert(const iterator& contactIt, const Phonebook::PhoneContact& contact)
{
  contacts_.insert(contactIt, contact);
}

void Phonebook::pushBack(const PhoneContact& contact)
{
  contacts_.push_back(contact);
}

Phonebook::iterator Phonebook::begin() noexcept
{
  return contacts_.begin();
}

Phonebook::iterator Phonebook::end() noexcept
{
  return contacts_.end();
}

Phonebook::const_iterator Phonebook::cbegin() const noexcept
{
  return contacts_.cbegin();
}

Phonebook::const_iterator Phonebook::cend() const noexcept
{
  return contacts_.cend();
}

Phonebook::PhoneContact::PhoneContact(const std::string& name, const std::string& number) :
  name_(name),
  number_(number)
{
  if (!std::all_of(number_.begin(), number_.end(), [](char a) { return isdigit(a); }))
  {
    throw std::invalid_argument("Invalid number");
  }
}

std::ostream& operator<<(std::ostream& output, const Phonebook::PhoneContact& phoneContact)
{
  output << phoneContact.number_ << " " << phoneContact.name_;
  return output;
}
