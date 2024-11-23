/*
  make it simple
  Player 只是作为一个记录(棋子及其数据)
  不涉及任何逻辑，个人水平有限*/

#pragma once

#include <memory>
#include <vector>

class Grid;
class Token;
class Prop;

class Player {
 public:
    using p_Token = std::shared_ptr<Token>;

    Player(int in_id, int in_money, int in_point, Grid * in_pos)
        : id(in_id), money(in_money), point(in_point), pos(in_pos) {}

    void move(Grid *in_pos) { pos = in_pos; }
    void getmoney(int get) { money += get; }
    bool paymoney(int pay) {
        money -= pay;
        if (money < 0) 
            return false;
        return true;
    }
    void getpoint(int get) { point += get; }
    void paypoint(int pay) {
        point -= pay;
        if (point < 0)
            point = 0;    
    }
    std::vector<p_Token> &getslot() { return slot; }

 private:
    int id;

    int money;
    int point;
    std::vector<Prop> vec_prop;
    Grid *pos;                  

    std::vector<p_Token> slot;  //当前角色接触的Token

};



