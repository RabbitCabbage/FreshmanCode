#include <iostream>

using namespace std;

class priority_queue {
    int *data;
    int current_size;

    //filter down to find the proper location;
    void perlocate(int hole) {
        while (1) {
            int child = hole * 2;
            if (child > current_size)break;
            else {
                if (child + 1 <= current_size && data[child + 1] < data[child])child = child + 1;
                if (data[child] < data[hole]) {
                    int tmp = data[hole];
                    data[hole] = data[child];
                    data[child] = tmp;
                    hole = child;
                } else break;
            }
        }
    }

public:
    //the first unit of the data should be empty;
    priority_queue(int *array, int size) {
        current_size = size;
        data = new int[current_size + 1];
        for (int i = 1; i <= size; ++i)data[i] = array[i - 1];
        for (int i = current_size / 2; i > 0; --i)perlocate(i);
    }

    ~priority_queue() { delete[]data; }

    void push(int a) {
        current_size++;
        data[current_size] = a;
        int hole = current_size;
        while (1) {
            int parent = hole / 2;
            if (parent == 0)break;
            else {
                if (data[parent] > data[hole]) {
                    int tmp = data[hole];
                    data[hole] = data[parent];
                    data[parent] = tmp;
                    hole = parent;
                } else break;
            }
        }
    }

    void pop() {
        data[1] = data[current_size];
        current_size--;
        perlocate(1);
    }

    int top() {
        return data[1];
    }

    bool empty() {
        return current_size == 0;
    }
};

int n, m, N;

int main() {
    cin >> n >> m;
    if ((n - 1) % (m - 1) != 0) {
        int extra0 = (m - 1) - (n - 1) % (m - 1);//we need so many zeros for the tree
        N = n + extra0;
    } else N = n;
    int array[N], i;// the array of the weight of the node.
    for (i = 0; i < n; ++i)cin >> array[i];
    for (; i < N; ++i)array[i] = 0;
    priority_queue pq(array, N);//build the tree for priority queue;
    long long answer = 0;
    while (1) {
        int inner_node = pq.top();
//        cout << "qwq " << pq.top() << endl;
        pq.pop();
        if (pq.empty()) {
            // the last root node has been calculated and the circle is ended;
//            answer += inner_node;
            break;
        } else {
            for (int j = 0; j < m - 1; ++j) {
                inner_node += pq.top();
//                cout << "qwq " << pq.top() << endl;
                pq.pop();
            }
            pq.push(inner_node);
            answer += inner_node;
        }
    }
    cout << answer << endl;
    return 0;
}