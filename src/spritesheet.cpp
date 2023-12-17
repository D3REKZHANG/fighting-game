#include "spritesheet.h"
#include "raylib.h"
#include "util.h"
#include <cassert>
#include <cmath>

Spritesheet::Spritesheet(Texture2D sheet, Vector2 dimensions, float scale)
  : sheet{sheet}, dimensions{dimensions}, scale{scale} {
  num_cols = sheet.width/dimensions.x;
  num_rows = sheet.height/dimensions.y;
}

void Spritesheet::draw(int n, Vector2 pos, bool inverse){
  assert(num_cols > 0);
  float col = (n-1) % num_cols;
  float row = floor((n-1) / num_cols);
  float width = dimensions.x;
  float height = dimensions.y;
  // DrawRectangleV(u::topleft(pos, width, height), {width, height}, DARKGRAY);
  Vector2 _pos = u::topleft(pos, width*scale, height*scale);
  DrawTexturePro(
    sheet,
    { col*width, row*height, inverse ? -width : width, height },
    { _pos.x, _pos.y, width*scale, height*scale },
    {0, 0},
    0,
    WHITE
  );
}

void Spritesheet::draw(int row, int col, Vector2 pos){
  float width = dimensions.x;
  float height = dimensions.y;
  DrawTextureRec(sheet, {col*width, row*height, width, height}, u::topleft(pos, width, height), WHITE);
}
