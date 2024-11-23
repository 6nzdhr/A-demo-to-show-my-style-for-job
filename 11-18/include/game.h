/*
  不独立,毋庸置疑这里涉及大量交互
  为了方便调试
  此类设计的比较粗糙
  编译顺序问题开始浮现。我对这个依赖目前还是有些模糊
  小细节,所有的 render 前期都当作调试函数来使用
*/

#pragma once

#include <vector>
#include <memory>
#include <random>
#include <string>

class Player;
class Grid;
class Token;
class State;
class Building;
class Event;

#define NUM_GRID 6

class Game {
 public:
    using p_Player = std::shared_ptr<Player>;
    using p_Grid = std::shared_ptr<Grid>;
    using p_Token = std::shared_ptr<Token>;
    using p_State = std::shared_ptr<State>;
    using p_Building = std::shared_ptr<Building>;
    using p_Event = std::shared_ptr<Event>;

    static int random(int in_begin, int in_end);    


    Game(int num);
    ~Game();        //do not forget
    void run();
    void render();

    std::vector<p_Grid>& grid() { return m_grid; }

 private:
    void operation(p_Player in_player);
    bool bankrupt(p_Player in_player);  //破产清算

    std::vector<p_Event> m_event_set;   //一些事件的集合 
    std::vector<p_Player> m_player;     
    std::vector<p_Grid> m_grid;
};

inline
int Game::random(int in_begin, int in_end) {
    static std::random_device rd; 
    static std::mt19937 gen(rd()); // Mersenne Twister 伪随机数生成器
    static std::uniform_int_distribution<> dis(in_begin, in_end); // 生成 1 到 6 之间的随机数
    return dis(gen);
}



