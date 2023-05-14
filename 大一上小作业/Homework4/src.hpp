#pragma once //include guard

#undef strcspn
#undef strstr


size_t strcspn(const char *s, const char *reject);

const char *strstr(const char *haystack, const char *needle);
//char *strstr (char *haystack, const char *needle);

long long length(const char *src_cp) {
    long long l_src = 0;
    for (; *src_cp != '\0'; ++src_cp)++l_src;
    return l_src;
}

size_t strcspn(const char *s, const char *reject) {
    //todo

}

const char *strstr(const char *haystack, const char *needle) {
    int *next;

    next = new int[length(needle)];
    next[0] = 0;
    for (int i = 1, j = 0; i < str.length(); i++) {
        while (j > 0 && str.charAt(j) != str.charAt(i)) {
            j = next[j - 1];
        }
        if (str.charAt(i) == str.charAt(j)) {
            j++;
        }
        next[i] = j;
    }
}

delete []next;
}



//char *strstr (char *haystack, const char *needle) {
//	return const_cast<char*>(strstr(const_cast<const char*>(haystack), needle));
//}


