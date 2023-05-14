#include <iostream>
#include<set>
#include<unordered_map>
#include <string>

using namespace std;

struct student {
    string name;
    char gender;
    int classnumber;
    int score0;
    int score1;
    int score2;
    int score3;
    int score4;
    int score5;
    int score6;
    int score7;
    int score8;

};

bool operator<(const student &lhs, const student &rhs) {
    int la = (lhs.score0 + lhs.score1 + lhs.score2 + lhs.score3 + lhs.score4 + lhs.score5 + lhs.score6 + lhs.score7 +
              lhs.score8) / 9;
    int ra = (rhs.score0 + rhs.score1 + rhs.score2 + rhs.score3 + rhs.score4 + rhs.score5 + rhs.score6 + rhs.score7 +
              rhs.score8) / 9;
    if (la == ra) {
        if (lhs.score0 == rhs.score0) {
            if (lhs.score1 == rhs.score1) {
                if (lhs.score2 == rhs.score2) {
                    if (lhs.score3 == rhs.score3) {
                        if (lhs.score4 == rhs.score4) {
                            if (lhs.score5 == rhs.score5) {
                                if (lhs.score6 == rhs.score6) {
                                    if (lhs.score7 == rhs.score7) {
                                        if (lhs.score8 == rhs.score8) {
                                            return lhs.name < rhs.name;
                                        } else return lhs.score8 > rhs.score8;
                                    } else return lhs.score7 > rhs.score7;
                                } else return lhs.score6 > rhs.score6;
                            } else return lhs.score5 > rhs.score5;
                        } else return lhs.score4 > rhs.score4;
                    } else return lhs.score3 > rhs.score3;
                } else return lhs.score2 > rhs.score2;
            } else return lhs.score1 > rhs.score1;
        } else return lhs.score0 > rhs.score0;
    } else
        return la > ra;
}

unordered_map<string, student> m;
set<student> s;
int length = 0;

int main() {
    string classifystr1;
    while (1) {
        cin >> classifystr1;
        if (classifystr1 == "START") break;
        string name1;
        cin >> name1;//判断是否存在，若不存在，添加进去；
        if (m.count(name1) == 0) {
            student stu1;
            stu1.name = name1;
            cin >> stu1.gender >> stu1.classnumber >> stu1.score0 >> stu1.score1 >> stu1.score2 >> stu1.score3
                >> stu1.score4
                >> stu1.score5 >> stu1.score6 >> stu1.score7 >> stu1.score8;
            //添加到map和set,用map记录下名次锁榜
            s.insert(stu1);
            m[name1] = stu1;
        } else {
            char invalid[70];
            cin.getline(invalid, 70);
            cout << "[Error]Add failed." << endl;
        }
    }
    length = s.size();
    student lockarray[length];
    int i = 0;
    set<student>::iterator ittt;
    for (ittt = s.begin(); ittt != s.end(); ++ittt) {
        student stu0 = *ittt;
        lockarray[i] = stu0;
        ++i;
    }
    string classifystr2;
    while (1) {
        cin >> classifystr2;
        if (classifystr2 == "END") break;

        else if (classifystr2 == "UPDATE") {
            string name2;
            cin >> name2;
            //找这个元素，找到了就erase
            /* int counter = 0;
             set<student>::iterator it2;
             for (it2 = s.begin(); it2 != s.end(); ++it2) {
                 student stu0 = *it2;
                 if (stu0.name == name2) {
                     ++counter;
                     s.erase(stu0) ;
                     break;
                 }
             }*/
            if (s.find(m[name2]) != s.end()) {
                s.erase(m[name2]);

                //if (counter == 1) {
                int code;
                cin >> code;
                if (code == 1) {
                    cin >> m[name2].score1;
                } else if (code == 2) {
                    cin >> m[name2].score2;
                } else if (code == 3) {
                    cin >> m[name2].score3;
                } else if (code == 4) {
                    cin >> m[name2].score4;
                } else if (code == 5) {
                    cin >> m[name2].score5;
                } else if (code == 6) {
                    cin >> m[name2].score6;
                } else if (code == 7) {
                    cin >> m[name2].score7;
                } else if (code == 0) {
                    cin >> m[name2].score0;
                } else {
                    cin >> m[name2].score8;
                }
                s.insert(m[name2]);
            } else {
                char invalid[10];
                cin.getline(invalid, 10);
                cout << "[Error]Update failed." << endl;
            }
        } else if (classifystr2 == "QUERY") {
            string name3;
            cin >> name3;
           // cout<<"[input]"+name3<<endl;
            if (s.find(m[name3]) != s.end()) {
                for (int j = 0; j < length; ++j) {
                    if (name3 == lockarray[j].name) cout << "STUDENT " << name3 << " NOW AT RANKING " << j + 1 << endl;
                }
            } else {
                char invalid0[70];
                cin.getline(invalid0, 70);
                cout << "[Error]Query failed." << endl;
            }
        } else if (classifystr2 == "FLUSH") {
            set<student>::iterator itt;
            int k = 0;
            for (itt = s.begin(); itt != s.end(); ++itt) {
                student stu0 = *itt;
                lockarray[k] = stu0;
                ++k;
            }
        } else if (classifystr2 == "PRINTLIST") {
            for (int h = 0; h < length; ++h) {
                student stu3 = lockarray[h];
                string gender1;
                if (stu3.gender == 'F') gender1 = "female";
                else gender1 = "male";
                student stu1 = m[stu3.name];
                int avr1 = (stu1.score1 + stu1.score2 + stu1.score3 + stu1.score4 + stu1.score5 + stu1.score6 +
                            stu1.score7 + stu1.score8 + stu1.score0) / 9;
                cout << h + 1 << " " << stu3.name << " " << gender1 << " " << stu3.classnumber
                     << " "
                     << avr1 << endl;
            }
        } else if (classifystr2 == "ADD") {
            char invalid[70];
            cin.getline(invalid, 70);
            cout << "[Error]Cannot add student now." << endl;
        }

    }

    return 0;
}

