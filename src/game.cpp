#include "game.h"
#include "player.h"
#include "inputHandler.h"
#include "raylib.h"
#include "spritesheet.h"
#include "util.cc"
#include <string>

Game::Game(int width, int height):screenWidth{width},screenHeight{height}{
  groundPosition = screenHeight - 50;
  p1 = new Player(RED, playerSize, this, false);
  p2 = new Player(BLUE, playerSize, this, true);
  h1 = new InputHandler(this, p1, {{"left", KEY_A}, {"right", KEY_D}, {"up", KEY_W}, {"down", KEY_S}, {"a", KEY_J}});
  h2 = new InputHandler(this, p2, {{"left", KEY_LEFT},{"right", KEY_RIGHT},{"up", KEY_UP},{"down", KEY_DOWN}, {"a", KEY_K}});
  h3 = new InputHandler(this, p1, {{"controller", 0}, {"left", 4},{"right", 2},{"up", 1},{"down", 3}, {"a", 5}});
}

void Game::loadAssets(){
  tx["motions"] = LoadTexture("assets/motions.png");       

  p1->loadAssets();
  p2->loadAssets();
}

void Game::draw(){
  DrawRectangle(0, groundPosition, screenWidth, 50, BLACK);
  p1->draw();
  p2->draw();
  h3->drawQueue();
}

void Game::update(){
  h3->handle();
  h2->handle();
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
  delete h1;
  delete h2;
}
