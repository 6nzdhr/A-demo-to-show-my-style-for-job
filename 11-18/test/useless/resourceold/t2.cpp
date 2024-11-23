#include <iostream>
#include <cstdio>

int main() {
    std::string input;
    
    // 模拟从标准输入读取数据，可能会遇到EOF
    while (std::cin >> input) {
        std::cout << "You entered: " << input << std::endl;
    }

    std::cout << "End of input reached. Reopening stdin..." << std::endl;

    // 重新打开 stdin（如果之前因为 EOF 关闭）
    freopen("/dev/tty", "r", stdin);  // Linux 下的标准终端设备

    std::cout << "Please enter some new input:" << std::endl;
    while (std::cin >> input) {
        std::cout << "You entered: " << input << std::endl;
    }

    return 0;
}
