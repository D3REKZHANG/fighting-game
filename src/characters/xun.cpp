#include "player.h"
#include "moveState.h"
#include "util.h"
#include "state.h"

using u::assets; 

Xun::Xun(Game* game, InputReader* inputReader): Player(game, inputReader) {
  defaultSize = {80, 75};
  size = defaultSize;

  anim["idle"] = new Animation(assets()->ss.at("xun_idle"), 1, 10, 8, true);
  anim["run"] = new Animation(assets()->ss.at("xun_run"), 1, 8, 8, true);
  anim["hurt"] = new Animation(assets()->ss.at("xun_hurt"), 1, 3, 8, false);
  anim["attack"] = new Animation(assets()->ss.at("xun_attack"), 1, 7, 8, false);
  anim["death"] = new Animation(assets()->ss.at("xun_death"), 1, 11, 8, false);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["light"] = new MoveState(
    this,
    anim.at("attack"),
    MoveState::Properties{ 5, 30 },
    {
      {STARTUP, {0, 0}, 3, {}, {defaultHurtbox}, {40,40}},
      {STARTUP, {0, 0}, 3, {}, {defaultHurtbox}, {40,40}},
      {STARTUP, {0, 0}, 3, {}, {defaultHurtbox}, {40,40}},
      {STARTUP, {0, 0}, 3, {}, {defaultHurtbox}, {40,40}},
      {ACTIVE, {0, 0}, 6, {{40,-80,80,100}, {10, -130, 100, 50}}, {defaultHurtbox, {30,-20,100,40}}, {40,40}},
      {RECOVERY, {0, 0}, 5, {}, {defaultHurtbox}, {40,40}},
      {RECOVERY, {0, 0}, 5, {}, {defaultHurtbox}, {40,40}},
    }
  );

  currentState = new ControlState(this);
  currentState->init();
}
