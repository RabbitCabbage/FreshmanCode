//助教好，我查阅了CSDN有关大整数类的介绍和代码实现，但是我的代码都是我自己写的
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <complex>


// 请不要使用 using namespace std;

namespace sjtu {
    class int2048 {
        // 输出两个大整数之和
        friend int2048 add(int2048 one, const int2048 &another);

        // 输出两个大整数之差
        friend int2048 minus(int2048 one, const int2048 &substract);

        friend int2048 operator+(int2048 one, const int2048 &another);

        friend int2048 operator/(const int2048 &dividend_initial, const int2048 &divisor_initial);

        friend std::istream &operator>>(std::istream &in, int2048 &num);

        friend std::ostream &operator<<(std::ostream &out, const int2048 &num);

        friend int2048 operator-(int2048 one, const int2048 &substract);

        friend int2048 operator*(int2048 one, const int2048 &another);

        inline friend bool operator==(const int2048 &one, const int2048 &another);

        inline friend bool operator!=(const int2048 &one, const int2048 &another);

        inline friend bool operator<(const int2048 &one, const int2048 &another);

        inline friend bool operator>(const int2048 &one, const int2048 &another);

        inline friend bool operator<=(const int2048 &one, const int2048 &another);

        inline friend bool operator>=(const int2048 &one, const int2048 &another);

    public:
        std::vector<long long> bigint;
        bool sign;

        // 构造函数
        int2048();

        int2048(long long x);

        int2048(const std::string &s);

        int2048(const int2048 &initial);

        // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
        // 如果需要，可以自行增加其他所需的函数
        // =================================== Integer1 ===================================

        // 读入一个大整数
        void read(const std::string &s);

        // 输出储存的大整数
        void print();

        // 加上一个大整数
        int2048 &add(const int2048 &another);

        // 减去一个大整数
        int2048 &minus(const int2048 &substract);

        // =================================== Integer2 ===================================

        int2048 &operator=(const int2048 &another);

        int2048 &operator+=(int2048 another);

        int2048 &operator-=(int2048 substract);


        int2048 &operator*=(const int2048 &);


        int2048 &operator/=(const int2048 &another);

    };


    void remove_zero(int2048 &a);

    int comp_abs(const int2048 &a, const int2048 &b);

    int2048 minus(int2048 one, const int2048 &substract);

    int2048 add(int2048 one, const int2048 &another);

    int2048 operator+(int2048 one, const int2048 &another);

    int2048 operator/(const int2048 &dividend_initial, const int2048 &divisor_initial);

    std::istream &operator>>(std::istream &in, int2048 &num);

    std::ostream &operator<<(std::ostream &out, const int2048 &num);

    int2048 operator-(int2048 one, const int2048 &substract);

    int2048 operator*(int2048 one, const int2048 &another);

    inline bool operator==(const int2048 &one, const int2048 &another);

    inline bool operator!=(const int2048 &one, const int2048 &another);

    inline bool operator<(const int2048 &one, const int2048 &another);

    inline bool operator>(const int2048 &one, const int2048 &another);

    inline bool operator<=(const int2048 &one, const int2048 &another);

    inline bool operator>=(const int2048 &one, const int2048 &another);

}

#endif

void sjtu::remove_zero(sjtu::int2048 &a) {
    int t = a.bigint.size() - 1;
    while (1) {
        if (a.bigint.empty())break;
        if (a.bigint[t] == 0)t--;
        else break;
    }
    a.bigint.resize(t + 1);
    if (a.bigint.empty())a.bigint.push_back(0);
}

int sjtu::comp_abs(const sjtu::int2048 &a, const sjtu::int2048 &b) {//比较绝对值，不看符号的
    if (a.bigint.size() < b.bigint.size())return -1;
    else if (a.bigint.size() > b.bigint.size())return 1;
    else {
        unsigned long len = a.bigint.size();
        int i;
        for (i = len - 1; i >= 0 && a.bigint[i] == b.bigint[i]; --i);//break:1,i<0;2,find difference;
        if (i < 0) return 0;
        else if (a.bigint[i] > b.bigint[i])return 1;
        else return -1;
    }
}

sjtu::int2048 sjtu::add(sjtu::int2048 one, const sjtu::int2048 &another) {
    if (one.sign && !another.sign) {
        sjtu::int2048 another_cp = another;
        another_cp.sign = true;
        one = sjtu::minus(one, another_cp);
    } else if (!one.sign && another.sign) {
        sjtu::int2048 another_cp = another;
        another_cp.sign = false;
        one = sjtu::minus(one, another_cp);
    } else {
        unsigned long len_of_another = another.bigint.size();

        while (one.bigint.size() < len_of_another) { one.bigint.push_back(0); }
        for (int i = 0; i < len_of_another; ++i) {
            one.bigint[i] = one.bigint[i] + another.bigint[i];
            if (one.bigint[i] / 1000000000) {
                if (i == one.bigint.size() - 1) {
                    one.bigint.push_back((one.bigint[i] / 1000000000));
                    one.bigint[i] = one.bigint[i] % 1000000000;
                } else {
                    one.bigint[i + 1] += 1;
                    one.bigint[i] = one.bigint[i] % 1000000000;
                }
            }
        }
    }
    return one;
}

sjtu::int2048 sjtu::minus(sjtu::int2048 one, const sjtu::int2048 &substract) {
    if (one.sign && !substract.sign) {
        sjtu::int2048 substract_cp = substract;
        substract_cp.sign = true;
        one = sjtu::add(one, substract_cp);
    } else if (!one.sign && substract.sign) {
        sjtu::int2048 substract_cp = substract;
        substract_cp.sign = false;
        one = sjtu::add(one, substract_cp);
    } else {
        //如果说被减数的绝对值更小，就变号了
        if (comp_abs(one, substract) == -1) {
            one.sign = !one.sign;
            while (one.bigint.size() < substract.bigint.size())one.bigint.push_back(0);

            sjtu::int2048 substract_cp = substract;
            for (int i = 0; i < one.bigint.size(); ++i) {
                if (substract_cp.bigint[i] < one.bigint[i]) {
                    substract_cp.bigint[i] += 1000000000;
                    substract_cp.bigint[i + 1]--;
                }
                one.bigint[i] = substract_cp.bigint[i] - one.bigint[i];
            }
        } else {
            sjtu::int2048 substract_cp = substract;
            while (one.bigint.size() > substract_cp.bigint.size())substract_cp.bigint.push_back(0);

            for (int i = 0; i < one.bigint.size(); ++i) {
                if (substract_cp.bigint[i] > one.bigint[i]) {
                    one.bigint[i] += 1000000000;
                    one.bigint[i + 1]--;
                }
                one.bigint[i] = one.bigint[i] - substract_cp.bigint[i];
            }
        }
    }
    remove_zero(one);
    return one;
}

void sjtu::int2048::read(const std::string &s) {
    if (s == "-0") {
        sign = true;
        bigint.push_back(0);
    } else {
        //string->vector;
        unsigned long len = s.length();
        int every_bit = 0;
        if (s[every_bit] == '-')sign = false;
        else sign = true;
        bigint.clear();
        every_bit = len - 1;//找到最后一位
        while (1) {
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0)break;
            int element = 0;
            element += s[every_bit] - '0';
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 10;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 100;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 1000;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 10000;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 100000;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 1000000;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else element += (s[every_bit] - '0') * 10000000;
            --every_bit;
            if (s[every_bit] == '+' || s[every_bit] == '-' || every_bit < 0) {
                bigint.push_back(element);
                break;
            } else {
                element += (s[every_bit] - '0') * 100000000;
                bigint.push_back(element);
            }
            every_bit--;
        }
    }
}

void sjtu::int2048::print() {
    unsigned long len = bigint.size();
    if ((len == 1) && (bigint[0] == 0))std::cout << 0 << std::endl;
    else {
        if (!sign) std::cout << '-';
        for (int i = 0; i < len; ++i) {
            if (bigint[len - 1 - i] == 0 && (len - i - 1) != len - 1)std::cout << "000000000";
            else if (bigint[len - 1 - i] < 10 && (len - i - 1) != len - 1)
                std::cout << "00000000" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 100 && (len - i - 1) != len - 1)
                std::cout << "0000000" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 1000 && (len - i - 1) != len - 1)
                std::cout << "000000" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 10000 && (len - i - 1) != len - 1)
                std::cout << "00000" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 100000 && (len - i - 1) != len - 1)
                std::cout << "0000" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 1000000 && (len - i - 1) != len - 1)
                std::cout << "000" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 10000000 && (len - i - 1) != len - 1)
                std::cout << "00" << bigint[len - 1 - i];
            else if (bigint[len - 1 - i] < 100000000 && (len - i - 1) != len - 1)
                std::cout << "0" << bigint[len - 1 - i];
            else std::cout << bigint[len - 1 - i];
        }
        std::cout << std::endl;
    }
}

sjtu::int2048 &sjtu::int2048::add(const sjtu::int2048 &another) {
    (*this) = sjtu::add((*this), another);
    return (*this);
}

sjtu::int2048 &sjtu::int2048::minus(const sjtu::int2048 &substract) {
    (*this) = sjtu::minus((*this), substract);
    return (*this);
}

sjtu::int2048::int2048() {
    sign = true;
    bigint.push_back(0);
}

sjtu::int2048::int2048(long long int x) {
    std::string s = "\0", tmp = "\0";
    if (x == 0) {
        sign = true;
        bigint.push_back(0);
    } else {//继续对s进行操作
        if (x < 0) {
            sign = false;
            s += '-';
            x = -x;
        } else sign = true;
        while (x) {
            long long int bit = x % 10;
            x /= 10;
            tmp += (char) (bit + '0');
        }
        unsigned long len = tmp.length();
        for (int i = 0; i < len; ++i) {
            s += tmp[len - 1 - i];
        }
        read(s);
    }

}

sjtu::int2048::int2048(const std::string &s) {
    read(s);
}

sjtu::int2048::int2048(const sjtu::int2048 &initial) {
    bigint = initial.bigint;
    sign = initial.sign;
}

sjtu::int2048 sjtu::operator*(sjtu::int2048 one, const sjtu::int2048 &another) {
    sjtu::int2048 product;
    product.bigint.resize(one.bigint.size() + another.bigint.size(), 0);
    for (int i = 0; i < one.bigint.size(); ++i) {
        for (int j = 0; j < another.bigint.size(); j++) {
            product.bigint[i + j] += one.bigint[i] * another.bigint[j];
            product.bigint[i + j + 1] += product.bigint[i + j] / 1000000000;
            product.bigint[i + j] %= 1000000000;
        }
    }
    sjtu::remove_zero(product);
    product.sign = (one.sign == another.sign);
    return product;
}

sjtu::int2048 sjtu::operator/(const sjtu::int2048 &dividend_initial, const sjtu::int2048 &divisor_initial) {
    sjtu::int2048 dividend = dividend_initial;
    sjtu::int2048 divisor = divisor_initial;
    if (divisor.bigint.size() == 1 && divisor.bigint[0] == 0) {
        sjtu::int2048 zero;
        return zero;
    }
    if (dividend.bigint.size() == 1 && dividend.bigint[0] == 0) {
        sjtu::int2048 zero;
        return zero;
    }
    if (comp_abs(dividend, divisor) == -1) {
        sjtu::int2048 zero;
        return zero;
    }
    sjtu::int2048 quotient;
    quotient.bigint.resize(dividend.bigint.size() - divisor.bigint.size() + 1, 0);
    long long dividend_high, quotient_high = (long long) quotient.bigint.size() - 1;
    while (quotient_high >= 0) {
        sjtu::int2048 sector;
        dividend_high = (long long) dividend.bigint.size() - 1;
        while (dividend.bigint[dividend_high] == 0 && dividend_high > 0)dividend_high--;//error:如果恰好除尽，最后剩下0的时候就指针越界了
        if (quotient_high > dividend_high)quotient_high = dividend_high;
        sector.bigint.assign(dividend.bigint.begin() + quotient_high,
                             dividend.bigint.begin() + dividend_high + 1);//assign左闭右开
        while (comp_abs(sector, divisor) == -1) {
            quotient_high--;
            if (quotient_high < 0)break;
            sector.bigint.assign(dividend.bigint.begin() + quotient_high, dividend.bigint.begin() + dividend_high + 1);
        }
        if (quotient_high < 0)break;


        long long left_range=1, right_range=999999999, factor;
        long long guess_dividend = sector.bigint[sector.bigint.size() - 1];
        long long guess_divisor = divisor.bigint[divisor.bigint.size() - 1];
        if (guess_dividend > guess_divisor) {
            left_range = guess_dividend / (guess_divisor + 1);
            right_range = guess_dividend / guess_divisor;
        } else if (guess_dividend < guess_divisor && sector.bigint.size() >= 2) {
            guess_dividend = guess_dividend * 1000000000 + sector.bigint[sector.bigint.size() - 2];
            left_range = guess_dividend / (guess_divisor + 1);
            right_range = guess_dividend / guess_divisor;
        }
        while (left_range < right_range) {
            factor = (left_range + right_range + 1) / 2;
            if (factor * divisor > sector) {//factor is too big,
                right_range = factor - 1;
            } else {
                left_range = factor;
            }
        }
        factor = left_range;
        quotient.bigint[quotient_high] = factor;
        //sector是取出来作为除数的，它减去被除数*试出来的根，要重新塞回除数里
        sector -= (divisor * factor);
        sjtu::remove_zero(dividend);
        long long new_size = dividend.bigint.size() - (dividend_high - quotient_high + 1) + sector.bigint.size();

        dividend.bigint.resize(new_size);
        long long return_num = quotient_high;

        for (int i = 0; i < sector.bigint.size(); ++i) {
            dividend.bigint[return_num] = sector.bigint[i];
            return_num++;
        }

        quotient_high--;
    }
    sjtu::remove_zero(quotient);
    return quotient;
}


bool sjtu::operator==(const sjtu::int2048 &one, const sjtu::int2048 &another) {
    if (one.bigint == another.bigint && one.sign == another.sign)return true;
    else return false;
}

sjtu::int2048 &sjtu::int2048::operator=(const sjtu::int2048 &another) {
    if (this == &another)return *this;
    else {
        (*this).bigint = another.bigint;
        (*this).sign = another.sign;
        return *this;
    }

}

sjtu::int2048 &sjtu::int2048::operator+=(sjtu::int2048 another) {
    (*this) = sjtu::add(*this, another);
    return *this;
}

sjtu::int2048 sjtu::operator+(sjtu::int2048 one, const sjtu::int2048 &another) {
    sjtu::int2048 sum = sjtu::add(one, another);
    return sum;
}

sjtu::int2048 &sjtu::int2048::operator-=(sjtu::int2048 substract) {
    (*this) = sjtu::minus((*this), substract);
    return *this;
}

sjtu::int2048 sjtu::operator-(sjtu::int2048 one, const sjtu::int2048 &substract) {
    sjtu::int2048 result = sjtu::minus(one, substract);
    return result;
}

sjtu::int2048 &sjtu::int2048::operator*=(const sjtu::int2048 &another) {
    (*this) = (*this) * another;
    return *this;
}

sjtu::int2048 &sjtu::int2048::operator/=(const sjtu::int2048 &another) {
    (*this) = (*this) / another;
    return *this;
}

bool sjtu::operator!=(const sjtu::int2048 &one, const sjtu::int2048 &another) {
    if (one == another) return false;
    else return true;
}

bool sjtu::operator<(const sjtu::int2048 &one, const sjtu::int2048 &another) {
    if (!one.sign && another.sign)return true;
    else if (one.sign && !another.sign)return false;
    else {
        if (one.sign) {//positive
            if (comp_abs(one, another) == -1)return true;
            else return false;
        } else {
            if (comp_abs(one, another) == 1)return true;
            else return false;
        }
    }
}

bool sjtu::operator>(const sjtu::int2048 &one, const sjtu::int2048 &another) {
    if (!one.sign && another.sign)return false;
    else if (one.sign && !another.sign)return true;
    else {
        if (one.sign) {//positive
            if (comp_abs(one, another) == 1)return true;
            else return false;
        } else {
            if (comp_abs(one, another) == -1)return true;
            else return false;
        }
    }
}

bool sjtu::operator<=(const sjtu::int2048 &one, const sjtu::int2048 &another) {
    if (!one.sign && another.sign)return true;
    else if (one.sign && !another.sign)return false;
    else {
        if (one.sign) {//positive
            if (comp_abs(one, another) == 1)return false;
            else return true;
        } else {
            if (comp_abs(one, another) == -1)return false;
            else return true;
        }
    }
}

bool sjtu::operator>=(const sjtu::int2048 &one, const sjtu::int2048 &another) {
    if (!one.sign && another.sign)return false;
    else if (one.sign && !another.sign)return true;
    else {
        if (one.sign) {//positive
            if (comp_abs(one, another) == -1)return false;
            else return true;
        } else {
            if (comp_abs(one, another) == 1)return false;
            else return true;
        }
    }
}

std::istream &sjtu::operator>>(std::istream &in, sjtu::int2048 &num) {
    std::string str;
    in >> str;
    num = str;
    return in;
}

std::ostream &sjtu::operator<<(std::ostream &out, const sjtu::int2048 &num) {
    unsigned long len = num.bigint.size();
    if ((len == 1) && (num.bigint[0] == 0))out << 0;
    else {
        if (!num.sign) out << '-';
        for (int i = 0; i < len; ++i) {
            if (num.bigint[len - 1 - i] == 0 && (len - i - 1) != len - 1)out << "000000000";
            else if (num.bigint[len - 1 - i] < 10 && (len - i - 1) != len - 1)
                out << "00000000" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 100 && (len - i - 1) != len - 1)
                out << "0000000" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 1000 && (len - i - 1) != len - 1)
                out << "000000" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 10000 && (len - i - 1) != len - 1)
                out << "00000" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 100000 && (len - i - 1) != len - 1)
                out << "0000" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 1000000 && (len - i - 1) != len - 1)
                out << "000" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 10000000 && (len - i - 1) != len - 1)
                out << "00" << num.bigint[len - 1 - i];
            else if (num.bigint[len - 1 - i] < 100000000 && (len - i - 1) != len - 1)
                out << "0" << num.bigint[len - 1 - i];
            else out << num.bigint[len - 1 - i];
        }
    }
    return out;
}