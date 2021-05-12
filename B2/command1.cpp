#include "commands.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <functional>
#include <limits>

#include "queue-with-priority.hpp"

using priority = QueueWithPriority<std::string>::priority;
static priority priorityConverter(const std::string& strPriority);

static std::istream& skipwsExceptNewline(std::istream& input);

static std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> parser(std::istream& input);

static std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> getParser(std::istream&);
static std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> addParser(std::istream& input);
static std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> accelerateParser(std::istream&);

void command1(std::istream& input, std::ostream& output)
{
  QueueWithPriority<std::string> queue;
  std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> command;
  while (input >> std::ws, !input.eof() && input.good())
  {
    try
    {
      command = parser(input);
      command(queue, output);
    }
    catch (const std::invalid_argument& invalidArgument)
    {
      output << invalidArgument.what() << "\n";
    }
    catch (const std::range_error& rangeError)
    {
      output << rangeError.what() << "\n";
    }
  }
  if (!input.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }
}

priority priorityConverter(const std::string& strPriority)
{
  static const std::map<std::string, priority> priorities{
    std::make_pair("high", priority::HIGH),
    std::make_pair("normal", priority::NORMAL),
    std::make_pair("low", priority::LOW)};

  auto it = priorities.find(strPriority);
  if (it != priorities.end())
  {
    return it->second;
  }
  else
  {
    throw std::invalid_argument("Invalid priority");
  }
}

std::istream& skipwsExceptNewline(std::istream& input)
{
  for (char temp = input.get(); isspace(temp) && temp != '\n'; temp = input.get())
  { }
  input.unget();
  return input;
}

std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> parser(std::istream& input)
{
  static const std::map<std::string, std::function<void(QueueWithPriority<std::string>&, std::ostream&)> (*)(
    std::istream&)> commands{
    std::make_pair("get", getParser),
    std::make_pair("add", addParser),
    std::make_pair("accelerate", accelerateParser)};

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
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> addParser(std::istream& input)
{
  std::string strPriority;
  input >> skipwsExceptNewline >> std::noskipws >> strPriority;
  if (input.fail())
  {
    input.clear();
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  priority priority = priority::LOW;
  try
  {
    priority = priorityConverter(strPriority);
  }
  catch (const std::invalid_argument& exception)
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string data;
  getline(input >> skipwsExceptNewline, data);
  if (data.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  return [data, priority](QueueWithPriority<std::string>& queue, std::ostream&) { queue.push(data, priority); };
}

std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> getParser(std::istream&)
{
  return [](QueueWithPriority<std::string>& queue, std::ostream& output)
  {
    if (queue.processingAndPopFront([&output](const std::string& string)
    {
      output << string << "\n";
      return 0;
    }) == 1)
    {
      throw std::range_error("<EMPTY>");
    }
  };
}

std::function<void(QueueWithPriority<std::string>& queue, std::ostream& output)> accelerateParser(std::istream&)
{
  return [](QueueWithPriority<std::string>& queue, std::ostream&) { queue.accelerate(); };
}
