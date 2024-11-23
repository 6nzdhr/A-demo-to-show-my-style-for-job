#include <iostream>
#include <memory>


// #include "player.h"
// #include "grid.h"
#include "game.h"
// #include "interaction.h"
// #include "building.h"
#include "utility.h"
using namespace std;



int main() {

    std::cout << " 一款模拟大富翁逻辑的小demo, 主要是展示一下代码风格" << std::endl;
    std::cout << "输入想要模拟的玩家人数(输入最好大于1,为1会导致bug不过我还是允许你输入1方便你测试)";
    int num = -1;
    while (num < 1) {
        num = utility::input_num();
        std::cout << "大于1";
    }


    // std::setlocale(LC_ALL, "");//乱码问题 就这样吧在linux上wcout cout 不能混用不然会爆炸,当我发现乱码问题时已经来不及了,凑合看吧

    auto game = make_shared<Game>(num);
    game->render();
    game->run();
}





    // for (int i = 0; i < 10 ; ++i)
    //     std::cout << a.random() << std::endl;
    


    // while (1)
        // std::cout << "test" << utility::input_num() << std::endl;








    //test 1 player 支付模块

    // Player p1(1, 30000, 50);
    // Player p2(2, 30000, 50);
    // cout << p1.Attributes();
    // p1.pay(&p2, 1000);
    // p1.pay(&p2, 20000);
    // p1.pay(&p2, 50000);
    // p1.getmoney(100);
    // p1.getpoint(10);
    // p1.paypoint(60);
    // cout << p1.Attributes();
    // cout << p2.Attributes();


    // test interaction.h 这个模块大概没问题,就不动了
    // std::cout << make_shared<Interaction>("title", "text")->choose() << std::endl;
    // make_shared<Message>(make_shared<Player>(1,50,50,make_shared<Grid>(1, make_shared<House>(1,1000))), "text");

