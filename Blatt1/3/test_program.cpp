#include "Cuboid.h"
#include <iostream>
#include <vector>

int main(void)
{
  Cuboid quader;
  std::vector<double> dimensions,dimensions2;
  dimensions.push_back(1.0);
  dimensions.push_back(2.0);
  dimensions.push_back(3.0);
  quader.SetDimensions(dimensions);
  std::cout << "Volume of the cuboid is: " << quader.CalculateVolume() << std::endl;
  std::cout << "Area of the cuboid is: " << quader.CalculateArea() << std::endl;
  dimensions2 = quader.GetDimensions();
  std::cout << "Dimensions of the cuboid are: " << dimensions2[0] << dimensions2[1] << dimensions2[2] << std::endl;
  
  return 0;
}
