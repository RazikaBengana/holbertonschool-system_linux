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
 * and prints its components
 *
 * this function is intended to extract the method, path, and version
 * from the request;
 * after parsing, it sends a 200 OK response back to the client
 *
 * @client_sd: the client socket descriptor to which the response is sent
 * @buf: the buffer containing the HTTP request received from the client
 *
 * Return: the result of sending the HTTP response to the client
 */

int parse_request(int client_sd, char *buf)
{
	char *DELIMS = " \t\r\n";
	char *method, *path, *version;

	method = strtok(buf, DELIMS);
	path = strtok(NULL, DELIMS);
	version = strtok(NULL, DELIMS);

	printf("Method: %s\nPath: %s\nVersion: %s\n", method, path, version);

	return (send_response(client_sd, RESPONSE_200));
}
