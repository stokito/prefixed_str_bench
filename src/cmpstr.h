#ifndef MICROBENCHMARK_CMSTR_H
#define MICROBENCHMARK_CMSTR_H

#include <string>
#include <cstring>

char Curl_raw_toupper(char in);
char raw_tolower(char in);
int Curl_strncasecompare(const char *first, const char *second, size_t max);
int Curl_strncasecompare_lower(const char *first, const char *second, size_t max);
const char *Curl_prefixed_str(const char *prefix, const char *str, size_t max);
const char *Curl_prefixed_str_lower(const char *prefix, const char *str, size_t max);
const char *Curl_prefixed_str_fast(const char *prefix, const char *str, size_t max);
const char *Curl_prefixed_str_fast_lower(const char *prefix, const char *str, size_t max);



#endif //MICROBENCHMARK_CMSTR_H
