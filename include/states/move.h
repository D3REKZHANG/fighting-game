#ifndef MOVE_H
#define MOVE_H

#include "animation.h"
#include "raylib.h"
#include "state.h"
#include "inputReader.h"
#include <vector>

enum FrameState { INACTIVE, STARTUP, ACTIVE, RECOVERY };

struct Frame {
  FrameState state = INACTIVE;
  Vector2 vel;
  int frameCount;
};

class Move : public State {
public:
  Animation* animation;
  std::vector<Frame> frameData; 
  int currentFrame = 0;
  int counter = 0;

  Move(Animation* animation, std::vector<Frame> frameData);

  virtual void init();
  virtual void exiting();
  virtual State* handleInput(Player* player, Input input);
  virtual void update(Player* player);
  virtual void draw(Player* player);
  virtual ~Move() = default;
  Frame getFrame();
  void reset();
};

#endif

