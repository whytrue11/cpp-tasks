#include "commands.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

#include "sort.hpp"
#include "toolkit.hpp"

static const size_t BUFFER = 1024;

SortOrder sortingOrderConverter(const char* sortOrder)
{
  if (sortOrder == nullptr)
  {
    throw std::invalid_argument("Sorting order must be not nullptr");
  }
  if (strcmp(sortOrder, "ascending") == 0)
  {
    return SortOrder::ascending;
  }
  else if (strcmp(sortOrder, "descending") == 0)
  {
    return SortOrder::descending;
  }
  else
  {
    throw std::invalid_argument("Invalid sorting order");
  }
}

void command1(const char* sortOrder)
{
  SortOrder order = sortingOrderConverter(sortOrder);

  std::vector<int> data;
  int temp;
  while (std::cin >> temp)
  {
    data.push_back(temp);
  }
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }
  if (data.empty())
  {
    return;
  }

  std::vector<int> dataCopy = data;

  IndexingOperatorAccess<std::vector<int>> indexingOperatorAccess(dataCopy);
  insertionSort(indexingOperatorAccess, order);
  printVectorWithSpaces(dataCopy);
  std::cout << "\n";

  dataCopy = data;
  AtFunctionAccess<std::vector<int>> atFunctionAccess(dataCopy);
  insertionSort(atFunctionAccess, order);
  printVectorWithSpaces(dataCopy);
  std::cout << "\n";

  IteratorAccess<std::vector<int>> iteratorAccess(data);
  insertionSort(iteratorAccess, order);
  printVectorWithSpaces(data);
}

void command2(const char* fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("File name must be not nullptr");
  }

  std::ifstream in(fileName);
  if (!in.is_open())
  {
    throw std::invalid_argument("Incorrect file name");
  }

  size_t capacity = BUFFER;

  char* data = static_cast<char*>(std::calloc(capacity, sizeof(char)));
  if (data == nullptr)
  {
    throw std::bad_alloc();
  }

  size_t size = 0;
  while (in.good())
  {
    in.read(&data[size], capacity - size);
    size += in.gcount();
    if (size == capacity)
    {
      char* temp = static_cast<char*>(std::realloc(data, sizeof(char) * capacity * 2));
      if (temp == nullptr)
      {
        free(data);
        throw std::bad_alloc();
      }
      data = temp;
      capacity *= 2;
    }
  }
  if (!in.eof())
  {
    free(data);
    if (in.fail())
    {
      throw std::ios_base::failure("Logical error on input operation or read error on input operation");
    }
    else
    {
      throw std::ios_base::failure("Unknown read error");
    }
  }

  std::vector<char> dataCopy(&data[0], &data[size]);
  printVector(dataCopy);
  free(data);
}

void command3()
{
  std::vector<int> data;

  int temp = 1;
  while (std::cin >> temp)
  {
    if (temp == 0)
    {
      break;
    }
    data.push_back(temp);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::ios_base::failure("Logical error on input operation or read error on input operation");
  }

  if (data.empty())
  {
    return;
  }

  if (temp != 0)
  {
    throw std::invalid_argument("Missing zero");
  }

  if (data.back() == 1)
  {
    for (auto i = data.begin(); i != data.end(); ++i)
    {
      if (*i % 2 == 0)
      {
        i = data.erase(i) - 1;
      }
    }
  }

  else if (data.back() == 2)
  {
    for (auto i = data.begin(); i != data.end(); ++i)
    {
      if (*i % 3 == 0)
      {
        i = data.insert(i + 1, 3, 1) + 2;
      }
    }
  }

  printVectorWithSpaces(data);
}

void command4(const char* sortOrder, int size)
{
  SortOrder order = sortingOrderConverter(sortOrder);

  std::vector<double> data(size);
  fillRandom(&data[0], size);
  printVectorWithSpaces(data);
  std::cout << "\n";

  IteratorAccess<std::vector<double>> iteratorAccess(data);
  insertionSort(iteratorAccess, order);
  printVectorWithSpaces(data);
}
