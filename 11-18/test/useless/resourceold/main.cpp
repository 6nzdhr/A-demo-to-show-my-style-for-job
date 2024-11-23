#include "space.h"
#include "building.h"
#include "player.h"
#include "map.h"
#include <memory>

using namespace::std;

int main() {


    // test 1 
    // Map map;
    // map.debug();
    // Player player1(10000, 50, map.p_start_space());
    // player1.debug();
    // player1.move(11);
    // player1.debug();

    // test2
    // Space s;
    // s.make_building(make_shared<Hotel>(2000));
    // s.debug();
    // s.make_building(make_shared<Empty>());
    // s.debug();    

    // test3
    // Map map;
    // map.debug();
    // Player player1(1, 10000, 50, map.p_start_space());
    // player1.debug();
    // player1.move(1);
    // player1.trade();
    // player1.debug();

    //test4
    Space s(0);
    s.make_building(make_shared<Hotel>(3100));
    s.debug();
    Player player1(1, 10000, 50, &s);
    Player player2(2, 10000, 50, &s);
    player1.debug();
    player2.debug();

    player1.trade();
    player1.debug();

    player2.trade();
    player2.debug();    

    player1.trade();
    player1.debug();

    player2.trade();
    player2.debug();    

    player1.trade();
    player1.debug();

    player2.trade();
    player2.debug();    

    player1.trade();
    player1.debug();

    player1.trade();
    player1.debug();

    player2.trade();
    player2.debug();    

}