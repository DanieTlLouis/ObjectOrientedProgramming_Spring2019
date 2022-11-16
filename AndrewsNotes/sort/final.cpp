
#include <iostream>
#include <functional>
#include <string>

using namespace std::string_literals;

struct finally
{
  finally(std::function<void()> f)
    : fn(f)
  { }
  ~finally()
  {
    fn();
  }
  std::function<void()> fn;
};

int 
main(int argc, char* argv[])
{
  bool err = (argc > 1 && argv[1] == "fail"s);

  // Registers f1 to execute at the end of
  // the function.
  finally f1([err]{ 
    // If we encounter an error, fail hard.
    if (err)
      throw std::runtime_error("error!");
    
    // Otherwise, print success.
    std::cout << "!!!!!!\n"; 
  });

  for (int i = 0; i < 10; ++i)
    std::cout << i << ' ';

  // finally f1 called here
};




