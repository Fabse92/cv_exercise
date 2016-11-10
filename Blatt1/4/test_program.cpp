#include <iostream>
#include <vector>
#include <string>

int main(void)
{
  std::vector<double> values;
  std::string input;
  float floats[3];
  std::vector<double>::iterator it; 
  
  std::cout << "Please insert three float values" << std::endl;
  std::cin >> floats[0];
  std::cin >> floats[1];
  std::cin >> floats[2];
  
  values.push_back(floats[0]);
  values.push_back(floats[1]);
  values.push_back(floats[2]);
  
  it = values.end();
  
  while (it != values.begin())
  {
    --it;
    std::cout << *it << std::endl;
  }
  
  return 0;
  
}
