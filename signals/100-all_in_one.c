#include "signals.h"

/**
 * all_signal_handler - universal signal handler program for most signals
 *
 * this function is called whenever a signal that can be handled is caught;
 * it uses the psiginfo() function to log the signal information to stdout
 *
 * @signum: the signal number received
 * @si: a pointer to siginfo_t structure providing context about the signal
 * @ucontext: a pointer to the context in which the signal was received
 *
 * Return: nothing (void)
 */

void all_signal_handler(int signum, siginfo_t *si, void *ucontext)
{
	(void)signum;
	(void)ucontext;

	psiginfo(si, "Caught");
}



/**
 * all_in_one - program that sets up a common signal handler
 * for all signals except SIGKILL and SIGSTOP
 *
 * this function iteratively registers the 'all_signal_handler'
 * for all signals that can be caught and handled, from signal
 * 1 to SIGRTMIN, except for SIGKILL and SIGSTOP which cannot
 * be caught or ignored
 *
 * Return: nothing (void)
 */

void all_in_one(void)
{
	struct sigaction sa;
	int sig;

	sa.sa_flags |= SA_SIGINFO;
	sa.sa_sigaction = all_signal_handler;

	for (sig = 1; sig < SIGRTMIN; sig++)
	{
		if (sig != SIGKILL && sig != SIGSTOP)
			sigaction(sig, &sa, NULL);
	}
}
