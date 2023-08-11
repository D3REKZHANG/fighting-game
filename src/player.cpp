#include "player.h"
#include "inputReader.h"
#include "raymath.h"
#include "game.h"
#include "spritesheet.h"
#include "animation.h"
#include "moveState.h"
#include "util.h"
#include "assetManager.h"
#include <typeinfo>

using u::assets; 

Player::Player(Color c, Vector2 size, Game* game, InputReader* inputReader, bool inverse)
  : colour{c},vel{0,0},size{size},game{game}, inverse{inverse}, inputReader{inputReader}
{
  //anim["idle"] = new Animation(ss["main"], 39, 42, 8, true);
  anim["idle"] = new Animation(assets()->ss["celsius"], 1, 1, 8, true);
  anim["swing"] = new Animation(assets()->ss["main"], 43, 59, 5);
  anim["special"] = new Animation(assets()->ss["main"], {5,14}, {4, 16}, 8);
  anim["thrust"] = new Animation(assets()->ss["celsius"], 2, 6, 0);
  anim["hurt"] = new Animation(assets()->ss["celsius_hurt"], 1, 1, 8, true);

  Player::Box defaultHurtbox = Player::Box{-size.x/2-20,-size.y/2, size.x+40, size.y};
  move["thrust"] = new MoveState(this, anim["thrust"], {
    {STARTUP, {2, 0}, 4, {}, {defaultHurtbox}},
    {ACTIVE, {4, 0}, 4, {{30,-10,200,20}}, {defaultHurtbox, {30,-20,100,40}}},
    {ACTIVE, {0, 0}, 4, {{30,-10,220,20}}, {defaultHurtbox, {30,-20,100,40}}},
    {RECOVERY, {-4, 0}, 4, {}, {defaultHurtbox, {30,-20,100,40}}},
    {RECOVERY, {-2, 0}, 4, {}, {defaultHurtbox}},
  });

  setAnimation("idle");
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
  if(anim.find(anim_key) == anim.end())
    throw "Animation key does not exist";

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
