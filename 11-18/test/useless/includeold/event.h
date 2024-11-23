#pragma once
#include "player.h"


class Player;
/*
   Event 事件 作为一个实体 在地图上放置或玩家间生效
  */
class Event {
 public:
     virtual void f(Player *) = 0;
 private:
     Player *source;
};