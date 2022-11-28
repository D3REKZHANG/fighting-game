#include "spritesheet.h"
#include "util.cc"

Spritesheet::Spritesheet(Texture2D sheet, Vector2 dimensions)
  : sheet{sheet}, dimensions{dimensions} {
  width = sheet.width/dimensions.x;
  height = sheet.height/dimensions.y;
  console::log(width, height);
}
