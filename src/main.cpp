#include <benchmark/benchmark.h>
#include <string>
#include <cstring>
#include "cmpstr.h"

static const char *const HAYSTACK = "Content-Disposition: attachment; filename=\"filename.jpg\"";
//static const char *const HAYSTACK = "Content-disposition: attachment; filename=\"filename.jpg\"";
//static const char *const HAYSTACK = "Content-Type: text/html; charset=utf-8";
static const int LEN = strlen("Content-Disposition"); //19;

static void B_cmp(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(Curl_strncasecompare("Content-Disposition", HAYSTACK, LEN));
    }
}

static void B_cmp_lower(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(Curl_strncasecompare_lower("Content-Disposition", HAYSTACK, LEN));
    }
}

static void B_cmp_prefix(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(Curl_prefixed_str("Content-Disposition", HAYSTACK, LEN));
    }
}

static void B_cmp_prefix_lower(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(Curl_prefixed_str_lower("Content-Disposition", HAYSTACK, LEN));
    }
}

static void B_cmp_prefix_fast(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(Curl_prefixed_str_fast("Content-Disposition", HAYSTACK, LEN));
    }
}

static void B_cmp_prefix_fast_lower(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(Curl_prefixed_str_fast_lower("content-disposition", HAYSTACK, LEN));
    }
}

BENCHMARK(B_cmp)->Iterations(40000000);;
BENCHMARK(B_cmp_lower)->Iterations(40000000);;
BENCHMARK(B_cmp_prefix)->Iterations(40000000);;
BENCHMARK(B_cmp_prefix_lower)->Iterations(40000000);;
BENCHMARK(B_cmp_prefix_fast)->Iterations(40000000);;
BENCHMARK(B_cmp_prefix_fast_lower)->Iterations(40000000);;

BENCHMARK_MAIN();