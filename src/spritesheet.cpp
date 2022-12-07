#include "spritesheet.h"
#include "util.cc"
#include <cmath>

Spritesheet::Spritesheet(Texture2D sheet, Vector2 dimensions)
  : sheet{sheet}, dimensions{dimensions} {
  width = sheet.width/dimensions.x;
  height = sheet.height/dimensions.y;
}

void Spritesheet::draw(int n, Vector2 pos){
  float rx = (n-1) % width;
  float ry = floor((n-1) / width);
  float rw = dimensions.x;
  float rh = dimensions.y;
  console::log(rh);
  DrawTextureRec(sheet, {rx*rw, ry*rh, rw, rh}, pos, WHITE);
}

void Spritesheet::draw(int row, int col, Vector2 pos){
  float rw = dimensions.x;
  float rh = dimensions.y;
  DrawTextureRec(sheet, {row*rw, col*rh, rw, rh}, pos, WHITE);
}
