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
  currentFrameNum = 0;
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

  if(counter != frameData[currentFrameNum].frameCount) {
    counter++;
    return nullptr;
  }

  if(currentFrameNum+1 == frameData.size()){
    return new ControlState(player);
  }

  currentFrameNum++;
  animation->currentFrame++;
  counter = 0;

  return nullptr;
}

void MoveState::draw(){
  animation->draw(player->pos, player->inverse);

  for(Player::Box hitbox : getHitbox()) {
    DrawRectangleLinesEx(hitbox.getTranslated(player), 1, RED);
  }

  for(Player::Box hurtbox : getHurtbox()) {
    DrawRectangleLinesEx(hurtbox.getTranslated(player), 1, GREEN);
  }

  // Draw Frame Data
  DrawText(std::to_string(currentFrameNum).c_str(), 300,50, 30, DARKGRAY);
  int frames = 0;
  for(size_t f=0;f<frameData.size();f++) {
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

      if((f == currentFrameNum && counter >= i) || f < currentFrameNum) {
        DrawRectangle(350+frames*(width+5),100,width,width,color);
      }
      frames++;
    }
  }
}

void MoveState::handleHit(Player* playerHit) {
  Vector2 forceVel = {static_cast<float>((playerHit->inverse) ? 10 : -10), 0};
  playerHit->handleStateChange(new HurtState(playerHit, 20, forceVel));
}

std::vector<Player::Box> MoveState::getHurtbox() {
  return frameData[currentFrameNum].hurtbox;
}

std::vector<Player::Box> MoveState::getHitbox() {
  return frameData[currentFrameNum].hitbox;
}

Frame MoveState::getFrame(){
  return frameData[currentFrameNum];
}

void MoveState::reset() {
  currentFrameNum = 0;
  counter = 0;
  animation->currentFrame = 0;
}
