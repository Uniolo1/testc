// SPDX-FileCopyrightText: NONE
// SPDX-License-Identifier: Unlicense

#ifndef LIBTESTC_H
#define LIBTESTC_H

struct libtests_test;
typedef struct libtest_tests libtest_tests;

#ifdef LIBTESTC_IMPLEMENTATION

#include <stdbool.h>
#include <stdlib.h>

struct libtest_tests
{
	bool initalized;

	size_t count;
	size_t cap;
	bool (**functions)(void);
};

libtest_tests libtest_init(void)
{
	libtest_tests ret = {.functions = NULL, .count = 0, .initalized = false, .cap = 10};
	ret.functions = calloc(ret.cap, sizeof(*ret.functions));
	return ret;
}

void libtest_free(libtest_tests *instance)
{
	free(instance->functions);
	instance->initalized = false;
}

int libtest_add_test(libtest_tests *instance, bool (*function)(void))
{
	if (instance->count == instance->cap)
	{
		void *temp_ptr = realloc(instance->functions,
		                         (instance->cap + 3) * sizeof(*instance->functions));

		if (temp_ptr == NULL)
			return 1;

		instance->cap = instance->cap + 3;
		instance->functions = temp_ptr;
	}

	instance->functions[instance->count] = function;
	instance->count++;

	return 0;
}

#endif

#endif
