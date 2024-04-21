#include "signals.h"

/**
 * sigset_init3 - program that initializes a signal set
 * with the specified signals
 *
 * @set: a pointer to the signal set to be initialized
 * @signals: the array of signal numbers to be added to the set;
 *           this array must be terminated by 0
 *
 * Return: 0 on success, -1 on error
 */

int sigset_init3(sigset_t *set, int *signals)
{
	int i;

	if (sigemptyset(set) == -1)
		return (-1);

	for (i = 0; signals[i]; i++)
	{
		if (sigaddset(set, signals[i]) != 0)
			return (-1);
	}

	return (0);
}



/**
 * signals_unblock - program that unblocks a set of signals
 * specified by the array
 *
 * @signals: the array of signal numbers to be unblocked;
 *           this array must be terminated by 0
 *
 * Return: 0 on success, -1 on failure
 */

int signals_unblock(int *signals)
{
	sigset_t sigset;

	if (sigset_init3(&sigset, signals) != 0)
		return (-1);

	return (sigprocmask(SIG_UNBLOCK, &sigset, NULL));
}