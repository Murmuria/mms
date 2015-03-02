#pragma once

#include <string>
#include <utility>
#include <vector>

#include "BasicTile.h"

namespace sim {

std::pair<int, int> getMazeSize(std::string mazeFilePath);
bool validMaze(std::string mazeFilePath);
bool officialMaze(std::string mazeFilePath);
void saveMaze(std::vector<std::vector<BasicTile>> maze, std::string mazeFilePath);

// Note: This should only be called on mazes that have been validated
std::vector<std::vector<BasicTile>> loadMaze(std::string mazeFilePath);

} // namespace sim
