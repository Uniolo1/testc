#define TESTC_H_IMPLEMENTATION
#include "testc.h"

#include <stdio.h>

int will_work(void)
{
	return 0;
}

int will_fail(void)
{
	/* Non-zero return codes are treated as failures. */
	return 1;
}

int main(void)
{
	printf("%s\n", testc_INFO);

	testc_tests *instance = testc_get();

	if (testc_init(instance) != 0)
	{
		puts("Failed to initialize testc");
		return 1;
	}

	if (testc_add_test(instance, will_work, "will-work") != 0)
		return 2;

	if (testc_add_test(instance, will_fail, "will-fail") != 0)
		return 2;

	return run_tests(instance) + 2;
}
