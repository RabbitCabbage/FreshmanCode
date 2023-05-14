#include <bits/stdc++.h>

#include <cstring>
#include <string>

using namespace std;

char *pokemon_type[7] = {"fire",   "water",  "grass", "electric",
                         "flying", "ground", "dragon"};
float damage[7][7] = {
    {0.5, 0.5, 2, 1, 1, 1, 0.5},   {2, 0.5, 0.5, 1, 1, 2, 0.5},
    {0.5, 2, 0.5, 1, 0.5, 2, 0.5}, {1, 2, 0.5, 1, 2, 0, 0.5},
    {1, 1, 2, 0.5, 1, 1, 1},       {2, 1, 0.5, 2, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 2}};

bool if_name_invalid(const char *name) {
    for (int i = 0; i < strlen(name); i++)
        if (*(name + i) < 'A' || *(name + i) > 'Z' && *(name + i) < 'a' ||
            *(name + i) > 'z')
            return true;
    return false;
}

string if_type_invalid(const char *types) {
    char tmp[80];
    strcpy(tmp, types);
    char *token = strtok(tmp, "#");
    while (token != nullptr) {
        for (int i = 0; i < 7; i++) {
            if (strcmp(pokemon_type[i], token) == 0) break;
            if (i == 6) return token;
        }
        token = strtok(nullptr, "#");
    }
    return "-1";
}

class BasicException {
   protected:
    string message;

   public:
    explicit BasicException(string _message) : message(_message) {}

    virtual string what() const { return message; }
};

class ArgumentException : public BasicException {
   public:
    explicit ArgumentException(const char *_message)
        : BasicException(_message) {}

    virtual string what() const { return message; }
};

class InvalidName : public ArgumentException {
   protected:
    string invalid_name;

   public:
    explicit InvalidName(const char *invalid_name)
        : ArgumentException("Argument Error: PM Name Invalid ") {
        this->invalid_name = string(invalid_name);
    }

    virtual string what() const { return message + '(' + invalid_name + ')'; }
};

class InvalidId : public ArgumentException {
   protected:
    int invalid_id;

   public:
    explicit InvalidId(int invalid_id)
        : ArgumentException("Argument Error: PM ID Invalid ") {
        this->invalid_id = invalid_id;
    }

    virtual string what() const {
        return message + '(' + to_string(invalid_id) + ')';
    }
};

class InvalidType : public ArgumentException {
   protected:
    string invalid_type;

   public:
    explicit InvalidType(const char *invalid_type)
        : ArgumentException("Argument Error: PM Type Invalid ") {
        this->invalid_type = string(invalid_type);
    }

    virtual string what() const { return message + '(' + invalid_type + ')'; }
};

class IteratorException : public BasicException {
   public:
    explicit IteratorException() : BasicException("IteratorException") {}

    virtual string what() const { return message; }
};

class InvalidIterator : public IteratorException {
   public:
    explicit InvalidIterator() : IteratorException() {}

    virtual string what() const { return "Iterator Error: Invalid Iterator"; }
};

class InvalidDereference : public IteratorException {
   public:
    explicit InvalidDereference() : IteratorException() {}

    virtual string what() const { return "Iterator Error: Dereference Error"; }
};

struct Pokemon {
    char name[12];
    int id;
    int typ = 0;

    Pokemon() = default;

    Pokemon(const char *name, int id) {
        strcpy(this->name, name);
        this->id = id;
    }
};

class Pokedex {
   private:
    map<int, Pokemon> handbook;
    char *fileName;
    int num = 0;
    ifstream in;
    ofstream out;

   public:
    explicit Pokedex(const char *_fileName) {
        fileName = new char[strlen(_fileName) + 1];
        strcpy(fileName, _fileName);
        in.open(_fileName, ifstream::binary | ifstream::in | ifstream::out);
        if (!in) {
            out.open(_fileName);
            out.close();
        } else {
            in.seekg(0);
            in.read(reinterpret_cast<char *>(&num), sizeof(int));
            for (int i = 1; i <= num; i++) {
                Pokemon tmp;
                in.read(reinterpret_cast<char *>(&tmp), sizeof(Pokemon));
                handbook[tmp.id] = tmp;
            }
            in.close();
        }
    }

    ~Pokedex() {
        out.open(fileName, ofstream::binary | ofstream::trunc | ofstream::out);
        out.seekp(0);
        out.write(reinterpret_cast<char *>(&num), sizeof(int));
        for (auto iter : handbook)
            out.write(reinterpret_cast<char *>(&iter.second), sizeof(Pokemon));
        out.close();
        delete[] fileName;
    }

    bool pokeAdd(const char *name, int id, const char *types) {
        if (if_name_invalid(name)) throw InvalidName(name);
        string if_invalid_type = if_type_invalid(types);
        if (if_invalid_type != "-1") throw InvalidType(if_invalid_type.c_str());
        if (id <= 0) throw InvalidId(id);

        if (handbook.find(id) != handbook.end()) return false;
        handbook[id] = Pokemon(name, id);
        char tmp[80];
        strcpy(tmp, types);
        char *token = strtok(tmp, "#");
        while (token != nullptr) {
            for (int i = 0; i < 7; i++)
                if (strcmp(pokemon_type[i], token) == 0) {
                    handbook[id].typ |= (1 << i);
                    break;
                }
            token = strtok(nullptr, "#");
        }
        num++;
        return true;
    }

    bool pokeDel(int id) {
        if (id <= 0) throw InvalidId(id);

        if (handbook.find(id) == handbook.end()) return false;
        handbook.erase(id);
        num--;
        return true;
    }

    std::string pokeFind(int id) {
        if (id <= 0) throw InvalidId(id);

        if (handbook.find(id) == handbook.end())
            return "None";
        else
            return handbook[id].name;
    }

    std::string typeFind(const char *types) const {
        string if_invalid_type = if_type_invalid(types);
        if (if_invalid_type != "-1") throw InvalidType(if_invalid_type.c_str());

        int query_type = 0;
        char tmp[80];
        strcpy(tmp, types);
        char *token = strtok(tmp, "#");
        while (token != nullptr) {
            for (int i = 0; i < 7; i++)
                if (strcmp(pokemon_type[i], token) == 0) {
                    query_type |= 1 << i;
                    break;
                }
            token = strtok(nullptr, "#");
        }
        int cnt = 0;
        map<int, string> ans;
        for (auto iter : handbook) {
            if ((iter.second.typ & query_type) == query_type) {
                cnt++;
                ans[iter.first] = iter.second.name;
            }
        }
        if (!cnt)
            return "None";
        else {
            int cntt = 0;
            string return_val;
            return_val += to_string(cnt), return_val += '\n';
            for (auto iter : ans) {
                cntt++;
                return_val += iter.second;
                if (cntt != cnt) return_val += '\n';
            }
            return return_val;
        }
    }

    float attack(const char *type, int id) {
        if (id <= 0) throw InvalidId(id);
        string if_invalid_type = if_type_invalid(type);
        if (if_invalid_type != "-1") throw InvalidType(if_invalid_type.c_str());

        if (handbook.find(id) == handbook.end()) return -1;
        float ans = 1;
        for (int i = 0; i < 7; i++) {
            if (strcmp(pokemon_type[i], type) == 0) {
                for (int j = 0; j < 7; j++)
                    if (handbook[id].typ & (1 << j)) ans *= damage[i][j];
                return ans;
            }
        }
    }

    int catchTry() {
        int cnt = 1;
        queue<int> belonged;
        vector<int> not_belonged;
        belonged.push(handbook.begin()->first);
        for (auto iter = ++handbook.begin(); iter != handbook.end(); iter++)
            not_belonged.push_back(iter->first);
        while (!belonged.empty()) {
            int id = belonged.front();
            belonged.pop();
            for (int i = 0; i < 7; i++) {
                if (handbook[id].typ & (1 << i)) {
                    for (auto iter = not_belonged.begin();
                         iter != not_belonged.end();) {
                        if (this->attack(pokemon_type[i], *iter) >= 2) {
                            belonged.push(*iter);
                            not_belonged.erase(iter);
                            cnt++;
                            iter = not_belonged.begin();
                        } else
                            iter++;
                    }
                }
            }
        }
        return cnt;
    }

    struct iterator {
        map<int, Pokemon>::iterator iter;
        map<int, Pokemon> *mp;
        bool if_init = false;

        iterator() {}

        iterator(map<int, Pokemon> *mp, map<int, Pokemon>::iterator iter) {
            int flag = 1;
            for (auto it = mp->begin(); it != mp->end(); it++)
                if (it == iter) {
                    flag = 0;
                    break;
                }
            if (flag && iter != mp->end()) throw InvalidIterator();
            this->iter = iter;
            this->mp = mp;
            if_init = true;
        }

        iterator &operator++() {
            if (this->iter == mp->end() || !if_init) throw InvalidIterator();
            iter++;
            return *this;
        }

        iterator &operator--() {
            if (this->iter == mp->begin() || !if_init) throw InvalidIterator();
            iter--;
            return *this;
        }

        iterator operator++(int) {
            if (this->iter == mp->end() || !if_init) throw InvalidIterator();
            iterator tmp(mp, iter++);
            tmp.if_init = true;
            return tmp;
        }

        iterator operator--(int) {
            if (this->iter == mp->begin() || !if_init) throw InvalidIterator();
            iterator tmp(mp, iter--);
            tmp.if_init = true;
            return tmp;
        }

        iterator &operator=(const iterator &rhs) {
            if_init = rhs.if_init;
            this->iter = rhs.iter;
            this->mp = rhs.mp;
            return *this;
        }

        bool operator==(const iterator &rhs) const {
            return this->iter == rhs.iter;
        }

        bool operator!=(const iterator &rhs) const {
            return this->iter != rhs.iter;
        }

        Pokemon &operator*() const {
            if (!if_init || this->iter == mp->end()) throw InvalidDereference();
            return iter->second;
        }

        Pokemon *operator->() const {
            if (!if_init || this->iter == mp->end()) throw InvalidDereference();
            return &iter->second;
        }
    };

    iterator begin() {
        iterator tmp(&handbook, handbook.begin());
        tmp.if_init = true;
        return tmp;
    }

    iterator end() {
        iterator tmp(&handbook, handbook.end());
        tmp.if_init = true;
        return tmp;
    }
};