#include <algorithm>
#include "event.h"
#include "game.h"
#include "building.h"
#include "token.h"
#include "grid.h"
#include "player.h"
#include "state.h"
#include "interaction.h"
#include "utility.h"
#include "prop.h"

std::shared_ptr<Grid> Go_to_hopital::m_hospital = NULL;

Game::Game(int num) {

    //粗糙的初始化地图就是NUM_GRID个格子
    for (int i = 0; i < NUM_GRID; i++) {
        m_grid.push_back(std::make_shared<Grid>(i+1, std::make_shared<Empty_land>(i+1, "empty_land")));
    }
    for (int i = 0; i < NUM_GRID; i++) {
        m_grid[i]->linknext(m_grid[(i+1)%NUM_GRID]);
    }
    // Public = std::make_shared<Player>(0, 1000000, 500, m_grid[0]);  //为了简化逻辑引入的Public角色,它也可能没有钱
    //粗糙的初始化 num 个人物,并手动添加道具
    for (int i = 0; i < num; i++) {
        m_player.push_back(std::make_shared<Player>(i+1, 30000, 50, m_grid[0]));
        m_player[i]->prop().push_back(std::make_shared<Remote_controlled_dice>());
        m_player[i]->prop().push_back(std::make_shared<Building_card>());
        m_player[i]->prop().push_back(std::make_shared<Bomb_card>());

    }



    m_grid[0]->building() = std::make_shared<Point_land>(1, 50);
    m_grid[1]->building() = std::make_shared<House>(2, 3000);
    m_grid[2]->building() = std::make_shared<Empty_land>(3, "hospital");  
    m_grid[3]->building() = std::make_shared<House>(4, 2500);


    // 初始化一些事件集合来填充Accident_land,没有仔细的设计,demo快到头了,就这样了
    m_event_set.push_back(std::make_shared<Get_money>());
    m_event_set.push_back(std::make_shared<Get_point>());
    m_event_set.push_back(std::make_shared<Go_to_hopital>(3));
    
    m_grid[4]->building() = std::make_shared<Accident_land>(5, m_event_set);
    m_grid[5]->building() = std::make_shared<PointShop_land>(6);

    // 初始化一些事件,有一定的扩展性吧
    Go_to_hopital::init(m_grid[2]); 
}





void Game::run() {
    int gameover = 1;
    while (gameover) {
        Message("新的回合开始了");
        for (auto &player : m_player) {
            player->init_state();          //这种补丁意味着程序即将爆炸
            Message(player, "'s turn: ============================================");
            // 处理state
            player->state().erase(std::remove_if(player->state().begin(), player->state().end(),        //借鉴chatgpt的
                [&player](p_State state) { 
                return !state->effect(player); 
                }),
                player->state().end());
            // operate
            if (player->able_to_operation()) {
                operation(player);
                render();

            }
            // move 
            if (player->able_to_move()) {
                while (1) {
                    std::cout << "For debug Enter the number of steps you want to take:(>=0)";
                    Message(player, "mov"); //眼快花了
                    int n = utility::input_num();
                    if (n >= 0) {
                        Message(player, "mov " + std::to_string(n));
                        player->move(n);
                        break;
                    }
                    std::cout << "illeagl\n";
                } 


            }

            // 和地图上的 Token 交互  那必然是混乱的重叠的
            auto old_pos = player->pos();
            for (auto &token : player->pos()->token()) {
                token->interact(player);
            }
            old_pos->token().clear();       //这种逻辑一多迟早爆炸
            render();
            // 和地图上的 building 交互
            if (!player->pos()->building()->interact(player)) {
                gameover = bankrupt(player);       //这真的会导致出局
            }
            if (gameover == 0) return;
            render();


        }
    }
}

void Game::operation(p_Player in_player) {
    while (1) {

        if (in_player->prop().empty()) {
            std::cout << "no prop to op" << std::endl;
            return;
        }

        int i = 0;
        for (auto &prop : in_player->prop()) {
            std::cout << ++i << ":" << prop->attr() << "  ";
        }
        std::cout << " A total of " << i << " props " << std::endl;
        //此时i为道具的数量
        std::cout << "Choose a prop based on the number (any illegal input to quit): ";

        int choose = utility::input_num() - 1;  //这里的 -1 曾经导致爆炸, 程序快要到头了
        if (choose >= 0 && choose < i) {
            if (in_player->prop()[choose]->used_by(m_grid, in_player)) { 
                in_player->prop().erase(in_player->prop().begin() + choose);
            }
        } else {
            std::cout << "you quit" << std::endl;
            return;
        }
    }
}


bool Game::bankrupt(p_Player in_player) {  //破产清算 智能指针的用处就体现在这里 返回值代表游戏是否还继续进行
    Message("player" + std::to_string(in_player->id()) + " went bankrupt!!!");
    //为了逻辑的简化,它所拥有的房子回归于银行,这个玩家不再调度,谁碰了他的房子照付他钱,逻辑上是给银行 就是懒了
    m_player.erase(m_player.begin() + in_player->id() - 1);
    if (m_player.size() == 1) {
        Message(m_player[0], "win==================================================================");        //粗糙结束了
        Message(m_player[0], "win==================================================================");
        Message(m_player[0], "win==================================================================");
        Message(m_player[0], "win==================================================================");
        Message(m_player[0], "win==================================================================");
        return 0;
    }
    return 1;
}

void Game::render() {
    std::cout << "\tgeneral map" << std::endl << "\n\t";
    for (unsigned i = 0; i < m_grid.size(); )
        std::cout << "Grid" << ++i << "->";
    std::cout << "Grid1" << std::endl;



    std::cout << "\n\tGAME RENDER===========" << std::endl;
    for (auto &grid : m_grid)
        grid->render();
    for (auto &player : m_player) 
        std::cout << player->attributes() << std::endl;
    std::cout << "\tGAME RENDER===========" << std::endl;

}

Game::~Game() {
    m_event_set.clear();
    m_player.clear();
    m_grid.clear();
}
