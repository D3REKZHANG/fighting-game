#include "state.h"
#include "player.h"
#include "raymath.h"
#include "util.h"
#include "moveState.h"

ControlState::ControlState(Player* player) : State(player) {}

std::string ControlState::getName() { return "CONTROL"; }

void ControlState::init() {
  player->setAnimation("idle");
  player->currentAnimation->play();
}
void ControlState::exiting() {
  player->currentAnimation->stop();
}

State* ControlState::handleInput(Input input) {
  int motion = input.motion;
  if(motion == 4 || motion == 6){
    if(motion == 4) player->vel.x = -player->speed;
    if(motion == 6) player->vel.x = player->speed;
  }
  if(motion == 5){
    player->vel.x = 0;
    player->setAnimation("idle");
  }
  if(motion == 7 || motion == 8 || motion == 9){
    return new JumpState(player);
  }

  if(input.button == LIGHT){
    return player->move["thrust"];
  }
  return nullptr;
}

State* ControlState::update(){
  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);
  return nullptr;
}

void ControlState::draw(){
  player->currentAnimation->draw(player->pos, player->inverse);

  for(Player::Box hurtbox : getHurtbox()) {
    DrawRectangleLinesEx(hurtbox.getTranslated(player), 1, GREEN);
  }
}

std::vector<Player::Box> ControlState::getHurtbox() {
  return {{-player->size.x/2-20,-player->size.y/2, player->size.x+40, player->size.y}};
}

ControlState::~ControlState() {}
