//
// Created by lu'ren'jia'd's on 2021/12/2.
//


#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>
#include <string>
#include <set>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    fstream file;
    fstream reuse;
    string file_name;
    int sizeofT = sizeof(T);
    std::set<int> vacant;
    string vacant_record;
public:
    MemoryRiver() = default;


    MemoryRiver(const string &file_name) : file_name(file_name) {
    }

    void initialise(const string &FN = "") {
        if (!FN.empty()) file_name = FN;//为文件命名
        file.open(file_name ,std::ios::out);//打开文件写入
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)//初始化在文件里全部写入0
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        vacant.clear();

        int vacant_location;
        vacant_record = "vacant_record" + file_name;
        reuse.open(vacant_record , std::ios::in);
        if (reuse) {
            reuse.read(reinterpret_cast<char *>(&vacant_location), sizeof(int));
            while (!reuse.eof()) {
                vacant.insert(vacant_location);
                reuse.read(reinterpret_cast<char *>(&vacant_location), sizeof(int));
            }
        }
        reuse.close();
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name);
        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name);
        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        /* your code here */
        int location;
        if (vacant.empty()) {
            file.open(file_name);
            file.seekp(std::ios::end);
            location = file.tellp();
        } else {
            file.open(file_name);
            location = *(vacant.begin());
            file.seekp(location);
            vacant.erase(location);
        }
        file.write(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
        return location;//返回是第几个字节
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        /* your code here */
        file.open(file_name);
        file.seekp(index, std::ios::beg);
        file.write(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        /* your code here */
        file.open(file_name);
        file.seekg(index, std::ios::beg);
        file.read(reinterpret_cast<char *>(&t), sizeof(T));
        file.close();
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index) {
        /* your code here */
        vacant.insert(index);
    }

    ~MemoryRiver() {
        reuse.open(vacant_record, std::ios::out);
        for (auto ptr = vacant.begin(); ptr != vacant.end(); ++ptr) {
            int location = *ptr;
            reuse.write(reinterpret_cast<char *>(&location), sizeof(int));
        }
        reuse.close();
    }
};


#endif //BPT_MEMORYRIVER_HPP
