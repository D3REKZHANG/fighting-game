#include "game.h"
#include "player.h"
#include "inputReader.h"
#include "raylib.h"
#include "spritesheet.h"
#include "util.h"
#include "state.h"
#include <string>

using u::assets;

Game::Game(int width, int height):screenWidth{width},screenHeight{height}{
  assets()->tx["motions"] = LoadTexture("assets/motions.png");       
  assets()->tx["spritesheet"] = LoadTexture("assets/adventurer_sprite.png");
  assets()->tx["cel_spritesheet"] = LoadTexture("assets/celsius_thrust.png");
  assets()->ss["main"] = new Spritesheet(assets()->tx["spritesheet"], {50, 37});
  assets()->ss["celsius"] = new Spritesheet(assets()->tx["cel_spritesheet"], {500, 250});

  groundPosition = screenHeight - 50;
  r1 = new InputReader(this, p1, ControlSet{KEYBOARD, -1, KEY_A, KEY_D, KEY_SPACE, KEY_S, KEY_J});
  r2 = new InputReader(this, p2, ControlSet{KEYBOARD, -1, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_L});
  r3 = new InputReader(this, p1, ControlSet{CONTROLLER, 0, 4, 2, 1, 3, 5});
  p1 = new Player(RED, playerSize, this, r1, false);
  p2 = new Player(BLUE, playerSize, this, r2, true);
}

void Game::draw(){
  DrawRectangle(0, groundPosition, screenWidth, 50, BLACK);
  p1->draw();
  p2->draw();
  r1->drawQueue();
  DrawText(p1->currentState->getName().c_str(), 10, 70, 20, DARKGRAY);
}

void Game::update(){
  p1->update();
  p2->update();
}

void Game::reset(){
  p1->pos = {playerSize.x, groundPosition-playerSize.y/2};
  p2->pos = {screenWidth - playerSize.x, groundPosition-playerSize.y/2};
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
