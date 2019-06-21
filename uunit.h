// uunit.h 1.0: micro unit testing library in C99 distributed under
// the zlib license. http://github.com/superzazu/uunit
//
// example:
// ```c
//     #include <stdio.h>
//
//     #define UUNIT_COLORS 1 // to enable colored output
//     // #define UUNIT_FAILFAST 1 // to stop on first fail
//     #include "uunit.h"
//
//     add_test(test_one) {
//         assert_true(3 == 3);
//     }
//
//     add_test(test_two) {
//         assert_eq(10, 16);
//     }
//
//     add_test(test_three) {
//         assert_gt(42, 1);
//     }
//
//     int main(void) {
//         run_test(test_one);
//         run_test(test_two);
//         run_test(test_three);
//
//         print_report();
//
//         return uunit_nb_tests_failed != 0;
//     }
// ```

#ifndef UUNIT_H
#define UUNIT_H

#include <stdio.h>
#include <math.h>

// if UUNIT_COLORS is set to 1, the output will be colored (UNIX only)
#ifndef UUNIT_COLORS
#define UUNIT_COLORS 0
#endif

#if UUNIT_COLORS == 1
#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CBLU "\x1b[34m"
#define CRST "\x1B[0m"
#else
#define CRED ""
#define CGRN ""
#define CBLU ""
#define CRST ""
#endif

// if UUNIT_FAILFAST is set to 1, the test run is stopped on first fail
#ifndef UUNIT_FAILFAST
#define UUNIT_FAILFAST 0
#endif

static int uunit_nb_tests = 0;
static int uunit_nb_tests_failed = 0;
static int uunit_nb_tests_skipped = 0;
static _Bool _uunit_has_failed = 0;

static void (*uunit_setup_func)(void) = NULL;
static void (*uunit_teardown_func)(void) = NULL;

#define add_test(name) static void name(void)

#define run_test(func) do { \
    if (UUNIT_FAILFAST && uunit_nb_tests_failed > 0) { \
        uunit_nb_tests_skipped += 1; break; \
    } \
    _uunit_has_failed = 0; \
    if (uunit_setup_func != NULL) uunit_setup_func(); \
    func(); \
    if (uunit_teardown_func != NULL) uunit_teardown_func(); \
    printf("%s %s\n", \
        _uunit_has_failed == 0 ? CGRN "[PASS]" : CRED "[FAIL]", \
        CRST #func); \
    uunit_nb_tests += 1; uunit_nb_tests_failed += _uunit_has_failed; \
    } while(0)

#define print_report() do { \
    printf("\nREPORT: executed %d tests, %d failed (%d skipped)%s.\n", \
        uunit_nb_tests, uunit_nb_tests_failed, \
        uunit_nb_tests_skipped, \
        UUNIT_FAILFAST ? " (failfast)" : ""); \
    } while(0)

#define assert_true(x) do { if (!(x)) { \
    printf(CBLU "%s:%d:%s: " CRED "error: " CBLU "assertion failed: %s \n" \
        CRST, __FILE__, __LINE__, __func__, #x); \
    _uunit_has_failed = 1; \
    } } while (0)

// shortcut functions:
#define assert_false(x) assert_true(!(x))
#define assert_eq(a, b) assert_true((a) == (b))
#define assert_ne(a, b) assert_true((a) != (b))
#define assert_lt(a, b) assert_true((a) < (b))
#define assert_le(a, b) assert_true((a) <= (b))
#define assert_gt(a, b) assert_true((a) > (b))
#define assert_ge(a, b) assert_true((a) >= (b))
#define assert_streq(a, b) assert_true(strcmp(a, b) == 0)
#define assert_strin(str, target) assert_true(strstr(str, target) != NULL)
#define assert_deq(a, b, diff) assert_true(fabs((a) - (b)) <= (diff))
#define assert_feq(a, b, diff) assert_true(fabsf((a) - (b)) <= (diff))

#endif // UUNIT_H
