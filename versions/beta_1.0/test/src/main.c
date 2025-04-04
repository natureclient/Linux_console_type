#include "../../src/filetype.h"
#include "test.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    assert(run_test(TEST1_FILEPATH, tf1_lines));
    printf("Test 1 Passed\n");

    assert(run_test(TEST2_FILEPATH, tf2_lines));
    printf("Test 2 Passed\n");

    return 0;
}
