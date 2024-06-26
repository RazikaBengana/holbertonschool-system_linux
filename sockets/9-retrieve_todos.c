#include "socket2.h"


static int ids;
static todo_t *todo_root;


int post_request(int client_sd, char *body, short content_length);
int get_request(int client_sd);


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
 * parse_request - program that parses an HTTP request, extracts
 * and handles different components like method, path, and headers
 *
 * this function parses an HTTP request, determines the type
 * (GET or POST), and routes it to the appropriate handler function
 *
 * @client_sd: the client socket descriptor
 * @buf: the buffer containing the HTTP request
 *
 * Return: 0 if successful, or an HTTP status code if an error occurs
 */

int parse_request(int client_sd, char *buf)
{
	char *start_line, *method, *path, *header, *body, *key, *value,
		*save_ptr1, *save_ptr2;
	short url_encoded = 0, content_length = 0;

	body = strstr(buf, CRLF CRLF);

	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buf, CRLF, &save_ptr1);
	method = strtok(start_line, SP);
	path = strtok(NULL, SP);
	path = strtok(path, "?");

	if (strcasecmp(path, PATH_TODOS) ||
	    (strcasecmp(method, METHOD_POST) && strcasecmp(method, METHOD_GET)))
		return (send_response(client_sd, RESPONSE_404));
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
		else if (!strcasecmp(key, CONTENT_LENGTH))
			content_length = atoi(value);
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}
	if (!strcasecmp(method, METHOD_POST))
	{
		if (!content_length)
			return (send_response(client_sd, RESPONSE_411));
		post_request(client_sd, body, content_length);
	}
	else if (!strcasecmp(method, METHOD_GET))
		get_request(client_sd);

	return (0);

	(void)url_encoded;
}



/**
 * post_request - program that handles POST requests to create
 * a new todo item
 *
 * this function parses the request body, creates a todo item,
 * and sends the appropriate HTTP response
 *
 * @client_sd: the client socket descriptor
 * @body: the request body content
 * @content_length: the length of the request body content
 *
 * Return: the status code indicating success or failure
 */

int post_request(int client_sd, char *body, short content_length)
{
	char *query, *key, *value, *save_ptr1, *save_ptr2,
		*title = NULL, *description = NULL;
	char buf1[1024] = {0}, buf2[1024] = {0};
	todo_t *todo, *node;

	body[content_length] = 0;

	query = strtok_r(body, "&", &save_ptr1);

	while (query)
	{
		key = strtok_r(query, "=", &save_ptr2);
		value = strtok_r(NULL, "=", &save_ptr2);

		printf("Body param: \"%s\" -> \"%s\"\n", key, value);

		if (!strcasecmp(key, KEY_TITLE))
			title = value;
		else if (!strcasecmp(key, KEY_DESCRIPTION))
			description = value;
		query = strtok_r(NULL, "&", &save_ptr1);
	}
	if (!title || !description)
		return (send_response(client_sd, RESPONSE_422));

	todo = calloc(1, sizeof(*todo));

	if (!todo)
		return (1);

	todo->id = ids++;
	todo->title = strdup(title);
	todo->description = strdup(description);

	if (!todo_root)
		todo_root = todo;
	else
	{
		node = todo_root;
		while (node->next)
			node = node->next;
		node->next = todo;
	}
	sprintf(buf2, "{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
	KEY_DESCRIPTION "\":\"%s\"}", ids - 1, title, description);
	sprintf(buf1, RESPONSE_201 CRLF CONTENT_LENGTH ": %lu" CRLF
	CONTENT_TYPE ": " JSON_TYPE CRLF CRLF "%s", strlen(buf2), buf2);

	return (send_response(client_sd, buf1));
}



/**
 * get_request - program that handles GET requests by sending
 * all todo items in JSON format
 *
 * @client_sd: the client socket descriptor
 *
 * Return: the status code indicating success or failure
 */

int get_request(int client_sd)
{
	char buf1[BUF_SIZE + 1] = {0}, buf2[BUF_SIZE + 1] = {0};
	todo_t *todo;

	buf2[0] = '[';

	for (todo = todo_root; todo; todo = todo->next)
		sprintf(buf2 + strlen(buf2),
			"{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
	KEY_DESCRIPTION "\":\"%s\"}%s", todo->id, todo->title,
		todo->description, todo->next ? "," : "");
	*(buf2 + strlen(buf2)) = ']';
	sprintf(buf1, "HTTP/1.1 200 OK" CRLF CONTENT_LENGTH ": %lu" CRLF
	CONTENT_TYPE ": " JSON_TYPE CRLF CRLF "%s", strlen(buf2), buf2);

	return (send_response(client_sd, buf1));
}
