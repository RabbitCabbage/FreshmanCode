#include<iostream>
#include<cstring>

using namespace std;
const int mod1 = 1e7 + 7;
const int seed1 = 31;

long long hash1(const char *s, int len) {
    long long res = 0;
    for (int i = 0; i < len; ++i) {
        res *= seed1;
        if (res < 0)res += mod1;
        res %= mod1;
        res += s[i] - 'a';
    }
    return res;
}


const int maxn = 1e3 + 5;
const int maxm = 1e5 + 5;
int m, n;
bool to_recite[mod1 + 5];
long long article[maxm];
int appear[mod1 + 5]{0};

int main() {
    scanf("%d\n", &n);
    char tmp[11];
    for (int i = 0; i < n; ++i) {
        scanf("%s", tmp);
//        cout << tmp << " " << hash1(tmp, strlen(tmp)) << endl;
        to_recite[hash1(tmp, strlen(tmp))] = true;
    }
    scanf("%d", &m);
    int count = 0;
    for (int i = 0; i < m; ++i) {
        scanf("%s", tmp);
        article[i] = hash1(tmp, strlen(tmp));//记下article里面出现的数字；
//        cout << tmp << " " << article[i] << endl;
        if (to_recite[article[i]]) {
            appear[article[i]] += 1;
            if (appear[article[i]] == 1)++count;
        }
    }
    //在这篇文章中出现的总共有count个
//    cout << "count = " << count << endl;
    if (count == 0) {
        printf("%d\n%d\n", 0, 0);
        return 0;
    }
    memset(appear, 0, sizeof(appear));
    int left = 0, right = 0, total = 0, min_len = 0;
    while (total < count && right < m) {
        if (to_recite[article[right]]) {
            if (appear[article[right]] == 0)total++;
            appear[article[right]]++;
        }
        right++;
    }
    right--;
    min_len = right + 1;
//    cout << "now the left bound is in the " << left << "  the right bound is in the " << right << " and the length is "
//         << min_len << endl;
    while (1) {
        while (total >= count && left < right) {
            if (to_recite[article[left]]) {
                appear[article[left]]--;
                if (appear[article[left]] == 0) {
                    total--;
                }
            }
            left++;
            if (total >= count) {
                if (right - left + 1 < min_len)min_len = right - left + 1;
//                cout << "LEFT CIRCLE " << "now the left bound is in the " << left
//                     << "  the right bound is in the " << right
//                     << " and the length is " << min_len << endl;
            } else break;
        }
        if (right == m)break;
        while (total < count && right < m) {
            right++;
            if (to_recite[article[right]]) {
                if (appear[article[right]] == 0)total++;
                appear[article[right]]++;
            }
        }
        if (total >= count) {
            if (right - left + 1 < min_len)min_len = right - left + 1;
//            cout << "RIGHT CIRCLE " << "now the left bound is in the " << left <<
//                 "  the right bound is in the " << right
//                 << " and the length is " << min_len << endl;
        }
    }
    printf("%d\n%d\n", count, min_len);
    return 0;
}

//const int mod2 = 19260817;
//const int seed2 = 83;


//long long hash2(const char *s, int len) {
//    long long res = 0;
//    for (int i = 0; i < len; ++i) {
//        res *= seed2;
//        res %= mod2;
//        res += s[i] - 'a';
//    }
//    return res;
//}

//bool equal(const char *s1, const char *s2) {
//    unsigned long l1 = strlen(s1), l2 = strlen(s2);
//    if (l1 != l2)return false;
//    long long s11 = hash1(s1, l1), s21 = hash1(s2, l2);
//    if (s11 != s21)return false;
//    long long s12 = hash2(s1, l1), s22 = hash2(s2, l2);
//    return s12 = s22;
//}
