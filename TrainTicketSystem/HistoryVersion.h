//
// Created by lu'ren'jia'd's on 2022/5/2.
//

#ifndef UNTITLED2_BPLUSTREE_H
#define UNTITLED2_BPLUSTREE_H

#include "MemoryRiver.h"
#include "FileException.h"
#include <functional>
#include <cstring>

namespace ds {
    template<typename Key, typename Info, const int max_key_num = 5, const int max_rcd_num = 5, class KeyCompare = std::less<Key>>

    class BPlusTree {
    public:
        struct Node {
            int location = -1;
            bool isleaf = true;//标记是不是叶节点
            int children_num = 0;
            int children[max_key_num];
            Key keys[max_key_num];

            void operator()(Node lhs, const Node &rhs) {
                lhs.location = rhs.location;
                lhs.isleaf = rhs.isleaf;
                lhs.children_num = rhs.children_num;
                for (int i = 0; i < rhs.children_num; ++i)lhs.children[i] = rhs.children[i];
                for (int i = 0; i < rhs.children_num; ++i)lhs.keys[i] = rhs.keys[i];
            }
        };


        struct Block {
            int next = -1, prior = -1;
            int location = -1;
            int size = 0;
            Key keys[max_rcd_num];
            Info record[max_rcd_num];
        };

    private:
        KeyCompare cmp;
        MemoryRiver<Node> *index_memory;
        MemoryRiver<Block> *record_memory;
        MemoryRiver<int> *int_memory;
        char *index_file;
        char *record_file;
        Node root;
        int root_index = -1;
        int scale;

        //this is a tool function to do binary search
        //find the first key that is smaller than or equal to the wanted
        //if every key is bigger than this one return -1;
//        void PeekNode(const Node &node) {
//            std::cout << "node location ";
//            std::cout << node.location << std::endl;
//            for (int i = 0; i < node.children_num; ++i) std::cout << node.keys << ' ';
//            std::cout << std::endl;
//        }


        int BinarySearchLess(Key array[], int size, const Key &key)

        //find the index of the key in the block
        // if don't find return -1;
        int BinarySearch(const Block &block, const Key &key)

        //return the index in the record file and the info struct
        // the first int is the index of the block and the second int is the index of the record in the block;
        //the index can be used to modify the struct infomation
        std::pair<std::pair<int, int>, Info> RecursionFind(const Key &key)

        //split the cur into new node and the info about new node are recorded by reference
        void Split(Node &cur, Node &new_node, int &new_node_loc, int &splited_child_index, int num)

        void AddChild(Node &cur, const Key &first_key, const Key &added_first_key, int added_loc,
                      int num)

        //to find the key in the current node;
        //the bool value it returns presents whether it needs to have changes as a father
        //the reference of the new_node is the node that should be added;
        bool
        RecursionInsert(Node &cur, const Key &key, const Info &info, bool &success, int &splited_child_index,
                        Node &new_node,
                        int &new_node_loc)

        //check if the problem can be dealt with in the cur and his brother
        //if the child can be borrowed return true and the node doesn't merge
        //else return false then merge the children
        bool BorrowChild(Node &cur, int num, Node &parent, int &brother_to_merge_index, Node &brother_to_merge)

        //merge rear into the front and then the rear will be deleted;
        void MergeBrothers(Node &front, Node rear)

        void MergeBlocks(Block &front, Block &rear, int front_loc)

        //merged index is the child that remains
        //we suppose that always remain the child that close to the front, merge the rare one
        bool RecursionRemove(Node &cur, const Key &key, bool &success, Node parent)

    public:

        //B+树的构造函数,由一个文件构造
        BPlusTree(
                const char *index_file_name,
                const char *record_file_name)

        //B+树的析构函数
        ~BPlusTree()

        //插入一个元素，参数是插入元素的键值和记录的详细信息，返回插入是否成功
        //如果说这个元素本来存在，插入失败返回false
        bool Insert(const Key &key, const Info &info)

        //删除一个元素，参数是要删除元素的键值，返回是否删除成功，
        //如果这个元素在B+树中不存在就删除失败
        bool Remove(const Key &key)

        //查询一个元素，参数是要查询元素的键值
        //返回值是一个pair，bool代表有没有找到
        //如果找到这个元素存在，返回true，同时返回记录信息的具体值
        //如果没有找到，返回false，这时的返回struct是随机值，不应该被访问
        std::pair<bool, std::pair<Key, Info>> Find(const Key &key)

        //修改一个元素，参数是要修改元素的键值和修改之后的信息
        //返回一个bool，修改成功返回true，否则返回false
        //如果这个要修改的元素在B+树中不存在就会返回false
        bool Modify(const Key &key, const Info &new_info)

        //清空B+树的有关文件
        void Clear()

        //返回现在总共有多少条记录
        int GetSize() {
            return scale;
        }

    private:
        int BinarySearchBigger(Key array[], int size, const Key &key)

        //要找到的key就是wanted，找到之后把这几个引用传递值修改了，
        //分别是：这个元素所在的block，这个元素所在的leaf_node，这个元素的key，info，
        //还有在这个叶节点之中是第几个block，在这个block中是第几条记录
        bool
        RecursionFindBigger(Node cur, const Key &wanted, Block &block, Node &leaf, Key &key,
                            Info &info, int &node_index, int &block_index, bool &need_brother)

    public:
        class iterator

        //返回指向比key更大的
        iterator FindBigger(const Key &wanted)

        void Traverse()
    };

}
#endif //UNTITLED2_BPLUSTREE_H
