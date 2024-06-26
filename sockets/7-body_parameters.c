#include "socket2.h"

/**
 * main - the entry point that starts the server to handle incoming requests
 *
 * this program calls the start_server function and ignores the command line
 * arguments
 *
 * @ac: argument count
 * @av: argument values
 *
 * Return: the return value from start_server()
 */

int main(int ac, char **av)
{
	return (start_server());
	(void)ac;
	(void)av;
}



/**
 * parse_request - program that parses an HTTP request from a client,
 * extracts and logs URL paths and parameters
 *
 * this function extracts and logs the path and parameters from an
 * HTTP request, and sends a 200 OK response;
 * it handles URL-encoded data if specified in the content-type of
 * the request header
 *
 * @client_sd: the client socket descriptor
 * @buf: the buffer containing the HTTP request data
 *
 * Return: the integer status code of the operation, 0 on success
 */

int parse_request(int client_sd, char *buf)
{
	char *start_line, *path, *header, *body, *query, *key, *value, *save_ptr1,
		*save_ptr2;
	short url_encoded = 0;

	body = strstr(buf, CRLF CRLF);

	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buf, CRLF, &save_ptr1);

	strtok(start_line, SP);

	path = strtok(NULL, SP);
	path = strtok(path, "?");

	printf("Path: %s\n", path);

	header = strtok_r(NULL, CRLF, &save_ptr1);

	while (header)
	{
		key = trim(strtok_r(header, ":", &save_ptr2));
		value = trim(strtok_r(NULL, CRLF, &save_ptr2));

		if (!strcasecmp(key, CONTENT_TYPE))
		{
			if (!strcasecmp(value, URL_ENCODED))
				url_encoded = 1;
		}
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}
	if (url_encoded)
	{
		query = strtok_r(body, "&", &save_ptr1);
		while (query)
		{
			key = strtok_r(query, "=", &save_ptr2);
			value = strtok_r(NULL, "=", &save_ptr2);
			printf("Body param: \"%s\" -> \"%s\"\n", key, value);
			query = strtok_r(NULL, "&", &save_ptr1);
		}
	}
	send_response(client_sd, RESPONSE_200);

	return (0);
}