//
// Created by lu'ren'jia'd's on 2021/12/1.
//

#ifndef UNTITLED4_POKEDEX_H
#define UNTITLED4_POKEDEX_H
//可以自己定义一些全局变量、引用头文件
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>

std::map<const std::string, int> types_map = {
        {"fire",     0},
        {"water",    1},
        {"grass",    2},
        {"electric", 3},
        {"flying",   4},
        {"ground",   5},
        {"dragon",   6}};
std::map<int, const std::string> types_from_int = {
        {0, "fire"},
        {1, "water"},
        {2, "grass"},
        {3, "electric"},
        {4, "flying"},
        {5, "ground"},
        {6, "dragon"}};
double hurt_times[7][7] = {{0.5, 2,   0.5, 1,   1,   2,   1},
                           {0.5, 0.5, 2,   2,   1,   1,   1},
                           {2,   0.5, 0.5, 0.5, 2,   0.5, 1},
                           {1,   1,   1,   1,   0.5, 2,   1},
                           {1,   1,   0.5, 2,   1,   0,   1},
                           {1,   2,   2,   0,   1,   1,   1},
                           {0.5, 0.5, 0.5, 0.5, 1,   1,   2}};

class BasicException {
protected:
    //可以自己定义所需要的成员
    std::string message;

public:
//    explicit BasicException(const std::string _message) {
//        //用错误信息初始化
//        message = _message;
//    }

    virtual std::string what() const {
        //return: 错误信息字符串
        return message;
    }
};

class ArgumentException : public BasicException {
public:
    explicit ArgumentException(const std::string &_message) {
        //用错误信息初始化
        message = "Argument Error: ";
        message += _message;
    }

    void add_info(const std::string info) {
        message += info;
    }

    std::string what() const {
        //return: 错误信息字符串

        return message;
    }

};

class IteratorException : public BasicException {

    std::string what() const {
        //return: 错误信息字符串

        return message;
    }

public:
    explicit IteratorException(const std::string &_message) {
        //用错误信息初始化
        message = "Iterator Error: ";
        message += _message;
    }
};

struct Pokemon {
    //设计你自己的宝可梦类！
    //唯一要求：一定要有名为name id的两个public成员变量，评测时需要用到
    char name[12]{'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    int id;
    int type_of[7]{-1, -1, -1, -1, -1, -1, -1};


};

bool operator<(const Pokemon &another, const Pokemon &one) {
    if (one.id > another.id)return true;
    else return false;
}

class Pokedex {
private:
    //可以自己定义需要的成员

    std::string file_name;
    std::set<int> pokemon_id;
    std::map<int, Pokemon> pokemon_info;
    static int array_size;
    static int current_size;
    static Pokemon *first;

    void double_space() {
        Pokemon *temp = first;
        first = new Pokemon[2 * array_size];
        for (int i = 0; i < current_size; ++i) { first[i] = temp[i]; }
        array_size *= 2;
        delete[]temp;
    }

    void add_pokemon(const int &add_id) {
        if (current_size == array_size)double_space();
        current_size++;
        first[current_size - 1] = pokemon_info[add_id];
        std::sort(first, first + current_size);
    };

    void delete_pokemon(const int &dele_id) {
        int i;
        for (i = 0; i < current_size; ++i) {
            if (first[i].id == dele_id)break;
        }
        current_size--;
        for (int j = i; j < current_size; j++) {
            first[j] = first[j + 1];
        }
    };//todo

public:
    explicit Pokedex(const char *_fileName) {
        //  TO DO: 构造函数，从名为_fileName的文件中读取数据（没有则创建）
        array_size = 100;
        current_size = 0;
        first = new Pokemon[100];
        file_name = _fileName;
        std::fstream file_read;
        file_read.open(file_name);
        if (file_read) {//todo
            file_read.seekg(0);
            Pokemon readp;
            while (file_read.peek() != EOF) {
                file_read.read(reinterpret_cast<char *>(&readp), sizeof(Pokemon));
                pokemon_info[readp.id] = readp;
                pokemon_id.insert(readp.id);
                add_pokemon(readp.id);
            }
        }
        file_read.close();
    }

    ~Pokedex() {
        std::fstream file_write;
        file_write.open(file_name, std::ios::out);
        for (auto ptr = pokemon_info.begin(); ptr != pokemon_info.end(); ptr++) {
            Pokemon writep = ptr->second;
            file_write.write(reinterpret_cast<char *>(&writep), sizeof(Pokemon));
        }
        file_write.close();
        delete[]first;
    }

    bool pokeAdd(const std::string &name, int id, const std::string types_add) {
        //TO DO: 添加宝可梦
        auto *addp = new Pokemon;
        for (int i = 0; i < name.length(); ++i) {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))) {
                delete addp;
                ArgumentException report_error("PM Name Invalid ");
                std::string report_name = "(" + name + ")";
                report_error.add_info(report_name);
                throw report_error;
            }
        }
        for (int i = 0; i < name.length(); ++i) {
            addp->name[i] = name[i];
        }
        if (id <= 0) {
            delete addp;
            ArgumentException report_error("PM ID Invalid ");
            std::stringstream ss;
            ss.clear();
            ss << id;
            std::string id_str;
            ss >> id_str;
            id_str = "(" + id_str + ")";
            report_error.add_info(id_str);
            throw report_error;
        } else { addp->id = id; }
        if (pokemon_id.count(id)) {
            delete addp;
            return false;
        }
        std::stringstream ss;
        ss.str(types_add);
        int i = 0;
        while (1) {
            std::string type;
            getline(ss, type, '#');
            if (type == "")break;
            if (type == "fire" || type == "water" || type == "grass" || type == "electric" ||
                type == "flying" || type == "ground" || type == "dragon") {
                addp->type_of[i] = types_map[type];
                i++;
            } else {
                delete addp;
                ArgumentException report_error("PM Type Invalid ");
                type = "(" + type + ")";
                report_error.add_info(type);
                throw report_error;
            }
        }
        pokemon_id.insert(id);
        pokemon_info[id] = *addp;
        add_pokemon(id);
        delete addp;
        return true;
    }

    bool pokeDel(int id) {
        //TO DO: 删除对应宝可梦
        //return: 返回是否删除成功
        if (id <= 0) {
            ArgumentException report_error("PM ID Invalid ");
            std::stringstream ss;
            ss.clear();
            ss << id;
            std::string id_str;
            ss >> id_str;
            id_str = "(" + id_str + ")";
            report_error.add_info(id_str);
            throw report_error;
        } else {
            if (!pokemon_id.count(id)) return false;
            else {
                pokemon_id.erase(id);
                pokemon_info.erase(id);
                delete_pokemon(id);
                return true;
            }
        }
    }

    std::string pokeFind(int id) {
        //TO DO: 查询id对应的宝可梦
        //return: 如果找到，返回宝可梦的name。否则返回字符串 "None"
        if (id <= 0) {
            ArgumentException report_error("PM ID Invalid ");
            std::stringstream ss;
            ss.clear();
            ss << id;
            std::string id_str;
            ss >> id_str;
            id_str = "(" + id_str + ")";
            report_error.add_info(id_str);
            throw report_error;
        } else {
            if (pokemon_info.count(id))return pokemon_info[id].name;
            else return "None";
        }
    }

    std::string typeFind(const char *types) {
        //TO DO: 查询属性包含了types中的属性的宝可梦
        //return: 如果找到，返回多行字符串。第一行为满足的宝可梦数量，
        //          接下来每一行为宝可梦的name，按id从小到大。
        //        如果找不到，返回字符串 "None"
        //注意，types可能为多种属性，同样用 # 号分隔
        std::stringstream ss;
        ss.str(types);
        std::set<Pokemon> ans;
        std::set<std::string> find_type;
        while (1) {
            std::string type;
            getline(ss, type, '#');
            if (type == "")break;
            if (type == "fire" || type == "water" || type == "grass" || type == "electric" ||
                type == "flying" || type == "ground" || type == "dragon") {
                find_type.insert(type);
            } else {
                ArgumentException report_error("PM Type Invalid ");
                type = "(" + type + ")";
                report_error.add_info(type);
                throw report_error;
            }
        }
        for (auto ptr = pokemon_info.begin(); ptr != pokemon_info.end(); ptr++) {
            Pokemon query = ptr->second;
            int can_has = 0;
            for (auto require = find_type.begin(); require != find_type.end(); require++) {
                //find *require
                for (int j = 0; j < 7; ++j) {
                    if (query.type_of[j] == -1)break;
                    if (query.type_of[j] == types_map[*require]) {
                        can_has++;
                        break;
                    }
                }
            }
            if (can_has == find_type.size())ans.insert(query);
        }


        int size = ans.size();
        std::string ans_str;
        std::stringstream trans;
        trans.clear();
        trans << size;
        trans >> ans_str;
        for (auto ptr = ans.begin(); ptr != ans.end(); ++ptr) {
            ans_str += '\n';
            ans_str += ptr->name;
        }
        if (ans_str == "0")ans_str = "None";
        return ans_str;
    }

    float attack(std::string type, int id) {
        //TO DO: 伤害倍率计算
        //return: 返回id对应的宝可梦受到属性type的攻击的伤害倍率。
        //          如果id对应不存在宝可梦，返回 -1
        //这里type保证为单属性
        if (id <= 0) {
            ArgumentException report_error("PM ID Invalid ");
            std::stringstream ss;
            ss.clear();
            ss << id;
            std::string id_str;
            ss >> id_str;
            id_str = "(" + id_str + ")";
            report_error.add_info(id_str);
            throw report_error;
        } else if (type != "fire" && type != "water" && type != "grass" && type != "electric" &&
                   type != "flying" && type != "ground" && type != "dragon") {
            ArgumentException report_error("PM Type Invalid ");
            type = "(" + type + ")";
            report_error.add_info(type);
            throw report_error;
        } else {
            if (pokemon_info.count(id)) {
                Pokemon victim = pokemon_info[id];
                double times = 1;
                int attacker_type_num = types_map[type];
                for (int j = 0; j < 7; ++j) {
                    if (victim.type_of[j] == -1)break;
                    times *= hurt_times[victim.type_of[j]][attacker_type_num];
                }
                return (float) times;
            } else return -1;

        }
    }

    int catchTry() {
        //TO DO: 全图鉴捕获尝试
        //return: 按照前文过程最后能拥有的宝可梦数量。
        int number = 1;
        std::queue<Pokemon> my_pokemon;
        my_pokemon.push(pokemon_info.begin()->second);
        std::set<int> uncaptured_id;
        for (auto ptr = ++pokemon_id.begin(); ptr != pokemon_id.end(); ++ptr)uncaptured_id.insert(*ptr);
        while (!my_pokemon.empty()) {
            Pokemon attacker = my_pokemon.front();
            my_pokemon.pop();
            for (auto victim = uncaptured_id.begin(); victim != uncaptured_id.end();) {
                int size = uncaptured_id.size();
                for (int i = 0; i < 7; ++i) {
                    if (attacker.type_of[i] == -1)break;
                    double hurt = attack(types_from_int[attacker.type_of[i]], *victim);
                    if (hurt >= 2) {
                        my_pokemon.push(pokemon_info[*victim]);
                        int cp = *victim;
                        ++victim;
                        uncaptured_id.erase(cp);
                        number++;
                        break;
                    }
                }
                if (size == uncaptured_id.size())++victim;
            }
        }
        return number;
    }

    struct iterator {
        friend Pokedex;
        //可以自己定义所需要的成员
        Pokemon *current;

        iterator &operator++() {
            //TO DO: ++迭代器
            Pokemon *end_of = first + current_size;
            if (current == end_of) {
                IteratorException report_error("Invalid Iterator");
                throw report_error;
            } else ++current;
            return *this;
        }

        iterator &operator--() {
            if (current == first) {
                IteratorException report_error("Invalid Iterator");
                throw report_error;
            } else --current;
            return *this;
        }

        iterator operator++(int k) {
            iterator temp{};
            temp.current = current;
            Pokemon *end_of = first + current_size;
            if (current == end_of) {
                IteratorException report_error("Invalid Iterator");
                throw report_error;
            } else ++current;
            return temp;
        }

        iterator operator--(int k) {
            iterator temp{};
            temp.current = current;
            if (current == first) {
                IteratorException report_error("Invalid Iterator");
                throw report_error;
            } else --current;
            return temp;
        }

        iterator &operator=(const iterator &rhs) {
            current = rhs.current;
            return *this;
        }

        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const iterator &rhs) const {
            return current != rhs.current;
        }

        Pokemon &operator*() const {
            if (current == first + current_size) {
                IteratorException report_error("Dereference Error");
                throw report_error;
            } else return *current;
        }

        /**
         * for the support of it->first.
         * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
         */
        Pokemon *operator->() const {
            if (current == first + current_size) {
                IteratorException report_error("Dereference Error");
                throw report_error;
            } else return current;
        }
    };

    iterator begin() {
        iterator temp{};
        temp.current = first;
        return temp;
    }

    iterator end() {
        //return: 返回指向图鉴尾部的迭代器。
        //准确的说，是“最后的一个元素”的后面，指向的内容为空，详情可以去了解标准库容器的 end()
        iterator temp{};
        temp.current = first + current_size;
        return temp;
    }

    //friend struct iterator;
};

int Pokedex::array_size;
int Pokedex::current_size;
Pokemon *Pokedex::first;

#endif //UNTITLED4_POKEDEX_H
