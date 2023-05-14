# ifndef _SJTU_CPP_FINAL_CPU_HPP_
# define _SJTU_CPP_FINAL_CPU_HPP_

# include <vector>
# include "task.hpp"

using namespace std;

typedef unsigned int uint;

namespace sjtu {
    // CPU base class, modifications is not allowed.
    class CPU {
    protected:
        CPUState state;
        vector<Task> tasks;

    public:
        CPU() : tasks() {
            state = idle;
        }

        // Add a new task.
        int addTask(const Task &t) {
            tasks.push_back(t);
            return 1;
        }

        // Change the priority of one process, return 1 if success and return 0 if fail.
        int changePriority(uint task_id, uint priority) {
            for (auto &task: tasks)
                if (task.task_id == task_id) {
                    task.priority = priority;
                    return 1;
                }
            return 0;
        }

        virtual pair<CPUState, uint> run() = 0;

        virtual ~ CPU() = default;
    };

    // FCFS method based CPU.
    class CPU_FCFS : public CPU {
        // TO DO: complete the FCFS method.
        pair<CPUState, uint> run() {
            if (tasks.empty()) {
                pair<CPUState, unsigned int> result = make_pair(idle, 0);
                return result;
            } else {
                auto ptr = tasks.begin();
                for (; ptr != tasks.end(); ++ptr) {
                    if (ptr->time != 0) {
                        break;
                    }
                }
                if (ptr != tasks.end()) {
                    ptr->time--;
                    pair<CPUState, unsigned int> result = make_pair(busy, ptr->task_id);
                    return result;
                } else {
                    pair<CPUState, unsigned int> result = make_pair(idle, 0);
                    return result;
                }
            }
        }
    };

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
        // TO DO: complete the SRTF method.
        pair<CPUState, uint> run() {
            if (tasks.empty()) {
                pair<CPUState, unsigned int> result = make_pair(idle, 0);
                return result;
            } else {
                auto the_task = tasks.begin();
                for (; the_task != tasks.end(); ++the_task) {
                    if (the_task->time != 0)break;
                }
                if (the_task == tasks.end()) {
                    pair<CPUState, unsigned int> result = make_pair(idle, 0);
                    return result;
                }
                auto ptr = the_task;
                for (; ptr != tasks.end(); ptr++) {
                    if (ptr->time != 0 && ptr->time < the_task->time)the_task = ptr;
                    else if (ptr->time == the_task->time) {
                        if (ptr->task_id < the_task->task_id)the_task = ptr;
                    }
                }
                the_task->time--;
                pair<CPUState, unsigned int> result = make_pair(busy, the_task->task_id);
                return result;
            }
        }
    };

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
        // TO DO: complete the priority method.
        pair<CPUState, uint> run() {
            if (tasks.empty()) {
                pair<CPUState, unsigned int> result = make_pair(idle, 0);
                return result;
            } else {
                auto the_task = tasks.begin();
                for (; the_task != tasks.end(); ++the_task) {
                    if (the_task->time != 0)break;
                }
                if (the_task == tasks.end()) {
                    pair<CPUState, unsigned int> result = make_pair(idle, 0);
                    return result;
                }
                auto ptr = the_task;
                for (; ptr != tasks.end(); ptr++) {
                    if (ptr->time != 0 && ptr->priority < the_task->priority)the_task = ptr;
                    else if (ptr->priority == the_task->priority) {
                        if (ptr->task_id < the_task->task_id)the_task = ptr;
                    }
                }
                the_task->time--;
                pair<CPUState, unsigned int> result = make_pair(busy, the_task->task_id);
                return result;
            }
        }
    };
}

# endif