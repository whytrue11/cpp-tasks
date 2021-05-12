#include "commands.hpp"
#include <algorithm>
#include "factorials-container.hpp"

void command2(std::ostream& output)
{
  FactorialsContainer factorialsContainer(1, 10);
  std::copy(factorialsContainer.cbegin(), factorialsContainer.cend(), std::ostream_iterator<int>(output, " "));
  output << "\n";

  std::copy(factorialsContainer.rbegin(), factorialsContainer.rend(), std::ostream_iterator<int>(output, " "));
  output << "\n";
}
