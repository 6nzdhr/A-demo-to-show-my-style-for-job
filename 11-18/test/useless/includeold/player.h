/*
  player: 大概思路:简单的解耦
  只把一些修改自身属性的函数作为接口。
  具体功能由交互物品实现。

  角色的持续效果通过一个事件vec来维持。
  先简单就这样      
  */


#pragma once

#include <memory>
#include <vector>
#include <cassert>

class Space;
class Event;

class Player {
 public:
    using p_Event = std::shared_ptr<Event>;
    using p_Player = Player*;
    using p_Space = Space*;

    Player(int in_id, int in_money, int in_point, p_Space in_p_pos)
        : id(in_id), money(in_money), point(in_point), p_pos(in_p_pos) {}

    void pay_money(p_Player, int pay_money); // 涉及数字,总是让人有担心溢出的风险,我也不好办。
    void get_money(int get_money);

    void pay_point(int pay_point);
    void get_point(int get_point);

    void move(int);
    void trade();
    void operation();
    void bankruptcy();


    void bind_event(p_Event);

    void debug();

 private:
    int id;

    int money;
    int point;
    std::vector<p_Event> slot;

    p_Space p_pos;                  //不涉及资源管理的智能指针用不习惯
};



