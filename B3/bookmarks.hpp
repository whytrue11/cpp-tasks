#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <map>
#include <string>
#include "phonebook.hpp"

namespace detail
{
  void add(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
    const Phonebook::PhoneContact& phoneContact);

  std::string
  store(const Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, const std::string& bookmark,
    const std::string& newBookmark);

  std::string
  insert(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, const std::string& directionStr,
    const std::string& bookmark, const Phonebook::PhoneContact& phoneContact);

  std::string
  erase(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, const std::string& bookmark);

  std::string
  show(const Phonebook& phonebook, const std::map<std::string, Phonebook::iterator>& bookmarks,
    const std::string& bookmark, std::ostream& output);

  std::string
  move(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, const std::string& bookmark,
    const std::string& stepsStr);
}

#endif
