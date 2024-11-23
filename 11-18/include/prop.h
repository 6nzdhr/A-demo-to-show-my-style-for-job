/*
  道具的实现也是高内聚,作用于player和grid
  */


#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Player;
class Grid;
class Prop {
 public:
    using p_Player = std::shared_ptr<Player>;
    using p_Grid = std::shared_ptr<Grid>;
    //高内聚,基本上所有的实现都是这样,模块化减少耦合,不然个人维护不了
    virtual bool used_by(std::vector<p_Grid> &in_grid, p_Player in_player) = 0;    //返回值代表使用成功与否
    virtual std::string attr() = 0;
    int point() { return m_point; }
 protected:
    int m_point;  //商店售卖价格
};

class Remote_controlled_dice : public Prop {
  public:
    Remote_controlled_dice() {m_point = 30; }
    bool used_by(std::vector<p_Grid> &in_grid, p_Player in_player) override;    
    std::string attr() override { return "Remote_dice"; }   
};

class Building_card : public Prop {
 public:
    Building_card() { m_point = 50; }
    bool used_by(std::vector<p_Grid> &in_grid, p_Player in_player) override;
    std::string attr() override { return "building_card"; }
};

class Bomb_card : public Prop {
 public:
    Bomb_card() { m_point = 10; }
    bool used_by(std::vector<p_Grid> &in_grid, p_Player in_player) override;
    std::string attr() override { return "bomb_card"; }

};



/*
=====================waring开发随笔===========================
道具的实现好伤脑筋,采取这样的实现,类似building高内聚
  这里的实现有点超出个人能力了,在building暴露尽量少的接口下（building压根就没接口）,building不大好改.
  没办法,为building定制接口吧,有个小技巧,building的接口以bool的形式作为返回值
  返回值为false表示不支持此接口,返回值为ture表示支持,
  
  还好player的接口很多.
  再写下去崩溃只是时间问题.
=====================waring开发随笔===========================
 */