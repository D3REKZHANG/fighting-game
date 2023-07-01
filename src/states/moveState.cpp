#include "moveState.h"
#include "player.h"
#include "state.h"
#include "util.h"

MoveState::MoveState(Player* player, Animation* animation, std::vector<Frame> frameData)
: State(player), animation{animation}, frameData{frameData} { }

std::string MoveState::getName() { return "MOVE"; }

void MoveState::init() {
  counter = 0;
  currentFrame = 0;
  animation->play();
}

void MoveState::exiting() {
  animation->stop();
}

State* MoveState::handleInput(Input input){
  switch(getFrame().state){
    case RECOVERY:
      // check for cancels?
      break;
    default:
      // check for normal buffers/gatlings
      break;
  }
  if(currentFrame == static_cast<int>(frameData.size()-1)){
    return new ControlState(player);
  }
  return nullptr;
}

State* MoveState::update(){
  if(counter != frameData[currentFrame].frameCount) {
    counter++;
    return nullptr;
  }
  currentFrame++;
  animation->currentFrame++;
  counter = 0;
  
  return nullptr;
}

void MoveState::draw(){
  animation->draw(player->pos, player->inverse);
}

Frame MoveState::getFrame(){
  return frameData[currentFrame];
}

void MoveState::reset() {
  currentFrame = 0;
  counter = 0;
  animation->currentFrame = 0;
}
