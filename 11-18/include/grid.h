/*
  make it simple
  make it stupid
  完全独立
  只是一个记录不涉及任何逻辑
  命名以在程序中清楚为第一准则(就是看main代码吧)
  */

#pragma once

#include <vector>
#include <memory>
#include <iostream>

class Token;
class Building;

class Grid {  // 棋盘的格子
 public:                            
    using p_Token = std::shared_ptr<Token>;
    using p_Building = std::shared_ptr<Building>;
    using p_Grid = std::shared_ptr<Grid>;

    Grid(int in_id, p_Building in_building) : m_id(in_id), m_building(in_building) {}
    int id() const { return m_id; }
    void linknext(p_Grid in_next) { m_next = in_next; }
    p_Grid next() const { return m_next; }

    void put(p_Token in_token) { m_token.push_back(in_token); } //放置Token

    p_Building &building() { return m_building; }


    std::vector<p_Token> &token() { return m_token; }

    void render();               //渲染用到的图形

 private:
    const int m_id;
    p_Grid m_next;               //交叉引用会爆炸,为了语法的简洁,容忍这点风险
    
    p_Building m_building;

    std::vector<p_Token> m_token;       //只是记录Token,和现实强相关,make it simple 这里的Token可以有各种功能,影响范围比较广
    
};





