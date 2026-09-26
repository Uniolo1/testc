<!--
SPDX-FileCopyrightText: NONE
SPDX-License-Identifier: Unlicense
-->

# testc

Very simple C single-header test framework I quickly made for ISO C99. UNLICENSE'd.

### quickstart

Put `testc.h` somewhere in your project's testing folder (its UNLICENSE'd so it shouldn't case any license conflicts) and start writing tests.

```c
#define LIBTESTC_IMPLEMENTATION
#include "testc.h"

int will_work(void)
{
	return 0;
}

int will_fail(void)
{
	// non-0 return codes are treated as failures
	return 1;
}

int main(void)
{
	printf("%s\n", libtest_INFO);
	libtest_tests instance = libtest_init();

	libtest_add_test(&instance, will_work, "will-work");
	libtest_add_test(&instance, will_fail, "will-fail");

	return (int)run_tests(&instance);
}

```

And that's about all there is! There is also `libtest_free(&instance);` but that is unnecessary in most cases.
