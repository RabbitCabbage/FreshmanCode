#include <iostream>

using namespace std;
const int maxn = 1e5 + 5;
//const long long maxl = 2e9 + 5;
//long long tree[maxl];
//建这么大一个树你怕怕不是个傻子，要用离散化
//离散化的思想是先把所有数据都读进来，统计一下都有哪些点被他问到了

struct node {
    bool tag = false;//tag 表示的是这一点下面的子树是否需要修改
    long long h_ = 0;//维护的是这一个区间的最大高度
    //描述的是从index到index+1一段的高度
};
node tree[maxn << 4];
//我们来计算一下，maxn个询问，每一次询问涉及两个点，然后又应该开四倍大小，正好是八倍
//维护一个线段树，里面是每一个横坐标对应的最大高度，这个横坐标是离散化处理过后的统计好的
//也就是说这颗线段树是建立在已经压缩之后的record数组之上的
long long l[maxn];
long long r[maxn];
long long h[maxn];//这三个数组作为询问的记录
long long record[maxn << 2];//这个数组是离线的离散化，等下要sort 并且unique，最后用它建立一颗树
long long ans_height[maxn << 2];
long long ans_index[maxn << 2];
int n;

void sort(long long array[], int left, int right) {
    if (left >= right)return;
    long long pivot = array[left];
    int start = left, end = right;
    while (left < right) {
        //最后退出循环的时候我们希望是停留在一个比pivot更小的元素上，因此要先让right--；
        while (array[right] >= pivot && right > left)right--;
        while (array[left] <= pivot && right > left)left++;
        if (left < right) {
            long long tmp = array[right];
            array[right] = array[left];
            array[left] = tmp;
        }
    }
    array[start] = array[left];
    array[left] = pivot;
    sort(array, start, left - 1);
    sort(array, left + 1, end);
}

void unique(long long array[], int left, int &right) {
    int j = left;
    array[j] = array[left];
    for (int i = left; i <= right; ++i) {
        while (array[i] == array[j])++i;
        array[++j] = array[i];
    }
    right = j;
}

void push_up(int p) {
    //父节点应该记下自己的左右儿子里面的高度最小值
    //这样当有高度更新的时候，要去巩固薄弱的部分
    tree[p].h_ = min(tree[p << 1].h_, tree[p << 1 | 1].h_);
}

void push_down(int p, int left, int right) {
    if (left == right)return;
    if (!tree[p].tag)return;
    tree[p].tag = false;
    if (tree[p].h_ > tree[p << 1].h_) {
        tree[p << 1].h_ = tree[p].h_;
        tree[p << 1].tag = true;
    }
    if (tree[p].h_ > tree[p << 1 | 1].h_) {
        tree[p << 1 | 1].h_ = tree[p].h_;
        tree[p << 1 | 1].tag = true;
    }
}

void modify(long long ml, long long mr, int p, int left, int right, long long height) {
    if (ml <= record[left] && mr >= record[right]) {
        if (height > tree[p].h_) {
            tree[p].h_ = height;
            tree[p].tag = true;
        }
        return;
    }
    push_down(p, left, right);
    int mid = (left + right) >> 1;
    if (ml <= record[mid])modify(ml, mr, p << 1, left, mid, height);
    if (mr >= record[mid + 1])modify(ml, mr, p << 1 | 1, mid + 1, right, height);
    push_up(p);
}

long long query(long long pos, int p, int left, int right) {
    if (left == right) {
        return tree[p].h_;
    }
    push_down(p, left, right);
    int mid = (left + right) >> 1;
    if (record[mid] >= pos)return query(pos, p << 1, left, mid);
    else return query(pos, p << 1 | 1, mid + 1, right);
}

int main() {
    int count = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld %lld", &h[i], &l[i], &r[i]);
        record[3 * i - 2] = l[i];
        record[3 * i - 1] = r[i];
        record[3 * i] = r[i] - 1;
        count += 3;
    }
    sort(record, 1, count);
    unique(record, 1, count);
    for (int i = 1; i <= n; ++i) {
        modify(l[i], r[i] - 1, 1, 1, count, h[i]);
//        for (int j = 1; j <= count; ++j) cout << record[j] << " " << query(record[j], 1, 1, count) << endl;
//        cout << endl;
    }
    long long last_height = 0;
    int number = 0;
    int j = 0;
    for (int i = 1; i <= count; ++i) {
        long long tmp = query(record[i], 1, 1, count);
        if (tmp != last_height) {
            ans_index[++j] = record[i];
            ans_height[j] = last_height;
            ans_index[++j] = record[i];
            ans_height[j] = tmp;
            number += 2;
            last_height = tmp;
        }
    }
    cout << number << endl;
    for (int i = 1; i <= j; ++i) cout << ans_index[i] << " " << ans_height[i] << endl;
    return 0;
}