#include "player.h"
#include "inputReader.h"
#include "raymath.h"
#include "game.h"
#include "spritesheet.h"
#include "animation.h"
#include "moveState.h"
#include "util.h"
#include <typeinfo>

Player::Player(Color c, Vector2 size, Game* game, InputReader* inputReader, bool inverse)
  : colour{c},vel{0,0},size{size},game{game}, inverse{inverse}, inputReader{inputReader}
{
  tx["spritesheet"] = LoadTexture("assets/adventurer_sprite.png");
  tx["cel_spritesheet"] = LoadTexture("assets/celsius_thrust.png");
  ss["main"] = new Spritesheet(tx["spritesheet"], {50, 37});
  ss["celsius"] = new Spritesheet(tx["cel_spritesheet"], {500, 250});

  //anim["idle"] = new Animation(ss["main"], 39, 42, 8, true);
  anim["idle"] = new Animation(ss["celsius"], 1, 1, 8, true);
  anim["swing"] = new Animation(ss["main"], 43, 59, 5);
  anim["special"] = new Animation(ss["main"], {5,14}, {4, 16}, 8);
  anim["thrust"] = new Animation(ss["celsius"], 2, 6, 0);

  move["thrust"] = new MoveState(this, anim["thrust"], {
    {STARTUP, {2, 0}, 4},
    {ACTIVE, {4, 0}, 4},
    {ACTIVE, {0, 0}, 4},
    {RECOVERY, {-4, 0}, 4},
    {RECOVERY, {-2, 0}, 4},
  });

  setAnimation("idle");
  currentState = new ControlState(this);
}

void Player::update(){
  State* newState = currentState->handleInput(inputReader->read());
  if(newState != nullptr){
    currentState->exiting();
    if(currentState->getName() != "MOVE") delete currentState;
    currentState = newState;
    newState->init();
  }
  State* newState2 = currentState->update();
  if(newState2 != nullptr){
    currentState->exiting();
    if(currentState->getName() != "MOVE") delete currentState;
    currentState = newState2;
    newState2->init();
  }
  /* if(currentAction) {
    if(currentAction->update()){
      currentAction = nullptr;
      state = IDLE;
      vel = {0,0};
    }else{
      vel = static_cast<Move*>(currentAction)->getFrame().vel;
      if(inverse) vel = u::negate(vel);
    }
  }  */
}

void Player::fireball(){
  currentAnimation = anim["special"];
  currentAnimation->play();
}

void Player::draw(){
  // collide box
  // DrawRectangleV(u::topleft(pos,size.x,size.y), size, GREEN);

  // if(currentAction){
  //   DrawText(std::to_string(static_cast<Move*>(currentAction)->currentFrame).c_str(), 50,400, 30, DARKGRAY);
  //   DrawText(std::to_string(static_cast<Move*>(currentAction)->counter).c_str(), 50,450, 30, DARKGRAY);
  //   FrameState state = static_cast<Move*>(currentAction)->getFrame().state;
  //   Color color;
  //   switch(state) {
  //     case STARTUP: color = YELLOW; break;
  //     case ACTIVE: color = RED; break;
  //     case RECOVERY: color = BLUE; break;
  //     case NONE: color = GRAY; break;
  //   }
  //   DrawRectangleV(u::topleft(pos,50,50), {50,50}, color);
  //   currentAction->draw(pos, inverse);
  // } else {
  //   currentAnimation->draw(pos, inverse);
  // }
  DrawRectangleV(u::topleft(pos,size.x,size.y), size, GREEN);
  currentState->draw();
}

void Player::setAnimation(std::string anim_key){
  if(anim.find(anim_key) == anim.end())
    throw "Animation key does not exist";

  currentAnimation = anim[anim_key];
}

Player::~Player() {
  for(auto s : ss){
    delete s.second;
  }
  for(auto a : anim){
    delete a.second;
  }
  for(auto m : move){
    delete m.second;
  }
}
