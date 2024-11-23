/*
  这里的命名有些老了,而且demo快结束了,就这样吧
  */

#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "interaction.h"


class Grid;

class State {
 public:
    using p_Player = std::shared_ptr<Player>;
    using p_Grid = std::shared_ptr<Grid>;
    State(int in_time) : m_time(in_time) {}


    virtual bool effect(p_Player) = 0;          //返回值为false代表这个效果可以被移除了
    virtual std::string attr() const = 0;       //没用上冗余的累了.
 protected:
    virtual bool out_of_state(p_Player) = 0;     //返回值无意义,为false   
    int m_time;         //持续时间
};



class Hurt : public State { //hurt 是形容词
 public:
    Hurt(int in_time, p_Grid in_hostipal) : State(in_time), m_hostipal(in_hostipal) {}

    bool effect(p_Player in_player) override;
    
    std::string attr() const;
 private:
    bool out_of_state(p_Player in_player) override; 
    
    p_Grid m_hostipal;    //存储住医院的地方,很合理这里出现冗余逻辑,我当看不见,因为项目快到头了
};

inline
bool Hurt::effect(p_Player in_player) {
    if (m_time-- <= 0) {
        return out_of_state(in_player);
    }
    Message("player" + std::to_string(in_player->id()) + " is in hospital ");
    in_player->can_not_operation();     
    in_player->can_not_nove();
    in_player->can_not_receive_money();
    return true;
}

inline
bool Hurt::out_of_state(p_Player in_player) {       //此刻老师正在讲课,这种频繁的耦合我只能随缘了。
    in_player->move(m_hostipal);
    Message(in_player, "out of hospital");
    return false;
}

inline
std::string Hurt::attr() const {
    return " is hurt and time = " + std::to_string(m_time) + " turn";
}



