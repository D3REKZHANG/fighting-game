#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"
#include <vector>

class Spritesheet;

class Animation {
  struct Range {
    int start, stop;
  };
public:
  Range range;
  Spritesheet* spritesheet;
  int currentFrame = 0;
  int counter = 0;
  int tickSpeed;
  bool repeat;
  bool active = false;

  Animation(Spritesheet* spritesheet, int start, int stop, int tickSpeed, bool repeat=false);
  Animation(Spritesheet* spritesheet, Vector2 start, Vector2 stop, int tickSpeed, bool repeat=false);
  void tick();
  void draw(Vector2 pos, bool inverse=false);
  void play();
  void stop();
};

#endif
