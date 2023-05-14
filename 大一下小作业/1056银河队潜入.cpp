//
// Created by lu'ren'jia'd's on 2022/5/14.
//

#include<iostream>
#include<cstring>

using namespace std;

void merge(long long array[], int l, int r, int mid) {
    //把两段排好序，一段l~mid 另一段mid+1~r
    long long tmp[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (array[i] > array[j])tmp[k++] = array[j++];
        else tmp[k++] = array[i++];
    }
    //k指向的是要放进去的空位子，ij指向要放的元素
    if (i == mid + 1)while (j <= r)tmp[k++] = array[j++];
    if (j == r + 1)while (i <= mid)tmp[k++] = array[i++];
    for (int p = 0, q = l; p < r - l + 1; p++, q++)
        array[q] = tmp[p];
}

void sort(long long array[], int start, int end) {
    if (start >= end)return;
    int mid = (start + end) >> 1;
    sort(array, start, mid);
    sort(array, mid + 1, end);
    merge(array, start, end, mid);
}

void unique(long long array[], int start, int &end) {
    int i = start, j = start;
    array[j] = array[i];
    while (i <= end) {
        while (i <= end && array[i] == array[j])++i;
        if (i <= end)array[++j] = array[i];
    }
    end = j;
}

int discretize(long long x, const long long array[], int start, int end) {
    int mid;
    int l = start, r = end;
    while (1) {
        mid = (l + r) >> 1;
        if (array[mid] == x)return mid;
        else if (array[mid] > x)r = mid - 1;
        else l = mid + 1;
    }
}

const int maxn = 3e5 + 5;

//记录每一个值他的链表的尾index；
int chain_rear[maxn];
long long record[maxn];
int count;//记录离散化总共有多少数据

struct Node {
    int pre, nxt;//前一个后一个value相同的节点都是哪个
    long long value;
    //开始时longlong，离散化之后就是int了，用离散化之后的值来做
} node[maxn];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &node[i].value);
        record[i] = node[i].value;
    }
    count = n;
    sort(record, 1, count);
    unique(record, 1, count);
    memset(chain_rear, 0, sizeof(chain_rear));//最初表尾都是空的
    for (int i = 1; i <= n; ++i) {
        node[i].value = discretize(node[i].value, record, 1, count);
        node[i].pre = chain_rear[node[i].value];//接到这个链上
        node[chain_rear[node[i].value]].nxt = i;
        chain_rear[node[i].value] = i;//更新链尾
    }
    int queue[maxn];
    bool visited[maxn];
    int dist[maxn];
    int distance = 0;
    memset(visited, false, sizeof(visited));
    memset(dist, 0, sizeof(dist));
    int head = -1, rear = -1;
    queue[++rear] = 1;//第一个节点进队列
    visited[1] = true;
    //bfs找距离
    while (head != rear) {
        int top = queue[++head];//头部元素出队
        //cout << top << " dequeued" << endl;
        //下面应该找到所有和top挨边的node，把他们的dist设置为distance+1
        //并且它们都要入队，等着下一波的bfs
        distance = dist[top] + 1;
        if (top - 1 != 0 && !visited[top - 1]) {
            dist[top - 1] = distance;
            if (top - 1 == n) {
                printf("%d\n", dist[n]);
                return 0;
            }
            visited[top - 1] = true;
            queue[++rear] = top - 1;
            //cout << top - 1 << " enqueued" << endl;
        }
        if (top + 1 != n + 1 && !visited[top + 1]) {
            dist[top + 1] = distance;
            if (top + 1 == n) {
                printf("%d\n", dist[n]);
                return 0;
            }
            visited[top + 1] = true;
            queue[++rear] = top + 1;
            //cout << top + 1 << " enqueued" << endl;
        }
        for (int i = node[top].pre; i; i = node[i].pre) {
            if (!visited[i]) {
                dist[i] = distance;
                if (i == n) {
                    printf("%d\n", dist[n]);
                    return 0;
                }
                visited[i] = true;
                queue[++rear] = i;
                //cout << i << " enqueued" << endl;
            }
        }
        for (int i = node[top].nxt; i; i = node[i].nxt) {
            if (!visited[i]) {
                dist[i] = distance;
                if (i == n) {
                    printf("%d\n", dist[n]);
                    return 0;
                }
                visited[i] = true;
                queue[++rear] = i;
                //cout << i << " enqueued" << endl;
            }
        }
        //把top从连表里删除
        node[node[top].pre].nxt = node[top].nxt;
        node[node[top].nxt].pre = node[top].pre;
    }
    printf("%d\n", dist[n]);
    return 0;
}

#include<iostream>
#include<cstring>

using namespace std;

void merge(long long array[], int l, int r, int mid) {
    //把两段排好序，一段l~mid 另一段mid+1~r
    long long tmp[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (array[i] > array[j])tmp[k++] = array[j++];
        else tmp[k++] = array[i++];
    }
    //k指向的是要放进去的空位子，ij指向要放的元素
    if (i == mid + 1)while (j <= r)tmp[k++] = array[j++];
    if (j == r + 1)while (i <= mid)tmp[k++] = array[i++];
    for (int p = 0, q = l; p < r - l + 1; p++, q++)
        array[q] = tmp[p];
}

void sort(long long array[], int start, int end) {
    if (start >= end)return;
    int mid = (start + end) >> 1;
    sort(array, start, mid);
    sort(array, mid + 1, end);
    merge(array, start, end, mid);
}

void unique(long long array[], int start, int &end) {
    int i = start, j = start;
    array[j] = array[i];
    while (i <= end) {
        while (i <= end && array[i] == array[j])++i;
        if (i <= end)array[++j] = array[i];
    }
    end = j;
}

int discretize(long long x, const long long array[], int start, int end) {
    int mid;
    int l = start, r = end;
    while (1) {
        mid = (l + r) >> 1;
        if (array[mid] == x)return mid;
        else if (array[mid] > x)r = mid - 1;
        else l = mid + 1;
    }
}

const int maxn = 3e5 + 5;
const int inf = maxn << 1;

//记录每一个值他的链表的尾index；
long long record[maxn];
long long value[maxn];
int count;//记录离散化总共有多少数据
struct edge {
    int to, next;
    int value;
} e[maxn << 2];
int first[maxn << 1];
int total = 0;

void add_edge(int from, int to, int val) {
    total++;
    e[total].to = to;
    e[total].next = first[from];
    e[total].value = val;
    first[from] = total;
}

int n;

int main() {
    memset(first, 0, sizeof(first));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &value[i]);
        record[i] = value[i];
    }
    count = n;
    sort(record, 1, count);
    unique(record, 1, count);
    for (int i = 1; i <= n; ++i) {
        int tmp = discretize(value[i], record, 1, count) + n;
        add_edge(i, tmp, 1);
        add_edge(tmp, i, 0);
//        cout << "add edge " << value[i] << " " << i << endl;
//        cout << "add edge " << i << " " << value[i] << endl;
    }
    int queue[maxn << 4];
    bool visited[maxn << 1];
    int dist[maxn << 1];
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < (n << 1); ++i)dist[i] = inf;
    dist[1] = 0;
    int head = -1, rear = -1;
    queue[++rear] = 1;//第一个节点进队列
    visited[1] = true;
    //bfs找距离
    while (head != rear) {
        int top = queue[++head];//头部元素出队
        visited[top] = false;//标记不在队里
//        cout << top << " dequeued" << endl;
        //下面应该找到所有和top挨边的node，把他们的dist设置为distance+1
        //并且它们都要入队，等着下一波的bfs
        if (top <= n) {
            if (top - 1 > 0 && dist[top - 1] > dist[top] + 1) {
                dist[top - 1] = dist[top] + 1;
                if (!visited[top - 1]) {
                    visited[top - 1] = true;
                    queue[++rear] = top - 1;
                }
//                cout << top - 1 << " enqueued  ";
//                cout << dist[top]+1 << endl;
            }
            if (top + 1 <= n && dist[top + 1] > dist[top] + 1) {
                dist[top + 1] = dist[top] + 1;
                if (!visited[top + 1]) {
                    visited[top + 1] = true;
                    queue[++rear] = top + 1;
                }
//                cout << top + 1 << " enqueued  ";
//                cout << distance << endl;
            }
        }
        for (int i = first[top]; i; i = e[i].next) {
            if (dist[e[i].to] > dist[top] + e[i].value) {
                dist[e[i].to] = dist[top] + e[i].value;
                if (!visited[e[i].to]) {
                    visited[e[i].to] = true;
                    queue[++rear] = e[i].to;
                }
//                cout << e[i].to << " enqueued  ";
//                cout << distance << endl;
            }
        }
    }
    printf("%d\n", dist[n]);
    return 0;
}