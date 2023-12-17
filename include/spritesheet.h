#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "raylib.h"

class Spritesheet {
public:
  Texture2D sheet;
  Vector2 dimensions;
  int num_cols, num_rows;
  float scale;

  Spritesheet(Texture2D sheet, Vector2 dimensions, float scale=1);

  void draw(int n, Vector2 pos, bool inverse=false);

  void draw(int row, int col, Vector2 pos);

  Vector2 getScaledDimensions() { return { dimensions.x*scale, dimensions.y*scale }; }
};

#endif
