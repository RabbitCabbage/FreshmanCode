#pragma once //include guard

#undef strcspn
#undef strstr


size_t strcspn (const char *s, const char *reject);
const char *strstr (const char *haystack, const char *needle);
//char *strstr (char *haystack, const char *needle);


size_t strcspn (const char *s, const char *reject) {
    //todo

}

const char *strstr (const char *haystack, const char *needle) {
    //todo

}


//char *strstr (char *haystack, const char *needle) {
//	return const_cast<char*>(strstr(const_cast<const char*>(haystack), needle));
//}


