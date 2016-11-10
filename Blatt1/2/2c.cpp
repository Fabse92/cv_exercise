#include <iostream>
//#include <string>

double addition (double a, double b)
{
  return a+b;
}

int main(void)
{
  double a,b;
  std::cout << "First double: " << std::endl;
  std::cin >> a;
  std::cout << "Second double: " << std::endl;
  std::cin >> b;
  std::cout << "a + b = " << addition (a,b) << std::endl;
}
