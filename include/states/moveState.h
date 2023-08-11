#ifndef MOVE_H
#define MOVE_H

#include "animation.h"
#include "raylib.h"
#include "state.h"
#include "inputReader.h"
#include "player.h"
#include <vector>

enum FrameState { INACTIVE, STARTUP, ACTIVE, RECOVERY };

struct Frame {
  FrameState state = INACTIVE;
  Vector2 vel;
  int frameCount;
  // boxes relative to character
  Player::Box hitbox;
  std::vector<Player::Box> hurtbox;
};

class MoveState : public State {
public:
  Animation* animation;
  std::vector<Frame> frameData; 
  int currentFrameNum = 0;
  int counter = 0;

  MoveState(Player* player, Animation* animation, std::vector<Frame> frameData);

  virtual void init();
  virtual void exiting();
  virtual State* handleInput(Input input);
  virtual State* update();
  virtual void draw();
  virtual std::string getName();
  virtual ~MoveState() = default;
  Frame getFrame();
  Player::Box getHitbox();
  std::vector<Player::Box> getHurtbox();
  void reset();
};

#endif
