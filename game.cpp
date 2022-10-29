#include "game.h"
#include "player.h"
#include "inputHandler.h"
#include "spritesheet.h"
#include <string>

Game::Game(int width, int height):screenWidth{width},screenHeight{height}{
  groundPosition = screenHeight - 50;
  p1 = new Player(RED, 0, groundPosition-playerSize.y, playerSize, this, false);
  p2 = new Player(BLUE, screenWidth - playerSize.x, groundPosition-playerSize.y, playerSize, this, true);
  h1 = new InputHandler(this, p1, {{"left", KEY_A}, {"right", KEY_D}, {"up", KEY_W}, {"down", KEY_S}});
  h2 = new InputHandler(this, p2, {{"left", KEY_LEFT},{"right", KEY_RIGHT},{"up", KEY_UP},{"down", KEY_DOWN}});
}

void Game::loadAssets(){
  tx["motions"] = LoadTexture("assets/motions.png");       
  tx["test"] = LoadTexture()

  p1->loadAssets();
  p2->loadAssets();
}

void Game::draw(){
  DrawRectangle(0, groundPosition, screenWidth, 50, BLACK);
  p1->draw();
  p2->draw();
  h1->drawQueue();
}

void Game::update(){
  h1->handle();
  h2->handle();
  p1->update();
  p2->update();
}

void Game::reset(){
  p1->pos = {0, groundPosition-playerSize.y};
  p2->pos = {screenWidth - playerSize.x, groundPosition-playerSize.y};
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
