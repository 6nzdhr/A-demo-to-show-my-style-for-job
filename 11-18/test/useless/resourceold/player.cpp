#include <iostream>
#include "player.h"
#include "space.h"
#include "building.h"

void Player::pay_money(p_Player p_player, int pay_money) {
    money -= pay_money;
    assert(money >= 0);
    if (p_player != NULL)
    {
      p_player->get_money(pay_money);
    }
}

void Player::get_money(int get_money) {
    money += get_money;
}

void Player::pay_point(int pay_point) {
    point -= pay_point;
}

void Player::get_point(int get_point) {
    point += get_point;
}

void Player::move(int num) {
    while(num--) {
        p_pos= p_pos->p_next();
    }
}

void Player::trade() {
    p_pos->get_building()->trade(this);
}

void Player::add(p_Event e) {
    return;
}

void Player::debug() {
    std::cout << "id = " << id << std::endl;
    std::cout << "\tmoney = " << money << std::endl;
    std::cout << "\tpoint = " << point << std::endl;
    std::cout << "\tpos   = " << p_pos->getid() << std::endl;     
}