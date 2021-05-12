#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <iosfwd>

bool stringToIntConverter(const std::string& string, int& integer);
std::istream& skipwsExceptNewline(std::istream& input);

#endif
