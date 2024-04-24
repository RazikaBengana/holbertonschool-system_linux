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
 * parse_request - program that parses the request from a client,
 * extracting and displaying HTTP headers
 *
 * each header is processed to split the key and value, which are then printed;
 * after parsing headers, sends a standard HTTP 200 response to the client
 *
 * @client_sd: the socket descriptor for the client connection
 * @buf: the buffer containing the request received from the client
 *
 * Return: 0 on successful parsing and response
 */

int parse_request(int client_sd, char *buf)
{
	char *start_line, *header, *key, *value, *save_ptr1, *save_ptr2;

	start_line = strtok_r(buf, CRLF, &save_ptr1);
	header = strtok_r(NULL, CRLF, &save_ptr1);

	while (header)
	{
		key = trim(strtok_r(header, ":", &save_ptr2));
		value = trim(strtok_r(NULL, CRLF, &save_ptr2));
		printf("Header: \"%s\" -> \"%s\"\n", key, value);
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}
	send_response(client_sd, RESPONSE_200);

	return (0);

	(void)start_line;
}
