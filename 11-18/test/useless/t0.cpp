#include <memory>
#include <iostream>
using namespace std;

int main() {
    auto p = make_shared<int>(10);
    auto q = p;
    std::cout << *p;
}