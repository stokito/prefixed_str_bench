#include "cmpstr.h"
#include <string.h>
#include <assert.h>

#define raw_switch_case(in, alpha, alphaInCase, zed)    (in < alpha || in > zed ? in : (char) (alphaInCase + in - alpha))

/*
#define Curl_raw_toupper(in)   raw_switch_case(in, 'a', 'A', 'z')
#define raw_tolower(in)  raw_switch_case(in, 'A', 'a', 'Z')
*/

char Curl_raw_toupper(char in)
{
    return raw_switch_case(in, 'a', 'A', 'z');
}

char raw_tolower(char in)
{
    return raw_switch_case(in, 'A', 'a', 'Z');
}

int Curl_strncasecompare(const char *first, const char *second, size_t max)
{
    while(*first && *second && max) {
        if(Curl_raw_toupper(*first) != Curl_raw_toupper(*second)) {
            break;
        }
        max--;
        first++;
        second++;
    }
    if(0 == max)
        return 1; /* they are equal this far */

    return Curl_raw_toupper(*first) == Curl_raw_toupper(*second);
}

int Curl_strncasecompare_lower(const char *first, const char *second, size_t max)
{
    while(*first && *second && max) {
        if(raw_tolower(*first) != raw_tolower(*second)) {
            break;
        }
        max--;
        first++;
        second++;
    }
    if(0 == max)
        return 1; /* they are equal this far */

    return raw_tolower(*first) == raw_tolower(*second);
}


const char *Curl_prefixed_str(const char *prefix, const char *str, size_t max)
{
    while(*prefix && *str && max) {
        if(Curl_raw_toupper(*prefix) != Curl_raw_toupper(*str)) {
            break;
        }
        max--;
        prefix++;
        str++;
    }
    if(0 == max)
        return str; /* they are equal this far */

    if(Curl_raw_toupper(*prefix) == Curl_raw_toupper(*str)) {
        return str;
    }
    return NULL;
}

const char *Curl_prefixed_str_lower(const char *prefix, const char *str, size_t max)
{
    while(*prefix && *str && max) {
        if(raw_tolower(*prefix) != raw_tolower(*str)) {
            break;
        }
        max--;
        prefix++;
        str++;
    }
    if(0 == max)
        return str; /* they are equal this far */

    if(raw_tolower(*prefix) == raw_tolower(*str)) {
        return str;
    }
    return NULL;
}

const char *Curl_prefixed_str_fast(const char *prefix, const char *str, size_t max)
{
    assert(max > 0);
    char ch1;
    char ch2;
    do {
        ch1 = *prefix;
        ch2 = *str;
        if (raw_tolower(ch1) != raw_tolower(ch2)) {
            return NULL;
        } else {
            max--;
            prefix++;
            str++;
        }
    } while (max);
    return str;
}

const char *Curl_prefixed_str_fast_lower(const char *prefix, const char *str, size_t max)
{
    assert(max > 0);
    char ch1;
    char ch2;
    do {
        ch1 = *prefix;
        ch2 = *str;
        if (ch1 != raw_tolower(ch2)) {
            return NULL;
        } else {
            max--;
            prefix++;
            str++;
        }
    } while (max);
    return str;
}

