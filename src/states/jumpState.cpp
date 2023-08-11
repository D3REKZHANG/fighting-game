#include "state.h"
#include "player.h"
#include "game.h"
#include "raymath.h"

JumpState::JumpState(Player* p): State(p) {}

std::string JumpState::getName() { return "JUMP"; }

void JumpState::init() {
  player->vel.y = -30;
  player->pos.y -= 1;

  player->setAnimation("idle");
  player->currentAnimation->play();
}
void JumpState::exiting() {
  player->currentAnimation->stop();
}

State* JumpState::handleInput(Input input) {
  return nullptr;
}

State* JumpState::update() {
  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);

  if (player->pos.y >= player->game->getGroundPos()-player->size.y/2) {
    player->pos.y = player->game->getGroundPos()-player->size.y/2;
    player->accel.y = 0;
    player->vel = {0, 0};
    return new ControlState(player);
  } else {
    player->accel.y = 3; // gravity
  }

  return nullptr;
};

void JumpState::draw() {
  player->currentAnimation->draw(player->pos, player->inverse);

  for(Player::Box hurtbox : getHurtbox()) {
    DrawRectangleLinesEx(hurtbox.getTranslated(player), 1, GREEN);
  }
};

std::vector<Player::Box> JumpState::getHurtbox() {
  return {{-player->size.x/2-20,-player->size.y/2, player->size.x+40, player->size.y}};
}

JumpState::~JumpState() {}
