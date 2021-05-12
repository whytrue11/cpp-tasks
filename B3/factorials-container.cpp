#include "factorials-container.hpp"

FactorialsContainer::FactorialsContainer(unsigned int lowerLimit, unsigned int upperLimit) :
  lowerLimit_(lowerLimit),
  upperLimit_(upperLimit + 1)
{ }

FactorialsContainer::Iterator::Iterator(unsigned int factorial, size_t pos) :
  factorial_(factorial),
  pos_(pos)
{ }

FactorialsContainer::Iterator& FactorialsContainer::Iterator::operator++()
{
  factorial_ *= ++pos_;
  if (factorial_ == 0)
  {
    factorial_ = pos_ = 1;
  }
  return *this;
}

FactorialsContainer::Iterator FactorialsContainer::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialsContainer::Iterator& FactorialsContainer::Iterator::operator--()
{
  if (pos_ - 1 == 0)
  {
    --pos_;
    factorial_ = 1;
  }
  else
  {
    factorial_ /= pos_--;
  }
  return *this;
}

FactorialsContainer::Iterator FactorialsContainer::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

bool FactorialsContainer::Iterator::operator==(FactorialsContainer::Iterator other) const
{
  return factorial_ == other.factorial_ && pos_ == other.pos_;
}

bool FactorialsContainer::Iterator::operator!=(FactorialsContainer::Iterator other) const
{
  return !(*this == other);
}

FactorialsContainer::Iterator::reference FactorialsContainer::Iterator::operator*() const
{
  return factorial_;
}

FactorialsContainer::const_iterator FactorialsContainer::cbegin() const noexcept
{
  if (lowerLimit_ == 0)
  {
    return Iterator(1, 0);
  }

  unsigned int factorial = 1;
  for (size_t i = 2; i <= lowerLimit_; ++i)
  {
    factorial *= i;
  }
  return Iterator(factorial, lowerLimit_);
}

FactorialsContainer::const_iterator FactorialsContainer::cend() const noexcept
{
  if (upperLimit_ == 0)
  {
    return Iterator(1, 0);
  }

  unsigned int factorial = 1;
  for (size_t i = 2; i <= upperLimit_; ++i)
  {
    factorial *= i;
  }
  return Iterator(factorial, upperLimit_);
}

FactorialsContainer::reverse_iterator FactorialsContainer::rbegin() const noexcept
{
  return std::reverse_iterator<FactorialsContainer::Iterator>(cend());
}

FactorialsContainer::reverse_iterator FactorialsContainer::rend() const noexcept
{
  return std::reverse_iterator<FactorialsContainer::Iterator>(cbegin());
}
