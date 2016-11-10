#ifndef GREETER_H
#define GREETER_H
class Greeter
{
public:
  Greeter();
  void hello();
  int getHelloCount() const;
private:
  int num_hello_;
};
#endif
