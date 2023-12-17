#include "player.h"
#include "moveState.h"
#include "state.h"
#include "util.h"

using u::assets; 

Adventurer::Adventurer(Game* game, InputReader* inputReader): Player(game, inputReader) {
  Spritesheet * ss = assets()->ss.at("adventurer");

  defaultSize = {50,110};
  size = defaultSize;

  anim["idle"] = new Animation(ss, 39, 42, 16, true);
  anim["run"] = new Animation(ss, 9, 14, 8, true);
  anim["thrust"] = new Animation(ss, 43, 49, 8);
  anim["thrust2"] = new Animation(ss, 50, 54, 8);
  anim["hurt"] = new Animation(ss, {1,10}, {6, 10}, 8);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["light"] = new MoveState(this, anim.at("thrust"), {
    {STARTUP, {2, 0}, 4, {}, {defaultHurtbox}},
    {ACTIVE, {4, 0}, 4, {{30,-40,30,80}}, {defaultHurtbox}},
    {ACTIVE, {0, 0}, 4, {{30,-40,30,80}}, {defaultHurtbox}},
    {RECOVERY, {-4, 0}, 4, {}, {defaultHurtbox}},
    {RECOVERY, {-2, 0}, 4, {}, {defaultHurtbox}},
  });
  move["medium"] = new MoveState(this, anim.at("thrust2"), {
    {STARTUP, {2, 0}, 8, {}, {defaultHurtbox}},
    {ACTIVE, {0, 0}, 6, {{30,-10,220,20}}, {defaultHurtbox, {30,-20,100,40}}},
    {RECOVERY, {-4, 0}, 6, {}, {defaultHurtbox, {30,-20,100,40}}},
    {RECOVERY, {-2, 0}, 4, {}, {defaultHurtbox}},
  });

  currentState = new ControlState(this);
  currentState->init();
}
