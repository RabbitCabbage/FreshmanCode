#include<string>
#include<iostream>

using namespace std;

int find(const string &str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] <= '9' && str[i] >= '0' && str[i + 1] <= 'Z' && str[i + 1] >= 'A')return i + 1;
    }
    return str.length();
}//找到最里面的要重复的字符串开头处
void decode(string &str) {
    int begin = find(str);
    if (begin == str.length())return;
    string middle, decoding;
    int times = 0, k = begin;
//    for ( k = begin; str[k] != ']'; ++k)middle += str[k];
    int couple = 0;
    while (1) {
        if (str[k] == '[') {
            couple++;
            middle+=str[k];
            ++k;
        } else if (str[k] == ']') {
            if (couple) {
                couple--;
                middle+=str[k];
                ++k;
            } else break;
        } else{
            middle+=str[k];
            ++k;
        }
    }
    int j;
    for (j = begin - 1; str[j] != '['; --j);
    for (int i = j + 1; i < begin; ++i)times = times * 10 + (str[i] - '0');
    for (int i = 0; i < times; ++i) {
        decoding += middle;
    }
    str.erase(j, k - j + 1);
    str.insert(j, decoding);
//    cout<<str<<endl;
    decode(str);
}

int main() {
    string str;
    cin >> str;
    decode(str);
    cout << str << endl;
}
//标答如下！！！
//#include<bits/stdc++.h>
//using namespace std;
//string read()
//{
//    int n;
//    string s="",s1;
//    char c;
//    while (cin>>c)//一直读入字符，直到Ctrl+z
//    {
//        if (c=='[')
//        {
//            cin>>n;//读入D
//            s1=read();//读入X
//            while (n--) s+=s1;//重复D次X
//            //注：上面不能写成while (n--) s+=read();
//        }
//        else
//        {
//            if (c==']') return s;//返回X
//            else s+=c;//如果不是'['和']'，那就是X的一个字符，所以加进X
//        }
//    }
//}
//int main()//巨短主函数
//{
//    cout<<read();
//    return 0;
//}