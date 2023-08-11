#ifndef STATE_H
#define STATE_H

#include "raylib.h"
#include "player.h"
#include <string>
#include <vector>

class Game;
struct Input;

class State { 
public:
  Player* player;
  State(Player* player);
  virtual void init() = 0;
  virtual State* handleInput(Input input) = 0;
  virtual State* update() = 0;
  virtual void draw() = 0;
  virtual void exiting() = 0;
  virtual std::string getName() = 0;
  virtual std::vector<Player::Box> getHurtbox() = 0;
  virtual ~State() = 0;
};

inline State::~State() {}
inline State::State(Player* player) : player{player} {}

#define METHODS \
public: \
  virtual std::string getName(); \
  virtual void init(); \
  virtual State* handleInput(Input input); \
  virtual State* update(); \
  virtual void draw(); \
  virtual void exiting(); \
  virtual std::vector<Player::Box> getHurtbox();

class ControlState : public State { METHODS ControlState(Player* p); ~ControlState(); };
class JumpState : public State { METHODS JumpState(Player* p); ~JumpState(); };

#endif
