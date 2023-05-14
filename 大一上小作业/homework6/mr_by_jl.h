//
// Created by lu'ren'jia'd's on 2021/12/2.
//

#ifndef UNTITLED4_MR_BY_JL_H
#define UNTITLED4_MR_BY_JL_H

#include <fstream>
#include<set>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    fstream file;
    fstream reuse;
    string file_name;
    string reuse_name;
    std::set<int> reuseIndex;
    int sizeofT = sizeof(T);//计算内存大小
    int sizeofInt = sizeof(int);
public:
    MemoryRiver() = default;//显式构造无参数构造函数

    MemoryRiver(const string& file_name0) {
        file_name = file_name0;
        reuse_name = file_name0 +"reuse";
    }
    ~MemoryRiver(){
        reuse.open(reuse_name);
        for(auto iter = reuseIndex.begin(); iter != reuseIndex.end(); ++iter){
            int index = *iter;
            reuse.write(reinterpret_cast<char *>(&index),sizeofInt);
        }
        reuse.close();
    }
    void initialise(string FN = "") {
        if (FN != ""){
            file_name = FN;
            reuse_name = file_name + "reuse";
        }
        file.open(file_name, std::ios::out);
//        reuse.open(file_name + "reuse");
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        reuse.open(reuse_name);
        if(reuse){
            reuseIndex.clear();
            while(!reuse.eof()){
                int index;
                reuse.read(reinterpret_cast<char *>(&index),sizeofInt);
                reuseIndex.insert(index);
            }
        }
        else reuseIndex.clear();
        reuse.close();
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name);
        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp),sizeof(int));
        file.close();
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name);
        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp),sizeof(int));
        file.close();
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        //有reuse块
        if(reuseIndex.size()){
            int index;
            auto iter = reuseIndex.begin();
            index = *iter;
            file.open(file_name);
            file.seekp(index);
            file.write(reinterpret_cast<char *>(&t), sizeofT);
            file.close();
            reuseIndex.erase(iter);
            return index;
        }
            //无reuse块
        else {
            int index, index0;
            get_info(index, 1);
            index0 = index;
            if (!index) {
                index += info_len * sizeof(int);
                index0 = index;
                file.open(file_name);
                file.seekp(index);
                file.write(reinterpret_cast<char *>(&t), sizeofT);
                file.close();
                index += sizeofT;
                write_info(index, 1);
            } else {
                file.open(file_name);
                file.seekp(index);
                file.write(reinterpret_cast<char *>(&t), sizeofT);
                file.close();
                index += sizeofT;
                write_info(index, 1);
            }
            return index0;
        }
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        file.open(file_name);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        file.open(file_name);
        file.seekg(index);
        file.read(reinterpret_cast<char *> (&t),sizeofT);
        file.close();
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index) {
        reuseIndex.insert(index);
    }
};


#endif //UNTITLED4_MR_BY_JL_H
