#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
// WARNING: NO more headers allowed!

using std::pair;
using std::string;
using std::vector;
using std::map;
using std::function;
namespace final {
    class arguments {
    private:
        // WARNING: You cannot add more member variables.
        int _argc;
        char **_argv;
    public:
        arguments() : _argc(0), _argv(nullptr) {}

        arguments(const string &cmd) {
            // to do implement constructor
            _argv = new char *[1000000];
            _argc = 0;
            char token[1000000];
            int counter=0;
            for (int i = 0; i <= cmd.length(); ++i) {
                if (cmd[i] == ' '||cmd[i] == '\0') {
                    token[counter]='\0';
                    //*_argv[_argc] = *token;
                    int trans=0;
                    _argv[_argc]=new char[1000000];
                    while(token[trans]!='\0'){
                        _argv[_argc][trans]=token[trans];
                        trans++;
                    }
                    _argv[_argc][trans]=token[trans];
                    _argc++;
                    counter=0;
                } else {
                    token[counter]=cmd[i];
                    counter++;
                }
            }

        }

        ~arguments() {
            // to do implement destructor
            for(int i=0;i<_argc;++i)
                delete []_argv[i];
            delete[]_argv;
        }

        // WARNING: You cannot modify the following functions
        int argc() const { return _argc; }

        char **argv() const { return _argv; }
    };

    // You don't need to modify shell.
    class shell {
    private:
        map<int, arguments> running_list;
    public:
        shell() = default;

        void run(int pid, const string &cmd, const function<void(int, char **)> &invoked) {
            running_list.emplace(pid, cmd);
            invoked(running_list[pid].argc(), running_list[pid].argv());
        }

        int subprocessExit(int pid, int return_value) {
            running_list.erase(pid);
            return return_value;
        }

        vector<int> getRunningList() const {
            vector<int> rt;
            for (auto &pair:running_list)rt.push_back(pair.first);
            return rt;
        }
    };
}