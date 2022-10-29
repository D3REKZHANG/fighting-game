#include "animation.h"
#include "spritesheet.h"
#include <cmath>
#include "util.cc"

Animation::Animation(Spritesheet* spritesheet, int start, int stop, int tickSpeed, bool repeat)
  : spritesheet{spritesheet}, range{start, stop}, tickSpeed{tickSpeed}, repeat{repeat} {}

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

void Animation::draw(Vector2 pos) {
  int n = range.start + currentFrame;
  //console::log(n);
  float rx = (n-1) % spritesheet->width;
  float ry = floor((n-1) / spritesheet->width);
  float rw = spritesheet->dimensions.x;
  float rh = spritesheet->dimensions.y;
  DrawTextureRec(spritesheet->sheet, {rx*rw, ry*rh, rw, rh}, pos, WHITE );
}

void Animation::play() {
  currentFrame = 0;
  active = true;
}

void Animation::stop() {
  active = false;
}
