#include "bookmarks.hpp"

#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

#include "phonebook.hpp"
#include "tools.hpp"

static Phonebook::iterator
moveContactIterator(const Phonebook& phonebook, const Phonebook::iterator& contactIt, int pos);

void detail::add(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
  const Phonebook::PhoneContact& phoneContact)
{
  phonebook.pushBack(phoneContact);
  if (phonebook.size() == 1)
  {
    std::for_each(bookmarks.begin(), bookmarks.end(), [&phonebook](auto& it) { it.second = phonebook.begin(); });
  }
}

std::string detail::store(const Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
  const std::string& bookmark, const std::string& newBookmark)
{
  if (phonebook.empty())
  {
    return "<EMPTY>";
  }

  auto bookmarkIt = bookmarks.find(bookmark);
  if (bookmarkIt == bookmarks.end())
  {
    return "<INVALID BOOKMARK>";
  }
  for (auto& i: newBookmark)
  {
    if (!isalnum(i) && i != '-')
    {
      return "<INVALID BOOKMARK>";
    }
  }

  bookmarks.emplace(newBookmark, bookmarkIt->second);
  return "";
}

std::string detail::insert(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
  const std::string& directionStr, const std::string& bookmark, const Phonebook::PhoneContact& phoneContact)
{
  if (phonebook.empty())
  {
    phonebook.pushBack(phoneContact);
    std::for_each(bookmarks.begin(), bookmarks.end(), [&phonebook](auto& it) { it.second = phonebook.begin(); });
    return "";
  }

  auto bookmarkIt = bookmarks.find(bookmark);
  if (bookmarkIt == bookmarks.end())
  {
    return "<INVALID BOOKMARK>";
  }

  auto contactIt = bookmarkIt->second;

  if (directionStr == "after")
  {
    if (contactIt == phonebook.end())
    {
      return "<INVALID COMMAND>";
    }
    phonebook.insert(++contactIt, phoneContact);
  }
  else if (directionStr == "before")
  {
    phonebook.insert(contactIt, phoneContact);
  }
  else
  {
    return "<INVALID COMMAND>";
  }

  return "";
}

std::string
detail::erase(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, const std::string& bookmark)
{
  if (phonebook.empty())
  {
    return "<EMPTY>";
  }

  auto bookmarkIt = bookmarks.find(bookmark);
  if (bookmarkIt == bookmarks.end())
  {
    return "<INVALID BOOKMARK>";
  }

  auto contactIt = bookmarkIt->second;

  if (contactIt == phonebook.end())
  {
    return "<INVALID COMMAND>";
  }

  auto updateContactIt = contactIt;
  ++updateContactIt;
  if (updateContactIt == phonebook.end() && phonebook.size() != 1)
  {
    updateContactIt = phonebook.begin();
  }

  for (auto& i : bookmarks)
  {
    if (i.second == contactIt)
    {
      i.second = updateContactIt;
    }
  }
  phonebook.erase(contactIt);
  return "";
}

std::string detail::show(const Phonebook& phonebook, const std::map<std::string, Phonebook::iterator>& bookmarks,
  const std::string& bookmark, std::ostream& output)
{
  auto bookmarkIt = bookmarks.find(bookmark);
  if (bookmarkIt == bookmarks.end())
  {
    return "<INVALID BOOKMARK>";
  }

  auto contactIt = bookmarkIt->second;

  if (phonebook.empty())
  {
    return "<EMPTY>";
  }

  if (contactIt == phonebook.cend())
  {
    return "<INVALID COMMAND>";
  }

  output << *contactIt;
  return "";
}

std::string
detail::move(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, const std::string& bookmark,
  const std::string& stepsStr)
{
  if (phonebook.empty())
  {
    return "<EMPTY>";
  }

  int steps = 0;
  auto bookmarkIt = bookmarks.find(bookmark);
  if (bookmarkIt == bookmarks.end())
  {
    return "<INVALID BOOKMARK>";
  }

  if (stepsStr == "first")
  {
    bookmarkIt->second = phonebook.begin();
  }
  else if (stepsStr == "last")
  {
    auto endIt = phonebook.end();
    bookmarkIt->second = --endIt;
  }
  else if (stringToIntConverter(stepsStr, steps))
  {
    try
    {
      bookmarkIt->second = moveContactIterator(phonebook, bookmarkIt->second, steps);
    }
    catch (const std::range_error& rangeError)
    {
      return "<INVALID STEP>";
    }
  }
  else
  {
    return "<INVALID STEP>";
  }

  return "";
}

Phonebook::iterator moveContactIterator(const Phonebook& phonebook, const Phonebook::iterator& contactIt, int pos)
{
  auto it = contactIt;
  int i = pos;
  for (; i < 0; ++i)
  {
    if (it == phonebook.cbegin())
    {
      throw std::range_error("Out of range of the start of the phonebook");
    }
    --it;
  }

  for (; i > 0; --i)
  {
    if (it == phonebook.cend())
    {
      throw std::range_error("Out of range of the end of the phonebook");
    }
    ++it;
  }

  return it;
}
