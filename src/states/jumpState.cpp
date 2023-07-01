#include "state.h"
#include "player.h"
#include "game.h"
#include "raymath.h"

JumpState::JumpState(Player* p): State(p) {}

std::string JumpState::getName() { return "JUMP"; }

void JumpState::init() {
  player->vel.y = -30;
  player->vel.x = 0;
}
void JumpState::exiting() {}

State* JumpState::handleInput(Input input) {
  return nullptr;
}

State* JumpState::update() {
  if (player->pos.y >= player->game->getGroundPos()-player->size.y/2) {
    player->pos.y = player->game->getGroundPos()-player->size.y/2;
    player->accel.y = 0;
    player->vel = {0, 0};
    player->currentState = new ControlState(player);
  } else {
    player->accel.y = 3; // gravity
  }

  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);

  return nullptr;
};

void JumpState::draw() {};

JumpState::~JumpState() {}
