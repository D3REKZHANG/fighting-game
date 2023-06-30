#include "move.h"
#include "player.h"
#include "state.h"
#include "util.h"

Move::Move(Animation* animation, std::vector<Frame> frameData)
: animation{animation}, frameData{frameData} {}

void Move::init() {}
void Move::exiting() {}

State* Move::handleInput(Player *player, Input input){
  switch(getFrame().state){
    case RECOVERY:
      // check for cancels?
      break;
    default:
      // check for normal buffers/gatlings
      break;
  }
  if(currentFrame == frameData.size()-1){
    return new ControlState();
  }
  return nullptr;
}

void Move::update(Player* player){
  if(counter != frameData[currentFrame].frameCount) {
    counter++;
    return;
  }
  currentFrame++;
  animation->currentFrame++;
  counter = 0;
}

void Move::draw(Player* player){
  animation->draw(player->pos, player->inverse);
}

Frame Move::getFrame(){
  return frameData[currentFrame];
}

void Move::reset() {
  currentFrame = 0;
  counter = 0;
  animation->currentFrame = 0;
}
