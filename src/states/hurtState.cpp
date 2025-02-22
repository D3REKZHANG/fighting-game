#include "state.h"
#include "player.h"
#include "raymath.h"
#include "util.h"
#include "moveState.h"

HurtState::HurtState(Player* player, int frames, Vector2 forceVel) : State(player), frames(frames), forceVel(forceVel) {}

std::string HurtState::getName() { return "HURT"; }

void HurtState::init() {
  player->setAnimation("hurt");
  player->currentAnimation->play();
  player->vel = forceVel;
  counter = 0;
}

void HurtState::exiting() {
  player->currentAnimation->stop();
}

State* HurtState::handleInput(Input input) {
  // check burst button?
  
  return nullptr;
}

State* HurtState::update(){
  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);
  player->currentAnimation->tick();

  if(abs(player->vel.x) > 0.1) {
    player->accel.x = (player->vel.x < 0) ? 2 : -2;
  } else {
    player->vel.x = 0;
    player->accel.x = 0;
  }

  if(abs(player->vel.y) > 0.1) {
    player->accel.y = (player->vel.y < 0) ? 2 : -2;
  } else {
    player->vel.y = 0;
    player->accel.y = 0;
  }

  counter++;
  if(counter > frames) {
    if(player->stats.current_health <= 0) {
      return new DeathState(player);
    }
    return new ControlState(player);
  }

  return nullptr;
}

void HurtState::draw(){
  player->currentAnimation->draw(player->pos, player->inverse);

  for(Player::Box hurtbox : getHurtbox()) {
    DrawRectangleLinesEx(hurtbox.getTranslated(player), 1, GREEN);
  }
}

std::vector<Player::Box> HurtState::getHurtbox() {
  return {{-player->size.x/2-20,-player->size.y/2, player->size.x+40, player->size.y}};
}

HurtState::~HurtState() {}
