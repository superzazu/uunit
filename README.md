# uunit

micro unit testing library in C99 distributed under the zlib license.

Example:

```c
#include <stdio.h>

#define UUNIT_COLORS 1 // to enable colored output
// #define UUNIT_FAILFAST 1 // to stop on first fail
#include "uunit.h"

add_test(test_one) {
    assert_true(3 == 3);
}

add_test(test_two) {
    assert_eq(10, 16);
}

add_test(test_three) {
    assert_gt(42, 1);
}

int main(void) {
    run_test(test_one);
    run_test(test_two);
    run_test(test_three);

    print_report();

    return uunit_nb_tests_failed != 0;
}
```

Outputs:

```
[PASS] test_one
example.c:12:test_two: error: assertion failed: (10) == (16)
[FAIL] test_two
[PASS] test_three

REPORT: executed 3 tests, 1 failed (0 skipped).
```
