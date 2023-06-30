#ifndef STATE_H
#define STATE_H

#include "raylib.h"

class Player;
class Game;
struct Input;

class State { 
public:
  virtual void init() = 0;
  virtual State* handleInput(Player* player, Input input) = 0;
  virtual void update(Player* player) = 0;
  virtual void draw(Player* player) = 0;
  virtual void exiting() = 0;
};

#define METHODS \
public: \
  virtual void init(); \
  virtual State* handleInput(Player* player, Input input); \
  virtual void update(Player* player); \
  virtual void draw(Player* player); \
  virtual void exiting();

class ControlState : public State { METHODS ControlState(); virtual ~ControlState(); };
class JumpState : public State { METHODS virtual ~JumpState(); };

#endif
