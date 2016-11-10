// my first program in C++
#include <iostream>
using namespace std;

int main ()
{
  int i,j,b;
  cout << "Please enter an integer value: ";
  cin >> i;
  cout << "Enter another integer value: ";
  cin >> j;
  cout << "Addition: " << i+j << endl;
  cout << "Substraction: " << i-j << endl;
  cout << "Multiplication: " << i*j << endl;
  b = (i < j) ? j : i;
  cout << "The bigger number is: " << b << endl;
  return 0;
}
