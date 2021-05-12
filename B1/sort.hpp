#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <iterator>
#include <stdexcept>

template<typename T>
bool ascendingCompare(const T& a, const T& b) noexcept;

template<typename T>
bool descendingCompare(const T& a, const T& b) noexcept;

enum SortOrder
{
  ascending,
  descending
};

template<class Container>
class IndexingOperatorAccess
{
public:
  using iterator = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  explicit IndexingOperatorAccess(Container& container) noexcept:
    container_(container)
  { }

  virtual typename Container::size_type begin() noexcept;
  virtual typename Container::size_type end() noexcept;
  virtual typename Container::reference indexing(size_t index);
protected:
  Container& container_;
};

template<class Container>
class AtFunctionAccess : public IndexingOperatorAccess<Container>
{
public:
  using iterator = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  explicit AtFunctionAccess(Container& container) noexcept:
    IndexingOperatorAccess<Container>(container)
  { }

  typename Container::reference indexing(size_t index) override;
};

template<class Container>
class IteratorAccess
{
public:
  using iterator = typename Container::iterator;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  explicit IteratorAccess(Container& container) noexcept:
    container_(container)
  { }

  typename Container::iterator begin() noexcept;
  typename Container::iterator end() noexcept;
  typename Container::reference indexing(typename Container::iterator index);
private:
  Container& container_;
};

template<class Container>
void insertionSort(Container& array, const SortOrder& order)
{
  bool (* compare)(typename Container::const_reference, typename Container::const_reference);
  if (order == SortOrder::ascending)
  {
    compare = ascendingCompare;
  }
  else if (order == SortOrder::descending)
  {
    compare = descendingCompare;
  }
  else
  {
    throw std::invalid_argument("Invalid sorting order");
  }

  Container container(array);
  for (typename Container::iterator i = container.begin(); i != container.end(); ++i)
  {
    for (typename Container::iterator j = i; j != container.begin(); --j)
    {
      typename Container::reference a = container.indexing(j);
      typename Container::reference b = container.indexing(j - 1);
      if (compare(a, b))
      {
        std::swap(a, b);
      }
      else
      {
        break;
      }
    }
  }
}

template<class Container>
typename Container::size_type IndexingOperatorAccess<Container>::begin() noexcept
{
  return 0;
}

template<class Container>
typename Container::iterator IteratorAccess<Container>::begin() noexcept
{
  return container_.begin();
}

template<class Container>
typename Container::size_type IndexingOperatorAccess<Container>::end() noexcept
{
  return container_.size();
}

template<class Container>
typename Container::iterator IteratorAccess<Container>::end() noexcept
{
  return container_.end();
}

template<class Container>
typename Container::reference IndexingOperatorAccess<Container>::indexing(size_t index)
{
  return container_[index];
}

template<class Container>
typename Container::reference AtFunctionAccess<Container>::indexing(size_t index)
{
  return IndexingOperatorAccess<Container>::container_.at(index);
}

template<class Container>
typename Container::reference IteratorAccess<Container>::indexing(typename Container::iterator index)
{
  return *index;
}

template<typename T>
bool ascendingCompare(const T& a, const T& b) noexcept
{
  return a < b;
}

template<typename T>
bool descendingCompare(const T& a, const T& b) noexcept
{
  return a > b;
}

#endif
