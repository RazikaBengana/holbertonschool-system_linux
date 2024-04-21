#include "signals.h"

/**
 * sigset_init2 - program that initializes a signal set
 * with the specified signals
 *
 * @set: a pointer to the signal set to be initialized
 * @signals: the array of signals to add to the set;
 *           the array must be terminated with a zero
 *
 * Return: 0 on success,
 *         -1 on failure (if any signal cannot be added)
 */

int sigset_init2(sigset_t *set, int *signals)
{
	int i;

	if (sigemptyset(set) == -1)  /* Clear all signals from the set */
		return (-1);

	for (i = 0; signals[i]; i++) /* Add specified signals to the set */
	{
		if (sigaddset(set, signals[i]) != 0)
			return (-1);
	}

	return (0);
}



/**
 * signals_block - program that blocks a list of signals specified in the array
 *
 * @signals: the array of signals to block, must end with a zero
 *
 * Return: 0 on success, -1 on failure (if signals cannot be blocked)
 */

int signals_block(int *signals)
{
	sigset_t sigset;

	/* Initialize signal set with specified signals */
	if (sigset_init2(&sigset, signals) != 0)
		return (-1);

	/* Apply blocking mask to the process */
	return (sigprocmask(SIG_BLOCK, &sigset, NULL));
}
