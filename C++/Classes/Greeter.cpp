#include "Greeter.h"
#include <iostream>
Greeter::Greeter()//	: num_hello_(1)
{
  num_hello_ = 3;
}
void Greeter::hello()
{
  std::cout << "Hello world!\n";
  num_hello_++;
}
int Greeter::getHelloCount() const
{
  return num_hello_;
}
