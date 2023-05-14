//参考谷歌C++代码风格
#include <iostream>
#include <unordered_map>
#include <set>
#include<functional>
#include<sstream>
#include <string>
#include <algorithm>

using namespace std;
int problem_count;//题目总数

struct Problem {//记录每道题的信息
    int submit_number = 0;//提交次数，正负有意义
    int total_submit = 0;//提交总数，仅正数
    int last_time_sub = 0;//最后一次提交时间
    int ac_time = 0;
    int tle_time = 0;
    int re_time = 0;
    int wa_time = 0;
    string last_status;//某一道题目的最后一次wa的时间，便于后期查询
    int first_ac_time = 0;
    int struggled_times = 0;//用来计算罚时
};
struct Team {
    string name;
    Problem parray[28];//保存各个题目的信息
    int ac_time_sorting[28]{0};//每个队伍的每道题目有首次ac时间,用于比较排名
    //下面的信息用于状态查询，所有题目里某个status最后提交的题目和时间
    int last_submit_time = 0;
    int last_ac_time = 0;
    int last_tle_time = 0;
    int last_wa_time = 0;
    int last_re_time = 0;
    char last_ac = '\0';
    char last_re = '\0';
    char last_wa = '\0';
    char last_tle = '\0';
    char last_submit = '\0';
    int acnum = 0;
    int code;
    int rank;
    int freeze_rank;
    int penalty = 0;
    bool change = false;
};

bool operator<(const Team &lhs, const Team &rhs) {

    if (lhs.acnum == rhs.acnum) {
        if (lhs.penalty == rhs.penalty) {
            int i = 0;
            for (i = 0; i < lhs.acnum && lhs.ac_time_sorting[i] == rhs.ac_time_sorting[i]; ++i);
            if (i == lhs.acnum) return lhs.name < rhs.name;
            else return lhs.ac_time_sorting[i] < rhs.ac_time_sorting[i];
        } else return lhs.penalty < rhs.penalty;
    } else return lhs.acnum > rhs.acnum;
}

Team team_array[10010];

struct int_comp {
    bool operator()(const int &lhs, const int &rhs) const {
        return team_array[lhs] < team_array[rhs];
    }
};

struct int_comp_rank {
    bool operator()(const int &lhs, const int &rhs) const {
        return team_array[lhs].freeze_rank < team_array[rhs].freeze_rank;
    }
};

bool compare(int &a, int &b) { return a > b; }

unordered_map<string, Team> m;
set<int, int_comp> s;

//下面是重载比较条件

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string stage_str1;
    cin >> stage_str1;
    int team_number = 0;
    while (1) {
        if (stage_str1 == "START") {
            //这里要做start相应的操作
            int duration;
            char ch[20];
            string start_information;
            stringstream info_deal;
            getline(cin, start_information);
            info_deal.clear();
            info_deal.str(start_information);
            info_deal >> ch >> duration >> ch >> problem_count;
            cout << "[Info]Competition starts.\n";
            break;
        } else {
            //这里是add
            string name_add;
            cin >> name_add;
            if (m.count(name_add) == 0) {
                Team team_add{name_add};
                team_add.code = team_number;
                m[team_add.name] = team_add;
                team_array[team_number] = team_add;
                s.insert(team_number);//分别放到map,set,array
                team_number++;//此时正好是数量
                cout << "[Info]Add successfully.\n";
            } else cout << "[Error]Add failed: duplicated team name.\n";
        }
        cin >> stage_str1;
    }
    //这里是封榜数组的最初输入，字典顺序
    set<int, int_comp>::iterator initial_it;
    int i = 0;

    for (initial_it = s.begin(); initial_it != s.end(); ++initial_it) {
        m[team_array[*initial_it].name].rank = i + 1;
        ++i;
    }

    string stage_str2;
    cin >> stage_str2;
    bool whether_lock = false;
    bool flush_choice = false;
    while (1) {
        if (stage_str2 == "END") {
            //end的相应操作
            cout << "[Info]Competition ends.\n";
            break;
        } else if (stage_str2 == "FREEZE") {
            if (whether_lock)cout << "[Error]Freeze failed: scoreboard has been frozen.\n";
            else {
                auto pointer = m.begin();
                for (; pointer != m.end(); pointer++) {
                    Team tmp = pointer->second;
                    if (tmp.change) {
                        s.erase(tmp.code);
                        tmp.change = false;
                        team_array[tmp.code] = tmp;
                        s.insert(tmp.code);
                    }
                }
                set<int, int_comp>::iterator iter;
                int f_rank = 1;
                for (iter = s.begin(); iter != s.end(); ++iter) {
                    team_array[*iter].freeze_rank = f_rank;
                    m[team_array[*iter].name].freeze_rank = f_rank;
                    f_rank++;
                }
                auto pointer2 = m.begin();
                for (; pointer2 != m.end(); pointer2++) {
                    Team tmp = pointer2->second;
                    if (tmp.change) {
                        s.erase(tmp.code);
                        tmp.change = false;
                        team_array[tmp.code] = tmp;
                        s.insert(tmp.code);
                    }
                }
                cout << "[Info]Freeze scoreboard.\n";
                whether_lock = true;
                flush_choice = true;
            }
        } else if (stage_str2 == "SCROLL") {
            if (whether_lock) {
                cout << "[Info]Scroll scoreboard.\n";
                whether_lock = false;
                //下面输出封榜前的排名，这时不能直接从map set里面取，因为是要输出：前：
                set<int, int_comp_rank>::iterator it_p;

                for (it_p = s.begin(); it_p != s.end(); ++it_p) {
                    Team print_team = team_array[*it_p];
                    cout << print_team.name << " " << print_team.freeze_rank << " " << print_team.acnum << " "
                         << print_team.penalty;
                    for (int k = 0; k < problem_count; ++k) {
                        int submit_number_now = m[print_team.name].parray[k].submit_number;
                        int submit_number_before = print_team.parray[k].submit_number;
                        if (submit_number_before == 1)cout << " " << '+';
                        else if (submit_number_before > 1)cout << " +" << submit_number_before - 1;
                        else if (m[print_team.name].parray[k].total_submit ==
                                 print_team.parray[k].total_submit) {//没有被冻结
                            if (submit_number_before == 0)cout << " " << '.';
                            else if (submit_number_before < 0)cout << " " << submit_number_before;
                        } else {//题目被冻结了
                            int submit_times =
                                    m[print_team.name].parray[k].total_submit - print_team.parray[k].total_submit;
                            cout << " " << submit_number_before << '/' << submit_times;
                        }
                    }
                    cout << "\n";
                }
                set<int, int_comp>::iterator itt, it_temp;
                itt = (--s.end());//指向最后一个元素
                Team past, present;
                while (itt != (--s.begin())) {
                    it_temp = itt;
                    past = team_array[*it_temp];
                    present = m[past.name];
                    for (int q = 0; q < problem_count; ++q) {
                        if (past.parray[q].submit_number != present.parray[q].submit_number) {
                            itt++;//指向了后一个元素
                            Team after_me;
                            if ((++it_temp) != s.end()) after_me = team_array[*(it_temp)];//如果是最后一个，为空
                            s.erase(past.code);
                            past.parray[q] = present.parray[q];
                            if (present.parray[q].submit_number > 0) {
                                past.ac_time_sorting[past.acnum] = present.parray[q].first_ac_time;
                                past.acnum++;
                                sort(past.ac_time_sorting, past.ac_time_sorting + 28, compare);//todo
                                past.penalty += present.parray[q].first_ac_time +
                                                present.parray[q].struggled_times * 20;
                            }
                            team_array[past.code] = past;
                            s.insert(past.code);
                            Team after_me_now;
                            it_temp = s.find(past.code);
                            if ((++it_temp) != s.end())after_me_now = team_array[*(it_temp)];//如果是最后一个的话，after_menow为空
                            if (after_me.name != after_me_now.name) {
                                cout << past.name << " " << after_me_now.name << " " << past.acnum << " "
                                     << past.penalty
                                     << "\n";
                            }
                            break;
                        }
                    }
                    --itt;
                }
                for (int h = 0; h < team_number; ++h) {
                    if (m[team_array[h].name].change) {
                        s.erase(h);
                        m[team_array[h].name].change = false;
                        team_array[h] = m[team_array[h].name];
                        s.insert(h);
                    }
                }
                set<int, int_comp>::iterator it;
                int rank = 0;
                for (it = s.begin(); it != s.end(); ++it) {
                    rank++;
                    Team &print_team1 = team_array[*it];
                    m[print_team1.name].rank = rank;
                    cout << print_team1.name << " " << rank << " " << print_team1.acnum << " "
                         << print_team1.penalty;
                    for (int h = 0; h < problem_count; ++h) {
                        if (print_team1.parray[h].submit_number == 1)cout << " " << '+';
                        else if (print_team1.parray[h].submit_number == 0)cout << " " << '.';
                        else if (print_team1.parray[h].submit_number > 1)
                            cout << " +" << print_team1.parray[h].submit_number - 1;
                        else if (print_team1.parray[h].submit_number < 0)
                            cout << " " << print_team1.parray[h].submit_number;
                    }
                    cout << "\n";
                }

            } else cout << "[Error]Scroll failed: scoreboard has not been frozen.\n";
        } else if (stage_str2 == "START") {
            string invalid;
            getline(cin, invalid, '\n');
            cout << "[Error]Start failed: competition has started.\n";
        } else if (stage_str2 == "ADDTEAM") {
            string invalid;
            getline(cin, invalid, '\n');
            cout << "[Error]Add failed: competition has started.\n";
        } else if (stage_str2 == "SUBMIT") {
            stringstream info_deal;
            string submit_info;
            getline(cin, submit_info);
            info_deal.clear();
            info_deal.str(submit_info);
            char problem_name;
            string team_name, status;
            char ch[25];
            int time;
            info_deal >> problem_name >> ch >> team_name >> ch >> status >> ch >> time;
            auto &team_submit = m[team_name];
            team_submit.parray[problem_name - 'A'].last_time_sub = time;
            int a = team_submit.parray[problem_name - 'A'].submit_number;
            if (!team_submit.change)team_submit.change = true;
            if (status == "Accepted") {
                if (team_submit.parray[problem_name - 'A'].ac_time == 0) {
                    team_submit.ac_time_sorting[team_submit.acnum] = time;
                    team_submit.acnum++;
                    sort(team_submit.ac_time_sorting, team_submit.ac_time_sorting + 28, compare);//todo
                    team_submit.parray[problem_name - 'A'].first_ac_time = time;
                    team_submit.parray[problem_name - 'A'].struggled_times = abs(
                            team_submit.parray[problem_name - 'A'].submit_number);
                    team_submit.penalty += team_submit.parray[problem_name - 'A'].first_ac_time +
                                           team_submit.parray[problem_name - 'A'].struggled_times * 20;
                }
                if (team_submit.parray[problem_name - 'A'].submit_number <= 0)
                    team_submit.parray[problem_name - 'A'].submit_number = abs(a) + 1;
                team_submit.parray[problem_name - 'A'].ac_time = time;
                team_submit.last_ac_time = time;
                team_submit.last_ac = problem_name;
                team_submit.last_submit_time = time;
                team_submit.last_submit = problem_name;
                team_submit.parray[problem_name - 'A'].last_status = "Accepted";
                team_submit.parray[problem_name - 'A'].total_submit++;
            } else if (status == "Wrong_Answer") {
                team_submit.parray[problem_name - 'A'].wa_time = time;
                if (team_submit.parray[problem_name - 'A'].submit_number <= 0)
                    --(team_submit.parray[problem_name - 'A'].submit_number);
                team_submit.last_wa_time = time;
                team_submit.last_wa = problem_name;
                team_submit.last_submit_time = time;
                team_submit.last_submit = problem_name;
                team_submit.parray[problem_name - 'A'].last_status = "Wrong_Answer";
                team_submit.parray[problem_name - 'A'].total_submit++;

            } else if (status == "Runtime_Error") {
                team_submit.parray[problem_name - 'A'].re_time = time;
                if (team_submit.parray[problem_name - 'A'].submit_number <= 0)
                    --(team_submit.parray[problem_name - 'A'].submit_number);
                team_submit.last_re_time = time;
                team_submit.last_re = problem_name;
                team_submit.last_submit_time = time;
                team_submit.last_submit = problem_name;
                team_submit.parray[problem_name - 'A'].last_status = "Runtime_Error";
                team_submit.parray[problem_name - 'A'].total_submit++;

            } else if (status == "Time_Limit_Exceed") {
                team_submit.parray[problem_name - 'A'].tle_time = time;
                if (team_submit.parray[problem_name - 'A'].submit_number <= 0)
                    --(team_submit.parray[problem_name - 'A'].submit_number);
                team_submit.last_tle_time = time;
                team_submit.last_tle = problem_name;
                team_submit.last_submit_time = time;
                team_submit.last_submit = problem_name;
                team_submit.parray[problem_name - 'A'].last_status = "Time_Limit_Exceed";
                team_submit.parray[problem_name - 'A'].total_submit++;

            }
        } else if (stage_str2 == "FLUSH") {
            cout << "[Info]Flush scoreboard.\n";
            //上面是用string sorting——array储存了排名
            if (!whether_lock) {//此时set里面的还没有更新其实是要更新team array

                for (int h = 0; h < team_number; ++h) {
                    if (m[team_array[h].name].change) {
                        s.erase(h);
                        m[team_array[h].name].change = false;
                        team_array[h] = m[team_array[h].name];
                        s.insert(h);
                    }

                }
                set<int, int_comp>::iterator it;
                int rank_ = 0;
                for (it = s.begin(); it != s.end(); ++it) {
                    m[team_array[(*it)].name].rank = rank_ + 1;
                    ++rank_;
                }//query 的时候就由array里面询问排名，从结构体里找具体信息
            } else if (flush_choice) {
                set<int, int_comp>::iterator set_it;
                for (set_it = s.begin(); set_it != s.end(); ++set_it) {
                    team_array[*set_it].rank = team_array[*set_it].freeze_rank;
                    m[team_array[*set_it].name].rank = team_array[*set_it].freeze_rank;
                }
                flush_choice = false;
            }
        } else if (stage_str2 == "QUERY_RANKING") {
            string team_name;
            cin >> team_name;
            auto pointerk = m.find(team_name);
            if (pointerk != m.end()) {
                cout << "[Info]Complete query ranking.\n";
                if (whether_lock)
                    cout << "[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled. "
                         << "\n";
                cout << team_name << " NOW AT RANKING " << pointerk->second.rank << "\n";
            } else cout << "[Error]Query ranking failed: cannot find the team.\n";
        } else if (stage_str2 == "QUERY_SUBMISSION") {
            string invalid_info, team_name;
            cin >> team_name;
            if (m.count(team_name) == 1) {
                cout << "[Info]Complete query submission.\n";
                auto &query_team = m[team_name];
                getline(cin, invalid_info, '=');
                string problem_query;
                cin >> problem_query;
                getline(cin, invalid_info, '=');
                string status_query;
                cin >> status_query;
                if (problem_query == "ALL" && status_query == "ALL") {

                    if (query_team.last_submit_time == 0)cout << "Cannot find any submission.\n";
                    else {
                        problem_query = query_team.last_submit;
                        status_query = query_team.parray[problem_query[0] - 'A'].last_status;
                        cout << team_name << " " << problem_query << " " << status_query << " "
                             << query_team.last_submit_time << "\n";
                    }
                } else if (problem_query == "ALL") {
                    if (status_query == "Accepted") {
                        problem_query = query_team.last_ac;
                        if (query_team.last_ac_time == 0)cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.last_ac_time << "\n";
                    } else if (status_query == "Wrong_Answer") {
                        problem_query = query_team.last_wa;
                        if (query_team.last_wa_time == 0)cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.last_wa_time << "\n";
                    } else if (status_query == "Runtime_Error") {
                        problem_query = query_team.last_re;
                        if (query_team.last_re_time == 0)cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.last_re_time << "\n";
                    } else if (status_query == "Time_Limit_Exceed") {
                        problem_query = query_team.last_tle;
                        if (query_team.last_tle_time == 0)cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.last_tle_time << "\n";
                    }
                } else if (status_query == "ALL") {
                    status_query = query_team.parray[problem_query[0] - 'A'].last_status;
                    if (query_team.parray[problem_query[0] - 'A'].last_time_sub == 0)
                        cout << "Cannot find any submission.\n";
                    else
                        cout << team_name << " " << problem_query << " " << status_query << " "
                             << query_team.parray[problem_query[0] - 'A'].last_time_sub << "\n";

                } else {
                    if (status_query == "Accepted") {
                        if (query_team.parray[problem_query[0] - 'A'].ac_time == 0)
                            cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.parray[problem_query[0] - 'A'].ac_time << "\n";
                    } else if (status_query == "Wrong_Answer") {
                        if (query_team.parray[problem_query[0] - 'A'].wa_time == 0)
                            cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.parray[problem_query[0] - 'A'].wa_time << "\n";
                    } else if (status_query == "Runtime_Error") {
                        if (query_team.parray[problem_query[0] - 'A'].re_time == 0)
                            cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.parray[problem_query[0] - 'A'].re_time << "\n";
                    } else if (status_query == "Time_Limit_Exceed") {
                        if (query_team.parray[problem_query[0] - 'A'].tle_time == 0)
                            cout << "Cannot find any submission.\n";
                        else
                            cout << team_name << " " << problem_query << " " << status_query << " "
                                 << query_team.parray[problem_query[0] - 'A'].tle_time << "\n";
                    }
                }
            } else cout << "[Error]Query submission failed: cannot find the team.\n";
        }
        cin >> stage_str2;
    }
    return 0;
}