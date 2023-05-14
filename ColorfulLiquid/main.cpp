#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <random>
#include <ctime>

using namespace std;

class Pack {//表示的是在一个试管中的所有的放在一起的同一个颜色；
public:
    int color_code;
    int volume;

    //初始化，记下这个颜色的色块，体积是零
    Pack(int color, int vo = 0) {
        color_code = color;
        volume = vo;
    }

    //表示的是加一滴
    void add_drop() {
        volume++;
    }

    //表示的是减一滴
    void sub_drop() {
        volume--;
    }
};

class Color {
public:
    int code;
    int total_volume;
    vector<pair<int, int>> packs;//tube codes and the volume;
    void add_tube(int t, int v) {
        packs.push_back({t, v});
        total_volume += v;
    }
};

void init_colors(Color *colors, int n) {
    for (int i = 1; i <= n; ++i) {
        colors[i].packs.clear();
        colors[i].total_volume = 0;
        colors[i].code = i;
    }
}

int t, colors, volume;

int main() {
    srand(time(0));
    scanf("%d %d %d", &t, &colors, &volume);
//    cout << t << " " << colors << " " << volume << endl;
    int c[colors];
    int **d;
    d = new int *[colors];
    for (int j = 0; j < colors; ++j) {
        d[j] = new int[colors];
    }
    int tubes = colors + 2;
    int spare_space[tubes];
    memset(spare_space, 0, sizeof(spare_space));
    spare_space[tubes - 2] = spare_space[tubes - 1] = volume;
    for (int i = 0; i < tubes; ++i)scanf("%d", &c[i]);
    for (int i = 0; i < colors; ++i)
        for (int j = 0; j < colors; ++j)
            scanf("%d", &d[i][j]);
    int drop;
    vector<Pack> distribution[tubes];
    for (int i = 0; i < tubes - 2; ++i) {
        //distribution[i]
        Pack pack(-1);
        for (int j = 0; j < volume; ++j) {
            scanf("%d", &drop);
//            cout << drop << " ";
            if (pack.color_code == -1)pack.color_code = drop;
            if (pack.color_code != drop) {
                distribution[i].push_back(pack);
                pack.volume = 0;
                pack.color_code = drop;
            }
            pack.add_drop();
        }
//        cout << endl;
        distribution[i].push_back(pack);
    }
    Color every_color_volume[colors + 1];
    int count = 0;
    while (1) {
//        count++;
//        if (count > 1048576)break;
        init_colors(every_color_volume, colors);
        //统计一下所有的颜色的总体积
        for (int i = 0; i < tubes; ++i) {
            if (distribution[i].empty())continue;
            auto pack = distribution[i].back();
            every_color_volume[pack.color_code].add_tube(i, pack.volume);
        }
        int the_color = -1;
        int the_volume = 0;
        for (int i = 1; i <= colors; ++i) {
            if (every_color_volume[i].packs.size() < 2)continue;
            if (every_color_volume[i].total_volume > the_volume) {
                the_color = i;
                the_volume = every_color_volume[i].total_volume;
            }
        }
        if (the_color == -1) {
            for (int i = 1; i <= colors; ++i) {
                if (every_color_volume[i].total_volume < volume && rand() % 2) {
                    the_color = i;
                    break;
                }
            }
            int the_tube = rand() % tubes;
            for (int i = 1; i <= colors; ++i) {
                if (every_color_volume[i].total_volume == volume &&
                    distribution[every_color_volume[i].packs[0].first].size() == 1
                    && rand() % 2) {
                    the_tube = i;
                    break;
                }
            }
            int the_space = every_color_volume[the_color].total_volume;
            if (the_space > spare_space[the_tube]) {
                for (int i = 0; i < the_space - spare_space[the_tube]; ++i) {
                    printf("2 %d\n", the_tube + 1);
                    count++;
                    if (count >= 1048576) {
                        printf("%d\n", count);
                        //todo
                        int number = 0;
                        for (int i = 1; i <= colors; ++i) {
                            if (every_color_volume[i].total_volume == volume &&
                                distribution[every_color_volume[i].packs[0].first].size() == 1)
                                number++;
                        }
                        printf("%d\n", number);
                        exit(0);
                    }
                    spare_space[the_tube]++;
                }
            }
            for (auto ptr = every_color_volume[the_color].packs.begin();
                 ptr != every_color_volume[the_color].packs.end(); ++ptr) {//遍历每一个颜色小包
                spare_space[ptr->first] += ptr->second;
                spare_space[the_tube] -= ptr->second;
                distribution[ptr->first].pop_back();
                for (int i = 0; i < ptr->second; ++i) {
                    if (ptr->first != the_tube) {
                        printf("1 %d %d\n", ptr->first + 1, the_tube + 1);
                        count++;
                        if (count >= 1048576) {
                            printf("%d\n", count);
                            //todo
                            int number = 0;
                            for (int i = 1; i <= colors; ++i) {
                                if (every_color_volume[i].total_volume == volume &&
                                    distribution[every_color_volume[i].packs[0].first].size() == 1)
                                    number++;
                            }
                            printf("%d\n", number);
                            exit(0);
                        }
                    }
                }
            }
            Pack total(the_color, every_color_volume[the_color].total_volume);
            distribution[the_tube].push_back(total);
            continue;
        }
        int the_space = every_color_volume[the_color].total_volume;
        //这里放在哪里应该会又很多考虑，
        //首先是这个地方的体积要已经尽可能的大，最好是已经够放
        //然后这个地方放下这个溶液的代价要尽可能的小
        //最后这个地方还应该尽可能的不要堵住别人本来能够很快的合并的溶液
        //这里可以搞一个所有的可以放的地方，然后给一个估价，最后选择估价最好的
        //像能不能放这种硬性要求就应改直接乘上一个0，然后代价越小所乘的数字就应该越大，
        //要耽误的溶液的总体积越小这个地方就应该越好,之间的代价越小这个地方越好
        double tubes_prices[tubes];
        double tubes_steps[tubes];
        double inf = 1e9;
        for (int i = 0; i < tubes; ++i) {
            double price = 0;
            if (distribution[i].empty())price = 0;
            else price = d[distribution[i].back().color_code - 1][the_color - 1];
            if (price == -1) {
                price = inf;
                tubes_steps[i] = inf;
            } else tubes_steps[i] = 0;
            int my_spare_space = spare_space[i];
            if (!distribution[i].empty() && the_color == distribution[i].back().color_code)
                my_spare_space += distribution[i].back().volume;
            if (the_space > my_spare_space) {
                price += c[i] * (the_space - my_spare_space);//移动到这个管道中的总代价算出来了
                tubes_steps[i] += the_space - my_spare_space;//加长这个管道中的总步数算出来了
            }
            if (!distribution[i].empty() && the_color != distribution[i].back().color_code) {
                price += every_color_volume[distribution[i].back().color_code].total_volume;
                tubes_steps[i] += the_space;
            } else {
                if (distribution[i].empty())tubes_steps[i] += the_space;
                else tubes_steps[i] += the_space - distribution[i].back().volume;//移动到这个管道中的总步数
            }
            tubes_prices[i] = price;
            if (!distribution[i].empty() && the_color != distribution[i].back().color_code)
                tubes_steps[i] += (every_color_volume[distribution[i].back().color_code].total_volume);
        }
        int the_tube = 0;
        for (int i = 0; i < tubes; ++i) {
            if (tubes_prices[the_tube] + 2.5 * tubes_steps[the_tube] > tubes_prices[i] + 2.5 * tubes_steps[i])
                the_tube = i;
        }
        int my_spare_space = spare_space[the_tube];
        if (!distribution[the_tube].empty() && the_color == distribution[the_tube].back().color_code)
            my_spare_space += distribution[the_tube].back().volume;
        if (the_space > my_spare_space) {
            for (int i = 0; i < the_space - my_spare_space; ++i) {
                printf("2 %d\n", the_tube + 1);
                count++;
                if (count >= 1048576) {
                    printf("%d\n", count);
                    //todo
                    int number = 0;
                    for (int i = 1; i <= colors; ++i) {
                        if (every_color_volume[i].total_volume == volume &&
                            distribution[every_color_volume[i].packs[0].first].size() == 1)
                            number++;
                    }
                    printf("%d\n", number);
                    exit(0);
                }
                spare_space[the_tube]++;
            }
        }
        for (auto ptr = every_color_volume[the_color].packs.begin();
             ptr != every_color_volume[the_color].packs.end(); ++ptr) {//遍历每一个颜色小包
            spare_space[ptr->first] += ptr->second;
            spare_space[the_tube] -= ptr->second;
            distribution[ptr->first].pop_back();
            for (int i = 0; i < ptr->second; ++i) {
                if (ptr->first != the_tube) {
                    printf("1 %d %d\n", ptr->first + 1, the_tube + 1);
                    count++;
                    if (count >= 1048576) {
                        printf("%d\n", count);
                        //todo
                        int number = 0;
                        for (int i = 1; i <= colors; ++i) {
                            if (every_color_volume[i].total_volume == volume &&
                                distribution[every_color_volume[i].packs[0].first].size() == 1)
                                number++;
                        }
                        printf("%d\n", number);
                        exit(0);
                    }
                }
            }
        }
        Pack total(the_color, every_color_volume[the_color].total_volume);
        distribution[the_tube].push_back(total);
        bool all_sorted = true;
        for (int i = 0; i < tubes; ++i) {
            if (!distribution[i].empty() && distribution[i].back().volume < volume) {
                all_sorted = false;
                break;
            }
        }
        if (all_sorted)break;
    }
    for (int j = 0; j < colors; ++j) {
        delete[]d[j];
    }
    delete[]d;
    printf("%d\n", count);
    return 0;
}