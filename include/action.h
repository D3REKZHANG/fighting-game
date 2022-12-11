#ifndef ACTION_H
#define ACTION_H

#include "raylib.h"

class Action {
public:
  virtual bool update() = 0;
  virtual void draw(Vector2 pos, bool inverse=false) = 0;
};


#endif
