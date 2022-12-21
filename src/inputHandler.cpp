#include "inputHandler.h"
#include "player.h"
#include "game.h"
#include "raylib.h"

#include <iostream>
#include <algorithm>
#include <cmath>

InputHandler::InputHandler(Game* game, Player* player, std::unordered_map<std::string, int> keyMap):game{game},player{player},keyMap{keyMap}{}

bool InputHandler::isDown(int key) {
  if(keyMap.find("controller") != keyMap.end()){
    return IsGamepadButtonDown(keyMap["controller"], key);
  }
  return IsKeyDown(key);
};

void InputHandler::readInput(){
  // 0 = left/up, 1 = neutral, 2 = right/down
  Vector2 key = {
    static_cast<float>(isDown(keyMap["right"])-isDown(keyMap["left"])+1),
    static_cast<float>(isDown(keyMap["up"])-isDown(keyMap["down"])+1)
  };

  // ternary conversion
  int motion = 3*key.y + key.x + 1;

  // if different, add to queue
  if(inputQueue.size() == 0 || motion != inputQueue.back().input)
    inputQueue.push_back({motion, GetTime()});
}


void InputHandler::handle(){
  auto handleRun = [](Player* player, int motion) {
    if(motion == 4 || motion == 6){
      if(motion == 4) player->vel.x = -player->speed;
      if(motion == 6) player->vel.x = player->speed;
      return true;
    }
    return false;
  };

  auto handleJump = [](Player* player, int motion) {
    if(motion == 7 || motion == 8 || motion == 9){
      player->vel.y = -30;
      player->vel.x = 0;
      if(motion == 7)
        player->vel.x = -player->speed;
      if(motion == 9)
        player->vel.x = player->speed;
      return true;
    }
    return false;
  };

  readInput();

  // check for motion inputs
  // 2 3 6
  int size = inputQueue.size();
  if(size >= 3 && inputQueue[size-3].input == 2 && inputQueue[size-2].input == 3 && inputQueue[size-1].input == 6){
    player->fireball();
  }

  if(isDown(keyMap["a"])){
    player->thrust();
  }

  int motion = inputQueue.back().input;
  switch(player->state){
    case IDLE:
      if(handleRun(player, motion))
        player->state = RUNNING;
        // set animation to running
      if(handleJump(player, motion))
        player->state = JUMPING;
        // set animation to jumping
      break;
    case RUNNING:
      handleRun(player, motion);
      if(motion == 5){
        player->vel.x = 0;
        player->state = IDLE;
        player->setAnimation("idle");
      }
      if(handleJump(player, motion))
        player->state = JUMPING;
      break;
  }

  // clear old inputs
  double currentTime = GetTime();
  if(currentTime - inputQueue.front().time > 1.5){
    inputQueue.pop_front();
  }
}

void InputHandler::drawQueue(){
  float drawn = 0;
  for(size_t i=std::max(static_cast<int>(inputQueue.size())-10, 0);i<inputQueue.size();i++){
    int motion = inputQueue[i].input;
    if(motion != 5){
      float r = floor(2-(motion-1)/3);
      float c = (motion-1)%3;
      DrawTextureRec(game->tx["motions"], Rectangle{c*50,r*50,50,50}, Vector2{10+50*drawn, 75}, WHITE);
      drawn++;
    }
  }
}
