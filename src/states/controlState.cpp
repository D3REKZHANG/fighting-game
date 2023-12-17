#include "state.h"
#include "player.h"
#include "raymath.h"
#include "util.h"
#include "moveState.h"
#include "game.h"
#include <iostream>
using namespace std;

ControlState::ControlState(Player* player) : State(player) {
  cout << player << endl;
}

std::string ControlState::getName() { return "CONTROL"; }

void ControlState::init() {
  player->setAnimation("idle");
  player->currentAnimation->play();
  player->size = player->defaultSize;
  player->pos.y = player->game->getGroundPos()-player->size.y/2;
}

void ControlState::exiting() {
  player->currentAnimation->stop();
}

State* ControlState::handleInput(Input input) {
  int motion = input.motion;
  if(motion == 4 || motion == 6){
    if(motion == 4) player->vel.x = -player->stats.walk_speed;
    if(motion == 6) player->vel.x = player->stats.walk_speed;
    player->setAnimation("run");
    player->currentAnimation->active = true;
  }
  if(motion == 5){
    player->vel.x = 0;
    player->setAnimation("idle");
  }
  if(motion == 7 || motion == 8 || motion == 9){
    return new JumpState(player);
  }

  if(input.button == LIGHT){
    return player->move["light"];
  }
  if(input.button == MEDIUM){
    return player->move["medium"];
  }
  return nullptr;
}

State* ControlState::update(){
  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);
  player->currentAnimation->tick();
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
