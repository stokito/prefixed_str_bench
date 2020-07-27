# prefixed_str benchmark
Benchmark for strcasecmp version for prefixed strings.
`strncasecmp()` is a function to compare part of two strings, ignoring case.

It widely used in different forms.
In OpenBSD [strncasecmp](https://pubs.opengroup.org/onlinepubs/009604499/functions/strcasecmp.html):

```
int
strncasecmp(const char *s1, const char *s2, size_t n)
{
        if (n == 0)
                return 0;

        do {
                unsigned char c1 = (unsigned char) *s1++;
                unsigned char c2 = (unsigned char) *s2++;

                if (c1 != c2) {
                        if (c1 >= 'A' && c1 <= 'Z' && 
                            c2 >= 'a' && c2 <= 'z')
                                c1 += 'a' - 'A';
                        else if (c1 >= 'a' && c1 <= 'z' && 
                                 c2 >= 'A' && c2 <= 'Z')
                                c2 += 'a' - 'A';
                        if (c1 != c2)
                                return c1 - c2;
                }
                if (c1 == 0)
                        break;
        } while (--n != 0);

        return 0;
}
```

In glib [g_ascii_strncasecmp](https://developer.gnome.org/glib/stable/glib-String-Utility-Functions.html#g-ascii-strncasecmp)

```c
/**
 * g_ascii_strncasecmp:
 * @s1: string to compare with @s2
 * @s2: string to compare with @s1
 * @n: number of characters to compare
 *
 * Compare @s1 and @s2, ignoring the case of ASCII characters and any
 * characters after the first @n in each string.
 *
 * Unlike the BSD strcasecmp() function, this only recognizes standard
 * ASCII letters and ignores the locale, treating all non-ASCII
 * characters as if they are not letters.
 *
 * The same warning as in g_ascii_strcasecmp() applies: Use this
 * function only on strings known to be in encodings where bytes
 * corresponding to ASCII letters always represent themselves.
 *
 * Returns: 0 if the strings match, a negative value if @s1 < @s2,
 *     or a positive value if @s1 > @s2.
 */
gint
g_ascii_strncasecmp (const gchar *s1,
                     const gchar *s2,
                     gsize        n)
{
  gint c1, c2;

  g_return_val_if_fail (s1 != NULL, 0);
  g_return_val_if_fail (s2 != NULL, 0);

  while (n && *s1 && *s2)
    {
      n -= 1;
      c1 = (gint)(guchar) TOLOWER (*s1);
      c2 = (gint)(guchar) TOLOWER (*s2);
      if (c1 != c2)
        return (c1 - c2);
      s1++; s2++;
    }

  if (n)
    return (((gint) (guchar) *s1) - ((gint) (guchar) *s2));
  else
    return 0;
}
```

Also it is used in curl:

```c
/* Shorter version of the Curl_strncasecompare,
 * used when the first argument is zero-byte terminated
 */
#define checkprefix(a,b)    curl_strnequal(a,b,strlen(a))

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
```

And used to get header value:

```c
if (checkprefix("Content-Disposition:", header)) {
    const char *header_value = header + strlen("Content-Disposition:");
```

Here is the the header starts with `Content-Disposition:` then we start parsing it.
As first step move pointer to header value.

The function is executed in 26.3 ns. See `B_cmp` bench bellow.

But we can significaly improve:
1. Most chars in prefix are in lower case but on comparision we switching them to upper case.
So we can replace this line
```c
        if(Curl_raw_toupper(*first) != Curl_raw_toupper(*second)) {
```
to
```c
        if(raw_tolower(*first) != raw_tolower(*second)) {
```

Now the func executed 19.8 ns i.e. we saved 6 ns. See `B_cmp_lower` bench.

2. We can return a pointer to the value

```c
const char* header_value;
if (header_value = Curl_prefixed_str("Content-Disposition:", header)) {
    printf("%s\n", header_value);
```

3. The max param is always more than 1 so we can use do {} while

```
    do {
        char ch1 = *prefix;
        char ch2 = *str;
        if (raw_tolower(ch1) != raw_tolower(ch2)) {
            return NULL;
        } else {
            max--;
            prefix++;
            str++;
        }
    } while (max);
    return str;
```

Result is 15.3 ns.

4. The prefix can be lower case string so we can not convert it to lower case
```c
const char* header_value;
if (header_value = Curl_prefixed_str("content-disposition:", header)) {
    printf("%s\n", header_value);
```

Result is 13.8 ns. See `B_cmp_prefix_fast_lower` bench.

## Build
You need to install https://github.com/google/benchmark first.

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

## Running

    sudo cpupower frequency-set --governor performance
    ./PrefixedStrBenchmark

Result looks like:
```
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
B_cmp/iterations:40000000                         26.3 ns         26.3 ns     40000000
B_cmp_lower/iterations:40000000                   19.8 ns         19.8 ns     40000000
B_cmp_prefix/iterations:40000000                  25.9 ns         25.9 ns     40000000
B_cmp_prefix_lower/iterations:40000000            19.8 ns         19.8 ns     40000000
B_cmp_prefix_fast/iterations:40000000             15.3 ns         15.3 ns     40000000
B_cmp_prefix_fast_lower/iterations:40000000       13.8 ns         13.8 ns     40000000
```