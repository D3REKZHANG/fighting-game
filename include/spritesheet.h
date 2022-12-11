#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "raylib.h"

class Spritesheet {
public:
  Texture2D sheet;
  Vector2 dimensions;
  int num_cols, num_rows;

  Spritesheet(Texture2D sheet, Vector2 dimensions);

  void draw(int n, Vector2 pos, bool inverse=false);

  void draw(int row, int col, Vector2 pos);
};

#endif
