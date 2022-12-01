#include "inputHandler.h"
#include "player.h"
#include "game.h"
#include "raylib.h"

#include <iostream>
#include <algorithm>
#include <cmath>

InputHandler::InputHandler(Game* game, Player* player, std::unordered_map<std::string, int> keyMap):game{game},player{player},keyMap{keyMap}{}

void InputHandler::readInput(){
  // 0 = left/up, 1 = neutral, 2 = right/down
  Vector2 key = {
    static_cast<float>(IsKeyDown(keyMap["right"])-IsKeyDown(keyMap["left"])+1),
    static_cast<float>(IsKeyDown(keyMap["up"])-IsKeyDown(keyMap["down"])+1)
  };

  // ternary conversion
  int motion = 3*key.y + key.x + 1;

  // if different, add to queue
  if(inputQueue.size() == 0 || motion != inputQueue.back().input)
    inputQueue.push_back({motion, GetTime()});
}

void InputHandler::handle(){
  readInput();

  // check for motion inputs
  // 2 3 6
  int size = inputQueue.size();
  if(size >= 3 && inputQueue[size-3].input == 2 && inputQueue[size-2].input == 3 && inputQueue[size-1].input == 6){
    player->fireball();
  }

  if(IsKeyPressed(KEY_J)){
    player->thrust();
  }

  int motion = inputQueue.back().input;
  if(player->grounded){
    if(motion == 4){
      player->vel.x = -player->speed;
    }
    else if(motion == 6){
      player->vel.x = player->speed;
    }
    else{
      player->vel.x = 0;
    }
    if(motion == 7 || motion == 8 || motion == 9){
      player->vel.y = -30;
      player->vel.x = 0;
      if(motion == 7)
        player->vel.x = -player->speed;
      if(motion == 9)
        player->vel.x = player->speed;
    }
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
