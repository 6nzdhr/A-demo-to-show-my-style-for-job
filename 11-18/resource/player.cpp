/**/

#include <algorithm>

#include "player.h"
#include "grid.h"
#include "state.h"
#include "interaction.h"
#include "prop.h"
void Player::move (int in_grid) {
    while (in_grid--) {
        m_pos = m_pos->next();
    }
}

std::string Player::attributes() const{
    std::stringstream ss;

    ss << "\t\tPlayer" << m_id << ": money = " << m_money << " point = " << m_point << " pos = " << m_pos->id() << std::endl << "\t\tstate: ";
    for (auto &state : m_state) {
        ss << state->attr();
    }
    return ss.str();
}

void Player::add(p_State in_state) {
    m_state.push_back(in_state);
}

// void Player::affected_by_state() {   //最后一个函数了,包给Game
//     // auto player = std::make_shared<Player>(this);      //这种代码666
//     m_state.erase(std::remove_if(m_state.begin(), m_state.end(),        //借鉴chatgpt的
//         [&player](p_State state) { 
//             return !state->effect(player); 
//         }),
//         m_state.end());
// }


bool Player::pay(p_Player in_player, int in_money) {
    if ( ! in_player->able_to_receive_money()) {
        Message("Don't need to pay");
        return true;
    }

    int pay_money = (m_money >= in_money) ? in_money : m_money;
    int result = (m_money >= in_money) ? true : false;

    in_player->getmoney(pay_money);
    m_money -= pay_money;
    
    return result;
}

/*===============waring开发感受====================
  解决编译依赖问题
  让player完全独立
  使用内联只是因为切换文件觉得麻烦
  cpp的编译慢的跟乌龟一样
  */