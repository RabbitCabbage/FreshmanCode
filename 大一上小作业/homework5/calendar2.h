//
// Created by lu'ren'jia'd's on 2021/11/17.
//

#ifndef UNTITLED6_CALENDAR_H
#define UNTITLED6_CALENDAR_H

#include <string>

#include<iostream>

class Calendar {
    friend bool operator==(const Calendar &one, const Calendar &another);

    friend bool operator!=(const Calendar &one, const Calendar &another);

    friend bool operator<=(const Calendar &one, const Calendar &another);

    friend bool operator>=(const Calendar &one, const Calendar &another);

    friend bool operator<(const Calendar &one, const Calendar &another);

    friend bool operator>(const Calendar &one, const Calendar &another);

    friend Calendar operator+(const Calendar &one, int x);

    friend Calendar operator-(const Calendar &one, int x);

    friend int operator-(const Calendar &one, const Calendar &another);

    friend std::istream &operator>>(std::istream &in, Calendar &obj);

    friend std::ostream &operator<<(std::ostream &out, const Calendar &obj);

private:
    int year;
    int day;
    int month;
public:
    operator std::string() {
        std::string s;
        s += year / 1000 + '0';
        s += (year / 100) % 10 + '0';
        s += (year / 10) % 10 + '0';
        s += year % 10 + '0';
        s += '-';
        s += month / 10 + '0';
        s += month % 10 + '0';
        s += '-';
        s += day / 10 + '0';
        s += day % 10 + '0';
        return s;
    }

    Calendar &operator++();

    Calendar &operator--();

    Calendar operator++(int x);

    Calendar operator--(int x);

    Calendar &operator-=(int x);

    Calendar &operator+=(int x);

    Calendar &operator=(const Calendar &another);

    Calendar();

    Calendar(const std::string &);

    Calendar(int year_, int month_, int day_);

    int getday();

    friend int traverse_to_int(const Calendar &querry);

    friend Calendar traverse_to_calendar(int querry_day);

    friend const Calendar operator ""_C(const char *col, size_t n);
};

Calendar traverse_to_calendar(int querry_day) {
    Calendar result;
    result.year = 1;
    const int four_hundred_years = 146097;
    const int one_hundred_years = 36524;//不含最后一年是闰年的
    const int four_years = 1461;
    result.year += (querry_day / four_hundred_years) * 400;
    querry_day %= four_hundred_years;//不到四百年了
    result.year += (querry_day / one_hundred_years) * 100;
    querry_day %= one_hundred_years;//不到一百年了
    result.year += (querry_day / four_years) * 4;
    querry_day %= four_years;//不到四年了，肯定全是平年
    if (querry_day == 1460) {
        result.year += 3;
        result.day = 30;
        result.month = 12;
    } else if (querry_day == 1461) {
        result.year += 3;
        result.day = 31;
        result.month = 12;
    } else {
        result.year += querry_day / 365;
        querry_day %= 365;
        if (querry_day == 0) {
            result.year--;
            result.month = 12;
            result.day = 31;
        } else if (querry_day <= 31) {
            result.month = 1;
            result.day = querry_day;
        } else if ((result.year % 4 == 0 && result.year % 100 != 0) || result.year % 400 == 0)//这是闰年；29
        {
            if (querry_day <= 60) {
                result.month = 2;
                result.day = querry_day - 31;
            } else if (querry_day <= 91) {
                result.month = 3;
                result.day = querry_day - 60;
            } else if (querry_day <= 121) {
                result.month = 4;
                result.day = querry_day - 91;
            } else if (querry_day <= 152) {
                result.month = 5;
                result.day = querry_day - 121;
            } else if (querry_day <= 182) {
                result.month = 6;
                result.day = querry_day - 152;
            } else if (querry_day <= 213) {
                result.month = 7;
                result.day = querry_day - 182;
            } else if (querry_day <= 244) {
                result.month = 8;
                result.day = querry_day - 213;
            } else if (querry_day <= 274) {
                result.month = 9;
                result.day = querry_day - 244;
            } else if (querry_day <= 305) {
                result.month = 10;
                result.day = querry_day - 274;
            } else if (querry_day <= 335) {
                result.month = 11;
                result.day = querry_day - 305;
            } else {
                result.month = 12;
                result.day = querry_day - 335;
            }
        } else {
            if (querry_day <= 59) {
                result.month = 2;
                result.day = querry_day - 31;
            } else if (querry_day <= 90) {
                result.month = 3;
                result.day = querry_day - 59;
            } else if (querry_day <= 120) {
                result.month = 4;
                result.day = querry_day - 90;
            } else if (querry_day <= 151) {
                result.month = 5;
                result.day = querry_day - 120;
            } else if (querry_day <= 181) {
                result.month = 6;
                result.day = querry_day - 151;
            } else if (querry_day <= 212) {
                result.month = 7;
                result.day = querry_day - 181;
            } else if (querry_day <= 243) {
                result.month = 8;
                result.day = querry_day - 212;
            } else if (querry_day <= 273) {
                result.month = 9;
                result.day = querry_day - 243;
            } else if (querry_day <= 304) {
                result.month = 10;
                result.day = querry_day - 273;
            } else if (querry_day <= 334) {
                result.month = 11;
                result.day = querry_day - 304;
            } else {
                result.month = 12;
                result.day = querry_day - 334;
            }
        }
    }

    return result;
}//todo

int traverse_to_int(const Calendar &querry) {
    int day_number = 0;
    int run = 0;
    for (int i = 1; i < querry.year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) run++;
    }//counter就是闰年的个数
    day_number += (run * 366 + (querry.year - run - 1) * 365);
    for (int i = 1; i < querry.month; ++i) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)day_number += 31;
        else if (i == 2) {
            if ((querry.year % 4 == 0 && querry.year % 100 != 0) || querry.year % 400 == 0)day_number += 29;
            else day_number += 28;
        } else day_number += 30;
    }
    day_number += querry.day;
    return day_number;
}


bool operator==(const Calendar &one, const Calendar &another) {
    if (one.day == another.day && one.month == another.month && one.year == another.year)return true;
    else return false;
}

bool operator!=(const Calendar &one, const Calendar &another) {
    if (one.day == another.day && one.month == another.month && one.year == another.year)return false;
    else return true;
}

bool operator<=(const Calendar &one, const Calendar &another) {
    if (one.year > another.year)return false;
    else if (one.year < another.year)return true;
    else {
        if (one.month > another.month)return false;
        else if (one.month < another.month)return true;
        else {
            if (one.day > another.day)return false;
            else if (one.day <= another.day)return true;
        }
    }
}

bool operator>=(const Calendar &one, const Calendar &another) {
    if (one.year < another.year)return false;
    else if (one.year > another.year)return true;
    else {
        if (one.month < another.month)return false;
        else if (one.month > another.month)return true;
        else {
            if (one.day < another.day)return false;
            else if (one.day >= another.day)return true;
        }
    }
}

bool operator<(const Calendar &one, const Calendar &another) {
    if (one.year < another.year)return true;
    else if (one.year > another.year)return false;
    else {
        if (one.month < another.month)return true;
        else if (one.month > another.month)return false;
        else {
            if (one.day < another.day)return true;
            else return false;
        }
    }
}

bool operator>(const Calendar &one, const Calendar &another) {
    if (one.year > another.year)return true;
    else if (one.year < another.year)return false;
    else {
        if (one.month > another.month)return true;
        else if (one.month < another.month)return false;
        else {
            if (one.day > another.day)return true;
            else return false;
        }
    }
}

Calendar operator+(const Calendar &one, int x) {
    Calendar result = traverse_to_calendar(traverse_to_int(one) + x);
    return result;
}

Calendar operator-(const Calendar &one, int x) {
    Calendar result = traverse_to_calendar(traverse_to_int(one) - x);
    return result;
}

int operator-(const Calendar &one, const Calendar &another) {
    return (traverse_to_int(one) - traverse_to_int(another));
}

std::istream &operator>>(std::istream &in, Calendar &obj) {
    char invalid;
    std::string str;
    in >> str;
    obj = Calendar(str);
    return in;
}

std::ostream &operator<<(std::ostream &out, const Calendar &obj) {
    char invalid = '-';
    std::string comps_year = "\0", comps_month = "\0", comps_day = "\0";
    if (obj.year < 10)comps_year = "000";
    else if (obj.year < 100)comps_year = "00";
    else if (obj.year < 1000)comps_year = "0";
    if (obj.month < 10)comps_month = "0";
    if (obj.day < 10)comps_day = "0";
    out << comps_year << obj.year << invalid << comps_month << obj.month << invalid << comps_day << obj.day;
    return out;
}

Calendar &Calendar::operator++() {
    (*this) = traverse_to_calendar(traverse_to_int(*this) + 1);
    return *this;
}

Calendar &Calendar::operator--() {
    (*this) = traverse_to_calendar(traverse_to_int(*this) - 1);
    return *this;
}

Calendar Calendar::operator++(int x) {
    Calendar before = (*this);
    (*this) = traverse_to_calendar(traverse_to_int(*this) + 1);
    return before;
}

Calendar Calendar::operator--(int x) {
    Calendar before = (*this);
    (*this) = traverse_to_calendar(traverse_to_int(*this) - 1);
    return before;
}

Calendar &Calendar::operator-=(int x) {
    (*this) = traverse_to_calendar(traverse_to_int(*this) - x);
    return *this;
}

Calendar &Calendar::operator+=(int x) {
    (*this) = traverse_to_calendar(traverse_to_int(*this) + x);
    return *this;
}

Calendar &Calendar::operator=(const Calendar &another) {
    year = another.year;
    month = another.month;
    day = another.day;
    return *this;
}

Calendar::Calendar() {
    year = 0;
    day = 0;
    month = 0;
}

Calendar::Calendar(const std::string &s) {
    year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
    month = (s[5] - '0') * 10 + (s[6] - '0');
    day = (s[8] - '0') * 10 + (s[9] - '0');
}

Calendar::Calendar(int year_, int month_, int day_) {
    year = year_;
    month = month_;
    day = day_;
}

int Calendar::getday() {
    int day_ = traverse_to_int(*this);
    return day_ % 7;
}

const Calendar operator "" _C(const char *col, size_t n) {
    int year_ = 0, month_ = 0, day_ = 0;
    for (int i = 0; i < 4; ++i) {
        year_ = year_ * 10 + (*col) - '0';
        ++col;
    }//指向了-
    ++col;
    month_ += (*col - '0') * 10;
    ++col;
    month_ += (*col - '0');
    ++col;
    ++col;
    day_ += (*col - '0') * 10;
    ++col;
    day_ += (*col - '0');
    return Calendar(year_, month_, day_);

}


#endif //UNTITLED6_CALENDAR_H