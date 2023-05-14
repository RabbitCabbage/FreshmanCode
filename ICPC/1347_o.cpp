// LTC 20211102
#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace icpc {
// 数据范围
// 队伍总数 N<=1e4，题目总数 M<=26，比赛时长 T<=1e5
// 操作次数 opt<=3e5，刷新榜单次数 opt_flush<=1000，封榜次数 opt_freeze<=10

const int kMaxTeamNum = 1e4 + 5;

bool running = false, started = false, frozen = false;     // 比赛状态
int duration_time, problem_num, team_num, submission_num;  // 比赛信息

// 根据 status 的首字母查找 status_id
// Accepted: lookup_status_id['A'] = 0;
// Wrong_Answer: lookup_status_id['W'] = 1;
// Runtime_Error: lookup_status_id['R'] = 2;
// Time_Limit_Exceed: lookup_status_id['T'] = 3;
int lookup_status_id[128];

// 根据 status_id 查找 status
// 0->Accepted; 1->Wrong_Answer; 2->Runtime_Error; 3->Time_Limit_Exceed
std::string lookup_status_name[4] = {"Accepted", "Wrong_Answer",
                                     "Runtime_Error", "Time_Limit_Exceed"};

struct Problem {
  int id;
  bool passed = false;
  // 如果冻结后通过此题，passed_after_freeze 设为 true，passed 仍为 false
  bool passed_after_freeze = false;
  bool frozen = false;  // 已经通过的题目不冻结

  int wrong_submission_num = 0;  // 错误提交次数，不包含封榜后的提交
  int submission_num_after_freeze = 0;  // 冻结后的所有提交次数
  int wrong_submission_num_after_freeze = 0;  // 冻结后、AC 前的错误提交次数
  int time;                                   // 通过时间

  // 以下信息用于 query submission
  int last_submission_time[4];  // 各种提交状态的最晚提交时间
  int last_submission_id[4] = {0, 0, 0, 0};  // 各种提交状态的最晚提交 id

  // 返回最晚提交的 submission 的 status_id
  inline int FindLastSubmission(int status_id) {
    if (status_id == -1) {
      int submission_id = 0;
      for (int i = 0; i < 4; ++i)
        if (last_submission_id[i] > submission_id)
          status_id = i, submission_id = last_submission_id[i];
    } else {
      if (last_submission_id[status_id] == 0) status_id = -1;
    }
    return status_id;
  }
};

struct CompareProblem {
  bool operator()(const Problem *a, const Problem *b) const {
    if (a->time != b->time)
      return a->time > b->time;
    else
      return a->id < b->id;
  }
};

struct Team {
  std::string name;
  int solved_problem_num = 0, penalty = 0;
  Problem problems[26];
  // 通过的题目按照通过时间从大到小排序；通过时间相同的按 problem_name 排序
  std::set<Problem *, CompareProblem> passed_problems;

  // 滚榜解封的时候用来减少遍历次数，并不一定指向第一个未被冻结的 problem
  int first_frozen_problem = 26;

  bool operator<(const Team &x) const {
    if (solved_problem_num != x.solved_problem_num) {
      return solved_problem_num > x.solved_problem_num;
    } else {
      if (penalty != x.penalty) {
        return penalty < x.penalty;
      } else {
        // 下面这段其实应该保留的，以防出错而不知，但是在保证正确性的前提下为了优化性能就注释掉了
        // if (passed_problems.size() != x.passed_problems.size()) {
        //   throw "Wrong!";
        // }
        for (auto i = passed_problems.begin(), j = x.passed_problems.begin();
             i != passed_problems.end(); ++i, ++j) {
          if ((*i)->time != (*j)->time) return (*i)->time < (*j)->time;
        }
        return name < x.name;
      }
    }
  }
  inline void NewPassedProblem(Problem &problem) {
    problem.passed = true;
    passed_problems.insert(&problem);
    solved_problem_num++;
    penalty += 20 * problem.wrong_submission_num + problem.time;
  }
  inline void UnfreezeProblem(Problem &problem) {
    problem.frozen = false;
    problem.wrong_submission_num += problem.wrong_submission_num_after_freeze;
    problem.wrong_submission_num_after_freeze = 0;
    problem.submission_num_after_freeze = 0;
  }
  inline std::pair<int, int> FindLastSubmission(  //
      int problem_id, const int status_id) {
    int status_id_matched = -1;
    if (problem_id == -1) {
      int submission_id = 0;
      for (int i = 0, tmp_status_id; i < problem_num; ++i) {
        Problem &problem = problems[i];
        tmp_status_id = problem.FindLastSubmission(status_id);
        if (tmp_status_id != -1 &&
            problem.last_submission_id[tmp_status_id] > submission_id) {
          problem_id = i;
          status_id_matched = tmp_status_id;
          submission_id = problem.last_submission_id[tmp_status_id];
        }
      }
    } else {
      status_id_matched = problems[problem_id].FindLastSubmission(status_id);
    }
    return std::make_pair(problem_id, status_id_matched);
  }
} teams[kMaxTeamNum];

std::unordered_map<std::string, int> map;  // 根据队名查询 team_id

int team_id_to_rank[kMaxTeamNum];
auto cmp = [](const int &a, const int &b) { return teams[a] < teams[b]; };
std::set<int, decltype(cmp)> set(cmp);  // set 储存 team_id，并实时排序

// 排名需要更新的队伍，等到 flush 时一并插入 set
std::unordered_set<int> need_update;

/* 输出榜单 */
inline void PrintRanking() {
  int rank = 0;
  for (int i: set) {
    ++rank;
    Team &team = teams[i];
    std::cout << team.name << ' ' << rank << ' ' << team.solved_problem_num << ' '
              << team.penalty << ' ';
    for (int j = 0; j < problem_num; ++j) {
      Problem &problem = team.problems[j];
      if (problem.frozen) {
        std::cout << -problem.wrong_submission_num << '/'
                  << problem.submission_num_after_freeze;
      } else {
        if (problem.passed) {
          std::cout << '+';
          if (problem.wrong_submission_num)
            std::cout << problem.wrong_submission_num;
        } else {
          if (problem.wrong_submission_num)
            std::cout << -problem.wrong_submission_num;
          else
            std::cout << '.';
        }
      }
      std::cout << ' ';
    }
    std::cout << '\n';
  }
}

/* 添加队伍 */
void AddTeam() {
  std::string team_name;
  std::cin >> team_name;
  if (started) {
    std::cout << "[Error]Add failed: competition has started.\n";
    return;
  }
  if (map.find(team_name) == map.end()) {
    ++team_num;
    teams[team_num].name = team_name;
    for (int i = 0; i < 26; ++i) teams[team_num].problems[i].id = i;
    map.emplace(team_name, team_num);
    set.insert(team_num);
    std::cout << "[Info]Add successfully.\n";
  } else {
    std::cout << "[Error]Add failed: duplicated team name.\n";
  }
}

inline void PreFlush(){
  for (auto team_id : need_update) set.insert(team_id);
  need_update.clear();
}

inline void FlushWithoutInfo() {
  PreFlush();

  int rank = 0;
  for (auto i : set) {
    ++rank;
    team_id_to_rank[i] = rank;
  }
}

/* 刷新榜单 */
void Flush() {
  if (!need_update.empty()) {
    FlushWithoutInfo();
  }
  std::cout << "[Info]Flush scoreboard.\n";
}

/* 开始比赛 */
void Start() {
  int duration_time_, problem_num_;
  std::string useless_word_receiver;
  std::cin >> useless_word_receiver >> duration_time_ >>
      useless_word_receiver >> problem_num_;

  if (started) {
    std::cout << "[Error]Start failed: competition has started.\n";
    return;
  }
  started = true;
  duration_time = duration_time_, problem_num = problem_num_;
  FlushWithoutInfo();
  std::cout << "[Info]Competition starts.\n";
}

/* 提交题目 */
void Submit() {
  char problem_name;
  std::string team_name, submit_status, useless_word_receiver;
  int time;
  std::cin >> problem_name >> useless_word_receiver >> team_name >>
      useless_word_receiver >> submit_status >> useless_word_receiver >> time;

  const int problem_id = problem_name - 'A';
  const int team_id = map[team_name];

  Team &team = teams[team_id];
  Problem &problem = team.problems[problem_id];
  if (!problem.passed && !problem.frozen && frozen) {
    problem.frozen = true;  // 封榜后至少有一次提交的题目将变成冻结状态
    if (problem_id < team.first_frozen_problem)
      team.first_frozen_problem = problem_id;
  }

  const int status_id = lookup_status_id[submit_status[0]];
  problem.last_submission_time[status_id] = time;
  problem.last_submission_id[status_id] = ++submission_num;

  if (!status_id) {         // Accepted
    if (!problem.passed) {  // 封榜前没通过
      if (!problem.passed_after_freeze) problem.time = time;
      if (!problem.frozen) {  // 没被封，更新 team
        bool succeeded = need_update.insert(team_id).second;
        if (succeeded) set.erase(team_id);  // 只有通过了题目才会对排名产生影响
        team.NewPassedProblem(problem);
      } else {  // 被封，更新被封后的提交次数
        ++problem.submission_num_after_freeze;
        problem.passed_after_freeze = true;
      }
    }
  } else {
    if (!problem.passed) {
      if (problem.frozen) {
        ++problem.submission_num_after_freeze;
        if (!problem.passed_after_freeze)
          ++problem.wrong_submission_num_after_freeze;
      } else {
        ++problem.wrong_submission_num;
      }
    }
  }
}

/* 封榜 */
void Freeze() {
  if (frozen) {
    std::cout << "[Error]Freeze failed: scoreboard has been frozen.\n";
    return;
  }
  frozen = true;
  std::cout << "[Info]Freeze scoreboard.\n";
}

/* 滚榜 */
void Scroll() {
  if (!frozen) {
    std::cout << "[Error]Scroll failed: scoreboard has not been frozen.\n";
    return;
  }
  // FlushWithoutInfo();
  PreFlush();
  std::cout << "[Info]Scroll scoreboard.\n";
  PrintRanking();

  auto end_iter = set.end();

  while (end_iter != set.begin()) {  // 开滚
    auto now_iter = end_iter;
    --now_iter;
    int last_team_id = *now_iter;

    Team &last_team = teams[last_team_id];
    bool have_frozen_problem = false;

    // for (int i = 0; i < problem_num; ++i) {
    for (int i = last_team.first_frozen_problem; i < problem_num; ++i) {
      Problem &problem = last_team.problems[i];
      if (problem.frozen) {  // 有冻结的题目，解冻
        have_frozen_problem = true;
        last_team.first_frozen_problem = i + 1;
        last_team.UnfreezeProblem(problem);
        if (problem.passed_after_freeze) {
          set.erase(last_team_id);  // 只有冻结后通过的题目会影响排名

          last_team.NewPassedProblem(problem);
          problem.passed_after_freeze = false;

          auto new_iter = set.insert(last_team_id).first;
          ++new_iter;
          if (end_iter != new_iter) {
            std::cout << last_team.name << " " << teams[*new_iter].name << " "
                      << last_team.solved_problem_num << " "
                      << last_team.penalty << "\n";
          }
        }
        break;
      }
    }
    if (!have_frozen_problem) --end_iter;
  }
  frozen = false;
  FlushWithoutInfo();
  PrintRanking();
}

/* 查询队伍排名 */
void QueryRanking() {
  std::string team_name;
  std::cin >> team_name;
  auto iter = map.find(team_name);
  if (iter == map.end()) {
    std::cout << "[Error]Query ranking failed: cannot find the team.\n";
  } else {
    std::cout << "[Info]Complete query ranking.\n";
    if (frozen)
      std::cout << "[Warning]Scoreboard is frozen. The ranking may be "
                   "inaccurate until it were scrolled.\n";

    std::cout << team_name << " NOW AT RANKING "
              << team_id_to_rank[iter->second] << "\n";
  }
}

/* 查询队伍提交情况 */
void QuerySubmission() {
  std::string useless_word_receiver;
  std::string team_name, problem_name, status;
  std::cin >> team_name >> useless_word_receiver >> problem_name >>
      useless_word_receiver >> status;
  problem_name = problem_name.substr(8);
  status = status.substr(7);

  int problem_id = -1, status_id = -1;
  if (status != "ALL") status_id = lookup_status_id[status[0]];
  if (problem_name != "ALL") problem_id = problem_name[0] - 'A';

  auto iter = map.find(team_name);
  if (iter == map.end()) {
    std::cout << "[Error]Query submission failed: cannot find the team.\n";
    return;
  } else {
    Team &team = teams[iter->second];
    auto [problem_id_matched, status_id_matched] =
        team.FindLastSubmission(problem_id, status_id);
    std::cout << "[Info]Complete query submission.\n";

    if (problem_id_matched != -1 && status_id_matched != -1)
      std::cout << team_name << ' ' << char(problem_id_matched + 'A') << ' '
                << lookup_status_name[status_id_matched] << ' '
                << team.problems[problem_id_matched]
                       .last_submission_time[status_id_matched]
                << '\n';
    else
      std::cout << "Cannot find any submission.\n";
  }
}

/* 结束比赛 */
inline void End() {
  std::cout << "[Info]Competition ends.\n";
  running = false;
}

inline void Run() {
  // 初始化 lookup_status_id 数组
  lookup_status_id['A'] = 0;  // Accepted
  lookup_status_id['W'] = 1;  // Wrong_Answer
  lookup_status_id['R'] = 2;  // Runtime_Error
  lookup_status_id['T'] = 3;  // Time_Limit_Exceed

  running = true;
  std::unordered_map<std::string, std::function<void()> > map_function = {
      {"ADDTEAM", AddTeam},
      {"START", Start},
      {"SUBMIT", Submit},
      {"FLUSH", Flush},
      {"FREEZE", Freeze},
      {"SCROLL", Scroll},
      {"QUERY_RANKING", QueryRanking},
      {"QUERY_SUBMISSION", QuerySubmission},
      {"END", End}};
  std::string command;
  while (running) {
    std::cin >> command;
    map_function[command]();
  }
}
}  // namespace icpc

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  // std::freopen("data/3.in", "r", stdin);
  icpc::Run();
  return 0;
}
