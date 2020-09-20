#include "cmpstr.h"
#include <cstdio>

static const char *const HAYSTACK = "Content-disposition: attachment; filename=\"filename.jpg\"";

void printN(const char *value) {
    if (value)
        printf("%s\n", value);
    else
        printf("NULL\n");
}

int main() {
    const char *value;
    int matched = Curl_strncasecompare("Content-Disposition", HAYSTACK, 19);
    printf("%d\n", matched);
    value = Curl_prefixed_str_fast_lower("content-disposition", HAYSTACK, 19);
    printN(value);
    value = Curl_prefixed_str_fast_lower("content-disposition", HAYSTACK, 1);
    printN(value);
    value = Curl_prefixed_str_fast_lower("content-disposition", "Content-dispo", 19);
    printN(value);
    value = Curl_prefixed_str_fast_lower("content-disposition", "Content-Type: text/html; charset=utf-8", 19);
    printN(value);
    value = Curl_prefixed_str_fast_lower("content-disposition", "content-disposition", 19);
    printN(value);
    return 0;
}
