#ifndef FACTORIALS_CONTAINER_HPP
#define FACTORIALS_CONTAINER_HPP

#include <iterator>

class FactorialsContainer
{
public:
  class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, unsigned int, unsigned int, const unsigned int*, unsigned int>
  {
  public:
    friend class FactorialsContainer;

    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    reference operator*() const;
    bool operator==(Iterator other) const;
    bool operator!=(Iterator other) const;

  private:
    explicit Iterator(unsigned int factorial, size_t pos);

    unsigned int factorial_;
    size_t pos_;
  };

  using const_iterator = Iterator;
  using reverse_iterator = std::reverse_iterator<FactorialsContainer::const_iterator>;

  FactorialsContainer(unsigned int lowerLimit, unsigned int upperLimit);

  const_iterator cend() const noexcept;
  const_iterator cbegin() const noexcept;
  reverse_iterator rbegin() const noexcept;
  reverse_iterator rend() const noexcept;

private:
  unsigned int lowerLimit_;
  unsigned int upperLimit_;
};

#endif
