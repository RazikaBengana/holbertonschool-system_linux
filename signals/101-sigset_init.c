#include "signals.h"

/**
 * sigset_init - program that initializes a signal set with the specified signals
 *
 * @set: a pointer to the signal set to be initialized
 * @signals: the null-terminated array of signal numbers to be added to the set
 *
 * Return: 0 on success, or -1 on failure if any signal cannot be added
 */

int sigset_init(sigset_t *set, int *signals)
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