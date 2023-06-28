# 南开2020软件工程结对编程

田佳业 田翔宇

| 参数名字 |         参数意义         |    范围限制    |         用法示例          | 用法解释                                                     |
| :------: | :----------------------: | :------------: | :-----------------------: | ------------------------------------------------------------ |
|    -c    |    需要的数独终盘数量    |   1-1000000    |     sudoku.exe -c 20      | 表示生成20个数独终盘                                         |
|    -s    | 需要解的数独棋盘文件路径 | 绝对或相对路径 |  sudoku.exe -s game.txt   | 表示从game.txt读取若干个数独游戏，并给出其解答，生成到sudoku.txt中 |
|    -n    |      需要的游戏数量      |    1-10000     |    sudoku.exe -n 1000     | 表示生成1000个数独游戏                                       |
|    -m    |      生成游戏的难度      |      1-3       |  sudoku.exe -n 1000 -m 1  | 表示生成1000个简单数独游戏，只有m和n一起使用才认为参数无误，否则请报错 |
|    -r    | 生成游戏中挖空的数量范围 |     20-55      | sudoku.exe -n 20 -r 20~55 | 表示生成20个挖空数在20到55之间的数独游戏，只有 r 和 n 一起使用才认为参数无误，否则请报错 |
|    -u    |     生成游戏的解唯一     |                |    sudoku.exe -n 20 -u    | 表示生成20个解唯一的数独游戏，只有u和 n 一起使用才认为参数无误，否则请报错 |

### 参数解析

测试用例

```
none

```

```
add_subdirectory(./googletest)include_directories(${PROJECT_SOURCE_DIR}/src/include ./googletest/include)link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/googletest)target_link_libraries(${PROJECT_NAME} gtest)
```