#include "animation.h"
#include "spritesheet.h"
#include "util.h"

Animation::Animation(Spritesheet* spritesheet, int start, int stop, int tickSpeed, bool repeat)
  : range{start, stop}, spritesheet{spritesheet}, tickSpeed{tickSpeed}, repeat{repeat} {}

Animation::Animation(Spritesheet* spritesheet, Vector2 start, Vector2 stop, int tickSpeed, bool repeat)
  : spritesheet{spritesheet}, tickSpeed{tickSpeed}, repeat{repeat} {
  range.start = start.x+(start.y-1)*spritesheet->num_cols;
  range.stop = stop.x+(stop.y-1)*spritesheet->num_cols;
}

void Animation::tick() {
  if(!active){
    return;
  }
  if(counter != tickSpeed){
    counter++;
    return;
  }

  counter = 0;

  if(range.start+currentFrame < range.stop){
    currentFrame++;
  }else{
    if(repeat) {
      currentFrame = 0;
    } else {
      stop();
    }
  }
}

void Animation::draw(Vector2 pos, bool inverse) {
  int n = range.start + currentFrame;
  spritesheet->draw(n, pos, inverse);
}

void Animation::play() {
  currentFrame = 0;
  active = true;
}

void Animation::stop() {
  active = false;
}
