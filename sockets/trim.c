#include "socket2.h"

/**
 * trim - program that trims leading and trailing whitespace from a string
 *
 * this function removes all whitespace characters from the beginning
 * and end of a string, modifying the original string in place;
 * it handles strings that are fully whitespace or have no whitespace
 * gracefully
 *
 * @str: a pointer to the string to be trimmed;
 *       if the string is NULL, the function returns NULL
 *
 * Return: a pointer to the modified string, which has the same address
 *         as the input string 'str'
 */

char *trim(char *str)
{
	ssize_t j = 0;

	if (!str)
		return (NULL);

	while (isspace((unsigned char)*str))
		str++;

	for (j = strlen(str) - 1; j >= 0; j--)
	{
		if (!isspace((unsigned char)str[j]))
			break;
		str[j] = 0;
	}
	return (str);
}