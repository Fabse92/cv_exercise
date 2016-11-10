#include "Cuboid.h"
#include <iostream>
#include <vector>

Cuboid::Cuboid()	: height(0), width(0), depth(0)
{
}
void Cuboid::SetDimensions(std::vector<double>& dimensions)
{
  height = dimensions[0];
  width = dimensions[1];
  depth = dimensions[2];
}

std::vector<double> Cuboid::GetDimensions() const
{
  std::vector<double> dimensions;
  dimensions.push_back(height);
  dimensions.push_back(width);
  dimensions.push_back(depth);
  
  return dimensions; 
}

double Cuboid::CalculateVolume() const
{  
  return height*width*depth;
}

double Cuboid::CalculateArea() const
{
  return 2*(height*width+height*depth+width*depth);
}
