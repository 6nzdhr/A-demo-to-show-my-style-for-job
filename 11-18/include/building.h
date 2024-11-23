/*高内聚,
  角色与建筑的交互模块集中于此.




  =======================waring开发随笔==========================
  和player交互 虽说受角色状态影响,这里进行解耦,state只影响角色操作,感觉以后可能要打补丁了,自然不是在这里。
  为了更好的利用多态与继承
  此处会有逻辑，希望逻辑独立吧
  最终决定把一些逻辑集中写在这里
  有利有弊吧
  就这样吧 高内聚低耦合
  */

#pragma once

#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include "utility.h"
#include "interaction.h"
#include "player.h"
#include "event.h"
#include "game.h"
#include "prop.h"

#define RD100(money) ((money) - (money)%100) //以100向下取整

class Building {
 public:
    using p_Player = std::shared_ptr<Player>;

    Building(int in_id) : m_id(in_id) {}
    int id() { return m_id; }

    virtual bool interact(p_Player player) = 0;           //返回角色是否还能继续游戏的状态
    virtual void render() = 0;

    virtual bool build_up() { return false; }              //返回值表示操作是否成功 这种突兀的接口是为了给道具进行操作 越多的道具,自然有越多的接口,程序逐渐走向崩溃    
    
    p_Player owner() { return m_owner; }
 protected:

    int m_id;
    p_Player m_owner = NULL;
    
};


class Empty_land : public Building {        //空地可以作为医院监狱的重生点(两个是一样的,偷懒了其实只实现了一个)
 public:
    Empty_land(int in_id, std::string in_attr) : Building(in_id), m_attr(in_attr) {} 
    bool interact(p_Player in_player) override { return 1; }           
    void render() override { std::cout << "\t" << m_attr << id() << std::endl; }
 private:
    std::string m_attr;
};

class Point_land : public Building {
 public:
    Point_land(int in_id, int in_point) : Building(in_id), m_point(in_point) {}
    bool interact(p_Player in_player) override;
    void render() override { std::cout << "\tPointland" << id() << " :" << m_point << std::endl; };

 private:
    const int m_point;
};

inline
bool Point_land::interact(p_Player in_player) {
    Message("player" + std::to_string(in_player->id()) + " get " + std::to_string(m_point) + " point");    
    return in_player->getpoint(m_point); 
}

class House : public Building { //高内聚实现自然没有太好的扩展性,就这样吧
 public:
    House(int in_id, int in_landprice) : Building(in_id), landprice(in_landprice) {}
    bool interact(p_Player player) override;            
    void render() override ;
    bool build_up() override;

 private:
    int m_level = 0;       

    const int landprice;            
    const int upcost = 500;         
    const static int MAXLEVEL = 3;  //level <= 3 为了速度,高内聚把权力集中在此 
    const int pay[MAXLEVEL + 1] = { 
        RD100(landprice / 10),
        RD100(landprice / 2),
        RD100(landprice * 2),
        RD100(landprice * 4) + 4000
    };
    
};

inline
bool House::interact(p_Player player) {     //个人觉得这段挺符合 代码即文档 的,感觉写的挺漂亮的,虽然cpp的原生代码有些长,但我还是决定保留。
    if (m_owner) {                          //开始是很优雅的,但是我决定把交互逻辑完全内聚在此处,我不知道 这还算优雅吗
        if (m_owner == player) {
            if (m_level < MAXLEVEL && std::make_shared<Interaction>("是否加盖房屋")->choose()) {
                Message("player" + std::to_string(player->id()) + " build up house" + std::to_string(id()));
                player->pay(upcost);
                ++m_level;
            }
            return true;
        } else {
            Message("player" + std::to_string(player->id()) + " pay player" + std::to_string(m_owner->id()) + " " + std::to_string(pay[m_level]) );
            return player->pay(m_owner, pay[m_level]);
        }
    } else {
        std::string title("是否购买此地");
        std::stringstream ss;
        ss << "购买此地将花费 " + landprice;
        std::string text(ss.str());
        if (player->money() >= upcost && std::make_shared<Interaction>(title, text)->choose()) {
            Message("player" + std::to_string(player->id()) + " buy house" + std::to_string(id()));
            m_owner = player;
            return player->pay(landprice);
        }
        std::make_shared<Interaction>("你没有足够的钱");
        return true;
    }
}

inline 
void House::render() {
    std::cout << "\tlandprice" << id() << ": " << landprice << " level = " << m_level << " pay = " << pay[m_level];
    if (m_owner)
        std::cout << "\towner = " << m_owner->id();
    std::cout << std::endl;
}

inline
bool House::build_up() {        //这个代码不知道什么时候写的 -11.23
    if (m_level < MAXLEVEL) {
        ++m_level;
        return true;
    }
    return false;
}

class Accident_land : public Building {
 public:
    using p_Event = std::shared_ptr<Event>;
    using p_State = std::shared_ptr<State>;

    Accident_land(int in_id, std::vector<p_Event> in_event_set);
    bool interact(p_Player in_player) override;            
    void render() override { std::cout << "\taccident_land" << id() << std::endl; }
 private:
    std::vector<p_Event> m_event_set;   //存储可能发生的事件集合
};
inline
Accident_land::Accident_land(int in_id, std::vector<p_Event> in_event_set) : Building(in_id){
    m_event_set = in_event_set;
}
inline 
bool Accident_land::interact(p_Player in_player) {
    if (!m_event_set.empty())        //无意间增加一点健壮性吧
        return m_event_set[Game::random(0, m_event_set.size()-1)]->happento(in_player);
    return true; 
}


class PointShop_land : public Building {    //懒了好累
 public:
    using p_Prop = std::shared_ptr<Prop>;
    PointShop_land(int in_id) : Building(in_id) {}
    bool interact(p_Player player) override;          
    void render() override { std::cout << "\tpointShop_land" << id() << std::endl; }
 private:

};

inline
bool PointShop_land::interact(p_Player player) {        //采取硬编码的形式了,项目快到头了,道具只能买一次
    std::vector<p_Prop> prop_set;
    prop_set.push_back(std::make_shared<Remote_controlled_dice>());
    prop_set.push_back(std::make_shared<Building_card>());
    prop_set.push_back(std::make_shared<Bomb_card>());
    
    while (1) {
        int i = 0;
        std::cout << "pointshop to buy card" << std::endl;;
        for(auto &prop : prop_set) {        
            std::cout << ++i << prop->attr() << "=" << prop->point() << " ";
        }
        std::cout << "input num to buy(any illegal to q): ";

        unsigned num = utility::input_num() - 1;        //unsigned 警告有些
        if (num >= 0 && num < prop_set.size()) {
            Message(player, "buy " + prop_set[num]->attr());
            player->prop().push_back(prop_set[num]);
            prop_set.erase(prop_set.begin() + num);//感谢智能指针
            if (prop_set.empty()) {
                std::cout << "shop is empty" << std::endl;       //纯展示逻辑
                return true;
            }
            continue;
        }
        return true;
    }
}         

class Game_land : public Building {     //累了不想写了
 public:
    bool interact(p_Player player) override { return true; };          
    void render() override { std::cout << "\t?????????" << id() << std::endl; }

 private:
};


