/*Player: 其实没啥可说的,类如其名,在设计的过程中也渐渐高内聚
  支持玩家操作道具涉及的模块过多,由Game类处理
  


=======================waring开发随笔============================
  编译上完全独立,逻辑随着模块的增多变得 有些混乱
  尽量不涉及任何逻辑（尽量只做出行为，不检查行为合法。意思就是尽量做到只是一个记录）
  但是 pay 有逻辑
  命名有一定规范  为了调用时外部的清晰牺牲了一定类内部的清晰程度
  全部用内敛可以减少切屏显著增加开发效率
  类中尽量不要嵌套对象,不然内敛和编译顺序会有要求,而且如果不加以限制,我用了智能指针基本不考虑,编译会爆炸除非头文件和源文件彻底分离
  为了程序尽可能的优雅, 只好删掉 类似 路障 这种破坏优雅的道具了
  终于此处涉及了循环引用,优雅好难
=======================waring开发随笔============================
  */

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
class Prop;
class State;    
class Grid;
class Game;

class Player {
 public:
    using p_Prop = std::shared_ptr<Prop>;
    using p_State = std::shared_ptr<State>;
    using p_Grid = std::shared_ptr<Grid>;
    using p_Player = std::shared_ptr<Player>;
    using p_Game = std::shared_ptr<Game>;

    Player(int in_id, int in_money, int in_point, p_Grid in_pos) : m_id(in_id), m_money(in_money), m_point(in_point), m_pos(in_pos) {}
    int id() { return m_id; }

    int money() const { return m_money; }
    int point() const { return m_point; }
    //钱足够返回true,钱不够返回false,并且只付拥有的钱
    bool pay(p_Player in_player, int money);
    bool pay(int in_money);       
    bool getmoney(int in_money) { return m_money += in_money; }
    bool getpoint(int in_point) { return m_point += in_point; }   
    void paypoint(int in_point) { m_point -= in_point; }

    void add(p_State in_state);
    // void affected_by_state(); //高内聚 这个也外包出去
    std::vector<p_State> &state() { return m_state; }  

    // void operation();   道具涉及模块太多,玩家的操作道具这部分交给Game处理.就是没有接口直接处理的垃圾设计了
    std::vector<p_Prop> &prop() { return m_prop; }

    void move(p_Grid in_pos)    { m_pos = in_pos; } 
    void move(int in_grid );



    bool able_to_operation() const  { return m_able_to_operation; }
    bool able_to_move() const       { return m_able_to_move; }
    bool able_to_receive_money() const { return m_able_to_receive_money; }
    void init_state()               { m_able_to_move = m_able_to_operation = m_able_to_receive_money = true; }    //这样好不写实
    void can_not_nove()             { m_able_to_move = false; }
    void can_not_operation()        { m_able_to_operation = false; }
    void can_not_receive_money()     { m_able_to_receive_money = false;}

    p_Grid pos() const              { return m_pos;}

    std::string attributes() const;

 private:
    int m_id;

    int m_money;
    int m_point;
    p_Grid m_pos;

    std::vector<p_Prop> m_prop;

    std::vector<p_State> m_state;
    bool m_able_to_operation = true;      //玩家能使用道具吗
    bool m_able_to_move = true;           //玩家能移动吗
    bool m_able_to_receive_money = true;  //玩家能收钱吗
};




inline
bool Player::pay(int in_money) {
    return (m_money -= in_money) >= 0;
}




