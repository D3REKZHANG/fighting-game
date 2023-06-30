#include "spritesheet.h"
#include "raylib.h"
#include "util.h"
#include <cmath>

Spritesheet::Spritesheet(Texture2D sheet, Vector2 dimensions)
  : sheet{sheet}, dimensions{dimensions} {
  num_cols = sheet.width/dimensions.x;
  num_rows = sheet.height/dimensions.y;
}

void Spritesheet::draw(int n, Vector2 pos, bool inverse){
  float col = (n-1) % num_cols;
  float row = floor((n-1) / num_cols);
  float width = dimensions.x;
  float height = dimensions.y;
  // DrawRectangleV(u::topleft(pos, width, height), {width, height}, DARKGRAY);
  DrawTextureRec(sheet, {col*width, row*height, inverse ? -width : width, height}, u::topleft(pos, width, height), WHITE);
}

void Spritesheet::draw(int row, int col, Vector2 pos){
  float width = dimensions.x;
  float height = dimensions.y;
  DrawTextureRec(sheet, {col*width, row*height, width, height}, u::topleft(pos, width, height), WHITE);
}
