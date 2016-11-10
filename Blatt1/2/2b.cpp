#include <iostream>
//#include <string>

int main(void)
{
  char input;
  int a;
  
  std::cout << "Please insert one of the following keys: <c>,<s> or <t>" << std::endl;
  std::cin >> input;  

  switch(input)
  {
    case 'c':
      std::cout << "Start calculation..." << std::endl;
      break;
    case 's':
      std::cout << "Start program..." << std::endl;
      break;
    case 't':
      std::cout << "Terminate program..." << std::endl;
      break;
    default:
      std::cout << "Unspecified input!" << std::endl;
  }
}
