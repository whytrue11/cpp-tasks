#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <map>
#include <iosfwd>
#include <functional>

#include "phonebook.hpp"

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
parser(std::istream& input);

std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
addParser(std::istream& input);
std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
storeParser(std::istream& input);
std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
insertParser(std::istream& input);
std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
eraseParser(std::istream& input);
std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
showParser(std::istream& input);
std::function<void(Phonebook& phonebook, std::map<std::string, Phonebook::iterator>& bookmarks, std::ostream& output)>
moveParser(std::istream& input);

#endif
