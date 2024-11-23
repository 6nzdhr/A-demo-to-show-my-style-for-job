
# 1. 配置源文件和头文件目录
SRC_DIR := resource
INC_DIR := include  # 假设 space.h 在 resource 目录下
BUILD_DIR := build

# 2. 获取所有源文件
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# 3. 生成目标文件列表
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# 4. 设置目标程序名称
TARGET := my_program

# 5. 编译器和编译选项
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I$(INC_DIR)  -Og -g# 添加 -I$(INC_DIR) 来包含 resource 目录

# 6. 默认目标
all: clean $(TARGET)

# 7. 链接目标文件生成可执行文件
$(TARGET): $(OBJS) 
	$(CXX) $(OBJS) -o $(TARGET)

# 8. 编译源文件为目标文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@mkdir -p $(BUILD_DIR)  # 创建build目录
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 9. 清理生成的文件
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# 10. 伪目标
.PHONY: all clean


