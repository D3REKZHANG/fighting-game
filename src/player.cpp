#include "player.h"
#include "inputReader.h"
#include "raymath.h"
#include "game.h"
#include "spritesheet.h"
#include "animation.h"
#include "moveState.h"
#include "util.h"
#include "assetManager.h"
#include <cassert>

Player::Player(Game* game, InputReader* inputReader)
  : game{game}, inputReader{inputReader}
{
  currentState = new ControlState(this);
}

void Player::update(){
  State* newState;

  newState = currentState->handleInput(inputReader->read());
  handleStateChange(newState);

  newState = currentState->update();
  handleStateChange(newState);
}

void Player::handleStateChange(State* state) {
  if(state != nullptr){
    currentState->exiting();
    if(currentState->getName() != "MOVE") delete currentState;
    currentState = state;
    state->init();
  }
}

void Player::fireball(){
  currentAnimation = anim["special"];
  currentAnimation->play();
}

void Player::draw(){
  currentState->draw();

  // Movement Collision Boxes
  Vector2 vec = u::topleft(pos,size.x,size.y);
  DrawRectangleLines(vec.x, vec.y, size.x, size.y, BROWN);
}

void Player::setAnimation(std::string anim_key){
  assert(anim.find(anim_key) != anim.end());

  currentAnimation = anim[anim_key];
}

Player::Box::Box(Rectangle rec): relativeBounds(rec) {}
Player::Box::Box(): relativeBounds(Rectangle{-1,0,0,0}) {}
Player::Box::Box(float x, float y, float w, float h): relativeBounds(Rectangle{x,y,w,h}) {}

Rectangle Player::Box::getTranslated(Player* player) {
  // get translated positioning
  float x;
  if(player->inverse) {
    x = player->pos.x-relativeBounds.x-relativeBounds.width; 
  } else {
    x = player->pos.x+relativeBounds.x;
  }

  return Rectangle{x, player->pos.y+relativeBounds.y, relativeBounds.width, relativeBounds.height };
}

Player::~Player() {
  for(auto a : anim){
    delete a.second;
  }
  for(auto m : move){
    delete m.second;
  }
}
