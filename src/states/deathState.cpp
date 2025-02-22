#include "state.h"
#include "player.h"
#include "game.h"
using namespace std;

DeathState::DeathState(Player* player) : State(player) {}

std::string DeathState::getName() { return "DEATH"; }

void DeathState::init() {
  player->setAnimation("death");
  player->currentAnimation->play();
  player->size = player->defaultSize;
  player->pos.y = player->game->getGroundPos()-player->size.y/2;
}

void DeathState::exiting() {
  player->currentAnimation->stop();
}

State* DeathState::handleInput(Input input) {
  return nullptr;
}

State* DeathState::update(){
  player->currentAnimation->tick();
  return nullptr;
}

void DeathState::draw(){
  player->currentAnimation->draw(player->pos, player->inverse);
}

std::vector<Player::Box> DeathState::getHurtbox() {
  return {{0,0,0,0}};
}

DeathState::~DeathState() {}
