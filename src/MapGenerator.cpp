#include "MapGenerator.hpp"

MapGenerator::MapGenerator(): default_random_(true) {
  TCODRandom copy = *TCODRandom::getInstance();
  random_ = std::make_unique<TCODRandom>(copy);
}

MapGenerator::MapGenerator(std::unique_ptr<TCODRandom> random): default_random_(false) {
  random_ = std::move(random);
}

Map MapGenerator::Generate(int width, int height, int num_shapes) {
  std::vector<MapShape*> shapes;

  return Map(width, height, shapes);
}
