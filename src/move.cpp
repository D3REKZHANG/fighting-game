#include "move.h"
#include "util.cc"

Move::Move(Animation* animation, std::vector<Frame> frameData)
: animation{animation}, frameData{frameData} {}

bool Move::update(){
  if(currentFrame == frameData.size()-1){
    return true;
  }
  if(counter != frameData[currentFrame].frameCount) {
    counter++;
    return false;
  }
  currentFrame++;
  animation->currentFrame++;
  counter = 0;
  return false;
}

void Move::draw(Vector2 pos){
  animation->draw(pos);
}

Frame Move::getFrame(){
  return frameData[currentFrame];
}

void Move::reset() {
  currentFrame = 0;
  counter = 0;
  animation->currentFrame = 0;
}
