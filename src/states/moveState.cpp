#include "moveState.h"
#include "player.h"
#include "raylib.h"
#include "state.h"
#include "util.h"
#include "raymath.h"

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
  return nullptr;
}

State* MoveState::update(){

  player->vel = getFrame().vel;
  if(player->inverse) player->vel = u::negate(player->vel);

  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);

  if(counter != frameData[currentFrame].frameCount) {
    counter++;
    return nullptr;
  }

  if(currentFrame+1 == frameData.size()){
    return new ControlState(player);
  }

  currentFrame++;
  animation->currentFrame++;
  counter = 0;

  return nullptr;
}

void MoveState::draw(){
  animation->draw(player->pos, player->inverse);

  // Draw Frame Data
  DrawText(std::to_string(currentFrame).c_str(), 300,50, 30, DARKGRAY);
  int frames = 0;
  for(int f=0;f<frameData.size();f++) {
    Color color;
    switch(frameData[f].state) {
      case STARTUP: color = BLUE; break;
      case ACTIVE: color = GREEN; break;
      case RECOVERY: color = RED; break;
      case INACTIVE: color = GRAY; break;
    }
    for(int i=0;i<frameData[f].frameCount;i++) {
      int width = 15;
      DrawRectangleLines(349+frames*(width+5),99,width+2,width+2,DARKGRAY);

      if((f==currentFrame && counter >= i) || f < currentFrame) {
        DrawRectangle(350+frames*(width+5),100,width,width,color);
      }
      frames++;
    }
  }
}

Frame MoveState::getFrame(){
  return frameData[currentFrame];
}

void MoveState::reset() {
  currentFrame = 0;
  counter = 0;
  animation->currentFrame = 0;
}
