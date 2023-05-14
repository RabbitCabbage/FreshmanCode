//这道题感谢林田川同学一个多小时的耐心讲解，才让我这榆木脑袋学会了
#include<iostream>

using namespace std;
const int maxn = 5e5 + 5;
const int maxe = 1e6 + 8;
const int maxv = (1 << 12) + 5;
struct node {
    int first_edge_index = -1;
};
struct edge {
    int weight;
    int next_edge_index = -1;
    int to;
};
node node_list[maxn];
edge edge_list[maxe];

void add(int from, int to, int weight) {
    static int total = 0;
    edge_list[total].to = to;
    edge_list[total].weight = weight;
    edge_list[total].next_edge_index = node_list[from].first_edge_index;
    node_list[from].first_edge_index = total;
    ++total;
}

int depth[maxn];
int xor_root[maxn];
bool exist_root[2][maxv]{false};
int visited[maxn]{false};

void dfs(int cur, int fa, int weight) {
    visited[cur] = true;
    depth[cur] = depth[fa] + 1;
    xor_root[cur] = xor_root[fa] ^ weight;
    bool depth_parity = depth[cur] & 1;//如果是奇数，那么结果就是true，如果是偶数的话，结果就是false
    if (!exist_root[depth_parity][xor_root[cur]])exist_root[depth_parity][xor_root[cur]] = true;
//    cout << cur << " depth " << depth[cur] << " xor to root " << xor_root[cur] << endl;
    int next_edge_index = node_list[cur].first_edge_index;
    while (next_edge_index != -1) {
        if (!visited[edge_list[next_edge_index].to]) {
            dfs(edge_list[next_edge_index].to, cur, edge_list[next_edge_index].weight);
        }
        next_edge_index = edge_list[next_edge_index].next_edge_index;
    }
}//dfs准备好了深度数组，到根的异或路径数组，以及到根的异或路径存在性数组（分奇偶），
int exist[2][maxv]{false};

//下面准备两两之间的异或路径的存在数组，依然根据奇偶分开存储；
void prepare_exist_array() {
    for (int i = 0; i < (1 << 12); ++i) {
        for (int j = i; j < (1 << 12); ++j) {
            if (exist_root[0][i]) {
                if (exist_root[0][j])if (!exist[false][i ^ j])exist[false][i ^ j] = true;
                if (exist_root[1][j])if (!exist[true][i ^ j])exist[true][i ^ j] = true;
            }
            if (exist_root[1][i]) {
                if (exist_root[1][j])if (!exist[false][i ^ j])exist[false][i ^ j] = true;
                if (exist_root[0][j])if (!exist[true][i ^ j])exist[true][i ^ j] = true;
            }
        }
    }
}

//根据exist数组建立字典树
int trie_false[maxv * 32][2];//01字典树,路径间隔是偶数的字典树
int total_false = 1;
int trie_true[maxv * 32][2];//10字典树，路径间隔是奇数的字典树
int total_true = 1;
int value_false[maxv * 32];
int value_true[maxv * 32];

void insert(int number, int trie_tree[maxv * 32][2], int &total, int value[maxv * 32]) {
    int u = 0;
    for (int i = 31; i >= 0; --i)//从高位到低位的取二进制数字
    {
        int v = (number >> i) & 1;
        if (trie_tree[u][v])u = trie_tree[u][v];
        else {
            trie_tree[total][0] = trie_tree[total][1] = 0;
            trie_tree[u][v] = total;
            u = trie_tree[u][v];
            value[u] = -1;
            total++;
        }
    }
    value[u] = number;//记下这个数字，它结束的地方是u；
}

void build() {
    trie_false[0][0] = trie_false[0][1] = 0;
    trie_true[0][0] = trie_true[0][1] = 0;
    for (int i = 0; i < (1 << 12); ++i) {
        if (exist[0][i]) {
            insert(i, trie_false, total_false, value_false);
        }
        if (exist[1][i]) {
            insert(i, trie_true, total_true, value_true);
        }
    }
}

//查询在某棵树中，与number异或的最大值，返回的是最大值
int find_max(int trie_tree[maxv * 32][2], int number, const int value[maxv * 32]) {
    int u = 0;
    for (int i = 31; i >= 0; --i) {
        int v = (number >> i) & 1;
//        if (trie_tree[u][v] ^ v)u = trie_tree[u][v];
        bool branch = v ^ 1;
        if (trie_tree[u][branch])u = trie_tree[u][branch];
        else u = trie_tree[u][!branch];
    }
    return number ^ value[u];
}

int n, m;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        add(a, b, w);
        add(b, a, w);
    }
    depth[0] = 0;
    xor_root[0] = 0;
    dfs(1, 0, 0);
//    cout << "exist to root" << endl;
//    for (int i = 0; i < 10; ++i)cout << exist_root[0][i] << " ";
//    cout << endl;
//    for (int i = 0; i < 10; ++i)cout << exist_root[1][i] << " ";
//    cout << endl;
    prepare_exist_array();
//    cout << "exist to each other" << endl;
//    for (int i = 0; i < 10; ++i)cout << exist[0][i] << " ";
//    cout << endl;
//    for (int i = 0; i < 10; ++i)cout << exist[1][i] << " ";
//    cout << endl;
    build();
    int V = 0;
    for (int i = 0; i < m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int s, t;
            scanf("%d %d", &s, &t);
            int depth_parity = (depth[s] + depth[t]) & 1;
            int xor_sum_st = xor_root[s] ^ xor_root[t];
            //如果说他俩的深度之和为奇数
            if (depth_parity) {
                //去奇数树里面找，不用异或V
                int result1 = find_max(trie_true, xor_sum_st, value_true);
                //或者取偶数树里找，需要异或上V
                int result2 = find_max(trie_false, xor_sum_st ^ V, value_false);
                printf("%d%c", max(result1, result2), '\n');
            } else {//他俩的深度值和是偶数
                //去奇数树里面找，并且还得异或上V
                int result1 = find_max(trie_true, xor_sum_st ^ V, value_true);
                //或者去偶数找，不用异或；
                int result2 = find_max(trie_false, xor_sum_st, value_false);
                printf("%d%c", max(result1, result2), '\n');
            }
        } else {
            int v;
            scanf("%d", &v);
            V ^= v;
        }
    }
    return 0;
}