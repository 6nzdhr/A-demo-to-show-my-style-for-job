#include "building.h"
#include "interaction.h"
#include "player.h"

void Hotel::interact(p_Player p_player) {
    if (p_owner == NULL) {
        Interaction ask_to_buy("是否要买此处空地");
        if (ask_to_buy.choose()) {
            p_player->pay_money(NULL, land_price);
            p_owner = p_player;
        }
    } else {
        if (p_owner == p_player) {
            Interaction ask_to_build("是否要加盖房屋");
                if (ask_to_build.choose()) {
                p_player->pay_money(NULL, house_price);
                ++level;
            }
        }
        else {
            p_player->pay_money(p_owner, pay[level]);
        }
    }
}

void Hotel::debug() {
    std::cout << "Hotel debug" << std::endl;
    std::cout << "\t\tland_price = " << land_price << "  pay0 = " << pay[0] 
    << "  pay1 = " << pay[1] << "  pay2 = " << pay[2] << "  pay3 = " << pay[3] << std::endl;
    std::cout << "\t\tlevel = " << level << std::endl;
    std::cout << "\t\tp_owner = " << p_owner << std::endl;
}


