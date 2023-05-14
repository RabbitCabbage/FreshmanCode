//其实应该做一个map将名字与结构体对应，这样就不用遍历来找元素是否存在了
//我在开始写学生会工作时候才意识到
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;
int vector_length;

struct activity {
    string str;
    int avr;
    int level;
};

bool operator<(const activity &lhs, const activity &rhs) {
    if (lhs.avr == rhs.avr) {
        if (lhs.level == rhs.level) {
            return lhs.str.front() < rhs.str.front();
        } else return lhs.level < rhs.level;
    } else return lhs.avr > rhs.avr;
}

map<string, vector<int>> m;
set<activity> s;
set<string> mapstring;

int main() {

    string classifystr1;
    while (1) {
        cin >> classifystr1;
        if (classifystr1 == "end") break;
        else if (classifystr1 == "map") {
            string classifystr2;
            cin >> classifystr2;
            if (classifystr2 == "insert") {
                //实现map insert功能
                string str1;
                cin >> str1;
                if (m.count(str1) == 0) {
                    cin >> vector_length;
                    vector<int> vec1;
                    for (int i = 0; i < vector_length; ++i) {
                        int time = 0;
                        cin >> time;
                        vec1.push_back(time);
                    }
                    m[str1] = vec1;
                    mapstring.insert(str1);
                } else cout << "Error" << endl;
            } else if (classifystr2 == "size") {
                //实现map size的功能
                cout << m.size() << endl;
            } else if (classifystr2 == "erase") {
                //实现map erase的功能
                string str2;
                cin >> str2;
                if (m.count(str2) != 0) {
                    m.erase(str2);
                    mapstring.erase(str2);
                } else cout << "Error" << endl;
            } else if (classifystr2 == "count") {
                //实现map count的功能
                string str3;
                cin >> str3;
                cout << m.count(str3) << endl;
            } else if (classifystr2 == "traverse") {
                //实现traverse
                set<string>::iterator itt;
                for (itt = mapstring.begin(); itt != mapstring.end(); ++itt) {
                    vector<int> vec2 = m[*itt];
                    cout << *itt << " ";
                    vector<int>::iterator it;
                    for (it = vec2.begin(); it != vec2.end(); ++it) {
                        cout << *it << " ";
                    }
                    cout << endl;

                }
            } else if (classifystr2 == "visitVec") {
                //实现map visitvec;
                string str4;
                cin >> str4;
                if (m.count(str4) != 0) {
                    vector<int> vec3 = m[str4];
                    int index;
                    cin >> index;
                    cout << vec3[index] << endl;
                } else cout << "Error" << endl;
            } else if (classifystr2 == "visit") {
                //实现map visit
                string str5;
                cin >> str5;
                if (m.count(str5) != 0) {
                    vector<int> vec4 = m[str5];
                    cout << vec4.size() << " ";
                    vector<int>::iterator it;
                    for (it = vec4.begin(); it != vec4.end(); ++it) {
                        cout << *it << " ";
                    }
                    cout << endl;
                } else cout << "Error" << endl;
            } else if (classifystr2 == "append") {
                //实现map append
                string str6;
                cin >> str6;
                if (m.count(str6) != 0) {
                    int element;
                    cin >> element;
                    m[str6].push_back(element);
                } else cout << "Error" << endl;
            } else continue;
        } else if (classifystr1 == "set") {
            string classifystr3;
            cin >> classifystr3;
            if (classifystr3 == "insert") {
                //实现set insert
                string setstr;
                int avg, level;
                cin >> avg >> level >> setstr;
                activity act1 = {setstr, avg, level};
                if (s.count(act1) == 0) {
                    s.insert(act1);
                } else cout << "Error" << endl;
            } else if (classifystr3 == "erase") {
                //实现set erase ;
                int avrtemp, leveltemp;
                cin >> avrtemp >> leveltemp;
                string setstr1;
                cin >> setstr1;
                set<activity>::iterator set_it;
                int counter = 0;
                for (set_it = s.begin(); set_it != s.end(); ++set_it) {
                    activity temp = *set_it;
                    if (temp.str == setstr1 && temp.avr == avrtemp && temp.level == leveltemp) {
                        s.erase(*set_it);
                        ++counter;
                        break;
                    }

                }
                if (counter == 0) cout << "Error" << endl;
            } else if (classifystr3 == "count") {
                //实现是set count
                int avrtemp, leveltemp;
                cin >> avrtemp >> leveltemp;
                string setstr2;
                cin >> setstr2;
                set<activity>::iterator set_it2;
                int counter = 0;
                for (set_it2 = s.begin(); set_it2 != s.end(); ++set_it2) {
                    activity temp = *set_it2;
                    if (temp.str == setstr2 && temp.avr == avrtemp && temp.level == leveltemp) ++counter;
                }
                if (counter == 1) cout << 1 << endl;
                else cout << 0 << endl;

            } else if (classifystr3 == "traverse") {
                //实现set traverse
                set<activity>::iterator ittt;
                for (ittt = s.begin(); ittt != s.end(); ++ittt) {
                    activity ac2 = *ittt;
                    cout << ac2.avr << " " << ac2.level << " " << ac2.str << endl;
                }

            } else if (classifystr3 == "size")cout << s.size() << endl;
        }
    }
    return 0;
}