#include "game.h"
#include "player.h"
#include "inputReader.h"
#include "raylib.h"
#include "spritesheet.h"
#include "util.h"
#include "state.h"
#include "moveState.h"
#include <string>

using u::assets;

Game::Game(int width, int height):screenWidth{width},screenHeight{height}{
  // initialize asset manager
  assets();

  groundPosition = screenHeight - 50;
  r1 = new InputReader(this, p1, ControlSet{KEYBOARD, -1, KEY_A, KEY_D, KEY_SPACE, KEY_S, KEY_J});
  r2 = new InputReader(this, p2, ControlSet{KEYBOARD, -1, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_L});
  r3 = new InputReader(this, p1, ControlSet{CONTROLLER, 0, 4, 2, 1, 3, 5});
  p1 = new Celsius(this, r1);
  p2 = new Naruto(this, r2);
}

void Game::draw(){
  DrawRectangle(0, groundPosition, screenWidth, 50, BLACK);
  p1->draw();
  p2->draw();
  r1->drawQueue();
  DrawText(p1->currentState->getName().c_str(), 10, 70, 20, DARKGRAY);
}

void detectHits(Player* attacker, Player* receiver) {
  if(attacker->currentState->getName() != "MOVE") {
    return;
  }

  MoveState* attackerState = static_cast<MoveState*>(attacker->currentState);

  for(Player::Box hitbox : attackerState->getHitbox()) {
    for(Player::Box hurtbox : receiver->currentState->getHurtbox()) {
      if(CheckCollisionRecs(hitbox.getTranslated(attacker), hurtbox.getTranslated(receiver))) {
        attackerState->handleHit(receiver);
        return;
      }
    }
  }
}

void Game::update(){
  p1->update();
  p2->update();

  detectHits(p1, p2);
  detectHits(p2, p1);

  // detect crossover, update inverse
  p1->inverse = p1->pos.x > p2->pos.x;
  p2->inverse = !p1->inverse;
}

void Game::reset(){
  p1->pos = {p1->size.x, groundPosition - p1->size.y/2};
  p2->pos = {screenWidth - p1->size.x, groundPosition - p1->size.y/2};
  player1Score = 0;
  player2Score = 0;
}

int Game::getWidth(){
  return screenWidth;
}
int Game::getHeight(){
  return screenHeight;
}
int Game::getGroundPos(){
  return groundPosition;
}

Game::~Game() {
  delete p1;
  delete p2;
  delete r1;
  delete r2;
  delete r3;
}
