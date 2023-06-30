#include "state.h"
#include "player.h"
#include "raymath.h"
#include "util.h"

ControlState::ControlState() {}

void ControlState::init() {}
void ControlState::exiting() {}

State* ControlState::handleInput(Player* player, Input input) {
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
    player->vel.y = -30;
    player->vel.x = 0;
    if(motion == 7)
      player->vel.x = -player->speed;
    if(motion == 9)
      player->vel.x = player->speed;
  }
  return nullptr;
}

void ControlState::update(Player* player){
  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);
}

void ControlState::draw(Player* player){

}

ControlState::~ControlState() {}
