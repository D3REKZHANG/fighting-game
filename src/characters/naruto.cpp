#include "naruto.h"
#include "moveState.h"
#include "util.h"
#include "state.h"

using u::assets; 

Naruto::Naruto(Game* game, InputReader* inputReader): Player(game, inputReader) {
  defaultSize = {30, 70};

  anim["idle"] = new Animation(assets()->ss.at("naruto"), 1, 4, 16, true);
  anim["run"] = new Animation(assets()->ss.at("naruto"), 5, 12, 8, true);
  anim["attack"] = new Animation(assets()->ss.at("naruto"), {1, 10}, {5, 10}, 0);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["light"] = new MoveState(this, anim.at("attack"), {
    {STARTUP, {0, 0}, 24, {}, {defaultHurtbox}, {40,40}},
    {STARTUP, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
    {ACTIVE, {0, 0}, 8, {{30,-10,200,20}}, {defaultHurtbox, {30,-20,100,40}}, {40,40}},
    {RECOVERY, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
    {RECOVERY, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
  });

  currentState = new ControlState(this);
}
