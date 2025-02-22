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
  std::vector<Player::Box> hitbox;
  std::vector<Player::Box> hurtbox;
  Vector2 size;
};

class MoveState : public State {
public:
  struct Properties {
    float damage;
    float knockbackVel;
    int hurtFrames;

    Properties(float damage, float knockbackVel, int hurtFrames = 30)
      : damage{damage}, knockbackVel{knockbackVel}, hurtFrames{hurtFrames} {}
  };

  Animation* animation;
  Properties properties;
  std::vector<Frame> frameData; 
  size_t currentFrameNum = 0;
  int counter = 0;
  bool hitHandled = false;

  MoveState(Player* player, Animation* animation, Properties properties, std::vector<Frame> frameData);

  virtual void init();
  virtual void exiting();
  virtual State* handleInput(Input input);
  virtual State* update();
  virtual void draw();
  virtual std::string getName();
  virtual ~MoveState() = default;
  Frame getFrame();
  std::vector<Player::Box> getHitbox();
  std::vector<Player::Box> getHurtbox();
  void handleHit(Player* playerHit);
  void reset();
  void drawFrames();
};

#endif
