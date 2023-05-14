#pragma once //include guard

#undef strcmp
#undef strcpy

int strcmp(const char *s1, const char *s2);

char *strcpy(char *__restrict dest, const char *__restrict src);


int strcmp(const char *s1, const char *s2) {
    int mark = 0;
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 > *s2) {
            mark = 1;
            break;
        } else if (*s1 < *s2) {
            mark = 2;
            break;
        } else {
            ++s1;
            ++s2;
        }
    }
    if (mark == 1 || (*s2 == '\0' && *s1 != '\0'))return 1;
    else if (mark == 2 || (*s1 == '\0' && *s2 != '\0'))return -1;
    else return 0;
}

char *strcpy(char *__restrict dest, const char *__restrict src) {
    char *__restrict src_cp = const_cast<char *>(src);
    char *__restrict src_cp2 = const_cast<char *>(src);
    long long l_src = 0;
    for (; *src_cp != '\0'; ++src_cp)++l_src;
    if (abs(dest-src)<=l_src)return dest;
    else {
        char *strdest = dest;
        for (; *src_cp2 != '\0'; ++src_cp2){
            (*strdest)=(*src_cp2);
            strdest++;
        }
        *strdest='\0';
        return dest;
    }

}