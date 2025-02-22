#include "moveState.h"
#include "game.h"
#include "player.h"
#include "raylib.h"
#include "state.h"
#include "util.h"
#include "raymath.h"

MoveState::MoveState(Player* player, Animation* animation, Properties properties, std::vector<Frame> frameData)
: State(player), animation{animation}, properties{properties}, frameData{frameData} { }

std::string MoveState::getName() { return "MOVE"; }

void MoveState::init() {
  counter = 0;
  currentFrameNum = 0;
  animation->play();
}

void MoveState::exiting() {
  animation->stop();
  hitHandled = false;
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
  if(player->inverse) player->vel = Vector2Negate(player->vel);

  player->vel = Vector2Add(player->vel, player->accel);
  player->pos = Vector2Add(player->pos, player->vel);

  Vector2 size = getFrame().size;
  if(size.x > 0 && size.y > 0) player->size = size;

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

}

void MoveState::drawFrames() {
  // Draw Frame Data
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
      DrawRectangleLines(12+frames*(width+5),59,width+2,width+2,DARKGRAY);

      if((f == currentFrameNum && counter >= i) || f < currentFrameNum) {
        DrawRectangle(13+frames*(width+5),60,width,width,color);
      }
      frames++;
    }
  }
}

void MoveState::handleHit(Player* playerHit) {
  if(hitHandled) return;
  if(playerHit->currentState->getName() == "DEATH") return;
  hitHandled = true;
  Vector2 forceVel = {static_cast<float>((playerHit->inverse) ? 1 : -1) * properties.knockbackVel, 0};
  playerHit->handleStateChange(new HurtState(playerHit, properties.hurtFrames, forceVel));
  u::log(player->game->training);
  if(!player->game->training) playerHit->stats.current_health -= properties.damage;
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
