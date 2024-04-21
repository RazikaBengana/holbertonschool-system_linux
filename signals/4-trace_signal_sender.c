#include "signals.h"

/**
 * sigquit_handler - signal handler program for SIGQUIT
 *
 * this function is registered as the handler for SIGQUIT signal;
 * it prints the PID of the process that sent the SIGQUIT signal
 *
 * @signum: the signal code
 * @si: a pointer to siginfo_t structure containing additional signal information
 * @ucontext: a pointer to ucontext_t structure containing the execution context
 *
 * Return: nothing (void)
 */

void sigquit_handler(int signum, siginfo_t *si, void *ucontext)
{
	(void)ucontext;

	if (signum == SIGQUIT)
		printf("SIGQUIT sent by %u\n", si->si_pid);
}



/**
 * trace_signal_sender - program that sets up the signal handler for SIGQUIT
 *
 * this function sets up the signal handler for SIGQUIT using sigaction;
 * it registers the 'sigquit_handler' function as the handler for SIGQUIT
 *
 * Return: 0 on success, -1 on failure
 */

int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigquit_handler;

	return (sigaction(SIGQUIT, &sa, NULL));
}
