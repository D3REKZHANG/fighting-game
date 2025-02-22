#include "player.h"
#include "moveState.h"
#include "util.h"
#include "state.h"

using u::assets; 

Naruto::Naruto(Game* game, InputReader* inputReader): Player(game, inputReader) {
  Spritesheet * ss = assets()->ss.at("naruto");

  defaultSize = {55, 94};
  size = defaultSize;

  anim["idle"] = new Animation(ss, 1, 4, 16, true);
  anim["run"] = new Animation(ss, 5, 12, 8, true);
  anim["attack"] = new Animation(ss, {1, 10}, {5, 10}, 0);
  anim["jump"] = new Animation(ss, {8, 2}, {2, 3}, 8);
  anim["hurt"] = new Animation(ss, {6, 3}, {6, 3}, 0);
  anim["knockdown"] = new Animation(ss, {1, 4}, {3, 4}, 8);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["light"] = new MoveState(
    this,
    anim.at("attack"), 
    MoveState::Properties{ 5, 10 },
    {
      {STARTUP, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
      {STARTUP, {0, 0}, 4, {}, {defaultHurtbox}, {40,40}},
      {ACTIVE, {0, 0}, 8, {{30,-10,200,20}}, {defaultHurtbox, {30,-20,100,40}}, {40,40}},
      {RECOVERY, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
      {RECOVERY, {0, 0}, 4, {}, {defaultHurtbox}, {40,40}},
    }
  );

  currentState = new ControlState(this);
  currentState->init();
}
