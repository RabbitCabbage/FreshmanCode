#include <iostream>

using namespace std;
enum calc {
    add, subtract, exclusive, leftb, rightb, nullop, protected_xor
};
enum type {
    num, ope, null
};

struct node {
    type t;
    int number = 0;
    calc op = nullop;
    node *left = nullptr;
    node *right = nullptr;

    node(type ty, int res) {
        if (ty == num) {
            t = num;
            number = res;
        } else {
            t = ope;
            op = (calc) res;
        }
    }
};

const int maxl = 4e6 + 5;
char expression[maxl];
static int index = 0;

type get_token(int &result) {
    char judge = expression[index++];
    if (judge == '\0')return null;
    result = 0;
    if (judge - '0' >= 0 && judge - '0' <= 9) {
        result = result * 10 + judge - '0';
        judge = expression[index++];;
        while (judge - '0' >= 0 && judge - '0' <= 9) {
            result = result * 10 + judge - '0';
            judge = expression[index++];;
        }
        index--;
        return num;
    } else {
        if (judge == '+')result = add;
        else if (judge == '-')result = subtract;
        else if (judge == '^')result = exclusive;
        else if (judge == '(')result = leftb;
        else result = rightb;
        return ope;
    }
}


//根节点的右孩子，或者右孩子的右孩子，总得有一个是空的
void create(node *&root) {
    while (1) {
        int result;
        type t = get_token(result);
        if (t == null)return;//表达式到头了，不用再往下读了；
        else if (t == num) {
            node *subtree = new node(num, result);//新new了一个节点出来；
            if (root == nullptr)root = subtree;
            else if (root->right == nullptr)root->right = subtree;
            else root->right->right = subtree;
        } else {
            calc op = (calc) result;//这是运算符的种类
            if (op == leftb) {
                node *subtree = nullptr;
                create(subtree);
                if (root == nullptr)root = subtree;
                else if (root->right == nullptr)root->right = subtree;
                else root->right->right = subtree;
            } else if (op == rightb) {
                if (root->op == exclusive)root->op = protected_xor;
                return;
            } else if (op == add || op == subtract) {
                if (root->op != exclusive) {
                    node *tmp = root;
                    root = new node(ope, op);
                    root->left = tmp;
                } else {
                    node *tmp = root->right;
                    root->right = new node(ope, op);
                    root->right->left = tmp;
                }
            } else {
                node *tmp = root;
                root = new node(ope, op);
                root->left = tmp;
            }
        }
    }
}

int result_test(node *tree) {
    if (tree->t == num)return tree->number;
    else {
        if (tree->op == add) {
            int l = result_test(tree->left), r = result_test(tree->right);
            cout << l << " + " << r << " = " << l + r << endl;
            return l + r;
        } else if (tree->op == subtract) {
            int l = result_test(tree->left), r = result_test(tree->right);
            cout << l << " - " << r << " = " << l - r << endl;
            return l - r;
        } else {
            int l = result_test(tree->left), r = result_test(tree->right);
            cout << l << " ^ " << r << " = " << (l ^ r) << endl;
            return l ^ r;
        }
    }
}

int result(node *tree) {
    if (tree->t == num)return tree->number;
    else {
        if (tree->op == add)return result(tree->left) + result(tree->right);
        else if (tree->op == subtract)return result(tree->left) - result(tree->right);
        else return result(tree->left) ^ result(tree->right);
    }
}

int main() {
    cin >> expression;
    node *root = nullptr;
    create(root);
    cout << result(root) << endl;
    return 0;
}

//(8^3)+3^4+(7^2)^3-1
//((3+(318+3^8000+51^8261)+(9+3-5))+100)-1
//(2343^3048)+3453^23434+(2345^32)^34535-892