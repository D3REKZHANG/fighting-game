#include "player.h"
#include "inputReader.h"
#include "raymath.h"
#include "game.h"
#include "spritesheet.h"
#include "animation.h"
#include "moveState.h"
#include "state.h"
#include "util.h"
#include "assetManager.h"
#include <cassert>

Player::Player(Game* game, InputReader* inputReader)
  : game{game}, inputReader{inputReader} {}

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
  if(!anim.contains(anim_key)) {
    u::log("ERROR: animation key \"" + anim_key + "\" not found.");
    assert(anim.contains(anim_key));
  }

  currentAnimation = anim[anim_key];
}

MoveState* Player::getMove(std::string move_key) {
  if(!move.contains(move_key)) {
    u::log("ERROR: move key \"" + move_key + "\" not found.");
    return nullptr;
  }

  return move[move_key];
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
