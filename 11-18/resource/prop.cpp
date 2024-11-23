#include "prop.h"
#include "player.h"
#include "building.h"
#include "game.h"
#include "grid.h"
#include "token.h"
#include "utility.h"

bool Building_card::used_by(std::vector<p_Grid> &in_grid, p_Player in_player) {    //涉及反射,怎么办,加接口。从此耦合多了起来。
    std::cout << "Using building_card input the id of the building that you want to build (any illegal to q)";
    unsigned num = utility::input_num() - 1;
    if (num < in_grid.size()) {   //地图为空那就不得不爆炸了
        if (in_grid[num]->building()->owner() != NULL && in_grid[num]->building()->build_up()) {    //出现冗余就这样了
            std::cout << "use success" << std::endl;
            return true;
        }
    }
    std::cout << "illegal operation" << std::endl;
    return false;       //返回值代表使用失败,不得不说大富翁游宝岛真好玩
}

bool Bomb_card::used_by(std::vector<p_Grid> &in_grid, p_Player in_player) {
    while(1) {
        std::cout << "Using bomb_card input the id of the grid that you want to put: ";
        unsigned num = utility::input_num() - 1;
        if (num < in_grid.size()) {   //地图为空那就不得不爆炸了
            std::cout << "use success" << std::endl;
            in_grid[num]->put(std::make_shared<Bomb>());
            return true;
        } else {
            std::cout << "illegal scope" << std::endl;
        }
    }
    return false;       //很显然我懒了,并不打算实现撤回机制
}



bool Remote_controlled_dice::used_by(std::vector<p_Grid> &in_grid, p_Player in_player) {
    while (1) {
        std::cout << "Please enter the distance you want to travel : " << std::endl;
        int num = utility::input_num();
        if (num > 0 && num <= 6) {//这种硬编码偷懒了,写到这里主要是展示下代码风格。
            Message(in_player, "use remote dice move " + num);
            in_player->move(num);
            in_player->can_not_nove();
            return true;
        }
        std::cout << "illeagl op" << std::endl;
    }
    return false;   //never reach here返回值代表操作成功与否,很显然我不打算添加退出机制
}


// class remote_dice {
//  public:
//     bool used_by(p_Game in_game, p_Player in_player) override;
// };

// inline
// void 
