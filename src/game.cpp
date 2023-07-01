#include "game.h"
#include "player.h"
#include "inputReader.h"
#include "raylib.h"
#include "spritesheet.h"
#include "util.h"
#include <string>

Game::Game(int width, int height):screenWidth{width},screenHeight{height}{
  tx["motions"] = LoadTexture("assets/motions.png");       

  groundPosition = screenHeight - 50;
  r1 = new InputReader(this, p1, ControlSet{KEYBOARD, -1, KEY_A, KEY_D, KEY_W, KEY_S, KEY_J});
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
