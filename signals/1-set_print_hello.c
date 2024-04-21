#include "signals.h"

/**
 * print_hello - program that prints hello
 *
 * @num: the signal number
 *
 * Return: nothing (void)
 */

void print_hello(int num)
{
	(void) num;
	puts("Hello :)");
	fflush(stdout);
}



/**
 * set_print_hello - program that set the handler
 * for SIGINT to 'print_hello'
 *
 * Return: nothing (void)
 */

void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}
