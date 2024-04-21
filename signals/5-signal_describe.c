#include "signals.h"

/**
 * main - program that prints the description of a signal
 *
 * this program takes exactly one command line argument, which is expected to be
 * a signal number (as a string);
 * it prints the description of the specified signal by converting the string
 * to an integer and using 'strsignal' to retrieve the corresponding signal description;
 * if the number of arguments is not exactly two (program name and one argument),
 * it prints the correct usage of the program
 *
 * @argc: the number of command line arguments
 * @argv: the array of command line arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on incorrect usage
 */

int main(int argc, char *argv[])
{
	/* Check if the number of command line arguments is correct */
	if (argc != 2)
	{
		/* Print the correct usage of the program */
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	/* Print the signal description for the given signal number */
	printf("%s: %s\n", argv[1], strsignal(atoi(argv[1])));

	return (EXIT_SUCCESS);
}
