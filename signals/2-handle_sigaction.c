#include "signals.h"

/**
 * sigint_handler2 - handler program for the SIGINT signal
 *
 * this function is called when the SIGINT signal (Ctrl+C) is received;
 * it prints "Gotcha! [signum]" to indicate the signal that was caught
 *
 * @signum: the signal number
 *
 * Return: nothing (void)
 */

void sigint_handler2(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}



/**
 * handle_sigaction - program that sets a handler for the SIGINT signal
 * using sigaction
 *
 * this function sets the handler for the SIGINT signal using
 * the sigaction function;
 * it associates the 'sigint_handler' function with the SIGINT signal
 *
 * Return: 0 on success, -1 on error (failed to set the signal handler)
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler2;  /* Set the handler function */
	sa.sa_flags = 0;

	/* Initialize the signal mask to an empty set */
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		return (-1);  /* Failed to set the signal handler */
	}

	return (0);  /* Signal handler successfully set */
}
