/*
  和交互有关的窗口
  */


#pragma once
#include <string>




class Interaction {
 public:
    using string = std::string;
    Interaction(string in_title, string in_text = "") 
        : title(in_title), text(in_text) {}

    bool choose() {
        return 1;       //粗糙一下
    }

 private:
    string title;
    string text;
};

class choose_Window {
 public:
    void render();
};