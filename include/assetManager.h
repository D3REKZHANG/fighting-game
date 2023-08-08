#ifndef ASSET_MANAGER_H 
#define ASSET_MANAGER_H

#include <unordered_map>
#include <string>
#include "raylib.h"
#include "spritesheet.h"

class AssetManager {

public:

  static AssetManager* instance;

  std::unordered_map<std::string, Texture2D> tx;
  std::unordered_map<std::string, Spritesheet*> ss;

  static AssetManager* getInstance();

  AssetManager();
  ~AssetManager();
};

#endif
