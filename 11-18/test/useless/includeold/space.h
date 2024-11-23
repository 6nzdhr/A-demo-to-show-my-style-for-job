#pragma once

#include <vector>
#include <memory>
#include <iostream>

class Building;
class Event;
class Player;


class Space {  // 棋盘的格子
 public:
    using p_Event = std::shared_ptr<Event>;
    using p_Building = std::shared_ptr<Building>;
    using p_Player = std::shared_ptr<Player>;
    using p_Space = Space*;                                 

    Space(int in_id = -1) : id(in_id) {}
    void setid(int in_id) { id = in_id; }
    int getid() { return id; }


    void linknext(p_Space);
    p_Space p_next() { return next; }
    p_Space p_prev() { return prev; }


    void make_building(p_Building);   
    p_Building get_building() { return p_building; }


    void put_Strongevent(p_Event);
    void trigger_Strongevent(p_Player);
    void put_Weakevent(p_Event);
    void trigger_Weakevent(p_Player);


    void debug();
 private:
 
    int id;
    
    //智能指针不习惯,指向this需要技巧,影响可读性。此数值不影响资源管理,用裸指针代替弱指针
    //冗余的实现,本来想着地图复杂化,没必要只要next就好,不动了。
    p_Space prev = NULL;
    p_Space next = NULL;            

    p_Building p_building;

    std::vector<p_Event> vec_p_Strongevent;

    std::vector<p_Event> vec_p_Weakevent;
};


