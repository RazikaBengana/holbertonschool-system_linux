#include "signals.h"

/**
 * sigint_handler3 - custom signal handler program for SIGINT
 *
 * this function is designed to handle the SIGINT signal
 * (typically triggered by Ctrl+C);
 * it prints the signal number, confirms the signal reception,
 * and then gracefully exits the program
 *
 * @signum: the signal number received
 *
 * Return: nothing (void)
 */

void sigint_handler3(int signum)
{
	printf("Caught %d\n", signum);
	printf("Signal received\n");
	fflush(stdout);
	_Exit(EXIT_SUCCESS);
}



/**
 * main - program that sets up a custom handler for the SIGINT signal
 * and then waits indefinitely
 *
 * this function configures 'sigint_handler' as the handler for SIGINT signals;
 * it blocks until a SIGINT signal is received, demonstrating how to handle
 * signals gracefully
 *
 * Return: always 0;
 *         however, the return might not be reached if SIGINT is handled
 */

int main(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler3;  /* Set the handler function for SIGINT */
	sigemptyset(&sa.sa_mask);         /* Initialize the signal mask */
	sa.sa_flags = 0;                  /* No special flags */

	sigaction(SIGINT, &sa, NULL);     /* Apply the signal handling configuration */

	pause(); /* Suspend indefinitely until a signal is received */

	return (0);
}
