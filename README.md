<!--
SPDX-FileCopyrightText: NONE
SPDX-License-Identifier: Unlicense
-->

# testc

Very simple C single-header test framework I quickly made for ISO C99. UNLICENSE'd.

### quickstart

Put `testc.h` somewhere in your project's testing folder (its UNLICENSE'd so it shouldn't case any license conflicts) and start writing tests.

```c
#define TESTC_H_IMPLEMENTATION
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
	printf("%s\n", testc_INFO);

	testc_tests instance = testc_get();
	if (testc_init(&instance))
	{
		puts("Failed to initalize testc");
		return 1;
	}

	testc_add_test(&instance, will_work, "will-work");
	testc_add_test(&instance, will_fail, "will-fail");

	return (int)run_tests(&instance);
}

```

And that's about all there is! There is also `testc_free(&instance);` but that is unnecessary in most cases (since the program will end right after the test is finished).
