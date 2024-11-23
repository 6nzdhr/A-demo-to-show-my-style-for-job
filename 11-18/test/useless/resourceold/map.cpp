#include "map.h"
#include "space.h"
#include "building.h"

Map::Map() {
    for(int i = 0; i < 10; i++) {
        space[i].setid(i);
        if (i % 3 == 0) {
            space[i].make_building(std::make_shared<Empty>());
        } else {
            space[i].make_building(std::make_shared<Hotel>((i%3) * 1000 + 1000));
        }
        space[i].linknext( &space[ (i+1)%10 ] );
    }
}

Space* Map::p_start_space() {
    return space;
}

void Map::debug() {
    for(int i = 0; i < 10; i++) {
        space[i].debug();
    }
}