/* 这里存放的是一些杂项比如处理输入的*/


#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include "utility.h"

int utility::input_num() {   //非法返回-1
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    int num;
    ss >> num; 
    if (ss.eof() && !ss.fail()) {
        return num;
    }
    return -1;  //太硬了
}







