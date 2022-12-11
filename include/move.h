#ifndef MOVE_H
#define MOVE_H

#include "animation.h"
#include "raylib.h"
#include "action.h"
#include <vector>

enum FrameState { NONE, STARTUP, ACTIVE, RECOVERY };

struct Frame {
  FrameState state = NONE;
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

  bool update();
  void draw(Vector2 pos, bool inverse=false);
  Frame getFrame();
  void reset();
};

#endif

