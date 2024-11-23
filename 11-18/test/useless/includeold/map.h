#include "space.h"

class Map {     //粗糙的实现一下        受制于内部的普通指针,为了简洁map只好不用智能指针了
 public:

    Map();

    Space* p_start_space();

    void debug();

 private:
    Space space[10];
};
