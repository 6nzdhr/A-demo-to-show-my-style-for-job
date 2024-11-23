#include <vector>

#include "player.h"
#include "map.h"



class gameflow {
 public:
    void init(int);

    void run();

    ~gameflow();
 private:
    std::vector<Player> player;     
    Map map;
};


inline
void gameflow::init(int num) {
    int i = 0;
    while(num--) {
        player.push_back(Player(++i, 10000, 50, map.p_start_space()));
    }
}


inline
void gameflow::run() {
    
}
