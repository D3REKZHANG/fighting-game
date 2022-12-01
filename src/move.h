#ifndef MOVE_H
#define MOVE_H

#include "animation.h"
#include "raylib.h"
#include <vector>

enum FrameState { startup, active, recovery };

struct Frame {
  FrameState state;
  Vector2 vel;
};

class Move {
public:
  Animation* animation;
  std::vector<Frame> frameData;
  int current;

  void tick();
  Frame getFrame();

};

#endif

