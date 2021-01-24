#include "cmpstr.h"
#include <string.h>

#define STRCMP(needle, haystack) (strncmp(needle, haystack, strlen(needle)))
const char *headers[] = {
//"Authorization",
        "Accept",
//"Accept-Encoding",
//"Accept-Language",
        "Cookie",
        "Date",
//"If-None-Match",
//"If-Modified-Since",
//"Content-Type",
//"Content-Length",
//"Referer",
//"User-Agent",
        NULL
};

int main() {
    unsigned int f = 0;
    char **headers_p = (char **) headers;
    char **headers_vals = (char **) calloc(sizeof(char *), 11);
    int i = 0;
    char *line;
    while (line = *headers_p) {
        int bit = 1;
        if (!(f & bit) && STRCMP("Authorization", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Accept", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Accept-Encoding", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Accept-Language", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Cookie", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Date", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("If-None-Match", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("If-Modified-Since", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Content-Type", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Content-Length", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("Referer", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        if (!(f & bit) && STRCMP("User-Agent", line) == 0) {
            f |= bit;
            headers_vals[i] = line;
        }
        bit <<= 1;
        printf("%s %d %d\n", line, bit, f);
        headers_p++;
        i++;
    }
    free(headers_vals);
    return 0;
}
