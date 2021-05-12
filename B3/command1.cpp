#include "commands.hpp"
#include <iostream>
#include <map>
#include "user-interface.hpp"

void command1(std::istream& input, std::ostream& output)
{
  Phonebook phonebook;
  std::map<std::string, Phonebook::iterator> bookmarks{{"current", phonebook.begin()}};
  while (input >> std::ws, !input.eof() && input.good())
  {
    parser(input)(phonebook, bookmarks, output);
  }
  if (!input.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }
}
