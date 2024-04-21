#include "signals.h"

/**
 * handle_pending - program that handles any pending signals by setting
 * a new signal handler
 *
 * this function checks for any pending signals and sets a new handler
 * for each of them;
 * it iterates over possible signal numbers (up to 64, considering
 * typical Unix/Linux environments);
 * for each signal that is currently pending, it tries to set
 * the specified handler
 *
 * @handler: the function to handle signals
 *
 * Return: 0 on success, -1 on failure
 */

int handle_pending(void (*handler)(int))
{
	sigset_t set;
	struct sigaction act;
	int i;

	memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigemptyset(&set);
	sigpending(&set);

	for (i = 1; i < 65; i++)
	{
		if (sigismember(&set, i))
		{
			if (sigaction(i, &act, NULL))
				return (-1);
		}
	}

	return (0);
}