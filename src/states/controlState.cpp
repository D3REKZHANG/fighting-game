#include "state.h"
#include "player.h"
#include "raymath.h"
#include "moveState.h"
#include "game.h"
using namespace std;

ControlState::ControlState(Player* player) : State(player) {}

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
  // LEFT/RIGHT
  if(motion == 4 || motion == 6) {
    float speed = player->stats.walk_speed;
    if (motion == 4) 
      speed *= -1; // for left walk
    
    player->vel.x = speed;
    player->setAnimation("run");
    player->currentAnimation->active = true;
  }
  // NEUTRAL
  if(motion == 5){
    player->vel.x = 0;
    player->setAnimation("idle");
  }
  // JUMP
  if(motion == 7 || motion == 8 || motion == 9){
    return new JumpState(player);
  }

  // MOVES
  if(input.button == LIGHT){
    return player->getMove("light");
  }
  if(input.button == MEDIUM){
    return player->getMove("medium");
  }
  if(input.button == HEAVY){
    return player->getMove("heavy");
  }
  return nullptr;
}

State* ControlState::update(){
  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);
  player->pos.x = Clamp(player->pos.x, 0.0f, (float)player->game->getWidth());
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
