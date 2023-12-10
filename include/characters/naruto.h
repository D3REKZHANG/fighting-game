#ifndef NARUTO_H
#define NARUTO_H

#include "player.h"

class Naruto : public Player { 
public:
  Naruto(Game* game, InputReader* inputReader);
};

#endif
