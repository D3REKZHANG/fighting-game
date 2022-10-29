#ifndef UTILCC
#define UTILCC

#include <string>
#include <iostream>
#include <vector>

class console {
public:
  static void log(std::string s) {
    std::cout << s << std::endl;
  }

  static void log(int s) {
    std::cout << std::to_string(s) << std::endl;
  }

  static void log(int a, int b) {
    std::cout << a << ", " << b << std::endl;
  }
};

#endif
