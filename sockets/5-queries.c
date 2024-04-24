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
 * parse_request - program that parses an HTTP request from a client
 * and constructs a response
 *
 * this function extracts the path and query from the request buffer
 * and logs them;
 * each part of the query is parsed into key-value pairs which are
 * also logged
 *
 * @client_sd: the socket descriptor for the client
 * @buf: the buffer containing the client's HTTP request
 *
 * Return: the integer returned by send_response() indicating the
 *         outcome of the response dispatch
 */

int parse_request(int client_sd, char *buf)
{
	char *DELIMS = " \t\r\n";
	char *path, *query, *save1, *key, *value, *save2;

	strtok(buf, DELIMS);

	path = strtok(NULL, DELIMS);
	path = strtok_r(path, "?", &save1);

	printf("Path: %s\n", path);

	query = strtok_r(NULL, "&", &save1);

	while (query)
	{
		key = strtok_r(query, "=", &save2);
		value = strtok_r(NULL, "=", &save2);
		printf("Query: \"%s\" -> \"%s\"\n", key, value);
		query = strtok_r(NULL, "&", &save1);
	}
	return (send_response(client_sd, RESPONSE_200));
}