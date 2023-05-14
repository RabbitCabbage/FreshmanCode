#include <iostream>

template<typename T>
void debugPrint(const T &head);


template<typename T, typename...Ts>
void debugPrint(T head, Ts...rest);
void debugPrint();
int main() {
    std::string str("test message");
    debugPrint("Hello, Happy World!", 19260817, false, str);
    debugPrint("debug");
    return 0;
}

void debugPrint() {
    std::cout <<std::endl;
}

template<typename T, typename...Ts>
void debugPrint(const T &head, const Ts &...rest) {
    std::cout << head << " ";
    debugPrint(rest...);
    std::cout<<std::endl;
}
template<typename T>
void debugPrint(const T &head){
    std::cout<<head<<std::endl;
}