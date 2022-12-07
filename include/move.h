#ifndef MOVE_H
#define MOVE_H

#include "animation.h"
#include "raylib.h"
#include "action.h"
#include <vector>

enum FrameState { none, startup, active, recovery };

struct Frame {
  FrameState state = none;
  Vector2 vel;
  int frameCount;
};

class Move : public Action {
public:
  Animation* animation;
  std::vector<Frame> frameData;
  int currentFrame = 0;
  int counter = 0;

  Move(Animation* animation, std::vector<Frame> frameData);

  void update();
  void draw(Vector2 pos);
  Frame getFrame();
};

#endif

