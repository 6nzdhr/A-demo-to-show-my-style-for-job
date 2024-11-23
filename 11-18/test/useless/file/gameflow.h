/*
  很粗糙,非常粗糙
  */
#define MAP_SIZE 20
#include <vector>

class Player;
class Grid;
class GameFlow { 
 public:
    GameFlow(int num_player);          


    
 private:
    std::vector<Player> player;
    Grid * map[MAP_SIZE];

    int turn = 0;
};