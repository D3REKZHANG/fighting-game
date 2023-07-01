#include "inputReader.h"
#include "player.h"
#include "game.h"
#include "raylib.h"
#include "util.h"

#include <iostream>
#include <algorithm>
#include <cmath>

InputReader::InputReader(Game* game, Player* player, ControlSet controls):game{game},player{player},controls{controls}{}

bool InputReader::isDown(int key) {
  if(controls.type == CONTROLLER){
    return IsGamepadButtonPressed(controls.controller_id, key);
  }
  return IsKeyDown(key);
};

Input InputReader::read(){
  // 0 = left/up, 1 = neutral, 2 = right/down
  Vector2 key = {
    static_cast<float>(isDown(controls.right)-isDown(controls.left)+1),
    static_cast<float>(isDown(controls.up)-isDown(controls.down)+1)
  };

  // ternary conversion
  int motion = 3*key.y + key.x + 1;

  Button button; 
  if(isDown(controls.a)) button = LIGHT;
  else button = NONE;

  Input input = { motion, button, GetTime() };
  if(inputQueue.size() == 0 || input != inputQueue.back()) {
    inputQueue.push_back(input);
  }

  // clear old inputs
  double currentTime = GetTime();
  if(currentTime - inputQueue.front().time > 1.5){
    inputQueue.pop_front();
  }

  return inputQueue.back();

  // check for motion inputs
  // 2 3 6
  /* int size = inputQueue.size();
  if(size >= 3 && inputQueue[size-3].motion == 2 && inputQueue[size-2].motion == 3 && inputQueue[size-1].motion == 6){
    player->fireball();
  }

  if(isDown(controls.a)){
    player->thrust();
  } */
}

void InputReader::drawQueue(){
  float drawn = 0;
  for(size_t i=std::max(static_cast<int>(inputQueue.size())-6, 0);i<inputQueue.size();i++){
    int motion = inputQueue[i].motion;
    if(inputQueue[i].button != NONE || motion != 5){
      float r = floor(2-(motion-1)/3);
      float c = (motion-1)%3;
      DrawTextureRec(game->tx["motions"], Rectangle{c*50,r*50,50,50}, Vector2{10, 340-50*drawn}, RED);
      if(inputQueue[i].button != NONE) 
        DrawRectangle(10+50+10,350-50*drawn,30,30,RED);
      drawn++;
    }
  }
}
