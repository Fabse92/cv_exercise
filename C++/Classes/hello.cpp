#include "Greeter.h"
#include <iostream>
int main(void)
{
  Greeter g;
  for (int i = 0; i < 10; ++i)
  {
    g.hello();
  }
  std::cout << "g greeted " << g.getHelloCount() << " times.\n";
  return 0;
}
