#include "move.h"

Move::Move(Animation* animation, std::vector<Frame> frameData)
: animation{animation}, frameData{frameData} {}

void Move::update(){
  if(counter != frameData[currentFrame].frameCount) {
    counter++;
    return;
  }
  currentFrame++;
  animation->currentFrame++;
  counter = 0;
}

void Move::draw(Vector2 pos){
  animation->draw(pos);
}

Frame Move::getFrame(){
  return frameData[currentFrame];
}
