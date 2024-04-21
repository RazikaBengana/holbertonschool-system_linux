#include "signals.h"

/**
 * sigint_handler - handler program for the SIGINT signal
 *
 * this function prints "Gotcha! [<signum>]" where <signum>
 * is the signal number
 *
 * @signum: the signal number
 *
 * Return: nothing (void)
 */

void sigint_handler(int signum)
{

	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}



/**
 * handle_signal - program that sets a handler for the SIGINT signal
 *
 * this function registers a signal handler for the SIGINT signal (Ctrl+C);
 * when a SIGINT signal is received, the provided handler function
 * (sigint_handler) will be called
 *
 * Return: 0 on success, or -1 if failed to set the signal handler
 */

int handle_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		return (-1); /* Failed to set the signal handler */
	}

	return (0); /* Signal handler successfully set */
}
