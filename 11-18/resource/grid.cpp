#include "token.h"
#include "grid.h"
#include "building.h"

void Grid::render() {
    std::cout << "Grid:" << m_id ;
    for (auto &token : m_token) {
        std::cout << " " << token->attr() << " ";
    }
    m_building->render();
}