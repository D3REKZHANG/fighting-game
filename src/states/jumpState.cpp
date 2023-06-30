#include "state.h"
#include "player.h"
#include "game.h"

void JumpState::init() {}
void JumpState::exiting() {}

State* JumpState::handleInput(Player* player, Input input) {
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

void JumpState::update(Player* player) {
  if (player->pos.y >= player->game->getGroundPos()-player->size.y/2) {
    player->pos.y = player->game->getGroundPos()-player->size.y/2;
    player->accel.y = 0;
    player->vel = {0, 0};
    player->state = new ControlState();
  } else {
    player->accel.y = 3; // gravity
  }
};

void JumpState::draw(Player* player) {};

JumpState::~JumpState() {}
