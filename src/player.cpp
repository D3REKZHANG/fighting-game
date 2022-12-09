#include "player.h"
#include "raymath.h"
#include "game.h"
#include "spritesheet.h"
#include "animation.h"
#include "move.h"
#include "util.cc"

Player::Player(Color c, int x, int y, Vector2 size, Game* game, bool inverse)
  : colour{c},pos{(float)x, (float)y},vel{0,0},size{size},game{game},state{IDLE},inverse{inverse} {}

void Player::loadAssets(){
  tx["spritesheet"] = LoadTexture("assets/adventurer_sprite.png");
  tx["cel_spritesheet"] = LoadTexture("assets/celsius_thrust.png");
  ss["main"] = new Spritesheet(tx["spritesheet"], {50, 37});
  ss["celsius"] = new Spritesheet(tx["cel_spritesheet"], {400, 250});

  //anim["idle"] = new Animation(ss["main"], 39, 42, 8, true);
  anim["idle"] = new Animation(ss["celsius"], 1, 1, 8, true);
  anim["swing"] = new Animation(ss["main"], 43, 59, 5);
  anim["special"] = new Animation(ss["main"], {5,14}, {4, 16}, 8);
  anim["thrust"] = new Animation(ss["celsius"], 2, 6, 3);

  move["thrust"] = new Move(anim["thrust"], {
    {STARTUP, {0, 0}, 5},
    {STARTUP, {0, 0}, 5},
    {ACTIVE, {10, 0}, 10},
    {RECOVERY, {0, 0}, 5},
    {RECOVERY, {0, 0}, 5},
    {RECOVERY, {0, 0}, 5},
  });

  setAnimation("idle");
}

void Player::update(){
  if(currentAction) {
    if(currentAction->update()){
      currentAction = nullptr;
    }
  } 
  // PHYSICS STUFF
  vel = Vector2Add(vel, accel);
  pos = Vector2Add(pos, vel);

  if(state == JUMPING) {
    if (pos.y >= game->getGroundPos()-size.y) {
      pos.y = game->getGroundPos()-size.y;
      state = IDLE;
      accel.y = 0;
    } else {
      accel.y = 3; // gravity
    }
  }
}

void Player::fireball(){
  currentAnimation = anim["special"];
  currentAnimation->play();
}

void Player::thrust(){
  if(!currentAction){
    currentAction = move["thrust"];
    move["thrust"]->reset();
  }
}

void Player::draw(){
  DrawText((currentAction)?"action":"nullptr", 50,400, 30, DARKGRAY);
  DrawRectangleV(pos, {50,50}, GREEN);
  if(currentAction){
    FrameState state = static_cast<Move*>(currentAction)->getFrame().state;
    Color color;
    switch(state) {
      case STARTUP: color = YELLOW; break;
      case ACTIVE: color = RED; break;
      case RECOVERY: color = BLUE; break;
      case NONE: color = GRAY; break;
    }
    DrawRectangleV(pos, size, color);
    currentAction->draw(pos);
  } else {
    currentAnimation->draw(pos);
  }
}

bool Player::setAnimation(std::string anim_key){
  if(anim.find(anim_key) == anim.end())
    return false;

  currentAnimation = anim[anim_key];
  return true;
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
