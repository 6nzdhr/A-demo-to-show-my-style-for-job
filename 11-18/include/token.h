/*
  Token 就是地图上的标记物,不涉及任何逻辑,
  demo到这已经快到头了
  */
#pragma once

#include <memory>
#include <string>

#include "event.h"
class Player;
class Token {
 public:
    // using p_State = std::shared_ptr<State>;
    // using p_Game = std::shared_ptr<Game>;
    // using p_Grid = std::shared_ptr<Grid>;
    using p_Player = std::shared_ptr<Player>;
    using p_Event = std::shared_ptr<Event>;

    virtual bool interact(p_Player in_player) = 0;    //返回的值用不上
    virtual std::string attr() = 0;
 protected:
    p_Event m_event;  //碰到Token触发事件很合理吧
};


class Bomb : public Token {
 public:
    Bomb();
    bool interact(p_Player in_player) override;
    std::string attr() { return "Bomb"; }
};

inline
Bomb::Bomb() {
    m_event = std::make_shared<Go_to_hopital>(3);
}


inline
bool Bomb::interact(p_Player in_player) {
    Message(in_player, "step on a bomb !!!");
    m_event->happento(in_player);
    return true;
}




