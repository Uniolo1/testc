// SPDX-FileCopyrightText: NONE
// SPDX-License-Identifier: Unlicense

/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software,
 * either in source code form or as a compiled binary, for any purpose, commercial or
 * non-commercial, and by any means.

 * In jurisdictions that recognize copyright laws, the author or authors of this software
 * dedicate any and all copyright interest in the software to the public domain. We make this
 * dedication for the benefit of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of relinquishment in perpetuity of
 * all present and future rights to this software under copyright law.

 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef LIBTESTC_H
#define LIBTESTC_H

extern const char *libtest_INFO;
extern const unsigned libtest_VERSION[3];

struct libtests_test;
typedef struct libtest_tests libtest_tests;

// initalization
libtest_tests libtest_init(void);
void libtest_free(libtest_tests *instance);

// add tests
int libtest_add_test(libtest_tests *instance, int (*function)(void),
                     const char *restrict name);

unsigned long run_tests(libtest_tests *instance);

#ifdef LIBTESTC_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct libtest_tests
{
	bool initalized;

	size_t count;
	size_t cap;

	int (**functions)(void);
	const char **names;
};

const char *libtest_INFO = "libtestc v0.0.0 <https://github.com/uniolo1/libtestc>";
const unsigned libtest_VERSION[3] = {0, 0, 0};

libtest_tests libtest_init(void)
{
	libtest_tests ret = {
	    .functions = NULL, .names = NULL, .count = 0, .initalized = false, .cap = 10};

	ret.functions = calloc(ret.cap, sizeof(*ret.functions));
	ret.names = calloc(ret.cap, sizeof(*ret.names));

	return ret;
}

void libtest_free(libtest_tests *instance)
{
	free(instance->functions);
	free(instance->names);

	instance->initalized = false;
}

int libtest_add_test(libtest_tests *instance, int (*function)(void), const char *restrict name)
{
	if (instance->count == instance->cap)
	{
		size_t new_cap = instance->cap + 3;

		void *temp_ptr =
		    realloc(instance->functions, new_cap * sizeof(*instance->functions));

		if (temp_ptr == NULL)
			return 1;

		instance->functions = temp_ptr;

		temp_ptr = realloc(instance->names, new_cap * sizeof(*instance->names));

		if (temp_ptr == NULL)
			return 1;

		instance->names = temp_ptr;
		instance->cap = new_cap;
	}

	instance->functions[instance->count] = function;
	instance->names[instance->count] = name;
	instance->count++;

	return 0;
}

unsigned long run_tests(libtest_tests *instance)
{
	if (instance->count == 0)
	{
		puts("No tests to run!");
		return 0;
	}

	printf("Running %zu tests\n", instance->count);
	unsigned failed = 0;

	for (size_t i = 0; i < instance->count; i++)
	{
		printf("\n--- \"%s\" (%zu) ---\n", instance->names[i], i);

		int result = instance->functions[i]();

		if (result != 0)
		{
			printf("[%d] FAIL: \"%s\" (%zu)\n", result, instance->names[i], i);
			failed++;
		}
		else
			printf("[0] PASS: \"%s\" (%zu)\n", instance->names[i], i);
	}

	printf("\nSummary: %u/%zu tests faled", failed, instance->count);
	return failed;
}

#endif

#endif
