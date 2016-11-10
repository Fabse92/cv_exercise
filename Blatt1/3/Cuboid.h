#ifndef CUBOID_H
#define CUBOID_H

#include <vector>
class Cuboid
{
  public:
    Cuboid();
    void SetDimensions(std::vector<double>& dimensions);
    std::vector<double> GetDimensions() const;
    double CalculateVolume() const;
    double CalculateArea() const;
  private:
    int height;
    int width;
    int depth;
};
#endif
