#include <iostream>
#include <limits>
#include <string>
using namespace std;

class A {
 public:
    void f() { std::cout << "A\n"; }
};

class B : public A{
    void f() { std::cout << "B\n"; }
};


int main() {
    A *a;

}
