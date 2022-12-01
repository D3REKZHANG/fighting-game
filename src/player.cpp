#include "player.h"
#include "raymath.h"
#include "game.h"
#include "spritesheet.h"
#include "animation.h"
#include "util.cc"

Player::Player(Color c, int x, int y, Vector2 size, Game* game, bool inverse):colour{c},pos{(float)x, (float)y},vel{0,0},size{size},game{game},grounded{true},inverse{inverse}{
}

void Player::loadAssets(){
  tx["spritesheet"] = LoadTexture("../assets/adventurer_sprite.png");
  tx["cel_spritesheet"] = LoadTexture("../assets/celsius_thrust.png");
  ss["main"] = new Spritesheet(tx["spritesheet"], {50, 37});
  ss["celsius"] = new Spritesheet(tx["cel_spritesheet"], {400, 250});

  //anim["idle"] = new Animation(ss["main"], 39, 42, 8, true);
  anim["idle"] = new Animation(ss["celsius"], 1, 1, 8, true);
  anim["swing"] = new Animation(ss["main"], 43, 59, 5);
  anim["special"] = new Animation(ss["main"], {5,14}, {4, 16}, 8);
  anim["thrust"] = new Animation(ss["celsius"], 2, 6, 3);

  currentAnimation = anim["idle"];
  currentAnimation->play();
  console::log("asdf");
}

void Player::update(){
  
  vel = Vector2Add(vel, accel);
  pos = Vector2Add(pos, vel);

  // adjust y position
  if (pos.y >= game->getGroundPos()-size.y) {
    pos.y = game->getGroundPos()-size.y;
    grounded = true;
  } else {
    grounded = false;
  }

  if(grounded) accel.y = 0;
  else accel.y = 3; // gravity
  
  // animations
  currentAnimation->tick();
}

void Player::fireball(){
  currentAnimation = anim["special"];
  currentAnimation->play();
}

void Player::thrust(){
  currentAnimation = anim["thrust"];
  currentAnimation->play();
}

void Player::draw(){
  DrawRectangleV(pos, size, colour);
  currentAnimation->draw(pos);
}

Player::~Player() {
  for(auto s : ss){
    delete s.second;
  }
  for(auto a : anim){
    delete a.second;
  }
}
