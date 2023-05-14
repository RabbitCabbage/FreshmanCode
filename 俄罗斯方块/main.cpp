#include <iostream>
#include <cstring>
#include <vector>

int max(int a, int b) {
    return (a > b ? a : b);
}

int max(int a, int b, int c) {
    a = (a > b ? a : b);
    return (a > c ? a : c);
}

void print(int b, bool board[9][9], int height[9]) {
    std::cout << std::endl;
    std::cout << "block " << b << std::endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j])printf("%c  ", '*');
            else printf("%c  ", '.');
        }
        printf("%c", '\n');
    }
    for (int i = 0; i < 9; ++i) {
        std::cout << height[i] << "  ";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    int t, n;
    bool board[9][9];
    int height[9];//记录每一列的最高点的高度
    scanf("%d", &t);
    scanf("%d", &n);
    memset(board, false, sizeof(board));
    memset(height, 0, sizeof(height));
    int b;
    for (int j = 0; j < n; ++j) {
        scanf("%d", &b);
        if (b == 1) {
            int column = 0;
            for (int c = 0; c < 9; ++c) {
                if (height[c] < height[column])
                    column = c;//找到高度最小的那一列
            }
            if (8 - height[column] >= 0)board[8 - height[column]][column] = true;
            //else return 0;
            height[column]++;
            printf("%d\n", column + 1);
        } else if (b == 2) {
            int column = 0;
            for (int c = 0; c < 9; ++c) {
                if (height[c] <= height[column])
                    column = c;//找到高度最小的那一列
            }
            if (7 - height[column] >= 0) {
                board[8 - height[column]][column] = true;
                board[7 - height[column]][column] = true;
            } //else return 0;
            height[column] += 2;
            printf("%d\n", column + 1);
        } else if (b == 4) {
            int column = 0;
            for (int c = 0; c < 9; ++c) {
                if (height[c] <= height[column])
                    column = c;//找到高度最小的那一列
            }
            if (8 - height[column] >= 0)board[8 - height[column]][column] = true;
            if (8 - height[column] - 1 >= 0)board[8 - height[column] - 1][column] = true;
            if (8 - height[column] - 2 >= 0)board[8 - height[column] - 2][column] = true;
            height[column] += 3;
            printf("%d\n", column + 1);
        } else if (b == 3) {
            std::vector<int> platform;
            int column = -1;//这个最低的,不管有没有平台
            int platform_column = -1;//这个记录的是最低的平台
            int min_h = 10;//这个是两列一起算里面最低的高度
            int min_platform = 10;//这是平台最低的高度
            for (int c = 0; c < 8; ++c) {
                //先遍历一遍，记下所有平的连续两个的
                //并且记下连续两个最低的
                if (height[c] == height[c + 1]) {
                    platform.push_back(c);
                    if (height[c] < min_platform) {
                        min_platform = height[c];
                        platform_column = c;
                    }
                }
                int h = max(height[c], height[c + 1]);
                if (h < min_h) {
                    min_h = h;
                    column = c;
                }
            }
            //现在我们有两种选择方法，一种是选择先填最低的，一中是先填满不留余下的格子
            if (!platform.empty() && min_platform < 9 && min_platform - min_h <= 1) {
                printf("%d\n", platform_column + 1);
                if (8 - min_platform >= 0)
                    board[8 - min_platform][platform_column] = board[8 - min_platform][platform_column + 1] = true;
                //else return 0;
                height[platform_column]++;
                height[platform_column + 1]++;
            } else {
                printf("%d\n", column + 1);
                if (8 - min_h >= 0)board[8 - min_h][column] = board[8 - min_h][column + 1] = true;
                //else return 0;
                height[column] = min_h + 1;
                height[column + 1] = min_h + 1;
            }
        } else if (b == 5) {
            std::vector<int> platform;
            int column = -1;//这个最低的,不管有没有平台
            int platform_column = -1;//这个记录的是最低的平台
            int min_h = 10;//这个是两列一起算里面最低的高度
            int min_platform = 10;//这是平台最低的高度
            for (int c = 0; c < 7; ++c) {
                //先遍历一遍，记下所有平的连续两个的
                //并且记下连续两个最低的
                if (height[c] == height[c + 1] && height[c + 1] == height[c + 2]) {
                    platform.push_back(c);
                    if (height[c] < min_platform) {
                        min_platform = height[c];
                        platform_column = c;
                    }
                }
                int h = max(height[c], height[c + 1], height[c + 2]);
                if (h < min_h) {
                    min_h = h;
                    column = c;
                }
            }
            //现在我们有两种选择方法，一种是选择先填最低的，一中是先填满不留余下的格子
            if (!platform.empty() && min_platform < 9 && min_platform - min_h <= 2) {
                printf("%d\n", platform_column + 1);
                if (8 - min_platform >= 0)
                    board[8 - min_platform][platform_column] = board[8 - min_platform][platform_column + 1]
                            = board[8 - min_platform][platform_column + 2] = true;
                //else return 0;
                height[platform_column]++;
                height[platform_column + 1]++;
                height[platform_column + 2]++;
            } else {
                //我们现在必须要让下面留格子了，但是想下面留着最少的格子,空出来的最少
                printf("%d\n", column + 1);
                if (8 - min_h >= 0)
                    board[8 - min_h][column] = board[8 - min_h][column + 1]
                            = board[8 - min_h][column + 2] = true;
                //else return 0;
                height[column] = min_h + 1;
                height[column + 1] = min_h + 1;
                height[column + 2] = min_h + 1;
            }
        } else if (b == 6) {
            std::vector<int> platform;
            int column = -1;//这个最低的,不管有没有平台
            int platform_column = -1;//这个记录的是最低的平台
            int min_h = 10;//这个是两列一起算里面最低的高度
            int min_platform = 10;//这是平台最低的高度
            for (int c = 0; c < 8; ++c) {
                //先遍历一遍，记下所有平的连续两个的
                //并且记下连续两个最低的
                if (height[c] == height[c + 1]) {
                    platform.push_back(c);
                    if (height[c] < min_platform) {
                        min_platform = height[c];
                        platform_column = c;
                    }
                }
                int h = max(height[c], height[c + 1]);
                if (h < min_h) {
                    min_h = h;
                    column = c;
                }
            }
            //现在我们有两种选择方法，一种是选择先填最低的，一中是先填满不留余下的格子
            if (!platform.empty() && min_platform < 8) {
                printf("%d\n", platform_column + 1);
                if (8 - min_platform >= 0)
                    board[8 - min_platform][platform_column] = board[8 - min_platform][platform_column + 1] = true;
                //else return 0;
                if (7 - min_platform >= 0)board[7 - min_platform][platform_column] = true;
                //else return 0;
                height[platform_column] += 2;
                height[platform_column + 1]++;
            } else {
                printf("%d\n", column + 1);
                if (8 - min_h >= 0)board[8 - min_h][column] = board[8 - min_h][column + 1] = true;
                //else return 0;
                height[column] = min_h + 2;
                height[column + 1] = min_h + 1;
            }
        } else if (b == 7) {
            std::vector<int> platform;
            int column = -1;//这个最低的,不管有没有平台
            int platform_column = -1;//这个记录的是最低的平台
            int min_h = 10;//这个是两列一起算里面最低的高度
            int min_platform = 10;//这是平台最低的高度
            for (int c = 0; c < 8; ++c) {
                //先遍历一遍，记下所有平的连续两个的
                //并且记下连续两个最低的
                if (height[c] == height[c + 1]) {
                    platform.push_back(c);
                    if (height[c] < min_platform) {
                        min_platform = height[c];
                        platform_column = c;
                    }
                }
                int h = max(height[c], height[c + 1]);
                if (h < min_h) {
                    min_h = h;
                    column = c;
                }
            }
            //现在我们有两种选择方法，一种是选择先填最低的，一中是先填满不留余下的格子
            if (!platform.empty() && min_platform < 8) {
                printf("%d\n", platform_column + 1);
                if (8 - min_platform >= 0)
                    board[8 - min_platform][platform_column] = board[8 - min_platform][platform_column + 1] = true;
                //else return 0;
                if (7 - min_platform >= 0)board[7 - min_platform][platform_column + 1] = true;
                //else return 0;
                height[platform_column]++;
                height[platform_column + 1] += 2;
            } else {
                printf("%d\n", column + 1);
                if (8 - min_h >= 0)board[8 - min_h][column] = board[8 - min_h][column + 1] = true;
                //else return 0;
                height[column] = min_h + 1;
                height[column + 1] = min_h + 2;
            }
        } else if (b == 8) {
            std::vector<int> platform;
            int column = -1;//这个最低的,不管有没有平台
            int platform_column = -1;//这个记录的是最低的平台
            int min_h = 10;//这个是两列一起算里面最低的高度
            int min_platform = 10;//这是平台最低的高度
            for (int c = 0; c < 8; ++c) {
                if (height[c] == height[c + 1] - 1) {
                    platform.push_back(c);
                    //这里的min_platform记下的是右边更高的
                    //但是platform——column记下的还是左边的开始
                    if (height[c + 1] < min_platform) {
                        min_platform = height[c + 1];
                        platform_column = c;
                    }
                }
                int h = max(height[c] + 1, height[c + 1]);
                //下面就是说这个方块落在哪里能让总体的高最小
                if (h < min_h) {
                    column = c;
                    min_h = h;
                }
            }
            if (!platform.empty() && min_platform < 9 && min_platform - min_h <= 1) {
                printf("%d\n", platform_column + 1);
                if (8 - min_platform >= 0) {
                    board[8 - min_platform][platform_column] = board[9 - min_platform][platform_column] = true;
                    board[8 - min_platform][platform_column + 1] = true;
                } //else return 0;
                height[platform_column] = height[platform_column + 1] = min_platform + 1;
            } else {
                printf("%d\n", column + 1);
                if (8 - min_h > 0) {
                    board[9 - min_h][column] = board[8 - min_h][column] = true;
                    board[8 - min_h][column + 1] = true;
                } //else return 0;
                height[column] = height[column + 1] = min_h + 1;
            }
        } else if (b == 9) {
            std::vector<int> platform;
            int column = -1;//这个最低的,不管有没有平台
            int platform_column = -1;//这个记录的是最低的平台
            int min_h = 10;//这个是两列一起算里面最低的高度
            int min_platform = 10;//这是平台最低的高度
            for (int c = 0; c < 8; ++c) {
                if (height[c] == height[c + 1] + 1) {
                    platform.push_back(c);
                    //这里的min_platform记下的是左边更高的
                    //platform——column记下的还是左边的开始
                    if (height[c] < min_platform) {
                        min_platform = height[c];
                        platform_column = c;
                    }
                }
                int h = max(height[c], height[c + 1] + 1);
                //下面就是说这个方块落在哪里能让总体的高最小
                if (h < min_h) {
                    column = c;
                    min_h = h;
                }
            }
            if (!platform.empty() && min_platform < 9 && min_platform - min_h <= 1) {
                printf("%d\n", platform_column + 1);
                if (8 - min_platform >= 0) {
                    board[8 - min_platform][platform_column] = true;
                    board[8 - min_platform][platform_column + 1] = board[9 - min_platform][platform_column +
                                                                                           1] = true;
                } //else return 0;
                height[platform_column] = height[platform_column + 1] = min_platform + 1;
            } else {
                printf("%d\n", column + 1);
                if (8 - min_h >= 0) {
                    board[9 - min_h][column + 1] = board[8 - min_h][column + 1] = true;
                    board[8 - min_h][column] = true;
                } //else return 0;
                height[column] = height[column + 1] = min_h + 1;
            }
        }
//        print(b, board, height);
        for (int row = 0; row < 9; ++row) {
            int count = 0;
            for (int column = 0; column < 9; ++column) {
                if (board[row][column])count++;
            }
            if (count == 9) {
                for (int r = row - 1; r >= 0; r--) {
                    for (int c = 0; c < 9; ++c) {
                        board[r + 1][c] = board[r][c];
                    }
                }
                for (int c = 0; c < 9; ++c) {
                    //height[c]--;
                    board[0][c] = false;
                    int r;
                    for (r = 0; r < 9; ++r) {
                        if (board[r][c])break;
                    }
                    height[c] = 9 - r;
                }
            }
        }
    }
    return 0;
}
