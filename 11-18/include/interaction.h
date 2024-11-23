/*此头文件实现的是类似窗口之类和交互相关的,代替图形库
  目前只定义了两个最基本,复用性强的。
  当然还有其它交互,但不在此处实现
  */



// ========================waring开发随笔============================
/*
  完全独立
  依赖它的模块省略了,应该不会有编译顺序的问题
  为了简洁,它将实现所有的功能,没有继承之说
  */
// ========================waring开发随笔============================
#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "player.h"

class Player;


//一个回答yes no的交互界面
class Interaction {
 public:
    Interaction(std::string in_title, std::string in_text = "") : m_title(in_title), m_text(in_text) {}  //命名规范如能坚持必将获益
    bool choose();

 private:
    std::string m_title;
    std::string m_text;
};

inline
bool Interaction::choose() {
    std::string input;
    while (1) {
        std::cout <<"==========="<< m_title << "===========" << std::endl;
        if (m_text.size()) 
            std::cout << m_text;
        std::cout << "y|n : ";
        std::getline(std::cin, input);
        if (std::cin.eof()) 
            exit(1);//shell特性
        if (input[0] == 'y') return true;
        if (input[0] == 'n') return false;
    }
} 

//一个传递某人做某事的消息界面
class Message { 
 public:
    using p_Player = std::shared_ptr<Player>;
    Message (p_Player in_player, std::string in_text);
    Message (std::string in_text) { std::cout << "SYSTEM: " << in_text <<std::endl; }
 private:
    p_Player m_player;
    std::string m_text;
};

inline
Message::Message (p_Player in_player, std::string in_text) {
    std::cout << "SYSTEM: " << "player" << in_player->id() << " : " << in_text << std::endl;
}
    