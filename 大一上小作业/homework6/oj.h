//
// Created by lu'ren'jia'd's on 2021/12/4.
//

#ifndef UNTITLED4_OJ_H
#define UNTITLED4_OJ_H

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>

class BaseJudger {
protected:
    char *answer_;
    size_t time_limit_;
    size_t memory_limit_;
public:
    size_t score_;

    virtual bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_, output) == 0;
    }

public:

    BaseJudger(const size_t time_limit, const size_t memory_limit, const char *answer) {
        int len;
        for (len = 0; answer[len] != '\0'; ++len);
        answer_ = new char[len + 1];
        time_limit_ = time_limit;
        memory_limit_ = memory_limit;
        for (int i = 0; i <= len; ++i) {
            answer_[i] = answer[i];
        }
        score_ = 0;
    }

    virtual void Submit(size_t time, size_t memory, const char *output) = 0;

    size_t GetScore() const { return score_; }

    virtual ~BaseJudger() {
        delete[]answer_;
    };
};


class OIJudger : public BaseJudger {
public:
    OIJudger(const size_t time_limit, const size_t memory_limit, const char *answer) : BaseJudger(time_limit,
                                                                                                  memory_limit,
                                                                                                  answer) {}

    bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        //处理掉每一行空格
        int len_output;
        for (len_output = 0; output[len_output] != '\0'; ++len_output);
        std::string deal_output, deal_answer_;
        while (len_output > 0) {
            if (output[len_output - 1] == '\n') {
                deal_output += output[len_output - 1];
                len_output--;
                while (output[len_output - 1] == ' ')len_output--;
                len_output++;
            } else { deal_output += output[len_output - 1]; }
            //此时len应该是上一个空格或者字符
            len_output--;
        }
        int len_;
        for (len_ = 0; answer_[len_] != '\0'; ++len_);
        while (len_ > 0) {
            if (answer_[len_ - 1] == '\n') {
                deal_answer_ += answer_[len_ - 1];
                len_--;
                while (answer_[len_ - 1] == ' ')len_--;
                len_++;
            } else { deal_answer_ += answer_[len_ - 1]; }
            //此时len应该是上一个空格或者字符
            len_--;
        }
        return deal_output == deal_answer_;
    }

    void Submit(size_t time, size_t memory, const char *output) {
        static bool have_sub = false;
        if (have_sub)score_ = 0;
        else {
            bool correct = CheckAnswer(output);
            if (correct && time <= time_limit_ && memory <= memory_limit_)score_ = 100;
            have_sub = true;
        }
    }

    ~OIJudger() {};
};

class ICPCJudger : public BaseJudger {
public:
    ICPCJudger(const size_t time_limit, const size_t memory_limit, const char *answer) : BaseJudger(time_limit,
                                                                                                    memory_limit,
                                                                                                    answer) {}

    bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_, output) == 0;
    }

    void Submit(size_t time, size_t memory, const char *output) {
        bool correct = CheckAnswer(output);
        if (correct && time <= time_limit_ && memory <= memory_limit_)score_ = 100;
    };

    ~ICPCJudger() {};
};


class SpacialJudger : public BaseJudger {
private:
    size_t full_score_time_, full_score_memory_;
public:
    SpacialJudger(const size_t time_limit, const size_t memory_limit, const size_t full_score_time,
                  const size_t full_score_memory, const char *answer) : BaseJudger(time_limit, memory_limit,
                                                                                   answer) {
        full_score_time_ = full_score_time;
        full_score_memory_ = full_score_memory;
    }

    bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_, output) == 0;
    }

    void Submit(size_t time, size_t memory, const char *output) {
        bool correct = CheckAnswer(output);
        if (!correct)score_ = (score_ > 0 ? score_ : 0);
        else {
            if (time <= full_score_time_ && memory <= full_score_memory_)score_ = 100;
            else if (time >= time_limit_ || memory >= memory_limit_)score_ = (score_ > 0 ? score_ : 0);
            else {
                size_t time_score = 100 * (time_limit_ - time) / (time_limit_ - full_score_time_);
                size_t memory_score = 100 * (memory_limit_ - memory) / (memory_limit_ - full_score_memory_);
                size_t should_score = floor(time_score * memory_score / 100);
                score_ = (score_ > should_score ? score_ : should_score);
            }
        }
    };

    ~SpacialJudger() {};
};

#endif //UNTITLED4_OJ_H
