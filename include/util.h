#ifndef UTILCC
#define UTILCC

#include <string>
#include <iostream>
#include <vector>
#include "assetManager.h"
#include "raylib.h"

namespace u {
  static void log(std::string s) {
    std::cout << s << std::endl;
  }

  static void log(int s) {
    std::cout << std::to_string(s) << std::endl;
  }

  static void log(int a, int b) {
    std::cout << a << ", " << b << std::endl;
  }

  static Vector2 topleft(Vector2 center_pos, float width, float height) {
    return {center_pos.x - width/2, center_pos.y - height/2};
  }

  static Vector2 negate(Vector2 vec) {
    return {-vec.x, -vec.y};
  }

  static AssetManager* assets() {
    return AssetManager::getInstance();
  }
};

#endif
