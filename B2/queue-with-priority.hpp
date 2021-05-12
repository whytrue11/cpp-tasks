#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <list>
#include <stdexcept>
#include <functional>

template<typename T>
class QueueWithPriority
{
public:
  using value_type = typename std::list<T>::value_type;
  using reference = typename std::list<T>::reference;

  enum priority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void push(const T& data, const priority& priority);
  int processingAndPopFront(const std::function<int(const T&)>& handler);
  void accelerate() noexcept;
  bool empty() const noexcept;

private:
  std::list<T> queue_[3];
};

template<typename T>
void QueueWithPriority<T>::push(const T& data, const priority& priority)
{
  if (priority == priority::HIGH)
  {
    queue_[0].push_back(data);
  }
  else if (priority == priority::NORMAL)
  {
    queue_[1].push_back(data);
  }
  else if (priority == priority::LOW)
  {
    queue_[2].push_back(data);
  }
  else
  {
    throw std::invalid_argument("Incorrect priority parameter");
  }
}

template<typename T>
int QueueWithPriority<T>::processingAndPopFront(const std::function<int(const T&)>& handler)
{
  if (empty())
  {
    return 1;
  }

  int error = 0;
  if (!queue_[0].empty())
  {
    error = handler(queue_[0].front());
    queue_[0].pop_front();
    return error;
  }
  else if (!queue_[1].empty())
  {
    error = handler(queue_[1].front());
    queue_[1].pop_front();
    return error;
  }
  else
  {
    error = handler(queue_[2].front());
    queue_[2].pop_front();
    return error;
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate() noexcept
{
  queue_[0].splice(queue_[0].cend(), queue_[2]);
}

template<typename T>
bool QueueWithPriority<T>::empty() const noexcept
{
  return queue_[0].empty() && queue_[1].empty() && queue_[2].empty();
}

#endif
