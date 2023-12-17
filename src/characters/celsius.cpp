#include "player.h"
#include "moveState.h"
#include "state.h"
#include "util.h"

using u::assets; 

Celsius::Celsius(Game* game, InputReader* inputReader): Player(game, inputReader) {
  defaultSize = {50, 250};

  anim["idle"] = new Animation(assets()->ss.at("celsius"), 1, 1, 8, true);
  anim["run"] = new Animation(assets()->ss.at("celsius"), 1, 1, 8, true);
  anim["thrust"] = new Animation(assets()->ss.at("celsius"), 2, 6, 0);
  anim["hurt"] = new Animation(assets()->ss.at("celsius_hurt"), 1, 1, 8, true);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["light"] = new MoveState(this, anim.at("thrust"), {
    {STARTUP, {2, 0}, 4, {}, {defaultHurtbox}},
    {ACTIVE, {4, 0}, 4, {{30,-10,200,20}}, {defaultHurtbox, {30,-20,100,40}}},
    {ACTIVE, {0, 0}, 4, {{30,-10,220,20}}, {defaultHurtbox, {30,-20,100,40}}},
    {RECOVERY, {-4, 0}, 4, {}, {defaultHurtbox, {30,-20,100,40}}},
    {RECOVERY, {-2, 0}, 4, {}, {defaultHurtbox}},
  });

  currentState = new ControlState(this);
  currentState->init();
}
