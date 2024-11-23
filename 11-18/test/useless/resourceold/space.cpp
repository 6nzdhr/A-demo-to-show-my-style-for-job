#include "space.h"
#include "player.h"
#include "building.h"
#include "event.h"
#include <iostream>

void Space::linknext(p_Space p_next) {
    next = p_next;
    p_next->prev = this;
}


void Space::make_building(p_Building in_p) {
    p_building = in_p;
}


void Space::put_Strongevent(p_Event in_p) {
    vec_p_Strongevent.push_back(in_p);
}

void Space::trigger_Strongevent(p_Player player) {
    for (auto &p : vec_p_Strongevent) 
        player->add(p);
    vec_p_Strongevent.clear();
}


void Space::put_Weakevent(p_Event in_p) {
    vec_p_Weakevent.push_back(in_p);
}

void Space::trigger_Weakevent(p_Player player) {
    for (auto &p : vec_p_Strongevent) 
    player->add(p);
    vec_p_Weakevent.clear();
}

void Space::debug() {
    std::cout << "id = " << id;
    if (prev)
        std::cout << "\t\tprev = " << prev->getid() << std::endl;
    if (next)
        std::cout << "\t\tnext = " << next->getid() << std::endl;
    if (p_building) {
        p_building->debug();
    }
}