#include "Map.hpp"
#include "memory"
#include <libtcod.h>

class MapGenerator {
private:
std::unique_ptr<TCODRandom> random_;
bool default_random_;
public:
  MapGenerator();
  MapGenerator(std::unique_ptr<TCODRandom> random);
  Map Generate(int width, int height, int num_shapes);
};
