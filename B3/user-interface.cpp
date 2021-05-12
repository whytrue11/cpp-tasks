#include "user-interface.hpp"

#include <iostream>
#include <functional>
#include <stdexcept>
#include <string>
#include <limits>
#include <map>

#include "phonebook.hpp"
#include "bookmarks.hpp"
#include "tools.hpp"

static void formattingName(std::string& name);
static Phonebook::PhoneContact initializePhoneContact(std::istream& input);
static void outputInvalidCommand(Phonebook&, std::map<std::string, Phonebook::iterator>&, std::ostream& output);

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
parser(std::istream& input)
{
  static const std::map<std::string, std::function<void(Phonebook& phonebook,
    std::map<std::string, Phonebook::iterator>&, std::ostream&)> (*)(
    std::istream&)> commands{
    std::make_pair("add", addParser),
    std::make_pair("store", storeParser),
    std::make_pair("insert", insertParser),
    std::make_pair("delete", eraseParser),
    std::make_pair("show", showParser),
    std::make_pair("move", moveParser)};

  std::string strCommand;
  input >> std::ws >> strCommand;
  if (input.fail())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }

  auto it = commands.find(strCommand);
  if (it != commands.end())
  {
    return it->second(input);
  }
  else
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return outputInvalidCommand;
  }
}

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
addParser(std::istream& input)
{
  Phonebook::PhoneContact phoneContact;
  try
  {
    phoneContact = initializePhoneContact(input);
  }
  catch (const std::invalid_argument&)
  {
    return outputInvalidCommand;
  }

  return [phoneContact](Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
    std::ostream&)
  {
    detail::add(phonebook, bookmarks, phoneContact);
  };
}

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
storeParser(std::istream& input)
{
  std::string bookmark;
  input >> skipwsExceptNewline >> std::noskipws >> bookmark;
  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }
  if (input.fail())
  {
    input.clear();
    return outputInvalidCommand;
  }

  std::string newBookmark;
  getline(input >> skipwsExceptNewline, newBookmark);

  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }

  if (!newBookmark.empty() && newBookmark.back() == '\r')
  {
    newBookmark.pop_back();
  }

  if (newBookmark.empty())
  {
    return outputInvalidCommand;
  }

  return [bookmark, newBookmark](Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
    std::ostream& output)
  {
    std::string message = detail::store(phonebook, bookmarks, bookmark, newBookmark);
    if (!message.empty())
    {
      output << message << "\n";
    }
  };
}

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
insertParser(std::istream& input)
{
  std::string directionStr;
  input >> skipwsExceptNewline >> std::noskipws >> directionStr;
  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }
  if (input.fail())
  {
    input.clear();
    return outputInvalidCommand;
  }

  if (directionStr != "before" && directionStr != "after")
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return outputInvalidCommand;
  }

  std::string bookmark;
  input >> skipwsExceptNewline >> std::noskipws >> bookmark;
  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }
  if (input.fail())
  {
    input.clear();
    return outputInvalidCommand;
  }

  Phonebook::PhoneContact phoneContact;
  try
  {
    phoneContact = initializePhoneContact(input);
  }
  catch (const std::invalid_argument&)
  {
    return outputInvalidCommand;
  }

  return [directionStr, bookmark, phoneContact](Phonebook& phonebook,
    std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)
  {
    std::string message = detail::insert(phonebook, bookmarks, directionStr, bookmark, phoneContact);
    if (!message.empty())
    {
      output << message << "\n";
    }
  };
}

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
eraseParser(std::istream& input)
{
  std::string bookmark;
  getline(input >> skipwsExceptNewline, bookmark);

  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }

  if (!bookmark.empty() && bookmark.back() == '\r')
  {
    bookmark.pop_back();
  }

  if (bookmark.empty())
  {
    return outputInvalidCommand;
  }

  return [bookmark](Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)
  {
    std::string message = detail::erase(phonebook, bookmarks, bookmark);
    if (!message.empty())
    {
      output << message << "\n";
    }
  };
}

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
showParser(std::istream& input)
{
  std::string bookmark;
  getline(input >> skipwsExceptNewline, bookmark);

  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }

  if (!bookmark.empty() && bookmark.back() == '\r')
  {
    bookmark.pop_back();
  }

  if (bookmark.empty())
  {
    return outputInvalidCommand;
  }

  return [bookmark](Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)
  {
    std::string message = detail::show(phonebook, bookmarks, bookmark, output);
    if (!message.empty())
    {
      output << message;
    }
    output << "\n";
  };
}

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
moveParser(std::istream& input)
{
  std::string bookmark;
  input >> skipwsExceptNewline >> std::noskipws >> bookmark;
  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }
  if (input.fail())
  {
    input.clear();
    return outputInvalidCommand;
  }

  std::string stepsStr;
  getline(input >> skipwsExceptNewline, stepsStr);

  if (!stepsStr.empty() && stepsStr.back() == '\r')
  {
    stepsStr.pop_back();
  }

  if (stepsStr.empty())
  {
    return outputInvalidCommand;
  }

  return [bookmark, stepsStr](Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks,
    std::ostream& output)
  {
    std::string message = detail::move(phonebook, bookmarks, bookmark, stepsStr);
    if (!message.empty())
    {
      output << message << "\n";
    }
  };
}

Phonebook::PhoneContact initializePhoneContact(std::istream& input)
{
  std::string number;
  input >> skipwsExceptNewline >> std::noskipws >> number;
  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }
  if (input.fail())
  {
    input.clear();
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  input >> skipwsExceptNewline;
  if (input.get() != '\"')
  {
    input.unget();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string name;
  getline(input, name);

  if (input.bad())
  {
    throw std::ios_base::failure("Irrecoverable stream error");
  }

  if (!name.empty() && name.back() == '\r')
  {
    name.pop_back();
  }

  if (name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  if (name.back() != '\"')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  else
  {
    name.pop_back();
  }

  Phonebook::PhoneContact phoneContact;
  try
  {
    formattingName(name);
    phoneContact = Phonebook::PhoneContact(name, number);
  }
  catch (const std::invalid_argument& invalidArgument)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  return phoneContact;
}

void outputInvalidCommand(Phonebook&, std::map<std::string, Phonebook::iterator>&, std::ostream& output)
{
  output << "<INVALID COMMAND>\n";
}

void formattingName(std::string& name)
{
  size_t pos = 0;
  while (pos = name.find('\\', pos), pos != std::string::npos)
  {
    if (pos + 1 != name.size() && (name[pos + 1] == '\"' || name[pos + 1] == '\\'))
    {
      name.erase(pos, 1);
      pos += 1;
    }
    else
    {
      throw std::invalid_argument("Invalid characters entered");
    }
  }
}
