/*
  这里的事件不是一次性的,而是持久的事件处理模板,故含有静态数据成员,且应该被初始化,这里的事件有一定的复用性
  即作为Accident_land的事件集合,也作为踩到Token发生的事情.
  */




/*=================waring开发随笔==============================
  初始化为一个集合被 Accident_land 和T oken 使用 累了真的到此为止了
  这里决定不存储动态类型,把动态数据类似持续时间全部分配给State,不然会爆炸
  这里的设计原则是 复用
  类如其名
  一些随机事件,作用于玩家，来源是系统.
  突然发现所有的基类的是private;恰好符合 继承类无需考虑基类的实现,更好的实现了复用. 其实就是忘了还有protected
  但是这个m_state是个列外,此处是为了更好的可读性,基类没有实现它,因为继承类不一定用到,所以此处protected
  =================waring开发随笔==============================
  */
#pragma once

#include <memory>

#include "interaction.h"
#include "player.h"
#include "state.h"
class Event {
 public:
    using p_State = std::shared_ptr<State>; 
    using p_Player = std::shared_ptr<Player>;
    using p_Grid = std::shared_ptr<Grid>; 
    
    virtual bool happento(p_Player in_player) = 0;    //事件的触发效果
};


class Get_money : public Event {
 public:
    bool happento(p_Player) override;
};
inline
bool Get_money::happento(p_Player in_player) {
    Message(in_player, "get 3000 money");   
    return in_player->getmoney(3000);
}

class Get_point : public Event {
 public:
    bool happento(p_Player) override;
};
inline
bool Get_point::happento(p_Player in_player) {
    Message(in_player, "get 100 point");   
    return in_player->getpoint(100);
}

class Go_to_hopital : public Event {         
 public:
    static void init(p_Grid in_grid) {m_hospital = in_grid;}
    Go_to_hopital(int in_hospital_day) : m_hospital_day(in_hospital_day) {}
    bool happento(p_Player) override;
 private:
    const int m_hospital_day;
    static p_Grid m_hospital;      //这是重生点,应该被初始化,没有定义源文件,所以在game里初始化
};

inline
bool Go_to_hopital::happento(p_Player in_player) {
    Message(in_player, "go to hospital");
    in_player->move(m_hospital);
    in_player->add(std::make_shared<Hurt> (m_hospital_day, m_hospital));    
    return true;
}

