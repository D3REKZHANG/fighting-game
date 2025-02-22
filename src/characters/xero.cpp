#include "player.h"
#include "moveState.h"
#include "util.h"
#include "state.h"

using u::assets; 

Xero::Xero(Game* game, InputReader* inputReader): Player(game, inputReader) {
  defaultSize = {80, 90};
  size = defaultSize;

  anim["idle"] = new Animation(assets()->ss.at("xero_idle"), 1, 10, 8, true);
  anim["run"] = new Animation(assets()->ss.at("xero_run"), 1, 8, 8, true);
  anim["hurt"] = new Animation(assets()->ss.at("xero_hurt"), 1, 3, 8, false);
  anim["jump"] = new Animation(assets()->ss.at("xero_jump"), 1, 2, 8, false);
  anim["attack1"] = new Animation(assets()->ss.at("xero_attack1"), 1, 7, 8, false);
  anim["attack2"] = new Animation(assets()->ss.at("xero_attack2"), 1, 6, 8, false);
  anim["death"] = new Animation(assets()->ss.at("xero_death"), 1, 6, 8, false);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["light"] = new MoveState(
    this,
    anim.at("attack1"),
    MoveState::Properties{10, 10, 30},
    {
      Frame{STARTUP, {0, 0}, 2, {}, {defaultHurtbox}, {40,40}},
      Frame{STARTUP, {0, 0}, 2, {}, {defaultHurtbox}, {40,40}},
      Frame{STARTUP, {0, 0}, 2, {}, {defaultHurtbox}, {40,40}},
      Frame{STARTUP, {0, 0}, 2, {}, {defaultHurtbox}, {40,40}},
      Frame{ACTIVE, {0, 0}, 8, {{40,-80,150,100}, {10, -130, 100, 50}}, {defaultHurtbox, {30,-20,100,40}}, {40,40}},
      Frame{RECOVERY, {0, 0}, 2, {}, {defaultHurtbox}, {40,40}},
    }
  );
  move["medium"] = new MoveState(
    this,
    anim.at("attack2"),
    MoveState::Properties{10, 30, 50},
    {
      Frame{STARTUP, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
      Frame{STARTUP, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
      Frame{STARTUP, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
      Frame{STARTUP, {0, 0}, 8, {}, {defaultHurtbox}, {40,40}},
      Frame{ACTIVE, {0, 0}, 24, {{40,-80,150,100}, {10, -130, 100, 50}}, {defaultHurtbox, {30,-20,100,40}}, {40,40}},
      Frame{RECOVERY, {0, 0}, 24, {}, {defaultHurtbox}, {40,40}},
    }
  );

  currentState = new ControlState(this);
  currentState->init();
}
