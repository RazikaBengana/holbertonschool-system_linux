#include "_getline.h"


#define READ_SIZE 1024


/**
 * _getline - program that reads a line from a file descriptor and returns
 * it as a string
 *
 * @fd: the file descriptor from which to read
 *
 * the function allocates memory for the string, which must be freed by the
 * caller;
 * it reads one character at a time from the file descriptor, and dynamically
 * reallocates the buffer to hold the string;
 * the string will not include the trailing newline character;
 *
 * Return: a pointer to the string read, or NULL if an error occurs
 *         or end-of-file is reached
 */

char *_getline(const int fd)
{
	size_t buffer_len = 0, buffer_size = READ_SIZE;
	ssize_t bytes_read = 0;
	char *buffer = malloc(buffer_size), *new_buffer, c;

	if (!buffer)
	{
		return (NULL);
	}

	while ((bytes_read = read(fd, &c, 1)) > 0)
	{
		if (buffer_len >= buffer_size)
		{
			buffer_size *= 2;
			new_buffer = realloc(buffer, buffer_size);

			if (!new_buffer)
			{
				free(buffer);
				return (NULL);
			}
			buffer = new_buffer;
		}
		buffer[buffer_len] = c;
		buffer_len++;

		if (c == '\n')
		{
			buffer[buffer_len - 1] = '\0';
			break;
		}
	}

	if (bytes_read <= 0 && buffer_len == 0)
	{
		free(buffer);
		return (NULL);
	}

	buffer[buffer_len] = '\0';

	return (buffer);
}
