#include "signals.h"

/**
 * main - program that sends a SIGINT signal to a process specified by PID
 *
 * this program takes a single command-line argument representing
 * a process ID (PID);
 * it sends a SIGINT signal to the specified process;
 * if the number of arguments is incorrect, or the signal cannot be sent,
 * the program will return an error and print the correct usage
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	/* Send SIGINT signal to the specified PID */
	if (kill((pid_t)atoi(argv[1]), SIGINT) != 0)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
