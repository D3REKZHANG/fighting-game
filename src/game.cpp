#include "game.h"
#include "player.h"
#include "inputReader.h"
#include "raylib.h"
#include "raymath.h"
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

  r1 = new InputReader(this, p1, ControlSet{KEYBOARD, -1, KEY_A, KEY_D, KEY_SPACE, KEY_S, KEY_J, KEY_K, KEY_L});
  r2 = new InputReader(this, p2, ControlSet{KEYBOARD, -1, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_U, KEY_I, KEY_O});
  r3 = new InputReader(this, p1, ControlSet{CONTROLLER, 0, 4, 2, 1, 3, 5});

  p1 = new Xero(this, r1);
  p2 = new Xun(this, r2);

  // Initialize camera
  camera.target = (Vector2){ static_cast<float>(screenWidth / 2.0f), static_cast<float>(groundPosition) };
  camera.offset = (Vector2){ static_cast<float>(screenWidth / 2.0f), static_cast<float>(groundPosition) };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  training = true;
}

void Game::draw(){
  BeginMode2D(camera);

  ClearBackground(LIGHTGRAY);

  DrawRectangle(-200, groundPosition, screenWidth+200*2, 200, DARKGRAY); // ground
  // DrawRectangle(-120, -200, 100, screenHeight+150, DARKGRAY); // left wall
  // DrawRectangle(screenWidth+20, -200, 100, screenHeight+150, DARKGRAY); // right wall
  p1->draw();
  p2->draw();
  // r1->drawQueue();
  // DrawText(p1->currentState->getName().c_str(), 10, 70, 20, DARKGRAY);

  EndMode2D();

  // move frames
  if(p1->currentState->getName() == "MOVE") static_cast<MoveState*>(p1->currentState)->drawFrames();
  if(p2->currentState->getName() == "MOVE") static_cast<MoveState*>(p2->currentState)->drawFrames();

  // healthbar
  const Vector2 bar = {300, 20};
  DrawRectangle(10,10, bar.x, bar.y, WHITE);
  DrawRectangle(screenWidth-bar.x-10, 10, 300, bar.y, WHITE);
  DrawRectangle(10,10, p1->stats.current_health/p1->stats.max_health * bar.x, bar.y, RED);
  DrawRectangle(screenWidth-p2->stats.current_health/p2->stats.max_health * bar.x-10, 10, p2->stats.current_health/p2->stats.max_health * bar.x, bar.y, RED);
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

  // middle of both players, clamping so that wall edges are always at edge of screen
  float targetPosition = Clamp((p1->pos.x + p2->pos.x) * 0.5f, screenWidth/4.0f, screenWidth - screenWidth/4.0f);
  
  float dist = fabsf(camera.target.x - targetPosition);
  camera.target.x = Lerp(camera.target.x, targetPosition, 0.01f + 0.002f*dist);

  // Calculate zoom level based on characters' distance
  float distance = fabsf(p1->pos.x-p2->pos.x);
  float newZoom = screenWidth / (distance * 1.3f); // Adjust multiplier as needed
  camera.zoom = Clamp(newZoom, 0.93f, 1.5f); // Clamp zoom level to desired range
}

void Game::reset(){
  p1->pos.x = p1->size.x;
  p2->pos.x = screenWidth - p2->size.x;
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
  // delete camera;
}
