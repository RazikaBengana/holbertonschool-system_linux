#include "signals.h"

/**
 * current_handler_sigaction - program that retrieves the current handler
 * of the SIGINT signal using sigaction
 *
 * this function retrieves the current handler of the SIGINT signal
 * using the sigaction function;
 * it returns a pointer to the current handler function for SIGINT
 *
 * Return: a pointer to the current handler function for SIGINT,
 *         or NULL on failure
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
	{
		return (NULL);  /* Failed to retrieve signal handler */
	}

	return (sa.sa_handler);  /* Return the current signal handler */
}
