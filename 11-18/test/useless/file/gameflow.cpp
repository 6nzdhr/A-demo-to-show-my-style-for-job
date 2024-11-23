#include "gameflow.h"
#include "player.h"
#include "grid.h"

GameFlow::GameFlow(int num_player) {
    int i = 0;
    while (num_player--) {
        player.push_back(Player(++i, 30000, 50, NULL));
    }
    for (int i = 0; i < MAP_SIZE; ++i) {
           
    }
}
