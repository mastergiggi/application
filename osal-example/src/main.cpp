/*
 * Copyright (c) 2024 Stefan Giggenbach (https://github.com/mastergiggi)
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdlib>
#include <cstdio>

#include <app_version.h>
#include <zephyr/sys/printk.h>
#include <osal/os-thread.hpp>

static void myThreadFunction()
{
	while (true) {
		printf("%s: Hello World!\n", __FUNCTION__);
		OS::Thread::msleep(500);
	}
}

int main()
{
	printf("Zephyr OSAL C++ Example Application %s\n", APP_VERSION_STRING);
	
	static OS::Thread::Config myThreadConfig =
	{
		.name = "Test-Thread",
		.stackSize = 512,
		.prio = 1
	};

	OS::Thread myThread(myThreadFunction, myThreadConfig);

	int count = 0;
	while (count < 5) {
		printf("%s: Hello World!\n", __FUNCTION__);
		++count;
		OS::Thread::sleep(1);
	}

	myThread.abort();
	myThread.join();

	return EXIT_SUCCESS;
}
